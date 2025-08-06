#ifndef SEARCH_STRATEGY_H
#define SEARCH_STRATEGY_H

enum class SearchStrategy
{
    iterate_from_lb,       // Search from lower bound iteratively
    step_from_lb,          // Search from lower bound with steps
    binary_search_from_lb, // Binary search strategy from lower bound
    binary_search_from_ub, // Binary search strategy from upper bound
};

#endif // SEARCH_STRATEGY_H