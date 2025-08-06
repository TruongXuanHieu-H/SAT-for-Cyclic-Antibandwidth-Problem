#ifndef CABW_SEARCHER_BINARY_H
#define CABW_SEARCHER_BINARY_H

#include "cabw_searcher.h"
#include <deque>

class CabwSearcherBinary : public CabwSearcher
{
public:
    CabwSearcherBinary();
    ~CabwSearcherBinary() = default;

protected:
    std::deque<int> create_search_order() override;
    void binary_partition(int first, int last, std::deque<int> &result);
};
#endif // CABW_SEARCHER_BINARY_H