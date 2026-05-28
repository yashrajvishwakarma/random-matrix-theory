#define EIGEN_USE_BLAS
#include <iostream>
#include <random>
#include <Eigen/Dense>
#include <matplot/matplot.h>
#include <vector>
#include <cmath>
#include <omp.h>
#include <chrono>


using Eigen::MatrixXf;

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    int size = 5000;
    MatrixXf mat(size, size);
    #pragma omp parallel 
    {
    std::mt19937 rng(101 + omp_get_thread_num());
    std::normal_distribution<float> gaussian(0.0, 1.0);
    #pragma omp for schedule(static)
    for (int i = 0; i < size; i++) {
        mat(i, i) = gaussian(rng);      
        for (int j = i + 1; j < size; j++) {
            float val = gaussian(rng);
            mat(i, j) = val;  
            mat(j, i) = val;     
        }
    }
}
    float scale = 1.0f / std::sqrt((float)size);
    mat *= scale;
    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXf> solve(mat, Eigen::EigenvaluesOnly);
    Eigen::VectorXf eigenvalues = solve.eigenvalues(); 
    std::vector<float> eig(eigenvalues.data(), eigenvalues.data() + eigenvalues.size());
    auto h = matplot::hist(eig);
    h->normalization(matplot::histogram::normalization::pdf);
    matplot::hold(true);
    auto curve = matplot::fplot([](double x) { return (2.0 / matplot::pi) * std::sqrt(4 - x * x) / 4.0;}, std::array<double, 2>{-2, 2});
    curve->line_width(3);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<float> elapsed = end - start;

    std::cout << "Total runtime: " << elapsed.count() << " seconds\n";
    matplot::show();


    return 0;

}

