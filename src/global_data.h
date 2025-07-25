#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include "graph/graph.h"
#include "enum/encode_type.h"
#include "enum/search_strategy.h"
#include <limits>

class GlobalData
{
public:
    GlobalData() = default;
    ~GlobalData() = default;

    static Graph *g; // Pointer to the global graph instance

    static int worker_count;

    static EncodeType encode_type;
    static SearchStrategy search_strategy;

    static bool just_print_dimacs;
    static int dimacs_width; // Width for DIMACS printing

    static bool enable_solution_verification;
    static int split_limit;
    static std::string symmetry_break_point;

    static bool overwrite_lb;
    static bool overwrite_ub;
    static int forced_lb;
    static int forced_ub;

    static int sample_rate; // Interval of sampler, in microseconds
    static int report_rate; // Interval of report, in number of sampler

    static float memory_limit;       // bound of total memory consumed by all the processes, in megabyte
    static float real_time_limit;    // bound of time consumed by main process, in seconds
    static float elapsed_time_limit; // bound of total time consumed by all the process, in seconds

    static void read_graph(std::string graph_file_name);
};

#endif // GLOBAL_DATA_H