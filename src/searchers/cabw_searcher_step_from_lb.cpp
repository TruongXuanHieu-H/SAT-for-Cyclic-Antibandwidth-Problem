#include "cabw_searcher_step_from_lb.h"
#include "../global_data.h"

#include <iostream>
#include <chrono>
#include <assert.h>
#include <sys/wait.h>
#include <sys/prctl.h>

CabwSearcherStepFromLB::CabwSearcherStepFromLB()
{
    assert(upper_bound - lower_bound >= 20);

    for (int i = lower_bound; i < upper_bound; i++)
    {
        in_wait_widths.insert(i);
        width_status[i] = SearchStatus::IN_WAIT;
    }
}

void CabwSearcherStepFromLB::encode_and_solve()
{
    fflush(stdout);
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time = std::chrono::high_resolution_clock::now();
    create_limit_pid();

    for (int i = 0; i < GlobalData::worker_count; i++)
    {
        int next_search_width = get_next_width_to_search();

        assert(next_search_width >= lower_bound && next_search_width <= upper_bound);

        create_cabp_pid(next_search_width);
        in_wait_widths.erase(next_search_width);
        in_search_widths.insert(next_search_width);
        width_status[next_search_width] = SearchStatus::IN_SEARCH;
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
            std::cout << "c [Main] Lim pid ends with result: " << WEXITSTATUS(status) << "\n";
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
                            for (int i = max_width_SAT + 1; i < it->first; i++)
                            {
                                if (width_status[i] == SearchStatus::IN_SEARCH)
                                {
                                    in_search_widths.erase(i);
                                }
                                else if (width_status[i] == SearchStatus::IN_WAIT)
                                {
                                    in_wait_widths.erase(i);
                                }
                                sat_widths.insert(i);
                                width_status[i] = SearchStatus::SAT;
                            }
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
                            for (int i = min_width_UNSAT - 1; i > it->first; i--)
                            {
                                if (width_status[i] == SearchStatus::IN_SEARCH)
                                {
                                    in_search_widths.erase(i);
                                }
                                else if (width_status[i] == SearchStatus::IN_WAIT)
                                {
                                    in_wait_widths.erase(i);
                                }
                                unsat_widths.insert(i);
                                width_status[i] = SearchStatus::UNSAT;
                            }
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
                    if (abp_pids.empty() && (get_next_width_to_search() < lower_bound || get_next_width_to_search() > upper_bound) && kill(lim_pid, 0) == 0)
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
            while (int(abp_pids.size()) < GlobalData::worker_count && get_next_width_to_search() >= lower_bound && get_next_width_to_search() <= upper_bound)
            {
                int next_search_width = get_next_width_to_search();
                create_cabp_pid(next_search_width);
                in_wait_widths.erase(next_search_width);
                in_search_widths.insert(next_search_width);
                width_status[next_search_width] = SearchStatus::IN_SEARCH;
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
    std::cout << "r [Main] Total memory consumed: " << *max_consumed_memory << " MB\n";
    std::cout << "r [Main] \n";
}

int CabwSearcherStepFromLB::get_next_width_to_search()
{
    int highest_width_in_search = get_highest_width_in_search();
    int highest_width_SAT = get_highest_width_SAT();
    int highest_width_in_search_or_SAT = std::max(highest_width_in_search, highest_width_SAT);

    if (highest_width_in_search_or_SAT < lower_bound)
    {
        return lower_bound;
    }

    if (min_width_UNSAT - highest_width_in_search_or_SAT >= 100)
    {
        return highest_width_in_search_or_SAT + step_widths[100];
    }

    if (min_width_UNSAT - highest_width_in_search_or_SAT >= 50)
    {
        return highest_width_in_search_or_SAT + step_widths[50];
    }

    if (min_width_UNSAT - highest_width_in_search_or_SAT >= 25)
    {
        return highest_width_in_search_or_SAT + step_widths[25];
    }

    if (min_width_UNSAT - highest_width_in_search_or_SAT >= 10)
    {
        return highest_width_in_search_or_SAT + step_widths[10];
    }

    if (min_width_UNSAT - highest_width_in_search_or_SAT >= 2)
    {
        return highest_width_in_search_or_SAT + step_widths[2];
    }

    return get_lowest_width_in_wait();
}

int CabwSearcherStepFromLB::get_highest_width_in_search()
{
    int highest_width_in_search = lower_bound - 1;

    for (int width : in_search_widths)
    {
        if (width > highest_width_in_search)
        {
            highest_width_in_search = width;
        }
    }

    return highest_width_in_search;
}

int CabwSearcherStepFromLB::get_highest_width_SAT()
{
    int highest_width_SAT = lower_bound - 1;

    for (int width : sat_widths)
    {
        if (width > highest_width_SAT)
        {
            highest_width_SAT = width;
        }
    }

    return highest_width_SAT;
}

int CabwSearcherStepFromLB::get_lowest_width_in_wait()
{
    int lowest_width_in_wait = upper_bound + 1;

    for (int width : in_wait_widths)
    {
        if (width < lowest_width_in_wait)
        {
            lowest_width_in_wait = width;
        }
    }

    return lowest_width_in_wait;
}