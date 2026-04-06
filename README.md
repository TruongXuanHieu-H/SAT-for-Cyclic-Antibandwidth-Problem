# SAT-CAB for Solving Cyclic AntiBandwidth

SAT-CAB is a SAT-based solver for the **Cyclic AntiBandwidth** problem.

The tool encodes the decision version of the problem (for a given width) into a CNF formula, then uses **CaDiCaL** as the SAT solver to evaluate it.

Other versions of CaDiCaL may be used by replacing `cadical.hpp` and `libcadical.a` in the `cadical/` directory. Compatibility is not guaranteed.

---

## Build

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
    Use ladder encoding

--check-solution
    Verify the computed solution
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
