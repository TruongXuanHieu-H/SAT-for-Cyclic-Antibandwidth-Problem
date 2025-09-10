#include "global_data.h"

GlobalData::GlobalData() {}

GlobalData::~GlobalData()
{
    if (g)
        delete g; // Clean up the global graph instance
}

Graph *GlobalData::g = nullptr;

int GlobalData::worker_count = 1;

EncodeType GlobalData::encode_type = EncodeType::Ladder;
SearchStrategy GlobalData::search_strategy = SearchStrategy::iterate_from_lb;
SymmetryBreakingType GlobalData::symmetry_break_strategy = SymmetryBreakingType::NONE;

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

std::unordered_map<std::string, int> GlobalData::cabw_LBs = {
    {"A-pores_1.mtx.rnd", 3},
    {"B-ibm32.mtx.rnd", 5},
    {"C-bcspwr01.mtx.rnd", 8},
    {"D-bcsstk01.mtx.rnd", 4},
    {"E-bcspwr02.mtx.rnd", 11},
    {"F-curtis54.mtx.rnd", 6},
    {"G-will57.mtx.rnd", 6},
    {"H-impcol_b.mtx.rnd", 4},
    {"I-ash85.mtx.rnd", 10},
    {"J-nos4.mtx.rnd", 16},
    {"K-dwt__234.mtx.rnd", 23},
    {"L-bcspwr03.mtx.rnd", 20},
    {"M-bcsstk06.mtx.rnd", 14},
    {"N-bcsstk07.mtx.rnd", 14},
    {"O-impcol_d.mtx.rnd", 46},
    {"P-can__445.mtx.rnd", 39},
    {"Q-494_bus.mtx.rnd", 110},
    {"R-dwt__503.mtx.rnd", 23},
    {"S-sherman4.mtx.rnd", 128},
    {"T-dwt__592.mtx.rnd", 52},
    {"U-662_bus.mtx.rnd", 110},
    {"V-nos6.mtx.rnd", 163},
    {"W-685_bus.mtx.rnd", 68},
    {"X-can__715.mtx.rnd", 56},

    {"hypercube_4_16.txt", 2},
    {"hypercube_5_32.txt", 5},
    {"hypercube_6_64.txt", 10},
    {"hypercube_7_128.txt", 21},
    {"hypercube_8_256.txt", 43},
    {"hypercube_9_512.txt", 89},
    {"hypercube_10_1024.txt", 182},
};

std::unordered_map<std::string, int> GlobalData::cabw_UBs = {
    {"A-pores_1.mtx.rnd", 8},
    {"B-ibm32.mtx.rnd", 9},
    {"C-bcspwr01.mtx.rnd", 17},
    {"D-bcsstk01.mtx.rnd", 9},
    {"E-bcspwr02.mtx.rnd", 22},
    {"F-curtis54.mtx.rnd", 13},
    {"G-will57.mtx.rnd", 14},
    {"H-impcol_b.mtx.rnd", 8},
    {"I-ash85.mtx.rnd", 27},
    {"J-nos4.mtx.rnd", 40},
    {"K-dwt__234.mtx.rnd", 58},
    {"L-bcspwr03.mtx.rnd", 39},
    {"M-bcsstk06.mtx.rnd", 72},
    {"N-bcsstk07.mtx.rnd", 72},
    {"O-impcol_d.mtx.rnd", 173},
    {"P-can__445.mtx.rnd", 120},
    {"Q-494_bus.mtx.rnd", 246},
    {"R-dwt__503.mtx.rnd", 71},
    {"S-sherman4.mtx.rnd", 272},
    {"T-dwt__592.mtx.rnd", 150},
    {"U-662_bus.mtx.rnd", 220},
    {"V-nos6.mtx.rnd", 337},
    {"W-685_bus.mtx.rnd", 136},
    {"X-can__715.mtx.rnd", 142},

    {"hypercube_4_16.txt", 4},
    {"hypercube_5_32.txt", 9},
    {"hypercube_6_64.txt", 19},
    {"hypercube_7_128.txt", 41},
    {"hypercube_8_256.txt", 85},
    {"hypercube_9_512.txt", 178},
    {"hypercube_10_1024.txt", 364},
    
    {"double_star_15_5.txt", 3},
    {"double_star_15_7.txt", 4},
    {"double_star_15_10.txt", 5},
    {"double_star_15_12.txt", 6},
    {"double_star_30_20.txt", 10},
    {"double_star_30_25.txt", 13},
    {"double_star_35_20.txt", 10},
    {"double_star_35_25.txt", 13},
    {"double_star_40_20.txt", 10},
    {"double_star_40_25.txt", 13},
    {"double_star_40_30.txt", 15},
    {"double_star_50_20.txt", 10},
    {"double_star_50_25.txt", 13},
    {"double_star_50_30.txt", 15},
    {"double_star_100_20.txt", 10},
    {"double_star_100_25.txt", 13},
    {"double_star_100_30.txt", 15},
    {"double_star_150_20.txt", 10},
    {"double_star_150_25.txt", 13},
    {"double_star_150_30.txt", 15},

    {"3dmesh_2_2_3.txt", 4},
    {"3dmesh_2_2_168.txt", 334},
    {"3dmesh_2_2_335.txt", 668},
    {"3dmesh_2_2_500.txt", 998},
    {"3dmesh_3_3_3.txt", 9},
    {"3dmesh_3_3_135.txt", 603},
    {"3dmesh_3_3_270.txt", 1211},
    {"3dmesh_3_3_400.txt", 1796},
    {"3dmesh_4_4_5.txt", 32},
    {"3dmesh_4_4_68.txt", 536},
    {"3dmesh_4_4_137.txt", 1088},
    {"3dmesh_4_4_200.txt", 1592},
    {"3dmesh_5_5_7.txt", 74},
    {"3dmesh_5_5_35.txt", 424},
    {"3dmesh_5_5_70.txt", 862},
    {"3dmesh_5_5_100.txt", 1237},
    {"3dmesh_6_6_8.txt", 125},
    {"3dmesh_6_6_36.txt", 629},
    {"3dmesh_6_6_72.txt", 1277},
    {"3dmesh_6_6_100.txt", 1781},

};