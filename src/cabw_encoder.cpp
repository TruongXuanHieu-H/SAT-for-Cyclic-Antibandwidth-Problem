#include "cabw_encoder.h"
#include <iostream>

CyclicAntiBandwidthEncoder::CyclicAntiBandwidthEncoder() {};

CyclicAntiBandwidthEncoder::~CyclicAntiBandwidthEncoder()
{
    delete g;
};

void CyclicAntiBandwidthEncoder::read_graph(std::string graph_file_name)
{
    g = new Graph(graph_file_name);
};

void CyclicAntiBandwidthEncoder::encode_and_solve()
{
    std::cout << "c Encoding and solving for graph: " << g->graph_name << std::endl;
};

void CyclicAntiBandwidthEncoder::encode_and_print_dimacs(int width)
{
    std::cout << "c Encoding and printing DIMACS for width: " << width << std::endl;
};