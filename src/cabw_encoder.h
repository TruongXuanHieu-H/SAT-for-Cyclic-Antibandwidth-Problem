#ifndef CABW_ENCODER_H
#define CABW_ENCODER_H

#include "searchers/cabw_searcher.h"

class CyclicAntiBandwidthEncoder
{
public:
    CyclicAntiBandwidthEncoder();
    ~CyclicAntiBandwidthEncoder();

    void encode_and_solve();
    void encode_and_print_dimacs();

private:
    CabwSearcher *cabw_searcher = nullptr;

    void setup_searcher();
};

#endif // CABW_ENCODER_H