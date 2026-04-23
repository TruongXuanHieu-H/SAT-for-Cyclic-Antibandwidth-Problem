#include <string>
#include <iostream>
#include <unordered_map>
#include <functional>
#include <stdexcept>

#include "global_data.h"
#include "cabw_encoder.h"
#include "utils/signal_handler.h"
#include "utils/usage.h"
#include "utils/version.h"
#include "enum/encode_type.h"
#include "enum/search_strategy.h"

using Command = std::function<void(int&, int, char**)>;

double get_double(const std::string& arg)
{
    try {
        return std::stod(arg);
    } catch (const std::exception& e) {
        throw std::runtime_error("Invalid number: " + arg);
    }
}

double get_positive_double(int& i, int argc, char** argv, const std::string& name)
{
    if (i + 1 >= argc)
        throw std::runtime_error("Missing value for " + name);
    double val = get_double(argv[++i]);
    if (val <= 0)
        throw std::runtime_error(name + " must be positive");
    return val;
}

int main(int argc, char **argv)
{
    SignalHandler::init_signals();

    Version::print_version();

    if (argc < 2)
    {
        std::cerr << "e [Param] Error, no graph file was specified.\n";
        Helper::print_usage();
        return 1;
    }

    CyclicAntiBandwidthEncoder cabw_enc;

    std::unordered_map<std::string, Command> cmd;

    cmd["--ladder"] = [](int&, int, char**) 
    {
        GlobalData::encode_type = EncodeType::Ladder;
    };

    cmd["--check-solution"] = [](int&, int, char**) 
    {
        GlobalData::enable_solution_verification = true;
    };

    cmd["--iterate-from-lb"] = [](int&, int, char**) 
    {
        GlobalData::search_strategy = SearchStrategy::iterate_from_lb;
    };

    cmd["--step-from-lb"] = [](int&, int, char**) 
    {
        GlobalData::search_strategy = SearchStrategy::step_from_lb;
    };

    cmd["--binary-search-from-lb"] = [](int&, int, char**) 
    {
        GlobalData::search_strategy = SearchStrategy::binary_search_from_lb;
    };

    cmd["--binary-search-from-ub"] = [](int&, int, char**) 
    {
        GlobalData::search_strategy = SearchStrategy::binary_search_from_ub;
    };

    cmd["--binary-search-bfs"] = [](int&, int, char**) 
    {
        GlobalData::search_strategy = SearchStrategy::binary_search_bfs;
    };

    cmd["-set-lb"] = [](int& i, int argc, char** argv) 
    {
        int val = get_positive_double(i, argc, argv, "lower bound");

        if (val < 2)
            throw std::runtime_error("Lower bound has to be at least 2");
        if (val > GlobalData::g->n / 2)
            throw std::runtime_error("Lower bound cannot be greater than n/2");

        GlobalData::forced_lb = val;
        GlobalData::overwrite_lb = true;

        std::cout << "c [Param] LB is predefined as " << val << ".\n";
    };

    cmd["-set-ub"] = [](int& i, int argc, char** argv) 
    {
        int val = get_positive_double(i, argc, argv, "upper bound");

        if (val < 2)
            throw std::runtime_error("Upper bound has to be at least 2");
        if (val > GlobalData::g->n / 2)
            throw std::runtime_error("Upper bound cannot be greater than n/2");
        
        GlobalData::forced_ub = val;
        GlobalData::overwrite_ub = true;

        std::cout << "c [Param] UB is predefined as " << val << ".\n";
    };

    cmd["-limit-memory"] = [](int& i, int argc, char** argv) 
    {
        int v = get_positive_double(i, argc, argv, "memory limit");
        GlobalData::memory_limit = v;
        std::cout << "c [Param] Memory limit is set to " << v << ".\n";
    };

    cmd["-limit-real-time"] = [](int& i, int argc, char** argv) 
    {
        int v = get_positive_double(i, argc, argv, "real time limit");
        GlobalData::real_time_limit = v;
        std::cout << "c [Param] Real time limit is set to " << v << ".\n";
    };

    cmd["-limit-elapsed-time"] = [](int& i, int argc, char** argv) 
    {
        int v = get_positive_double(i, argc, argv, "elapsed time limit");
        GlobalData::elapsed_time_limit = v;
        std::cout << "c [Param] Elapsed time limit is set to " << v << ".\n";
    };

    cmd["-sample-rate"] = [](int& i, int argc, char** argv) 
    {
        int v = get_positive_double(i, argc, argv, "sample rate");
        GlobalData::sample_rate = v;
        std::cout << "c [Param] Sample rate is set to " << v << ".\n";
    };

    cmd["-report-rate"] = [](int& i, int argc, char** argv) 
    {
        int v = get_positive_double(i, argc, argv, "report rate");
        GlobalData::report_rate = v;
        std::cout << "c [Param] Report rate is set to " << v << ".\n";
    };

    cmd["-split-size"] = [](int& i, int argc, char** argv) 
    {
        int v = get_positive_double(i, argc, argv, "split size");
        GlobalData::split_limit = v;
        std::cout << "c [Param] Splitting clauses at length " << v << ".\n";
    };

    cmd["-worker-count"] = [](int& i, int argc, char** argv) 
    {
        int v = get_positive_double(i, argc, argv, "worker count");
        GlobalData::worker_count = v;
        std::cout << "c [Param] Worker count is set to " << v << ".\n";
    };

    cmd["-symmetry-break"] = [](int& i, int argc, char** argv) 
    {
        if (i + 1 >= argc)
            throw std::runtime_error("Missing symmetry type");

        std::string s = argv[++i];

        if (s == "none")
            GlobalData::symmetry_break_strategy = SymmetryBreakingType::NONE;
        else if (s == "first")
            GlobalData::symmetry_break_strategy = SymmetryBreakingType::FIRST;
        else if (s == "highest-degree")
            GlobalData::symmetry_break_strategy = SymmetryBreakingType::HIGHEST_DEGREE;
        else if (s == "lowest-degree")
            GlobalData::symmetry_break_strategy = SymmetryBreakingType::LOWEST_DEGREE;
        else
            throw std::runtime_error("Unrecognized symmetry breaking type: " + s);
    };

    cmd["-sat-solver"] = [](int& i, int argc, char** argv) 
    {
        if (i + 1 >= argc)
            throw std::runtime_error("Missing solver type");

        std::string s = argv[++i];

        if (s == "cadical")
            GlobalData::sat_solver_type = SATSolverType::CaDiCaL;
        else
            throw std::runtime_error("Unrecognized SAT solver type: " + s);
    };

    cmd["-just-print-dimacs"] = [](int& i, int argc, char** argv) 
    {
        if (i + 1 >= argc)
            throw std::runtime_error("Missing directory");

        GlobalData::just_print_dimacs = true;
        GlobalData::dimacs_directory = argv[++i];
    };

    cmd["-lb-skip-threshold"] = [](int& i, int argc, char** argv) 
    {
        double v = get_positive_double(i, argc, argv, "LB skip threshold");
        if (v < 0 || v > 1)
            throw std::runtime_error("LB skip threshold must be between 0 and 1");
        GlobalData::lb_skip_threshold = v;
        std::cout << "c [Param] LB skip threshold is set to " << v << ".\n";
    };

    try {
        for (int i = 1; i < argc; i++) 
        {
            std::string arg = argv[i];

            if (arg[0] != '-') {
                GlobalData::read_graph(arg);
                continue;
            }

            auto it = cmd.find(arg);
            if (it != cmd.end()) {
                it->second(i, argc, argv);
            } else if (arg == "--help") {
                Helper::print_usage();
                return 0;
            } else {
                throw std::runtime_error("Unrecognized option: " + arg);
            }
        }
    }
    catch (const std::exception& e) 
    {
        std::cerr << "e [Param] " << e.what() << "\n";
        return 1;
    }

    if (GlobalData::just_print_dimacs)
        cabw_enc.encode_and_print_dimacs();
    else
        cabw_enc.encode_and_solve();

    return 0;
}
