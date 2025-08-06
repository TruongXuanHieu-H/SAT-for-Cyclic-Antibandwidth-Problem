#include "cabw_searcher_binary.h"
#include "../global_data.h"

#include <iostream>

CabwSearcherBinary::CabwSearcherBinary()
{
    search_order = create_search_order();
    std::cout << "c [Main] Search order: ";
    for (const auto &width : search_order)
    {
        std::cout << width << " ";
    }
    std::cout << "\n";
}

std::deque<int> CabwSearcherBinary::create_search_order()
{
    std::deque<int> order_result;
    binary_partition(lower_bound, upper_bound, order_result);
    return order_result;
}

void CabwSearcherBinary::binary_partition(int first, int last, std::deque<int> &result)
{
    if (first > last)
        return;

    int mid = (first + last) / 2;
    result.push_back(mid);

    binary_partition(first, mid - 1, result);
    binary_partition(mid + 1, last, result);
}
