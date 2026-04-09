#include "global_data.h"
#include "cabw_encoder.h"
#include "searchers/cabw_searcher_iterate_from_lb.h"
#include "searchers/cabw_searcher_step_from_lb.h"
#include "searchers/cabw_searcher_binary_from_lb.h"
#include "searchers/cabw_searcher_binary_from_ub.h"
#include "searchers/cabw_searcher_binary_bfs.h"

#include <iostream>

CyclicAntiBandwidthEncoder::CyclicAntiBandwidthEncoder() {
};

CyclicAntiBandwidthEncoder::~CyclicAntiBandwidthEncoder()
{
    if (cabw_searcher != nullptr)
    {
        delete cabw_searcher;
        cabw_searcher = nullptr;
    }
};

void CyclicAntiBandwidthEncoder::setup_searcher()
{
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
    case SearchStrategy::binary_search_from_lb:
        std::cout << "c [Main] Search strategy: Binary search from lower bound.\n";
        cabw_searcher = new CabwSearcherBinaryFromLB();
        break;
    case SearchStrategy::binary_search_from_ub:
        std::cout << "c [Main] Search strategy: Binary search from upper bound.\n";
        cabw_searcher = new CabwSearcherBinaryFromUB();
        break;
    case SearchStrategy::binary_search_bfs:
        std::cout << "c [Main] Search strategy: Binary search using BFS.\n";
        cabw_searcher = new CabwSearcherBinaryBFS();
        break;

    default:
        std::cerr << "e [Main] Unrecognized search strategy " << static_cast<int>(GlobalData::search_strategy) << ".\n";
        break;
    }
};

void CyclicAntiBandwidthEncoder::encode_and_solve()
{
    std::cout << "c [Main] Encoding and solving for graph: " << GlobalData::g->graph_name << ".\n";

    setup_searcher();

    cabw_searcher->encode_and_solve();
};

void CyclicAntiBandwidthEncoder::encode_and_print_dimacs()
{
    std::cout << "c [Main] Encoding and printing DIMACS for graph: " << GlobalData::g->graph_name << ".\n";

    setup_searcher();

    cabw_searcher->encode_and_print_dimacs();
};
