# SAT-CAB for Solving Cyclic AntiBandwidth

SAT-CAB is a SAT-based solver for the **Cyclic AntiBandwidth** problem.

The tool encodes the decision version of the problem (for a given width) into a CNF formula, then uses **CaDiCaL** as the SAT solver to evaluate it.

Other versions of CaDiCaL may be used by replacing `cadical.hpp` and `libcadical.a` in the `solver/cadical/` directory. Compatibility is not guaranteed.

---
## Benchmark for SAT Competition 2026

The benchmark instances submitted to SAT Competition 2026 are located in [selected_instances](sat_competition_2026_benchmark/harwell_boeing/selected_instances).

In addition, we provide a set of particularly challenging instances that were not submitted to the competition, available in [non_selected_instances](sat_competition_2026_benchmark/harwell_boeing/non_selected_instances).

Detailed information about all instances, including experimental configurations and general statistics, can be found in [HB_benchmark_information.xlsx](sat_competition_2026_benchmark/harwell_boeing/HB_benchmark_information.xlsx). This file contains two sheets: **Selected instances**, which lists the submitted benchmarks, and **All instances**, which includes both submitted and non-submitted instances.

---
## Experiment Results

The experiment results are located in [results](experiments/results). Note that `experiments/results/logs_150s`, `experiments/results/logs_1800s`, and `experiments/results/meta_heuristic` include the experiment results on the CAB problem, while `experiments/results/logs_single_width` includes the experiment results on a single CAB value.

We also include the tools to automatically run the experiments with all implemented configurations. They basically are several **.sh** files and located in [run_tool](experiments/run_tools) directory.

---

## Build

```bash
make
```

If you want a clean build, instead run:

```bash
make clean && make
```

The executable `cabw_enc` will be generated in the `build/` directory.

---

## Usage

```bash
./cabw_enc <graph-file> [options]
```

---

## Options

### General

```
--help
    Print usage message

--ladder
    Use ladder encoding (Our proposed encoding)

--check-solution
    Verify the computed solution for Cyclic Antibandwidth Problem
```

### Search Strategies

```
--iterate-from-lb
    Linear search starting from lower bound

--step-from-lb
    Stepwise increasing search from lower bound

--binary-search-from-lb
    Binary search starting from lower bound

--binary-search-from-ub
    Binary search starting from upper bound

--binary-search-bfs
    Binary search using BFS-style exploration
```

### Bounds

```
-set-lb <int>
    Set lower bound (must be >= 2)

-set-ub <int>
    Set upper bound (must be >= 2)
```

### Resource Limits

```
-limit-memory <int>
    Set memory limit

-limit-real-time <int>
    Set real time limit

-limit-elapsed-time <int>
    Set CPU elapsed time limit
```

### Logging

```
-sample-rate <int>
    Set sampling rate

-report-rate <int>
    Set reporting frequency
```

### Encoding / Performance

```
-split-size <int>
    Split clauses longer than given size

-worker-count <int>
    Number of parallel workers
```

### Symmetry Breaking

```
-symmetry-break none
    Disable symmetry breaking

-symmetry-break first
    Fix first vertex

-symmetry-break highest-degree
    Fix highest-degree vertex

-symmetry-break lowest-degree
    Fix lowest-degree vertex
```

---

### SAT Solver

```
-sat-solver <sat solver>
    Specify the SAT solver to use (currently only supports 'cadical')
```

---

### Print dimacs

```
-just-print-dimacs <dimacs directory>
    Encodes and prints dimacs to given directory without solving it.
```

---