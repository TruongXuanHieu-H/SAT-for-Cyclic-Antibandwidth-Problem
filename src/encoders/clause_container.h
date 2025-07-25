#ifndef CLAUSE_CONTAINER_H
#define CLAUSE_CONTAINER_H

#include <vector>
#include "var_handler.h"

typedef std::vector<int> Clause;
typedef std::vector<Clause> Clauses;

class ClauseContainer
{
public:
    ClauseContainer();
    ~ClauseContainer();

    Clauses clause_list;

    void add_clause(const Clause &c);
    void print_dimacs();
    void print_clauses();
    int size();

protected:
    VarHandler *vh;

    ClauseContainer(VarHandler *, int split_size = 0);
    bool do_split = false;

private:
    void do_add_clause(const Clause &c);
    void do_print_dimacs();
    void do_print_clauses();
    int do_size();
    void do_clear();
};

#endif // CLAUSE_CONTAINER_H