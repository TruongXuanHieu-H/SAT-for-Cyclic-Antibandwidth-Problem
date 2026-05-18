#include "ladder_split_encoder.h"
#include "../global_data.h"
#include "instance_data.h"

#include <iostream>
#include <assert.h>

LadderSplitEncoder::LadderSplitEncoder() {}
LadderSplitEncoder::~LadderSplitEncoder() {}

void LadderSplitEncoder::encode_labels()
{
    for (int vertex = 0; vertex < GlobalData::g->n; vertex++)
    {
        std::vector<int> node_labels_eo(GlobalData::g->n);

        for (int label = 0; label < GlobalData::g->n; label++)
        {
            node_labels_eo[label] = vertex * GlobalData::g->n + label + 1;
        }

        encode_exactly_one_product(node_labels_eo);
    }
};

void LadderSplitEncoder::encode_obj_k()
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

    int number_sub_ladders = 2;
    int avg_sub_ladder_width = InstanceData::width / number_sub_ladders;
    int exceed_sub_ladder_width = InstanceData::width % number_sub_ladders;

    for (int i = 0; i < GlobalData::g->n; i++)
    {
        std::vector<std::pair<std::vector<int>, int>> sub_ladders = split_into_sub_ladders(ladders_vars[i], InstanceData::width, number_sub_ladders);

        assert(avg_sub_ladder_width == sub_ladders[0].second);
        std::vector<int> compact_sub_ladder_vars = sub_ladders[0].first;

        for (int j = 1; j < number_sub_ladders; j++)
        {
            assert(avg_sub_ladder_width == sub_ladders[j].second);
            compact_sub_ladder_vars.insert(compact_sub_ladder_vars.end(), sub_ladders[j].first.end() - sub_ladders[j].second, sub_ladders[j].first.end());
        }

        if (exceed_sub_ladder_width == avg_sub_ladder_width)
        {
            compact_sub_ladder_vars.insert(compact_sub_ladder_vars.end(), sub_ladders.back().first.end() - sub_ladders.back().second, sub_ladders.back().first.end());
        }

        encode_ladder(compact_sub_ladder_vars, avg_sub_ladder_width);

        if (exceed_sub_ladder_width > 0 && exceed_sub_ladder_width < avg_sub_ladder_width)
        {
            encode_ladder(sub_ladders.back().first, exceed_sub_ladder_width);
        }

        connect_sub_ladders(sub_ladders);
    }

    for (auto edge : GlobalData::g->edges)
    {
        connect_ladder(ladders_vars[edge.first - 1], ladders_vars[edge.second - 1], InstanceData::width);
    }
};

std::vector<std::pair<std::vector<int>, int>> LadderSplitEncoder::split_into_sub_ladders(const std::vector<int> ladder_vars, int width, int number_splits)
{
    if (is_debugged)
    {
        std::cout << "c Splitting ladder ";
        for (int var : ladder_vars)
        {
            std::cout << var << " ";
        }
        std::cout << "with width " << width << std::endl;
    }

    std::vector<std::pair<std::vector<int>, int>> sub_ladders;

    int avg_sub_ladder_width = width / number_splits;
    int exceed_sub_ladder_width = width % number_splits;

    for (int i = 0; i < number_splits; i++)
    {
        std::vector<int> sub_ladder_vars(ladder_vars.begin() + i * avg_sub_ladder_width, ladder_vars.end() - (number_splits - 1 - i) * avg_sub_ladder_width - exceed_sub_ladder_width);
        sub_ladders.push_back({sub_ladder_vars, avg_sub_ladder_width});
    }

    if (exceed_sub_ladder_width > 0)
    {
        std::vector<int> sub_ladder_vars(ladder_vars.begin() + number_splits * avg_sub_ladder_width, ladder_vars.end());
        sub_ladders.push_back({sub_ladder_vars, exceed_sub_ladder_width});
    }

    if (is_debugged)
    {
        std::cout << "c Created sub-ladders:" << std::endl;
        for (int i = 0; i < (int)sub_ladders.size(); i++)
        {
            std::cout << "c Sub-ladder " << i + 1 << ": ";
            for (int var : sub_ladders[i].first)
            {
                std::cout << var << " ";
            }
            std::cout << "with width " << sub_ladders[i].second << std::endl;
        }
    }
    return sub_ladders;
}

void LadderSplitEncoder::connect_sub_ladders(const std::vector<std::pair<std::vector<int>, int>> sub_ladders)
{
    if (is_debugged)
    {
        std::cout << "c Connecting sub-ladders: " << std::endl;
        for (auto sub_ladder : sub_ladders)
        {
            std::cout << "c Sub-ladder vars: ";
            for (int var : sub_ladder.first)
            {
                std::cout << var << " ";
            }
            std::cout << "with width " << sub_ladder.second << std::endl;
        }
    }

    int number_sub_ladders = (int)sub_ladders.size();
    assert(number_sub_ladders > 1);
    for (int i = 0; i < number_sub_ladders - 1; i++)
    {
        assert((int)sub_ladders[i].first.size() - sub_ladders[i].second == (int)sub_ladders[i + 1].first.size() - sub_ladders[i + 1].second);
    }

    int avg_sub_ladder_width = sub_ladders[0].second;

    int number_connections = sub_ladders[0].first.size() - sub_ladders[0].second + 1;
    for (int i = 0; i < number_connections; i++)
    {
        std::vector<int> sum_vars;
        for (int j = 0; j < number_sub_ladders; j++)
        {
            sum_vars.insert(sum_vars.end(), sub_ladders[j].first.begin() + i, sub_ladders[j].first.begin() + i + sub_ladders[j].second);
        }

        if (is_debugged)
        {
            std::cout << "c Sum vars: ";
            for (int var : sum_vars)
            {
                std::cout << var << " ";
            }
            std::cout << std::endl;
        }

        std::vector<std::vector<int>> expressions;
        std::vector<std::vector<int>> sum_var_groups;

        int first_expression_size = avg_sub_ladder_width - i % avg_sub_ladder_width;
        int number_full_expressions = ((int)sum_vars.size() - first_expression_size) / avg_sub_ladder_width;
        int last_expression_size = ((int)sum_vars.size() - first_expression_size) % avg_sub_ladder_width;

        std::vector<int> first_expression(sum_vars.begin(), sum_vars.begin() + first_expression_size);
        expressions.push_back(first_expression);
        sum_var_groups.push_back(first_expression);
        for (int j = 0; j < number_full_expressions; j++)
        {
            std::vector<int> expression(sum_vars.begin() + first_expression_size + j * avg_sub_ladder_width, sum_vars.begin() + first_expression_size + (j + 1) * avg_sub_ladder_width);
            expressions.push_back(expression);
            std::vector<int> sum_var_group = sum_var_groups.back();
            sum_var_group.insert(sum_var_group.end(), expression.begin(), expression.end());
            sum_var_groups.push_back(sum_var_group);
        }
        if (last_expression_size > 0)
        {
            std::vector<int> expression(sum_vars.end() - last_expression_size, sum_vars.end());
            expressions.push_back(expression);
            std::vector<int> sum_var_group = sum_var_groups.back();
            sum_var_group.insert(sum_var_group.end(), expression.begin(), expression.end());
            sum_var_groups.push_back(sum_var_group);
        }

        if (is_debugged)
        {
            for (auto sum_var_group : sum_var_groups)
            {
                std::cout << "c Sum var group: ";
                for (int var : sum_var_group)
                {
                    std::cout << var << " ";
                }
                std::cout << std::endl;
            }
        }

        assert((int)expressions.size() == (int)sum_var_groups.size());

        std::vector<int> clause;
        clause.push_back(-get_obj_k_aux_var(sum_vars));
        for (int j = 0; j < (int)expressions.size(); j++)
        {
            InstanceData::cc->add_clause({-get_obj_k_aux_var(expressions[j], true), get_obj_k_aux_var(sum_vars)});
            clause.push_back(get_obj_k_aux_var(expressions[j]));
        }
        InstanceData::cc->add_clause(clause);
    }
}

void LadderSplitEncoder::connect_ladder(const std::vector<int> first_ladder_vars, const std::vector<int> second_ladder_vars, int width)
{
    if (is_debugged)
    {
        std::cout << "c Connecting ladders: " << std::endl;
        std::cout << "c First ladder vars: ";
        for (int var : first_ladder_vars)
        {
            std::cout << var << " ";
        }
        std::cout << std::endl;
        std::cout << "c Second ladder vars: ";
        for (int var : second_ladder_vars)
        {
            std::cout << var << " ";
        }
        std::cout << std::endl;
    }

    assert(first_ladder_vars.size() == second_ladder_vars.size());

    int number_connections = first_ladder_vars.size() - width + 1;
    for (int i = 0; i < number_connections; i++)
    {
        InstanceData::cc->add_clause({-get_obj_k_aux_var(std::vector<int>(first_ladder_vars.begin() + i, first_ladder_vars.begin() + i + width), true),
                                      -get_obj_k_aux_var(std::vector<int>(second_ladder_vars.begin() + i, second_ladder_vars.begin() + i + width), true)});
    }
}