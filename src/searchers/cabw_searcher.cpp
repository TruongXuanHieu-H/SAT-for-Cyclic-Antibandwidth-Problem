#include "cabw_searcher.h"
#include "../global_data.h"
#include "../encoders/cabw_instance.h"
#include "../utils/pid_manager.h"

#include <iostream>
#include <assert.h>
#include <sys/mman.h>
#include <cmath>
#include <sys/prctl.h>
#include <sys/wait.h>

CabwSearcher::CabwSearcher()
{
    max_consumed_memory = (float *)mmap(nullptr, sizeof(float), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    setup_bounds(lower_bound, upper_bound);
}

CabwSearcher::~CabwSearcher()
{
    abp_pids.clear();
}

/*
 *  Check if limit conditions are satified or not
 *  Return:
 *      0   if all the conditions is satified.
 *      -1  if out of memory.
 *      -2  if out of real time.
 *      -3  if out of elapsed time.
 */
int CabwSearcher::is_limit_satisfied()
{
    if (consumed_memory > GlobalData::memory_limit)
        return -1;

    if (consumed_real_time > GlobalData::real_time_limit)
        return -2;

    if (consumed_elapsed_time > GlobalData::elapsed_time_limit)
        return -3;

    return 0;
}

void CabwSearcher::setup_bounds(int &w_from, int &w_to)
{
    lookup_bounds(w_from, w_to);

    if (GlobalData::overwrite_lb)
    {
        std::cout << "c [Main] LB " << w_from << " is overwritten with " << GlobalData::forced_lb << ".\n";
        w_from = GlobalData::forced_lb;
    }
    if (GlobalData::overwrite_ub)
    {
        std::cout << "c [Main] UB " << w_to << " is overwritten with " << GlobalData::forced_ub << ".\n";
        w_to = GlobalData::forced_ub;
    }
    if (w_from > w_to)
    {
        int tmp = w_from;
        w_from = w_to;
        w_to = tmp;
        std::cout << "c [Main] Flipped LB and UB to avoid LB > UB: (LB = " << w_from << ", UB = " << w_to << ").\n";
    }

    assert((w_from <= w_to) && (w_from >= 1));
};

void CabwSearcher::lookup_bounds(int &lb, int &ub)
{
    auto pos = GlobalData::cabw_LBs.find(GlobalData::g->graph_name);
    if (pos != GlobalData::cabw_LBs.end())
    {
        lb = pos->second;
        std::cout << "c [Main] Lower bound is set to " << lb << ".\n";
    }
    else
    {
        lb = 2;
        std::cout << "c [Main] No predefined lower bound is found for " << GlobalData::g->graph_name << ".\n";
        std::cout << "c [Main] LB-w = 2 (default value).\n";
    }

    pos = GlobalData::cabw_UBs.find(GlobalData::g->graph_name);
    if (pos != GlobalData::cabw_UBs.end())
    {
        ub = pos->second;
        std::cout << "c [Main] Upper bound is set to " << ub << ".\n";
    }
    else
    {
        ub = GlobalData::g->n / 2 + 1;
        std::cout << "c [Main] No predefined upper bound is found for " << GlobalData::g->graph_name << ".\n";
        std::cout << "c [Main] UB-w = " << ub << " (default value calculated as n/2+1).\n";
    }
};

void CabwSearcher::create_limit_pid()
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

void CabwSearcher::create_cabp_pid(int width)
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

int CabwSearcher::do_cabp_pid_task(int width)
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
