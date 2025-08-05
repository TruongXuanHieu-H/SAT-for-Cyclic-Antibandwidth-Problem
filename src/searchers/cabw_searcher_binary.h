#ifndef CABW_SEARCHER_BINARY_H
#define CABW_SEARCHER_BINARY_H

#include "cabw_searcher.h"
#include <deque>

class CabwSearcherBinary : public CabwSearcher
{
public:
    CabwSearcherBinary();
    ~CabwSearcherBinary() = default;

    void encode_and_solve() override;

protected:
    std::deque<int> search_order; // Stores the order of widths to search

    int get_next_width_to_search();

    void binary_partition(int first, int last, std::deque<int> &result);
};
#endif // CABW_SEARCHER_BINARY_H