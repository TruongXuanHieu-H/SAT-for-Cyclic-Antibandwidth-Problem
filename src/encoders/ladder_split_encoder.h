#ifndef LADDER_SPLIT_ENCODER_H
#define LADDER_SPLIT_ENCODER_H

#include "ladder_encoder.h"

#include <vector>

class LadderSplitEncoder : public LadderEncoder
{
public:
    LadderSplitEncoder();
    ~LadderSplitEncoder() override;

private:
    int number_sub_ladders = 2;

    void encode_labels() override;
    void encode_obj_k() override;
    void connect_ladder(const std::vector<int> first_ladder_vars, const std::vector<int> second_ladder_vars, int width) override;

    std::vector<std::vector<int>> get_ladders_vars(int number_ladder, int width);
    std::vector<std::pair<std::vector<int>, int>> split_into_sub_ladders(const std::vector<int> &ladder_vars, int width, int number_splits);
    std::pair<std::vector<int>, int> get_compact_sub_ladder(std::vector<std::pair<std::vector<int>, int>> &sub_ladders);
    void connect_sub_ladders(const std::vector<std::pair<std::vector<int>, int>> &sub_ladders, std::vector<int> &ladder, int width);
};

#endif // LADDER_SPLIT_ENCODER_H