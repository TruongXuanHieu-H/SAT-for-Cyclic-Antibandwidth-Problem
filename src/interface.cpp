#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <signal.h>
#include <stdexcept>
#include <map>

#include "utils/signal_handler.h"
#include "utils/usage.h"
#include "utils/version.h"
#include "cabw_encoder.h"
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

    std::string graph_file;
    int cabw_value = 2;
    bool just_print_dimacs = false;
    int split_size = 0;

    Version::print_version();

    if (argc < 2)
    {
        std::cerr << "c Error, no graph file was specified." << std::endl;
        Helper::print_usage();
        return 1;
    }

    CyclicAntiBandwidthEncoder *cabw_enc = new CyclicAntiBandwidthEncoder();

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] != '-')
        {
            cabw_enc->read_graph(argv[i]);
            cabw_enc->g->print_stat();
        }
        else if (argv[i] == std::string("--help"))
        {
            Helper::print_usage();
            delete cabw_enc;
            return 1;
        }
        else if (argv[i] == std::string("--seq"))
        {
            cabw_enc->enc_choice = EncodeType::Seq;
        }
        else if (argv[i] == std::string("--conf-sat"))
        {
            cabw_enc->sat_configuration = "sat";
        }
        else if (argv[i] == std::string("--conf-unsat"))
        {
            cabw_enc->sat_configuration = "unsat";
        }
        else if (argv[i] == std::string("--conf-def"))
        {
            cabw_enc->sat_configuration = "";
        }
        else if (argv[i] == std::string("--force-phase"))
        {
            cabw_enc->force_phase = true;
        }
        else if (argv[i] == std::string("--check-solution"))
        {
            cabw_enc->check_solution = true;
        }
        else if (argv[i] == std::string("--from-lb"))
        {
            cabw_enc->enc_strategy = SearchStrategy::from_lb;
        }
        else if (argv[i] == std::string("-print-w"))
        {
            cabw_value = get_number_arg(argv[++i]);
            if (cabw_value < 2)
            {
                std::cout << "Error, width has to be at least 2." << std::endl;
                delete cabw_enc;
                return 1;
            }
            std::cout << "c DIMACS Printing mode for w = " << cabw_value << "." << std::endl;
            just_print_dimacs = true;
        }
        else if (argv[i] == std::string("-set-lb"))
        {
            cabw_enc->forced_lb = get_number_arg(argv[++i]);
            if (cabw_enc->forced_lb < 2)
            {
                std::cout << "Error, width has to be at least 2." << std::endl;
                delete cabw_enc;
                return 1;
            }
            cabw_enc->overwrite_lb = true;
            std::cout << "c LB is predefined as " << cabw_enc->forced_lb << "." << std::endl;
        }
        else if (argv[i] == std::string("-set-ub"))
        {
            cabw_enc->forced_ub = get_number_arg(argv[++i]);
            if (cabw_enc->forced_ub < 0)
            {
                std::cout << "Error, width has to be positive." << std::endl;
                delete cabw_enc;
                return 1;
            }
            cabw_enc->overwrite_ub = true;
            std::cout << "c UB is predefined as " << cabw_enc->forced_ub << "." << std::endl;
        }
        else if (argv[i] == std::string("-split-size"))
        {
            split_size = get_number_arg(argv[++i]);
            if (split_size < 0)
            {
                std::cout << "Error, split size has to be positive." << std::endl;
                delete cabw_enc;
                return 1;
            }
            std::cout << "c Splitting clauses at length " << split_size << "." << std::endl;
            cabw_enc->split_limit = split_size;
        }
        else if (argv[i] == std::string("-symmetry-break"))
        {
            std::string break_point = argv[++i];
            if (break_point == std::string("f"))
            {
                cabw_enc->symmetry_break_point = break_point;
                std::cout << "c Symetry breaking in the first node." << std::endl;
            }
            else if (break_point == std::string("h"))
            {
                cabw_enc->symmetry_break_point = break_point;
                std::cout << "c Symetry breaking in the highest degree node." << std::endl;
            }
            else if (break_point == std::string("l"))
            {
                cabw_enc->symmetry_break_point = break_point;
                std::cout << "c Symetry breaking in the lowest degree node." << std::endl;
            }
            else if (break_point == std::string("n"))
            {
                cabw_enc->symmetry_break_point = break_point;
                std::cout << "c Symetry breaking is not applied." << std::endl;
            }
            else
            {
                std::cout << "c Invalid symetry breaking point." << std::endl;

                delete cabw_enc;
                return 1;
            }
        }
        else
        {
            std::cerr << "Unrecognized option: " << argv[i] << std::endl;

            delete cabw_enc;
            return 1;
        }
    }

    if (just_print_dimacs)
    {
        cabw_enc->encode_and_print_dimacs(cabw_value);
    }
    else
    {
        cabw_enc->encode_and_solve();
    }

    delete cabw_enc;
    return 0;
}
