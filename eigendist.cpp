#define EIGEN_USE_BLAS
#include <iostream>
#include <random>
#include <Eigen/Dense>
#include <matplot/matplot.h>
#include <vector>
#include <cmath>
#include <chrono>
#include <omp.h>

using Eigen::MatrixXf;

MatrixXf selfadjoint(int size, std::mt19937& rng) {
    MatrixXf mat(size, size);
    std::normal_distribution<float> gaussian(0.0, 1.0);
    for (int i = 0; i < size; i++) {
        mat(i, i) = gaussian(rng);
        for (int j = i + 1; j < size; j++) {
            float val = gaussian(rng);
            mat(i, j) = val;
            mat(j, i) = val;
        }
    }
    return mat;
}

std::vector<float> get_eigenvalues(int N, std::mt19937& rng) {
    MatrixXf m = selfadjoint(N, rng);
    m /= std::sqrt((float)N);
    Eigen::SelfAdjointEigenSolver<MatrixXf> solver(m);
    std::vector<float> eigs(solver.eigenvalues().data(),
                            solver.eigenvalues().data() + N);
    return eigs;
}

std::vector<float> get_pooled_eigenvalues(int size, int num_simulations) {
    std::vector<float> pooled(num_simulations * size);

    #pragma omp parallel
    {
        std::mt19937 rng(42 + omp_get_thread_num() * 1000);

        #pragma omp for schedule(dynamic, 32)
        for (int k = 0; k < num_simulations; k++) {
            auto eigs = get_eigenvalues(size, rng);
            std::copy(eigs.begin(), eigs.end(), pooled.begin() + k * size);
        }
    }
    return pooled;
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    std::mt19937 rng_single(42);
    std::vector<float> eigen3 = get_eigenvalues(3, rng_single);
    std::vector<float> eigen9 = get_eigenvalues(9, rng_single);
    std::vector<float> eigen100 = get_eigenvalues(100, rng_single);

    std::vector<float> eigen3avg = get_pooled_eigenvalues(3,   20000);
    std::vector<float> eigen9avg = get_pooled_eigenvalues(9,   20000);
    std::vector<float> eigen100avg = get_pooled_eigenvalues(100, 20000);

    auto f = matplot::figure();
    f->size(1200, 600);

    auto ax1 = f->add_subplot(2, 3, 0);
    auto ax2 = f->add_subplot(2, 3, 1);
    auto ax3 = f->add_subplot(2, 3, 2);
    auto ax4 = f->add_subplot(2, 3, 3);
    auto ax5 = f->add_subplot(2, 3, 4);
    auto ax6 = f->add_subplot(2, 3, 5);

    f->current_axes(ax1);
    ax1->hist(eigen3);
    ax1->title("N=3");

    f->current_axes(ax2);
    ax2->hist(eigen9);
    ax2->title("N=9");

    f->current_axes(ax3);
    ax3->hist(eigen100);
    ax3->title("N=100");

    f->current_axes(ax4);
    ax4->hist(eigen3avg);
    ax4->title("N=3, averaged");

    f->current_axes(ax5);
    ax5->hist(eigen9avg);
    ax5->title("N=9, averaged");

    f->current_axes(ax6);
    ax6->hist(eigen100avg);
    ax6->title("N=100, averaged");

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed = end - start;
    std::cout << "Total runtime: " << elapsed.count() << " seconds\n";

    matplot::save("eigenplot.png");
    matplot::show();
}