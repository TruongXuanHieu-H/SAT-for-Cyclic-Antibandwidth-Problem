#include "cabw_searcher_binary_from_ub.h"
#include "../global_data.h"

#include <iostream>

CabwSearcherBinaryFromUB::CabwSearcherBinaryFromUB()
{
    search_order = create_search_order();
    std::cout << "c [Main] Search order:";
    for (const auto &width : search_order)
    {
        std::cout << " " << width;
    }
    std::cout << ".\n";
}

std::deque<int> CabwSearcherBinaryFromUB::create_search_order()
{
    std::deque<int> order_result;
    binary_partition(lower_bound, upper_bound, order_result);
    return order_result;
}

void CabwSearcherBinaryFromUB::binary_partition(int first, int last, std::deque<int> &result)
{
    if (first > last)
        return;

    int mid = (first + last) / 2;
    result.push_back(mid);

    binary_partition(mid + 1, last, result);
    binary_partition(first, mid - 1, result);
}
