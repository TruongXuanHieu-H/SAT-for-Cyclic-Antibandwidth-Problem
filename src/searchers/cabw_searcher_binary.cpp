#include "cabw_searcher_binary.h"
#include "../global_data.h"

#include <iostream>
#include <chrono>
#include <sys/wait.h>

CabwSearcherBinary::CabwSearcherBinary()
{
    search_order = create_search_order();
    std::cout << "c [Main] Binary search order: ";
    for (const auto &width : search_order)
    {
        std::cout << width << " ";
    }
    std::cout << "\n";
}

std::deque<int> CabwSearcherBinary::create_search_order()
{
    std::deque<int> order_result;
    binary_partition(lower_bound, upper_bound, order_result);
    return order_result;
}

void CabwSearcherBinary::binary_partition(int first, int last, std::deque<int> &result)
{
    if (first > last)
        return;

    int mid = (first + last) / 2;
    result.push_back(mid);

    binary_partition(first, mid - 1, result);
    binary_partition(mid + 1, last, result);
}

int CabwSearcherBinary::get_next_width_to_search()
{
    if (search_order.empty())
        return lower_bound - 1; // To terminate the search if no valid width is left. Value (upper_bound + 1) also works.

    int next_width = search_order.front();
    search_order.pop_front();

    while (next_width <= max_width_SAT || next_width >= min_width_UNSAT)
    {
        if (search_order.empty())
            return lower_bound - 1; // To terminate the search if no valid width is left. Value (upper_bound + 1) also works.

        next_width = search_order.front();
        search_order.pop_front();
    }

    return next_width;
}

void CabwSearcherBinary::encode_and_solve()
{
    fflush(stdout);
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time = std::chrono::high_resolution_clock::now();
    create_limit_pid();

    for (int i = 0; i < GlobalData::worker_count && i < (upper_bound + 1 - lower_bound); i += 1)
    {
        int next_width_to_seach = get_next_width_to_search();
        if (next_width_to_seach <= lower_bound - 1 || next_width_to_seach >= upper_bound + 1)
        {
            break; // No valid width to search
        }
        else
        {
            create_cabp_pid(next_width_to_seach);
        }
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
                    if (abp_pids.empty() && search_order.empty() && kill(lim_pid, 0) == 0)
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
            while (int(abp_pids.size()) < GlobalData::worker_count)
            {
                int next_width_to_seach = get_next_width_to_search();
                if (next_width_to_seach <= lower_bound - 1 || next_width_to_seach >= upper_bound + 1)
                {
                    break; // No valid width to search
                }
                else
                {
                    create_cabp_pid(next_width_to_seach);
                }
            }

            if (abp_pids.empty() && search_order.empty())
            {
                kill(lim_pid, SIGTERM);
            }
        }
    }
    std::cout << "c [Main] All children have completed.\n";

    std::chrono::time_point<std::chrono::high_resolution_clock> end_time = std::chrono::high_resolution_clock::now();
    auto encode_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    std::cout << "r [Main] \n";
    std::cout << "r [Main] Final results: \n";
    std::cout << "r [Main] Max width SAT:  \t" << ((max_width_SAT == lower_bound - 1) ? "-" : std::to_string(max_width_SAT)) << "\n";
    std::cout << "r [Main] Min width UNSAT:\t" << ((min_width_UNSAT == upper_bound + 1) ? "-" : std::to_string(min_width_UNSAT)) << "\n";
    std::cout << "r [Main] Total real time: " << encode_duration << " ms\n";
    std::cout << "r [Main] Total memory consumed: " << *max_consumed_memory << " MB\n";
    std::cout << "r [Main] \n";
}
