#ifndef CABW_ENCODER_H
#define CABW_ENCODER_H

#include "enum/encode_type.h"
#include "enum/search_strategy.h"
#include "graph/graph.h"

#include <string>

class CyclicAntiBandwidthEncoder
{
public:
    CyclicAntiBandwidthEncoder();
    virtual ~CyclicAntiBandwidthEncoder();

    // Encoder type
    EncodeType enc_choice = EncodeType::Seq;

    // Search strategy
    SearchStrategy enc_strategy = SearchStrategy::from_lb;

    // Verbose output
    bool verbose = true;

    // Check solution validity
    bool check_solution = true;

    // Force phase setting
    bool force_phase = false;

    // SAT configuration
    std::string sat_configuration = "sat";

    // Split limit for clauses
    // If set to 0, no splitting occurs
    // If set to a positive integer, clauses longer than this limit are split
    // into two by introducing a new variable
    int split_limit = 0;

    // Symmetry break point
    std::string symmetry_break_point = "n";

    // Overwrite bounds
    bool overwrite_lb = false;
    bool overwrite_ub = false;
    int forced_lb = 0;
    int forced_ub = 0;

    void read_graph(std::string graph_file_name);
    void encode_and_solve();
    void encode_and_print_dimacs(int width);

    Graph *g = nullptr;
};

#endif // CABW_ENCODER_H