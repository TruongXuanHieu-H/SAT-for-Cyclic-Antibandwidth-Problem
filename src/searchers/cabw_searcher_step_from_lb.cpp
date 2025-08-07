#include "cabw_searcher_step_from_lb.h"
#include "../global_data.h"

#include <iostream>

CabwSearcherStepFromLB::CabwSearcherStepFromLB()
{
    search_order = create_search_order();
    std::cout << "c [Main] Search order:";
    for (const auto &width : search_order)
    {
        std::cout << " " << width;
    }
    std::cout << ".\n";
}

std::deque<int> CabwSearcherStepFromLB::create_search_order()
{
    std::deque<int> order_result;
    std::deque<int> stashed_widths;

    int current_width = lower_bound;
    while (current_width <= upper_bound)
    {
        order_result.push_back(current_width);

        int step = 0;
        if (upper_bound - current_width >= 100)
        {
            step = step_widths[100];
        }
        else if (upper_bound - current_width >= 50)
        {
            step = step_widths[50];
        }
        else if (upper_bound - current_width >= 25)
        {
            step = step_widths[25];
        }
        else if (upper_bound - current_width >= 10)
        {
            step = step_widths[10];
        }
        else if (upper_bound - current_width >= 1)
        {
            step = step_widths[1];
        }
        else
        {
            step = 0; // No more steps available
            break;
        }

        for (int i = 1; i < step; i++)
        {
            stashed_widths.push_back(current_width + i);
        }

        current_width += step;
    }

    while (!stashed_widths.empty())
    {
        int w = stashed_widths.front();
        stashed_widths.pop_front();
        order_result.push_back(w);
    }

    return order_result;
}