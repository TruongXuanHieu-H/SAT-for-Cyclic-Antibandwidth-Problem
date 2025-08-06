#include "global_data.h"
#include "cabw_encoder.h"
#include "searchers/cabw_searcher_iterate_from_lb.h"
#include "searchers/cabw_searcher_step_from_lb.h"
#include "searchers/cabw_searcher_binary_from_lb.h"

#include <iostream>

CyclicAntiBandwidthEncoder::CyclicAntiBandwidthEncoder() {
};

CyclicAntiBandwidthEncoder::~CyclicAntiBandwidthEncoder()
{
    if (cabw_searcher)
    {
        delete cabw_searcher;
        cabw_searcher = nullptr;
    }
};

void CyclicAntiBandwidthEncoder::encode_and_solve()
{
    std::cout << "c [Main] Encoding and solving for graph: " << GlobalData::g->graph_name << std::endl;

    switch (GlobalData::search_strategy)
    {
    case SearchStrategy::iterate_from_lb:
        std::cout << "c [Main] Search strategy: Iterating from lower bound.\n";
        cabw_searcher = new CabwSearcherIterateFromLB();
        break;

    case SearchStrategy::step_from_lb:
        std::cout << "c [Main] Search strategy: Stepping from lower bound.\n";
        cabw_searcher = new CabwSearcherStepFromLB();
        break;
    case SearchStrategy::binary_search:
        std::cout << "c [Main] Search strategy: Binary search.\n";
        cabw_searcher = new CabwSearcherBinaryFromLB();
        break;

    default:
        std::cerr << "e [Main] Unrecognized search strategy " << static_cast<int>(GlobalData::search_strategy) << ".\n";
        break;
    }

    cabw_searcher->encode_and_solve();
};
