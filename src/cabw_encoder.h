#ifndef CABW_ENCODER_H
#define CABW_ENCODER_H

#include "searchers/cabw_searcher.h"

class CyclicAntiBandwidthEncoder
{
public:
    CyclicAntiBandwidthEncoder();
    ~CyclicAntiBandwidthEncoder();

    void encode_and_solve();

private:
    CabwSearcher *cabw_searcher;
};

#endif // CABW_ENCODER_H