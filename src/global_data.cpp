#include "global_data.h"

Graph *GlobalData::g = nullptr;

int GlobalData::worker_count = 1;

EncodeType GlobalData::encode_type = EncodeType::Ladder;
SearchStrategy GlobalData::search_strategy = SearchStrategy::from_lb;

bool GlobalData::just_print_dimacs = false;
int GlobalData::dimacs_width = 2; // Default width for DIMACS printing

bool GlobalData::enable_solution_verification = true;
int GlobalData::split_limit = 0;

bool GlobalData::overwrite_lb = false;
bool GlobalData::overwrite_ub = false;
int GlobalData::forced_lb = 0;
int GlobalData::forced_ub = 0;

int GlobalData::sample_rate = 100000;
int GlobalData::report_rate = 100;

float GlobalData::memory_limit = std::numeric_limits<float>::max();
float GlobalData::real_time_limit = std::numeric_limits<float>::max();
float GlobalData::elapsed_time_limit = std::numeric_limits<float>::max();

void GlobalData::read_graph(std::string graph_file_name)
{
    g = new Graph(graph_file_name);
};
