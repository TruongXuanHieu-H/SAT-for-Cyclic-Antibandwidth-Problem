#ifndef LADDER_ENCODER_H
#define LADDER_ENCODER_H

#include "instance_encoder.h"
#include <map>
#include <vector>

class LadderEncoder : public InstanceEncoder
{
public:
    LadderEncoder();
    ~LadderEncoder() override;

    void encode_cyclic_antibandwidth() override;

private:
    bool is_debug_mode = false;

    // Use to save aux vars of LABELS and VERTICES constraints
    std::map<int, int> aux_vars = {};

    // Use to save aux vars of OBJ-K constraints
    std::map<std::pair<int, int>, int> obj_k_aux_vars;

    void do_encode_antibandwidth();

    int get_obj_k_aux_var(int first, int last);

    void encode_vertices();
    void encode_labels();
    void encode_exactly_one_product(const std::vector<int> &vars);
    void encode_amo_seq(const std::vector<int> &vars);

    void encode_obj_k();
    void encode_stair(int stair);
    void encode_window(int window, int stair);
    void glue_window(int window, int stair);
    void glue_stair(int stair1, int stair2);

    int get_circle_variable(int var);
};
#endif