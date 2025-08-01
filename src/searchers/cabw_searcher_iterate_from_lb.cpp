#include "cabw_searcher_iterate_from_lb.h"
#include "../global_data.h"
#include "../utils/pid_manager.h"
#include "../encoders/cabw_instance.h"

#include <iostream>
#include <chrono>
#include <sys/wait.h>
#include <cmath>
#include <sys/prctl.h>

void CabwSearcherIterateFromLB::encode_and_solve()
{
    fflush(stdout);
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time = std::chrono::high_resolution_clock::now();
    create_limit_pid();

    int current_width = start_w;
    int number_width = stop_w - start_w;

    for (int i = 0; i < GlobalData::worker_count && i < number_width; i += step)
    {
        create_cabp_pid(current_width);
        current_width += step;
    }

    bool limit_violated = false;

    // Parent process waits until all child processes finish
    while (!abp_pids.empty())
    {
        int status;
        pid_t finished_pid = wait(&status); // Wait for any child to complete

        if (finished_pid == lim_pid)
        {
            limit_violated = true;
            std::cout << "c [Lim] End with result: " << WEXITSTATUS(status) << "\n";
            while (!abp_pids.empty())
            {
                kill(abp_pids.begin()->second, SIGTERM);
                abp_pids.erase(abp_pids.begin());
            }
        }
        else if (WIFEXITED(status))
        {
            // Remove the finished child from the map
            for (auto it = abp_pids.begin(); it != abp_pids.end(); ++it)
            {
                if (it->second == finished_pid)
                {
                    // std::cout << "c Child pid " << it->first << " - " << it->second << " exited with status " << WEXITSTATUS(status) << "\n";

                    switch (WEXITSTATUS(status))
                    {
                    case 10:
                        if (it->first > max_width_SAT)
                        {
                            max_width_SAT = it->first;
                            std::cout << "c [Main] Max width SAT is set to " << it->first << "\n";
                        }

                        for (auto ita = abp_pids.begin(); ita != abp_pids.end(); ita++)
                        {
                            // Pid with lower width than SAT pid is also SAT.
                            if (ita->first < it->first)
                            {
                                std::cout << "c [Main] Kill lower pid " << ita->first << ".\n";
                                kill(ita->second, SIGTERM);
                            }
                        }
                        break;
                    case 20:
                        if (it->first < min_width_UNSAT)
                        {
                            min_width_UNSAT = it->first;
                            std::cout << "c [Main] Min width UNSAT is set to " << it->first << "\n";
                        }

                        for (auto ita = abp_pids.begin(); ita != abp_pids.end(); ita++)
                        {
                            // Pid with higher width than UNSAT pid is also UNSAT.
                            if (ita->first > it->first)
                            {
                                std::cout << "c [Main] Kill higher pid " << ita->first << ".\n";
                                kill(ita->second, SIGTERM);
                            }
                        }
                        break;
                    default:
                        break;
                    }

                    abp_pids.erase(it);
                    if (abp_pids.empty() && (current_width >= min_width_UNSAT || current_width == stop_w) && kill(lim_pid, 0) == 0)
                    {
                        kill(lim_pid, SIGTERM);
                    }
                    break;
                }
            }
        }
        else if (WIFSIGNALED(status))
        {
            // Remove the terminated child from the map
            for (auto it = abp_pids.begin(); it != abp_pids.end(); ++it)
            {
                if (it->second == finished_pid)
                {
                    std::cout << "c [Main] Child pid " << it->first << " - " << it->second << " terminated by signal " << WTERMSIG(status) << "\n";
                    abp_pids.erase(it);
                    if (abp_pids.empty() && kill(lim_pid, 0) == 0)
                    {
                        kill(lim_pid, SIGTERM);
                    }
                    break;
                }
            }
        }
        else
        {
            for (auto it = abp_pids.begin(); it != abp_pids.end(); ++it)
            {
                if (it->second == finished_pid)
                {
                    std::cerr << "e [Main] Child pid " << it->first << " - " << it->second << " stopped or otherwise terminated.\n";
                    abp_pids.erase(it);
                    if (abp_pids.empty() && kill(lim_pid, 0) == 0)
                    {
                        kill(lim_pid, SIGTERM);
                    }
                    break;
                }
            }
        }

        if (!limit_violated)
        {
            fflush(stdout);
            while (int(abp_pids.size()) < GlobalData::worker_count && current_width < stop_w && current_width < min_width_UNSAT)
            {
                create_cabp_pid(current_width);
                current_width += step;
            }
        }
    }
    std::cout << "c [Main] All children have completed.\n";

    std::chrono::time_point<std::chrono::high_resolution_clock> end_time = std::chrono::high_resolution_clock::now();
    auto encode_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    std::cout << "r [Main] \n";
    std::cout << "r [Main] Final results: \n";
    std::cout << "r [Main] Max width SAT:  \t" << (max_width_SAT == std::numeric_limits<int>::min() ? "-" : std::to_string(max_width_SAT)) << "\n";
    std::cout << "r [Main] Min width UNSAT:\t" << (min_width_UNSAT == std::numeric_limits<int>::max() ? "-" : std::to_string(min_width_UNSAT)) << "\n";
    std::cout << "r [Main] Total real time: " << encode_duration << " ms\n";
    std::cout << "r [Main] Total memory consumed " << *max_consumed_memory << " MB\n";
    std::cout << "r [Main] \n";
}

void CabwSearcherIterateFromLB::create_limit_pid()
{
    lim_pid = fork();
    if (lim_pid < 0)
    {
        std::cerr << "e [Lim] Fork Failed!\n";
        exit(-1);
    }
    else if (lim_pid == 0)
    {
        pid_t main_pid = getppid();
        int limit_state = is_limit_satisfied();

        while (limit_state == 0)
        {
            consumed_memory = std::round(PIDManager::get_total_memory_usage(main_pid) * 10 / 1024.0) / 10;
            consumed_real_time += std::round((float)GlobalData::sample_rate * 10 / 1000000.0) / 10;
            consumed_elapsed_time += (float)(GlobalData::sample_rate * (PIDManager::get_descendant_pids(main_pid).size() - 1)) / 1000000.0;

            if (consumed_memory > *max_consumed_memory)
            {
                *max_consumed_memory = consumed_memory;
                // std::cout << "[Lim] Memory consumed: " << max_consumed_memory << " MB\n";
            }

            sampler_count++;
            if (sampler_count >= GlobalData::report_rate)
            {
                // std::cout << "c [Lim] Sampler:\t" << "Memory: " << consumed_memory << " MB\tReal time: " << consumed_real_time << "s\tElapsed time: " << consumed_elapsed_time << "s\n";
                sampler_count = 0;
            }
            usleep(GlobalData::sample_rate);

            limit_state = is_limit_satisfied();
        }

        exit(limit_state);
    }
    else
    {
        // std::cout << "c Lim pid is forked at " << lim_pid << "\n";
    }
}

void CabwSearcherIterateFromLB::create_cabp_pid(int width)
{
    // std::cout << "p PID: " << getpid() << ", PPID: " << getppid() << "\n";
    pid_t pid = fork();
    // std::cout << "q PID: " << getpid() << ", PPID: " << getppid() << "\n";

    if (pid < 0)
    {
        std::cerr << "e [w = " << width << "] Fork failed!\n";
        exit(-1);
    }
    else if (pid == 0)
    {
        prctl(PR_SET_PDEATHSIG, SIGTERM);
        std::cout << "c [w = " << width << "] Start task in PID: " << getpid() << ".\n";

        // Child process: perform the task
        int result = do_cabp_pid_task(width);

        exit(result);
    }
    else
    {
        // Parent process stores the child's PID
        // std::cout << "c Child pid " << width << " - " << pid << " is tracked in PID: " << getpid() << ".\n";
        abp_pids[width] = pid;
    }
}

int CabwSearcherIterateFromLB::do_cabp_pid_task(int width)
{
    // Dynamically allocate and use ABPEncoder in child process
    CABWInstance *cabp_ins = new CABWInstance(width);

    int result = cabp_ins->encode_and_solve_cabp();

    std::cout << "c [w = " << width << "] Result: " << result << "\n";

    // Clean up dynamically allocated memory
    delete cabp_ins;

    // std::cout << "c [w = " << width << "] Child " << width << " completed task.\n";
    return result;
}
