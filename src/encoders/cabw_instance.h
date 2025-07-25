#ifndef CABW_INSTANCE_H
#define CABW_INSTANCE_H

#include "../graph/graph.h"
#include "../enum/encode_type.h"
#include "instance_encoder.h"
#include "clause_container.h"
#include "sat_solver.h"

#include <string>

class CABWInstance
{
public:
    CABWInstance(int width);
    virtual ~CABWInstance();

    int encode_and_solve_cabp();

private:
    int SAT_res = 0;

    int verify_solution();
    bool extract_node_labels(std::vector<int> &node_labels);
};
#endif // CABW_INSTANCE_H