#ifndef INSTANCE_DATA_H
#define INSTANCE_DATA_H

#include "../graph/graph.h"
#include "instance_encoder.h"
#include "clause_container.h"
#include "var_handler.h"
#include "sat_solver.h"

class InstanceData
{
public:
    InstanceData();
    ~InstanceData();

    static int width; // Width of the instance

    static InstanceEncoder *enc;
    static ClauseContainer *cc;
    static VarHandler *vh;
    static SATSolver *solver;

    static std::string get_signature();

    static void set_up_encoder();
    static void setup_for_solving();
    static void cleanup_solving();
};

#endif // INSTANCE_DATA_H