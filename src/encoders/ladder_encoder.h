#ifndef LADDER_ENCODER_H
#define LADDER_ENCODER_H

#include "instance_encoder.h"

class LadderEncoder : public InstanceEncoder
{
public:
    LadderEncoder();
    ~LadderEncoder() override;

    void encode_cyclic_antibandwidth() override;
};
#endif