#include "ladder_encoder.h"
#include "../global_data.h"
#include "instance_data.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cmath>

LadderEncoder::LadderEncoder() {}
LadderEncoder::~LadderEncoder() {}

void LadderEncoder::encode_cyclic_antibandwidth()
{
    if (InstanceData::width < 1 || InstanceData::width > GlobalData::g->n)
    {
        std::cout << "c Non-valid value of w, nothing to encode." << std::endl;
        return;
    }
    do_encode_antibandwidth();
}

void LadderEncoder::do_encode_antibandwidth()
{
    aux_vars.clear();
    obj_k_aux_vars.clear();

    encode_vertices();

    // We embed labels into encode_stair to achieve better encoding
    // encode_labels();

    encode_obj_k();
};

int LadderEncoder::get_obj_k_aux_var(int first, int last)
{

    auto pair = obj_k_aux_vars.find({first, last});

    if (pair != obj_k_aux_vars.end())
        return pair->second;

    if (first == last)
        return first;

    int new_obj_k_aux_var = InstanceData::vh->get_new_var();
    obj_k_aux_vars.insert({{first, last}, new_obj_k_aux_var});
    return new_obj_k_aux_var;
}

void LadderEncoder::encode_vertices()
{
    for (int i = 0; i < GlobalData::g->n; i++)
    {
        std::vector<int> node_vertices_eo(GlobalData::g->n);
        int j = 0;

        std::generate(node_vertices_eo.begin(), node_vertices_eo.end(), [this, &j, i]()
                      { return (j++ * GlobalData::g->n) + i + 1; });

        encode_exactly_one_product(node_vertices_eo);
    }
}

void LadderEncoder::encode_labels()
{
    for (int i = 0; i < GlobalData::g->n; i++)
    {
        std::vector<int> node_labels_eo(GlobalData::g->n);
        std::iota(node_labels_eo.begin(), node_labels_eo.end(), (i * GlobalData::g->n) + 1);

        encode_exactly_one_product(node_labels_eo);
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
        aux_vars.insert({new_var, new_var});
    }
    for (int j = 1; j <= q; ++j)
    {
        int new_var = InstanceData::vh->get_new_var();
        v_vars.push_back(new_var);
        aux_vars.insert({new_var, new_var});
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
        aux_vars.insert({next, next});
        InstanceData::cc->add_clause({-1 * prev, -1 * curr});
        InstanceData::cc->add_clause({-1 * prev, next});
        InstanceData::cc->add_clause({-1 * curr, next});

        prev = next;
    }
    InstanceData::cc->add_clause({-1 * prev, -1 * vars[vars.size() - 1]});
};

void LadderEncoder::encode_obj_k()
{
    for (int i = 0; i < GlobalData::g->n; i++)
    {
        encode_stair(i);
    }

    for (auto edge : GlobalData::g->edges)
    {
        glue_stair(edge.first - 1, edge.second - 1);
    }
}

void LadderEncoder::encode_stair(int stair)
{
    if (is_debug_mode)
        std::cout << "Encode stair " << stair << " with width " << InstanceData::width << std::endl;

    for (int gw = 0; gw < ceil((float)(GlobalData::g->n + InstanceData::width - 1) / InstanceData::width); gw++)
    {
        if (is_debug_mode)
            std::cout << "Encode window " << gw << std::endl;
        encode_window(gw, stair);
    }

    for (int gw = 0; gw < ceil((float)(GlobalData::g->n + InstanceData::width - 1) / InstanceData::width) - 1; gw++)
    {
        if (is_debug_mode)
            std::cout << "Glue window " << gw << " with window " << gw + 1 << std::endl;
        glue_window(gw, stair);
    }

    // Embedded labels using constructed windows
    std::vector<std::pair<int, int>> windows = {};
    int number_windows = ceil((float)GlobalData::g->n / InstanceData::width);

    for (int i = 0; i < number_windows; i++)
    {
        int stair_anchor = stair * GlobalData::g->n;
        int window_anchor = i * InstanceData::width;
        if (window_anchor + InstanceData::width > GlobalData::g->n)
            windows.push_back({stair_anchor + window_anchor + 1, stair_anchor + GlobalData::g->n});
        else
            windows.push_back({stair_anchor + window_anchor + 1, stair_anchor + window_anchor + InstanceData::width});
    }

    std::vector<int> alo_clause = {};
    for (int i = 0; i < number_windows; i++)
    {
        int first_window_aux_var = get_obj_k_aux_var(windows[i].first, windows[i].second);
        alo_clause.push_back(first_window_aux_var);
        for (int j = i + 1; j < number_windows; j++)
        {
            int second_window_aux_var = get_obj_k_aux_var(windows[j].first, windows[j].second);
            InstanceData::cc->add_clause({-first_window_aux_var, -second_window_aux_var});
        }
    }
    InstanceData::cc->add_clause(alo_clause);
}

/*
 * Encode each window separately.
 * The first window only has lower part.
 * The last window only has upper part.
 * Other windows have both upper part and lower part.
 */
void LadderEncoder::encode_window(int window, int stair)
{
    /*
        Offset of the stair.
        Actual variable = stair offset + index of that variable in the stair.

        *************************************************
        1   2   3   4
            2   3   4   5
                3   4   5   6
                    4   5   6   7
                        5   6   7   8
                            6   7   8   9
                                7   8   9   10
                                    8   9   10  1
                                        9   10  1   2
                                            10  1   2   3
        *************************************************

        The index of the variable should be modified by g->n to get the correct index in the stair.
        For example, the 12th variable in the stair with 10 nodes has index 12 % 10 = 2.
    */
    int offset = stair * GlobalData::g->n;

    if (window == 0)
    {
        // Encode the first window, which only have lower part
        int lastVar = window * InstanceData::width + InstanceData::width;

        for (int i = InstanceData::width - 1; i >= 1; i--)
        {
            int var = window * InstanceData::width + i;
            InstanceData::cc->add_clause({-(offset + get_circle_variable(var)),
                                          get_obj_k_aux_var(offset + get_circle_variable(var), offset + get_circle_variable(lastVar))});
        }

        for (int i = InstanceData::width; i >= 2; i--)
        {
            int var = window * InstanceData::width + i;
            InstanceData::cc->add_clause({-get_obj_k_aux_var(offset + get_circle_variable(var), offset + get_circle_variable(lastVar)),
                                          get_obj_k_aux_var(offset + get_circle_variable(var - 1), offset + get_circle_variable(lastVar))});
        }

        for (int i = 1; i < InstanceData::width; i++)
        {
            int var = window * InstanceData::width + i;
            int main = get_obj_k_aux_var(offset + get_circle_variable(var), offset + get_circle_variable(lastVar));
            int sub = get_obj_k_aux_var(offset + get_circle_variable(var + 1), offset + get_circle_variable(lastVar));
            InstanceData::cc->add_clause({offset + get_circle_variable(var), sub, -main});
        }

        for (int i = 1; i < InstanceData::width; i++)
        {
            int var = window * InstanceData::width + i;
            InstanceData::cc->add_clause({-(int)(offset + get_circle_variable(var)),
                                          -get_obj_k_aux_var(offset + get_circle_variable(var + 1), offset + get_circle_variable(lastVar))});
        }
    }
    else if (window == ceil((float)(GlobalData::g->n + InstanceData::width - 1) / InstanceData::width) - 1)
    {
        // Encode the last window, which only have upper part and may have width lower than w
        int firstVar = window * InstanceData::width + 1;

        if ((window + 1) * InstanceData::width > GlobalData::g->n + InstanceData::width - 1)
        {
            int real_w = (GlobalData::g->n + InstanceData::width - 1) % InstanceData::width;
            // Upper part
            for (int i = 2; i <= real_w; i++)
            {
                int reverse_var = window * InstanceData::width + i;
                InstanceData::cc->add_clause({-(offset + get_circle_variable(reverse_var)),
                                              get_obj_k_aux_var(offset + get_circle_variable(firstVar), offset + get_circle_variable(reverse_var))});
            }

            for (int i = real_w - 1; i > 0; i--)
            {
                int reverse_var = window * InstanceData::width + real_w - i;
                InstanceData::cc->add_clause({-get_obj_k_aux_var(offset + get_circle_variable(firstVar), offset + get_circle_variable(reverse_var)),
                                              get_obj_k_aux_var(offset + get_circle_variable(firstVar), offset + get_circle_variable(reverse_var + 1))});
            }

            for (int i = 0; i < (int)real_w - 1; i++)
            {
                int var = window * InstanceData::width + real_w - i;
                int main = get_obj_k_aux_var(offset + get_circle_variable(firstVar), offset + get_circle_variable(var));
                int sub = get_obj_k_aux_var(offset + get_circle_variable(firstVar), offset + get_circle_variable(var - 1));
                InstanceData::cc->add_clause({offset + get_circle_variable(var), sub, -main});
            }

            for (int i = real_w; i > 1; i--)
            {
                int reverse_var = window * InstanceData::width + i;
                InstanceData::cc->add_clause({-(int)(offset + get_circle_variable(reverse_var)),
                                              -get_obj_k_aux_var(offset + get_circle_variable(firstVar), offset + get_circle_variable(reverse_var - 1))});
            }
        }
        else
        {
            // Upper part
            for (int i = 2; i <= InstanceData::width; i++)
            {
                int reverse_var = window * InstanceData::width + i;
                InstanceData::cc->add_clause({-(offset + get_circle_variable(reverse_var)),
                                              get_obj_k_aux_var(offset + get_circle_variable(firstVar), offset + get_circle_variable(reverse_var))});
            }

            for (int i = InstanceData::width - 1; i >= 1; i--)
            {
                int reverse_var = window * InstanceData::width + InstanceData::width - i;
                InstanceData::cc->add_clause({-get_obj_k_aux_var(offset + get_circle_variable(firstVar), offset + get_circle_variable(reverse_var)),
                                              get_obj_k_aux_var(offset + get_circle_variable(firstVar), offset + get_circle_variable(reverse_var + 1))});
            }

            for (int i = 0; i < InstanceData::width - 1; i++)
            {
                int var = window * InstanceData::width + InstanceData::width - i;
                int main = get_obj_k_aux_var(offset + get_circle_variable(firstVar), offset + get_circle_variable(var));
                int sub = get_obj_k_aux_var(offset + get_circle_variable(firstVar), offset + get_circle_variable(var - 1));
                InstanceData::cc->add_clause({offset + get_circle_variable(var), sub, -main});
            }

            for (int i = InstanceData::width; i > 1; i--)
            {
                int reverse_var = window * InstanceData::width + i;
                InstanceData::cc->add_clause({-(offset + get_circle_variable(reverse_var)),
                                              -get_obj_k_aux_var(offset + get_circle_variable(firstVar), offset + get_circle_variable(reverse_var - 1))});
            }
        }
    }
    else
    {
        // Encode the middle windows, which have both upper and lower path, and always have width w

        // Upper part
        int firstVar = window * InstanceData::width + 1;
        for (int i = 2; i <= InstanceData::width; i++)
        {
            int reverse_var = window * InstanceData::width + i;
            InstanceData::cc->add_clause({-(offset + get_circle_variable(reverse_var)),
                                          get_obj_k_aux_var(offset + get_circle_variable(firstVar), offset + get_circle_variable(reverse_var))});
        }

        for (int i = InstanceData::width - 1; i >= 1; i--)
        {
            int reverse_var = window * InstanceData::width + InstanceData::width - i;
            InstanceData::cc->add_clause({-get_obj_k_aux_var(offset + get_circle_variable(firstVar), offset + get_circle_variable(reverse_var)),
                                          get_obj_k_aux_var(offset + get_circle_variable(firstVar), offset + get_circle_variable(reverse_var + 1))});
        }

        for (int i = 0; i < InstanceData::width - 1; i++)
        {
            int var = window * InstanceData::width + InstanceData::width - i;
            int main = get_obj_k_aux_var(offset + get_circle_variable(firstVar), offset + get_circle_variable(var));
            int sub = get_obj_k_aux_var(offset + get_circle_variable(firstVar), offset + get_circle_variable(var - 1));
            InstanceData::cc->add_clause({offset + get_circle_variable(var), sub, -main});
        }

        for (int i = InstanceData::width; i > 1; i--)
        {
            int reverse_var = window * InstanceData::width + i;
            InstanceData::cc->add_clause({-(offset + get_circle_variable(reverse_var)),
                                          -get_obj_k_aux_var(offset + get_circle_variable(firstVar), offset + get_circle_variable(reverse_var - 1))});
        }

        // Lower part
        int lastVar = window * InstanceData::width + InstanceData::width;
        for (int i = InstanceData::width - 1; i >= 1; i--)
        {
            int var = window * InstanceData::width + i;
            InstanceData::cc->add_clause({-(offset + get_circle_variable(var)),
                                          get_obj_k_aux_var(offset + get_circle_variable(var), offset + get_circle_variable(lastVar))});
        }

        for (int i = InstanceData::width; i >= 2; i--)
        {
            int var = window * InstanceData::width + i;
            InstanceData::cc->add_clause({-get_obj_k_aux_var(offset + get_circle_variable(var), offset + get_circle_variable(lastVar)),
                                          get_obj_k_aux_var(offset + get_circle_variable(var - 1), offset + get_circle_variable(lastVar))});
        }

        for (int i = 1; i < InstanceData::width; i++)
        {
            int var = window * InstanceData::width + i;
            int main = get_obj_k_aux_var(offset + get_circle_variable(var), offset + get_circle_variable(lastVar));
            int sub = get_obj_k_aux_var(offset + get_circle_variable(var + 1), offset + get_circle_variable(lastVar));
            InstanceData::cc->add_clause({offset + get_circle_variable(var), sub, -main});
        }

        // Can be disable
        // for (int i = 1; i < (int)w; i++)
        // {
        //     int var = window * (int)w + i;
        //     InstanceData::cc->add_clause({-(offset + get_circle_variable(var)),
        //                     -get_obj_k_aux_var(offset + get_circle_variable(var + 1), offset + get_circle_variable(lastVar))});
        //     num_obj_k_constraints++;
        // }
    }
}

/*
 * Glue adjacent windows with each other.
 * Using lower part of the previous window and upper part of the next window
 * as anchor points to glue.
 */
void LadderEncoder::glue_window(int window, int stair)
{
    /*  The stair look like this:
     *          Window 1            Window 2            Window 3            Window 4
     *      1   2   3   4   |                   |                   |                   |
     *          2   3   4   |   5               |                   |                   |
     *              3   4   |   5   6           |                   |                   |
     *                  4   |   5   6   7       |                   |                   |
     *                      |   5   6   7   8   |                   |                   |
     *                      |       6   7   8   |   9               |                   |
     *                      |           7   8   |   9   10          |                   |
     *                      |               8   |   9   10  1       |                   |
     *                      |                   |   9   10  1   2   |                   |
     *                      |                   |       10  1   2   |   3  `            |
     *
     */
    int offset = stair * GlobalData::g->n;
    if ((window + 2) * InstanceData::width > GlobalData::g->n + InstanceData::width - 1)
    {
        int real_w = (GlobalData::g->n + InstanceData::width - 1) % InstanceData::width;
        for (int i = 1; i <= real_w; i++)
        {
            int first_reverse_var = (window + 1) * InstanceData::width + 1;
            int last_var = window * InstanceData::width + InstanceData::width;

            int reverse_var = (window + 1) * InstanceData::width + i;
            int var = window * InstanceData::width + i + 1;

            InstanceData::cc->add_clause({-get_obj_k_aux_var(offset + get_circle_variable(var), offset + get_circle_variable(last_var)),
                                          -get_obj_k_aux_var(offset + get_circle_variable(first_reverse_var), offset + get_circle_variable(reverse_var))});
        }
    }
    else
    {
        for (int i = 1; i < InstanceData::width; i++)
        {
            int first_reverse_var = (window + 1) * InstanceData::width + 1;
            int last_var = window * InstanceData::width + InstanceData::width;

            int reverse_var = (window + 1) * InstanceData::width + i;
            int var = window * InstanceData::width + i + 1;

            InstanceData::cc->add_clause({-get_obj_k_aux_var(offset + get_circle_variable(var), offset + get_circle_variable(last_var)),
                                          -get_obj_k_aux_var(offset + get_circle_variable(first_reverse_var), offset + get_circle_variable(reverse_var))});
        }
    }
}

void LadderEncoder::glue_stair(int stair1, int stair2)
{
    if (is_debug_mode)
        std::cout << "Glue stair " << stair1 << " with stair " << stair2 << std::endl;
    int number_step = GlobalData::g->n;
    for (int i = 0; i < number_step; i++)
    {
        int mod = i % InstanceData::width;
        int subset = i / InstanceData::width;
        int stair1_offset = stair1 * GlobalData::g->n;
        int stair2_offset = stair2 * GlobalData::g->n;
        if (mod == 0)
        {
            int firstVar = get_obj_k_aux_var(stair1_offset + get_circle_variable(subset * InstanceData::width + 1), stair1_offset + get_circle_variable(subset * InstanceData::width + InstanceData::width));
            int secondVar = get_obj_k_aux_var(stair2_offset + get_circle_variable(subset * InstanceData::width + 1), stair2_offset + get_circle_variable(subset * InstanceData::width + InstanceData::width));
            InstanceData::cc->add_clause({-firstVar, -secondVar});
        }
        else
        {
            int firstVar = get_obj_k_aux_var(stair1_offset + get_circle_variable(subset * InstanceData::width + 1 + mod), stair1_offset + get_circle_variable(subset * InstanceData::width + InstanceData::width));
            int secondVar = get_obj_k_aux_var(stair1_offset + get_circle_variable(subset * InstanceData::width + InstanceData::width + 1), stair1_offset + get_circle_variable(subset * InstanceData::width + InstanceData::width + mod));
            int thirdVar = get_obj_k_aux_var(stair2_offset + get_circle_variable(subset * InstanceData::width + 1 + mod), stair2_offset + get_circle_variable(subset * InstanceData::width + InstanceData::width));
            int forthVar = get_obj_k_aux_var(stair2_offset + get_circle_variable(subset * InstanceData::width + InstanceData::width + 1), stair2_offset + get_circle_variable(subset * InstanceData::width + InstanceData::width + mod));
            InstanceData::cc->add_clause({-firstVar, -thirdVar});
            InstanceData::cc->add_clause({-firstVar, -forthVar});
            InstanceData::cc->add_clause({-secondVar, -thirdVar});
            InstanceData::cc->add_clause({-secondVar, -forthVar});
        }
    }
}

int LadderEncoder::get_circle_variable(int var)
{
    return (var - 1) % GlobalData::g->n + 1;
}