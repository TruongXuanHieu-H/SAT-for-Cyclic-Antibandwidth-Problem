#include "cabw_searcher.h"
#include "../global_data.h"

#include <iostream>
#include <assert.h>
#include <sys/mman.h>

CabwSearcher::CabwSearcher()
{
    max_consumed_memory = (float *)mmap(nullptr, sizeof(float), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    int lb, ub;
    lookup_bounds(lb, ub);
    start_w = lb;
    stop_w = ub + 1;
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
    }
    else
    {
        ub = GlobalData::g->n / 2 + 1;
        std::cout << "c [Main] No predefined upper bound is found for " << GlobalData::g->graph_name << ".\n";
        std::cout << "c [Main] UB-w = " << ub << " (default value calculated as n/2+1).\n";
    }
};