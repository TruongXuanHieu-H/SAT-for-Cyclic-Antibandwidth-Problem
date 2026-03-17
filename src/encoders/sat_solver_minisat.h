#ifndef SAT_SOLVER_MINISAT_H
#define SAT_SOLVER_MINISAT_H

#include "sat_solver.h"
#include "../../src_solver/minisat/minisat/core/Solver.h"

class SATSolverMinisat : public SATSolver
{
public:
    SATSolverMinisat();
    ~SATSolverMinisat() override;

    void set_up_solver() override;
    void add_clause(const Clause &c) override;
    int solve() override;
    std::vector<int> extract_result() override;
    void clear_solver() override;

    Minisat::Solver *solver;
};

#endif // SAT_SOLVER_MINISAT_H