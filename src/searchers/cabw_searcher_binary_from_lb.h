#ifndef CABW_SEARCHER_BINARY_FROM_LB_H
#define CABW_SEARCHER_BINARY_FROM_LB_H

#include "cabw_searcher.h"
#include <deque>

class CabwSearcherBinaryFromLB : public CabwSearcher
{
public:
    CabwSearcherBinaryFromLB();
    ~CabwSearcherBinaryFromLB() = default;

protected:
    std::deque<int> create_search_order() override;
    void binary_partition(int first, int last, std::deque<int> &result);
};
#endif // CABW_SEARCHER_BINARY_FROM_LB_H