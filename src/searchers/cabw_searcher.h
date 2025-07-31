#ifndef CABW_SEARCHER_H
#define CABW_SEARCHER_H

#include <limits>
#include <unordered_map>
#include <unistd.h>

class CabwSearcher
{
public:
    CabwSearcher();
    virtual ~CabwSearcher();

    virtual void encode_and_solve() = 0;

protected:
    int max_width_SAT = std::numeric_limits<int>::min();
    int min_width_UNSAT = std::numeric_limits<int>::max();

    int start_w;
    int stop_w;

    std::unordered_map<int, pid_t> abp_pids;
    pid_t lim_pid;

    int sampler_count = 0;

    float *max_consumed_memory;
    float consumed_memory = 0;       // total memory consumed by all the processes, in megabyte
    float consumed_real_time = 0;    // time consumed by main process, in seconds
    float consumed_elapsed_time = 0; // total time consumed by all the process, in seconds

    int is_limit_satisfied();

    void lookup_bounds(int &lb, int &ub);
    void setup_bounds(int &w_from, int &w_to);
};
#endif // CABW_SEARCHER_H