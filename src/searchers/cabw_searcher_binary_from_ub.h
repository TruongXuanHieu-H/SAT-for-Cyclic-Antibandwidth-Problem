#ifndef CABW_SEARCHER_BINARY_FROM_UB_H
#define CABW_SEARCHER_BINARY_FROM_UB_H

#include "cabw_searcher.h"
#include <deque>

class CabwSearcherBinaryFromUB : public CabwSearcher
{
public:
    CabwSearcherBinaryFromUB();
    ~CabwSearcherBinaryFromUB() = default;

protected:
    std::deque<int> create_search_order() override;
    void binary_partition(int first, int last, std::deque<int> &result);
};
#endif // CABW_SEARCHER_BINARY_FROM_UB_H