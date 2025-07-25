#ifndef INSTANCE_ENCODER_H
#define INSTANCE_ENCODER_H

class InstanceEncoder
{
public:
    InstanceEncoder();
    virtual ~InstanceEncoder();

    virtual void encode_cyclic_antibandwidth();
};

#endif // INSTANCE_ENCODER_H