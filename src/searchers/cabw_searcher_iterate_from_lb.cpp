#include "cabw_searcher_iterate_from_lb.h"
#include "../global_data.h"

#include <iostream>

CabwSearcherIterateFromLB::CabwSearcherIterateFromLB()
{
    search_order = create_search_order();
    std::cout << "c [Main] Search order:";
    for (const auto &width : search_order)
    {
        std::cout << " " << width;
    }
    std::cout << ".\n";
}

std::deque<int> CabwSearcherIterateFromLB::create_search_order()
{
    std::deque<int> order_result;
    for (int i = lower_bound; i < upper_bound; i++)
    {
        order_result.push_back(i);
    }
    return order_result;
}