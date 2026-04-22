#include <map>
#include <string>
#include <iostream>
#include <iomanip>

#include "usage.h"

const std::map<std::string, std::string> Helper::option_list = {
    {"--help", "Print usage message with all possible options"},
    {"--ladder", "Use ladder encoding"},
    {"--check-solution", "Verify the found solution by recomputing cyclic antibandwidth"},

    // Search strategies
    {"--iterate-from-lb", "Linear search starting from lower bound"},
    {"--step-from-lb", "Stepwise search starting from lower bound"},
    {"--binary-search-from-lb", "Binary search starting from lower bound"},
    {"--binary-search-from-ub", "Binary search starting from upper bound"},
    {"--binary-search-bfs", "Binary search using BFS-style exploration"},

    // Bounds
    {"-set-lb <int>", "Set lower bound (2 <= lower bound <= upper bound <= number of vertices/2)"},
    {"-set-ub <int>", "Set upper bound (2 <= lower bound <= upper bound <= number of vertices/2)"},

    // Resource limits
    {"-limit-memory <int>", "Set memory limit"},
    {"-limit-real-time <int>", "Set real time limit"},
    {"-limit-elapsed-time <int>", "Set CPU elapsed time limit"},

    // Logging
    {"-sample-rate <int>", "Set sampling rate"},
    {"-report-rate <int>", "Set reporting frequency"},

    // Encoding / performance
    {"-split-size <int>", "Split clauses longer than given size"},
    {"-worker-count <int>", "Number of parallel workers"},

    // Symmetry breaking
    {"-symmetry-break none", "Disable symmetry breaking"},
    {"-symmetry-break first", "Fix first vertex"},
    {"-symmetry-break highest-degree", "Fix highest-degree vertex"},
    {"-symmetry-break lowest-degree", "Fix lowest-degree vertex"},

    // SAT Solver
    {"-sat-solver <solver>", "Specify the SAT solver to use (currently only supports 'cadical')"},

    // Print dimacs
    {"-just-print-dimacs <dimacs directory>", "Only encodes and prints the generated DIMACS CNF formula to the specified directory, without invoking the SAT solver"},
};

void Helper::print_usage()
{
    std::cout << "c [Usage] Usage: cabw_enc path_to_graph_file [ <option> ... ].\n";
    std::cout << "c [Usage] where '<option>' is one of the following options:\n";
    std::cout << std::endl;
    for (const auto &option : option_list)
    {
        std::cout << std::left << "\t" << std::setw(30) << option.first << "\t" << option.second << ".\n";
    }
    std::cout << std::endl;
}