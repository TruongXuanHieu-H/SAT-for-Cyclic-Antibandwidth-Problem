#include "instance_data.h"
#include "../global_data.h"

#include "sat_solver_cadical.h"

#include "ladder_encoder.h"

InstanceData::~InstanceData()
{
    if (enc)
        delete enc;
    if (cc)
        delete cc;
    if (vh)
        delete vh;
    if (solver)
        delete solver;
}

int InstanceData::width = 0;

InstanceEncoder *InstanceData::enc = nullptr;
ClauseContainer *InstanceData::cc = nullptr;
VarHandler *InstanceData::vh = nullptr;
SATSolver *InstanceData::solver = nullptr;

std::string InstanceData::get_signature()
{
    return "[w = " + std::to_string(width) + "]";
};

void InstanceData::set_up_encoder()
{
    switch (GlobalData::encode_type)
    {
    case EncodeType::Ladder:
        enc = new LadderEncoder();
        break;

    default:
        break;
    }
};

void InstanceData::setup_for_solving()
{
    cc = new ClauseContainer();
    vh = new VarHandler(1, GlobalData::g->n);
    solver = new SATSolverCadical();

    set_up_encoder();
}

void InstanceData::cleanup_solving()
{
    delete enc;
    delete cc;
    delete vh;
    delete solver;
}