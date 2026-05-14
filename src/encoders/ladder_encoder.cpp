#include "ladder_encoder.h"
#include "../global_data.h"
#include "instance_data.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <assert.h>

LadderEncoder::LadderEncoder() {}
LadderEncoder::~LadderEncoder() {}

void LadderEncoder::encode_cyclic_antibandwidth()
{
    if (InstanceData::width < 1 || InstanceData::width > GlobalData::g->n)
    {
        std::cout << "c Non-valid value of w, nothing to encode.\n";
        return;
    }
    do_encode_antibandwidth();
}

void LadderEncoder::do_encode_antibandwidth()
{
    obj_k_aux_vars.clear();

    if (GlobalData::symmetry_break_strategy == SymmetryBreakingType::FIRST)
    {
        encode_symmetry_break_first_node();
    }
    else if (GlobalData::symmetry_break_strategy == SymmetryBreakingType::HIGHEST_DEGREE)
    {
        encode_symmetry_break_highest_degree_node();
    }
    else if (GlobalData::symmetry_break_strategy == SymmetryBreakingType::LOWEST_DEGREE)
    {
        encode_symmetry_break_lowest_degree_node();
    }

    encode_vertices();

    encode_obj_k();

    encode_labels();
};

int LadderEncoder::get_obj_k_aux_var(std::vector<int> key)
{

    auto pair = obj_k_aux_vars.find(key);

    if (pair != obj_k_aux_vars.end())
        return pair->second;

    if (key.front() == key.back() && key.size() == 1)
    {
        return key.front();
    }

    int new_obj_k_aux_var = InstanceData::vh->get_new_var();
    obj_k_aux_vars.insert({key, new_obj_k_aux_var});
    return new_obj_k_aux_var;
}

void LadderEncoder::encode_vertices()
{
    for (int label = 0; label < GlobalData::g->n; label++)
    {
        std::vector<int> node_vertices_eo(GlobalData::g->n);

        for (int vertex = 0; vertex < GlobalData::g->n; vertex++)
        {
            node_vertices_eo[vertex] = vertex * GlobalData::g->n + label + 1;
        }

        encode_exactly_one_product(node_vertices_eo);
    }
}

void LadderEncoder::encode_labels()
{
    for (int vertex = 0; vertex < GlobalData::g->n; vertex++)
    {
        int number_windows = ceil((float)GlobalData::g->n / InstanceData::width);
        std::vector<std::vector<int>> vertice_vars(number_windows);

        for (int window = 0; window < number_windows; window++)
        {
            int start = vertex * GlobalData::g->n + window * InstanceData::width + 1;
            int end = std::min(
                vertex * GlobalData::g->n + (window + 1) * InstanceData::width,
                vertex * GlobalData::g->n + GlobalData::g->n);

            for (int var = start; var <= end; var++)
            {
                vertice_vars[window].push_back(var);
            }
        }

        std::vector<int> alo_clause = {};
        for (int window = 0; window < number_windows; window++)
        {
            int first_window_aux_var = get_obj_k_aux_var(vertice_vars[window]);
            alo_clause.push_back(first_window_aux_var);
            for (int next_window = window + 1; next_window < number_windows; next_window++)
            {
                int second_window_aux_var = get_obj_k_aux_var(vertice_vars[next_window]);
                InstanceData::cc->add_clause({-first_window_aux_var, -second_window_aux_var});
            }
        }
        InstanceData::cc->add_clause(alo_clause);
    }
}

void LadderEncoder::encode_exactly_one_product(const std::vector<int> &vars)
{
    if (vars.size() < 2)
        return;
    if (vars.size() == 2)
    {
        // simplifies to vars[0] /\ -1*vars[0], in case vars[0] == vars[1]
        InstanceData::cc->add_clause({vars[0], vars[1]});
        InstanceData::cc->add_clause({-1 * vars[0], -1 * vars[1]});
        return;
    }

    int len = vars.size();
    int p = std::ceil(std::sqrt(len));
    int q = std::ceil((float)len / (float)p);

    std::vector<int> u_vars;
    std::vector<int> v_vars;
    for (int i = 1; i <= p; ++i)
    {
        int new_var = InstanceData::vh->get_new_var();
        u_vars.push_back(new_var);
    }
    for (int j = 1; j <= q; ++j)
    {
        int new_var = InstanceData::vh->get_new_var();
        v_vars.push_back(new_var);
    }

    int i, j;
    std::vector<int> or_clause = std::vector<int>();
    for (int idx = 0; idx < (int)vars.size(); ++idx)
    {
        i = std::floor(idx / p);
        j = idx % p;

        InstanceData::cc->add_clause({-1 * vars[idx], v_vars[i]});
        InstanceData::cc->add_clause({-1 * vars[idx], u_vars[j]});

        or_clause.push_back(vars[idx]);
    }
    InstanceData::cc->add_clause(or_clause);

    encode_amo_seq(u_vars);
    encode_amo_seq(v_vars);
};

void LadderEncoder::encode_amo_seq(const std::vector<int> &vars)
{
    if (vars.size() < 2)
        return;

    int prev = vars[0];

    for (int idx = 1; idx < (int)vars.size() - 1; ++idx)
    {
        int curr = vars[idx];
        int next = InstanceData::vh->get_new_var();
        InstanceData::cc->add_clause({-1 * prev, -1 * curr});
        InstanceData::cc->add_clause({-1 * prev, next});
        InstanceData::cc->add_clause({-1 * curr, next});

        prev = next;
    }
    InstanceData::cc->add_clause({-1 * prev, -1 * vars[vars.size() - 1]});
};

void LadderEncoder::encode_obj_k()
{
    std::vector<std::vector<int>> ladders_vars;
    for (int vertex = 0; vertex < GlobalData::g->n; vertex++)
    {
        std::vector<int> ladder_vars;
        for (int label = 0; label < GlobalData::g->n; label++)
        {
            ladder_vars.push_back(vertex * GlobalData::g->n + label + 1);
        }
        for (int label = 0; label < InstanceData::width - 1; label++)
        {
            ladder_vars.push_back(vertex * GlobalData::g->n + label + 1);
        }
        ladders_vars.push_back(ladder_vars);
    }

    for (int i = 0; i < GlobalData::g->n; i++)
    {
        encode_ladder(ladders_vars[i], InstanceData::width);
    }

    for (auto edge : GlobalData::g->edges)
    {
        connect_ladder(ladders_vars[edge.first - 1], ladders_vars[edge.second - 1], InstanceData::width); // Have to reduce by 1 since edges are start from 1
    }
}

void LadderEncoder::encode_ladder(const std::vector<int> ladder_vars, int width)
{
    std::vector<std::vector<int>> windows_vars;
    int number_ladder_vars = (int)ladder_vars.size();

    for (int i = 0; i < number_ladder_vars; i += width)
    {
        int end = std::min(i + width, number_ladder_vars);
        windows_vars.emplace_back(ladder_vars.begin() + i, ladder_vars.begin() + end);
    }

    int number_windows = (int)windows_vars.size();

    for (int i = 0; i < number_windows; i++)
    {
        encode_window(windows_vars[i], i == 0, i == number_windows - 1);
    }

    for (int i = 0; i < number_windows - 1; i++)
    {
        connect_windows(windows_vars[i], windows_vars[i + 1]);
    }
}

void LadderEncoder::encode_window(const std::vector<int> window_vars, bool is_first_window, bool is_last_window)
{
    int window_vars_size = (int)window_vars.size();

    if (!is_first_window)
    {
        for (int i = 1; i < window_vars_size; i++)
        {
            InstanceData::cc->add_clause({-(window_vars[i]),
                                          get_obj_k_aux_var(std::vector<int>(window_vars.begin(), window_vars.begin() + i + 1))});
        }

        for (int i = 0; i < window_vars_size - 1; i++)
        {
            InstanceData::cc->add_clause({-get_obj_k_aux_var(std::vector<int>(window_vars.begin(), window_vars.begin() + i + 1)),
                                          get_obj_k_aux_var(std::vector<int>(window_vars.begin(), window_vars.begin() + i + 2))});
        }

        for (int i = window_vars_size - 1; i > 0; i--)
        {
            InstanceData::cc->add_clause({window_vars[i],
                                          get_obj_k_aux_var(std::vector<int>(window_vars.begin(), window_vars.begin() + i)),
                                          -get_obj_k_aux_var(std::vector<int>(window_vars.begin(), window_vars.begin() + i + 1))});
        }

        for (int i = window_vars_size - 1; i > 0; i--)
        {
            InstanceData::cc->add_clause({-(window_vars[i]),
                                          -get_obj_k_aux_var(std::vector<int>(window_vars.begin(), window_vars.begin() + i))});
        }
    }

    if (!is_last_window)
    {
        for (int i = window_vars_size - 2; i >= 0; i--)
        {
            InstanceData::cc->add_clause({-(window_vars[i]),
                                          get_obj_k_aux_var(std::vector<int>(window_vars.begin() + i, window_vars.end()))});
        }

        for (int i = window_vars_size - 1; i >= 1; i--)
        {
            InstanceData::cc->add_clause({-get_obj_k_aux_var(std::vector<int>(window_vars.begin() + i, window_vars.end())),
                                          get_obj_k_aux_var(std::vector<int>(window_vars.begin() + i - 1, window_vars.end()))});
        }

        for (int i = 0; i < window_vars_size - 1; i++)
        {
            InstanceData::cc->add_clause({window_vars[i],
                                          get_obj_k_aux_var(std::vector<int>(window_vars.begin() + i + 1, window_vars.end())),
                                          -get_obj_k_aux_var(std::vector<int>(window_vars.begin() + i, window_vars.end()))});
        }

        if (is_first_window)
        {
            for (int i = 0; i < window_vars_size - 1; i++)
            {
                InstanceData::cc->add_clause({-(window_vars[i]),
                                              -get_obj_k_aux_var(std::vector<int>(window_vars.begin() + i + 1, window_vars.end()))});
            }
        }
    }
}

void LadderEncoder::connect_windows(const std::vector<int> first_window_vars, const std::vector<int> second_window_vars)
{
    int number_first_window_vars = (int)first_window_vars.size();
    int number_second_window_vars = (int)second_window_vars.size();
    assert(number_first_window_vars < number_second_window_vars);

    int number_connections = number_first_window_vars == number_second_window_vars ? number_second_window_vars - 1 : number_second_window_vars;

    for (int i = 0; i < number_connections; i++)
    {
        InstanceData::cc->add_clause({-get_obj_k_aux_var(std::vector<int>(first_window_vars.begin() + i + 1, first_window_vars.end())),
                                      -get_obj_k_aux_var(std::vector<int>(second_window_vars.begin(), second_window_vars.begin() + i + 1))});
    }
}

void LadderEncoder::connect_ladder(const std::vector<int> first_ladder_vars, const std::vector<int> second_ladder_vars, int width)
{
    assert(first_ladder_vars.size() == second_ladder_vars.size());

    int number_connections = first_ladder_vars.size() - width + 1;
    for (int i = 0; i < number_connections; i++)
    {
        int mod = i % width;
        if (mod == 0)
        {
            int first_aux_var = get_obj_k_aux_var(std::vector<int>(first_ladder_vars.begin() + i, first_ladder_vars.begin() + i + width));
            int second_aux_var = get_obj_k_aux_var(std::vector<int>(second_ladder_vars.begin() + i, second_ladder_vars.begin() + i + width));

            InstanceData::cc->add_clause({-first_aux_var, -second_aux_var});
        }
        else
        {
            int first_aux_var_1 = get_obj_k_aux_var(std::vector<int>(first_ladder_vars.begin() + i, first_ladder_vars.begin() + i + width - mod));
            int first_aux_var_2 = get_obj_k_aux_var(std::vector<int>(first_ladder_vars.begin() + i + width - mod, first_ladder_vars.begin() + i + width));
            int second_aux_var_1 = get_obj_k_aux_var(std::vector<int>(second_ladder_vars.begin() + i, second_ladder_vars.begin() + i + width - mod));
            int second_aux_var_2 = get_obj_k_aux_var(std::vector<int>(second_ladder_vars.begin() + i + width - mod, second_ladder_vars.begin() + i + width));

            InstanceData::cc->add_clause({-first_aux_var_1, -second_aux_var_1});
            InstanceData::cc->add_clause({-first_aux_var_1, -second_aux_var_2});
            InstanceData::cc->add_clause({-first_aux_var_2, -second_aux_var_1});
            InstanceData::cc->add_clause({-first_aux_var_2, -second_aux_var_2});
        }
    }
}