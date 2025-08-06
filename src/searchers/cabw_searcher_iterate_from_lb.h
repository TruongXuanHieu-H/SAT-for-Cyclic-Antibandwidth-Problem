#ifndef CABW_SEARCHER_ITERATE_FROM_LB_H
#define CABW_SEARCHER_ITERATE_FROM_LB_H

#include "cabw_searcher.h"

class CabwSearcherIterateFromLB : public CabwSearcher
{
public:
    CabwSearcherIterateFromLB();
    ~CabwSearcherIterateFromLB() = default;

protected:
    std::deque<int> create_search_order() override;
};

#endif // CABW_SEARCHER_ITERATE_FROM_LB_H