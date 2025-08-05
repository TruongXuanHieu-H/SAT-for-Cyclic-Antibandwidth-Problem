#ifndef CABW_SEARCHER_STEP_FROM_LB_H
#define CABW_SEARCHER_STEP_FROM_LB_H

#include "cabw_searcher.h"
#include <unordered_map>
#include <unordered_set>

enum SearchStatus
{
    IN_WAIT = 0,    // The width is waiting for searching
    IN_SEARCH = 10, // The width is being searched
    SAT = 20,       // The width is found to be SAT
    UNSAT = 30,     // The width is found to be UNSAT
};

class CabwSearcherStepFromLB : public CabwSearcher
{
public:
    CabwSearcherStepFromLB();
    ~CabwSearcherStepFromLB() = default;

    void encode_and_solve() override;

protected:
    std::unordered_map<int, int> step_widths = {
        {100, 10},
        {50, 5},
        {25, 3},
        {10, 2},
        {2, 1},
    };

    std::unordered_map<int, SearchStatus> width_status;
    std::unordered_set<int> in_wait_widths;
    std::unordered_set<int> in_search_widths;
    std::unordered_set<int> sat_widths;
    std::unordered_set<int> unsat_widths;

    int get_next_width_to_search();
    int get_highest_width_in_search();
    int get_highest_width_SAT();
    int get_lowest_width_in_wait();
};

#endif // CABW_SEARCHER_STEP_FROM_LB_H