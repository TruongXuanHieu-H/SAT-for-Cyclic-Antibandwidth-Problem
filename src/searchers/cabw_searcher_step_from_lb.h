#ifndef CABW_SEARCHER_STEP_FROM_LB_H
#define CABW_SEARCHER_STEP_FROM_LB_H

#include "cabw_searcher.h"
#include <unordered_map>

class CabwSearcherStepFromLB : public CabwSearcher
{
public:
    CabwSearcherStepFromLB();
    ~CabwSearcherStepFromLB() = default;

protected:
    std::deque<int> create_search_order() override;
    std::unordered_map<int, int> step_widths = {
        {100, 10},
        {50, 5},
        {25, 3},
        {10, 2},
        {1, 1},
    };
};

#endif // CABW_SEARCHER_STEP_FROM_LB_H