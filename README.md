# Cyclic AntiBandwidth


For the integration of SAT solvers:
- CaDiCaL: CaDiCaL version 2.1.3 has already included in ./solver/cadical. This folder include both .hpp (header file) and lib file of CaDiCaL.
- Minisat: Minisat is integrated through repository available at https://github.com/niklasso/minisat. This process is done with the process below:
    + Clone Minisat repository to ./src_solver/minisat (we have to clone this repo because the release version does not provide .hpp file likes CaDiCaL).
    + Build Minisat using makefile provided inside Minisat repository.
    + Minisat solver now ready to be used in our encoder (remember to rebuild encoder using makefile provided in root directory).
