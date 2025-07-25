#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <signal.h>
#include <stdexcept>
#include <map>

#include "global_data.h"
#include "cabw_encoder.h"
#include "utils/signal_handler.h"
#include "utils/usage.h"
#include "utils/version.h"
#include "enum/encode_type.h"
#include "enum/search_strategy.h"

int get_number_arg(std::string const &arg)
{
    try
    {
        std::size_t pos;
        int x = std::stoi(arg, &pos);
        if (pos < arg.size())
        {
            std::cerr << "Trailing characters after number: " << arg << '\n';
        }
        return x;
    }
    catch (std::invalid_argument const &ex)
    {
        std::cerr << "Invalid number: " << arg << '\n';
        return 0;
    }
    catch (std::out_of_range const &ex)
    {
        std::cerr << "Number out of range: " << arg << '\n';
        return 0;
    }
}

int main(int argc, char **argv)
{
    SignalHandler::init_signals();

    Version::print_version();

    if (argc < 2)
    {
        std::cerr << "c Error, no graph file was specified.\n";
        Helper::print_usage();
        return 1;
    }

    CyclicAntiBandwidthEncoder *cabw_enc = new CyclicAntiBandwidthEncoder();

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] != '-')
        {
            GlobalData::read_graph(argv[i]);
        }
        else if (argv[i] == std::string("--help"))
        {
            Helper::print_usage();
            delete cabw_enc;
            return 1;
        }
        else if (argv[i] == std::string("--ladder"))
        {
            GlobalData::encode_type = EncodeType::Ladder;
        }
        else if (argv[i] == std::string("--check-solution"))
        {
            GlobalData::enable_solution_verification = true;
        }
        else if (argv[i] == std::string("--from-lb"))
        {
            GlobalData::search_strategy = SearchStrategy::from_lb;
        }
        else if (argv[i] == std::string("-set-lb"))
        {
            GlobalData::forced_lb = get_number_arg(argv[++i]);
            if (GlobalData::forced_lb < 2)
            {
                std::cout << "Error, width has to be at least 2.\n";
                delete cabw_enc;
                return 1;
            }
            GlobalData::overwrite_lb = true;
            std::cout << "c LB is predefined as " << GlobalData::forced_lb << ".\n";
        }
        else if (argv[i] == std::string("-set-ub"))
        {
            GlobalData::forced_ub = get_number_arg(argv[++i]);
            if (GlobalData::forced_ub < 0)
            {
                std::cout << "Error, width has to be positive.\n";
                delete cabw_enc;
                return 1;
            }
            GlobalData::overwrite_ub = true;
            std::cout << "c UB is predefined as " << GlobalData::forced_ub << ".\n";
        }
        else if (argv[i] == std::string("-limit-memory"))
        {
            int lim_mem = get_number_arg(argv[++i]);
            if (lim_mem <= 0)
            {
                std::cout << "e Error, memory limit has to be positive.\n";
                delete cabw_enc;
                return 1;
            }
            std::cout << "c Memory limit is set to " << lim_mem << ".\n";
            GlobalData::memory_limit = lim_mem;
        }
        else if (argv[i] == std::string("-limit-real-time"))
        {
            int limit_real_time = get_number_arg(argv[++i]);
            if (limit_real_time <= 0)
            {
                std::cout << "e Error, real time limit has to be positive.\n";
                delete cabw_enc;
                return 1;
            }
            std::cout << "c Real time limit is set to " << limit_real_time << ".\n";
            GlobalData::real_time_limit = limit_real_time;
        }
        else if (argv[i] == std::string("-limit-elapsed-time"))
        {
            int limit_elapsed_time = get_number_arg(argv[++i]);
            if (limit_elapsed_time <= 0)
            {
                std::cout << "e Error, elapsed time limit has to be positive.\n";
                delete cabw_enc;
                return 1;
            }
            std::cout << "c Elapsed time limit is set to " << limit_elapsed_time << ".\n";
            GlobalData::elapsed_time_limit = limit_elapsed_time;
        }
        else if (argv[i] == std::string("-sample-rate"))
        {
            int sample_rate = get_number_arg(argv[++i]);
            if (sample_rate <= 0)
            {
                std::cout << "e Error, sample rate has to be positive.\n";
                delete cabw_enc;
                return 1;
            }
            std::cout << "c Sample rate is set to " << sample_rate << ".\n";
            GlobalData::sample_rate = sample_rate;
        }
        else if (argv[i] == std::string("-report-rate"))
        {
            int report_rate = get_number_arg(argv[++i]);
            if (report_rate <= 0)
            {
                std::cout << "e Error, sample rate has to be positive.\n";
                delete cabw_enc;
                return 1;
            }
            std::cout << "c Sample rate is set to " << report_rate << ".\n";
            GlobalData::report_rate = report_rate;
        }
        else if (argv[i] == std::string("-split-size"))
        {
            int split_size = get_number_arg(argv[++i]);
            if (split_size < 0)
            {
                std::cout << "Error, split size has to be positive.\n";
                delete cabw_enc;
                return 1;
            }
            std::cout << "c Splitting clauses at length " << split_size << ".\n";
            GlobalData::split_limit = split_size;
        }
        else if (argv[i] == std::string("-worker-count"))
        {
            GlobalData::worker_count = get_number_arg(argv[++i]);
        }
        else
        {
            std::cerr << "Unrecognized option: " << argv[i] << std::endl;

            delete cabw_enc;
            return 1;
        }
    }

    cabw_enc->encode_and_solve();

    delete cabw_enc;
    return 0;
}
