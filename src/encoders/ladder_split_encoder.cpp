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

std::vector<std::vector<int>> LadderSplitEncoder::get_ladders_vars(int number_ladder, int width)
{
    std::vector<std::vector<int>> ladders_vars;
    for (int vertex = 0; vertex < number_ladder; vertex++)
    {
        std::vector<int> ladder_vars;
        for (int label = 0; label < number_ladder; label++)
        {
            ladder_vars.push_back(vertex * number_ladder + label + 1);
        }
        for (int label = 0; label < width - 1; label++)
        {
            ladder_vars.push_back(vertex * number_ladder + label + 1);
        }
        ladders_vars.push_back(ladder_vars);
    }
    return ladders_vars;
}

std::pair<std::vector<int>, int> LadderSplitEncoder::get_compact_sub_ladder(std::vector<std::pair<std::vector<int>, int>> &sub_ladders)
{
    std::vector<int> compact_sub_ladder_vars = sub_ladders[0].first;
    int compact_sub_ladder_width = sub_ladders[0].second;

    for (int j = 1; j < (int)sub_ladders.size(); j++)
    {
        if (sub_ladders[j].second == compact_sub_ladder_width)
        {
            compact_sub_ladder_vars.insert(compact_sub_ladder_vars.end(), sub_ladders[j].first.end() - sub_ladders[j].second, sub_ladders[j].first.end());
        }
        else
        {
            assert(sub_ladders[j].second < sub_ladders[0].second && j == (int)sub_ladders.size() - 1); // Must be the last sub-ladder with smaller width
        }
    }

    return {compact_sub_ladder_vars, compact_sub_ladder_width};
}

void LadderSplitEncoder::encode_obj_k()
{
    std::vector<std::vector<int>> ladders_vars = get_ladders_vars(GlobalData::g->n, InstanceData::width);

    int number_sub_ladders = 2;

    for (int i = 0; i < GlobalData::g->n; i++)
    {
        std::vector<std::pair<std::vector<int>, int>> sub_ladders = split_into_sub_ladders(ladders_vars[i], InstanceData::width, number_sub_ladders);

        std::pair<std::vector<int>, int> compact_sub_ladder = get_compact_sub_ladder(sub_ladders);

        encode_ladder(compact_sub_ladder.first, compact_sub_ladder.second);

        if (InstanceData::width % number_sub_ladders > 0)
            encode_ladder(sub_ladders.back().first, InstanceData::width % number_sub_ladders);

        connect_sub_ladders(sub_ladders, ladders_vars[i], InstanceData::width);
    }

    for (auto edge : GlobalData::g->edges)
    {
        connect_ladder(ladders_vars[edge.first - 1], ladders_vars[edge.second - 1], InstanceData::width);
    }
};

std::vector<std::pair<std::vector<int>, int>> LadderSplitEncoder::split_into_sub_ladders(const std::vector<int> &ladder_vars, int width, int number_splits)
{
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
    return sub_ladders;
}

void LadderSplitEncoder::connect_sub_ladders(const std::vector<std::pair<std::vector<int>, int>> &sub_ladders, std::vector<int> &ladder, int width)
{
    int avg_sub_ladder_width = sub_ladders[0].second;

    int number_connections = (int)ladder.size() - width + 1;
    int number_sub_ladders = (int)sub_ladders.size();
    for (int i = 0; i < number_sub_ladders; i++)
    {
        assert((int)sub_ladders[i].first.size() - sub_ladders[i].second + 1 == number_connections);
    }

    for (int i = 0; i < number_connections; i++)
    {
        std::vector<int> connected_expression(ladder.begin() + i, ladder.begin() + i + width);

        std::vector<std::vector<int>> sub_expressions;

        int first_expression_size = avg_sub_ladder_width - i % avg_sub_ladder_width;
        std::vector<int> first_expression(connected_expression.begin(), connected_expression.begin() + first_expression_size);
        sub_expressions.push_back(first_expression);

        int number_full_expressions = (width - first_expression_size) / avg_sub_ladder_width;
        for (int j = 0; j < number_full_expressions; j++)
        {
            std::vector<int> expression(connected_expression.begin() + first_expression_size + j * avg_sub_ladder_width, connected_expression.begin() + first_expression_size + (j + 1) * avg_sub_ladder_width);
            sub_expressions.push_back(expression);
        }

        int last_expression_size = (width - first_expression_size) % avg_sub_ladder_width;
        if (last_expression_size > 0)
        {
            std::vector<int> expression(connected_expression.end() - last_expression_size, connected_expression.end());
            sub_expressions.push_back(expression);
        }

        std::vector<int> clause;
        clause.push_back(-get_obj_k_aux_var(connected_expression));
        for (int j = 0; j < (int)sub_expressions.size(); j++)
        {
            InstanceData::cc->add_clause({-get_obj_k_aux_var(sub_expressions[j], true), get_obj_k_aux_var(connected_expression)});
            clause.push_back(get_obj_k_aux_var(sub_expressions[j]));
        }
        InstanceData::cc->add_clause(clause);
    }
}

void LadderSplitEncoder::connect_ladder(const std::vector<int> first_ladder_vars, const std::vector<int> second_ladder_vars, int width)
{
    assert(first_ladder_vars.size() == second_ladder_vars.size());

    int number_connections = first_ladder_vars.size() - width + 1;
    for (int i = 0; i < number_connections; i++)
    {
        InstanceData::cc->add_clause({-get_obj_k_aux_var(std::vector<int>(first_ladder_vars.begin() + i, first_ladder_vars.begin() + i + width), true),
                                      -get_obj_k_aux_var(std::vector<int>(second_ladder_vars.begin() + i, second_ladder_vars.begin() + i + width), true)});
    }
}