This repository contains C++ code, optimized using OpenMP, which performs various fast computations to verify foundational results in random matrix theory. Currently, main.cpp constructs a 50000x50000 selfadjoint matrix containing Gaussian entries, performs eigendecomposition and plots a normalized histogram which obeys Wigner's semicircle law. The second file, eigendist.cpp, repeats the same procedure as main.cpp for N = 3, 9, 100, but also computes an averaged eigenvalue histogram for each N after 20000 simulations. This repository will also contain code for the following: 
- Histograms for various random matrix ensembles (GUE, GOE)
- Eigenvalue repulsion
- Modelling the energy levels of heavy nuclei
