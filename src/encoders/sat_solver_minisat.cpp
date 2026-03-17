#include "sat_solver_minisat.h"
#include "instance_data.h"
#include "../global_data.h"
#include <iostream>
#include <csignal>

SATSolverMinisat::SATSolverMinisat()
{
    set_up_solver();
}

SATSolverMinisat::~SATSolverMinisat()
{
    clear_solver();
}

void SATSolverMinisat::set_up_solver()
{
    solver = new Minisat::Solver();
    std::cout << "c " << InstanceData::get_signature() << " Initializing Minisat.\n";
}

void SATSolverMinisat::clear_solver()
{
    delete solver;
    solver = nullptr;
}

void SATSolverMinisat::add_clause(const Clause &c)
{
    Minisat::vec<Minisat::Lit> clause;
    for (const auto &lit : c)
    {
        int var = std::abs(lit) - 1;
        while (var >= solver->nVars())
            solver->newVar();
        clause.push((lit > 0) ? Minisat::mkLit(var) : ~Minisat::mkLit(var));        
    }
    solver->addClause(clause);
}

int SATSolverMinisat::solve()
{
    bool res = solver->solve();
    if (res)
        return 10; 
    else
        return 20;
}

std::vector<int> SATSolverMinisat::extract_result()
{
    std::vector<int> result(GlobalData::g->n, -1);

    for (int node = 0; node < GlobalData::g->n; ++node)
    {
        int assigned_label = -1;
        for (int label = 1; label <= GlobalData::g->n; ++label)
        {
            int var = node * GlobalData::g->n + (label - 1);
            if (var >= solver->nVars())
                continue;

            Minisat::lbool val = solver->modelValue(var);
            if (val == Minisat::l_True)
            {
                if (assigned_label != -1)
                {
                    std::cerr << "e " << InstanceData::get_signature()
                              << " Error: Multiple labels for node " << node << "\n";
                    raise(SIGABRT);
                }
                assigned_label = label;
            }
        }

        result[node] = assigned_label;
    }

    return result;
}
