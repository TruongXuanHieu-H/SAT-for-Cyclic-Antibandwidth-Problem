#include "cabw_searcher_binary_bfs.h"
#include "../global_data.h"

#include <iostream>

struct Segment
{
    int left, right;
};

CabwSearcherBinaryBFS::CabwSearcherBinaryBFS()
{
    search_order = create_search_order();
    std::cout << "c [Main] Search order: ";
    for (const auto &width : search_order)
    {
        std::cout << width << " ";
    }
    std::cout << "\n";
}

std::deque<int> CabwSearcherBinaryBFS::create_search_order()
{
    std::deque<int> result;
    if (lower_bound > upper_bound)
        return result;

    std::deque<Segment> dq;
    dq.push_back({lower_bound, upper_bound});

    while (!dq.empty())
    {
        Segment current = dq.front();
        dq.pop_front();

        int mid = (current.left + current.right) / 2;
        result.push_back(mid);

        if (current.left < mid)
            dq.push_back({current.left, mid - 1});
        if (mid < current.right)
            dq.push_back({mid + 1, current.right});
    }

    return result;
}

std::deque<int> CabwSearcherBinaryBFS::binary_partition(int first, int last)
{
    std::deque<int> result;
    if (first > last)
        return result;

    std::deque<Segment> dq;
    dq.push_back({first, last});

    while (!dq.empty())
    {
        Segment current = dq.front();
        dq.pop_front();

        int mid = (current.left + current.right) / 2;
        result.push_back(mid);

        if (current.left < mid)
            dq.push_back({current.left, mid - 1});
        if (mid < current.right)
            dq.push_back({mid + 1, current.right});
    }

    return result;
}
