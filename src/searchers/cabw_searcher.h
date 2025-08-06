#ifndef CABW_SEARCHER_H
#define CABW_SEARCHER_H

#include <unordered_map>
#include <unistd.h>
#include <deque>

class CabwSearcher
{
public:
    CabwSearcher();
    virtual ~CabwSearcher();

    void encode_and_solve();

protected:
    int max_width_SAT;
    int min_width_UNSAT;

    int lower_bound;
    int upper_bound;

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

    void create_limit_pid();
    void create_cabp_pid(int width);
    int do_cabp_pid_task(int width);

    std::deque<int> search_order; // Stores the order of widths to search
    int get_next_width_to_search();
    virtual std::deque<int> create_search_order() = 0;
};
#endif // CABW_SEARCHER_H