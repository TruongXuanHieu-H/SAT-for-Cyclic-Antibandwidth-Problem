#ifndef CABW_SEARCHER_ITERATE_FROM_LB_H
#define CABW_SEARCHER_ITERATE_FROM_LB_H

#include "cabw_searcher.h"

class CabwSearcherIterateFromLB : public CabwSearcher
{
public:
    CabwSearcherIterateFromLB() = default;
    ~CabwSearcherIterateFromLB() = default;

    void encode_and_solve() override;

protected:
    int step = 1;
};

#endif // CABW_SEARCHER_ITERATE_FROM_LB_H