#ifndef CABW_SEARCHER_BINARY_BFS_H
#define CABW_SEARCHER_BINARY_BFS_H

#include "cabw_searcher.h"
#include <deque>

class CabwSearcherBinaryBFS : public CabwSearcher
{
public:
    CabwSearcherBinaryBFS();
    ~CabwSearcherBinaryBFS() = default;

protected:
    std::deque<int> create_search_order() override;
};
#endif // CABW_SEARCHER_BINARY_BFS_H