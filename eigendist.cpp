#define EIGEN_USE_BLAS
#include <iostream>
#include <random>
#include <Eigen/Dense>
#include <matplot/matplot.h>
#include <vector>
#include <cmath>

using Eigen::MatrixXd;

std::mt19937 rng(101);
std::normal_distribution<double> gaussian(0.0, 1.0);

MatrixXd selfadjoint(MatrixXd mat, int size) {
    for (int i = 0; i < size; i++) {
        mat(i, i) = gaussian(rng);
        for (int j = i + 1; j < size; j++) {
            double val = gaussian(rng);
            mat(i, j) = val;
            mat(j, i) = val;
        }
    }
    return mat;
}

std::vector<double> get_eigenvalues(int N) {
    MatrixXd m(N, N);
    m = selfadjoint(m, N);
    m /= std::sqrt((double)N);
    Eigen::SelfAdjointEigenSolver<MatrixXd> solver(m);
    std::vector<double> eigs(solver.eigenvalues().data(), solver.eigenvalues().data() + N);
    return eigs;
}

std::vector<double> get_pooled_eigenvalues(int size, int num_simulations) {
    std::vector<double> pooled;
    for (int k = 0; k < num_simulations; k++) {
        auto eigs = get_eigenvalues(size);
        pooled.insert(pooled.end(), eigs.begin(), eigs.end());
    }
    return pooled;
}

int main() {
    std::vector<double> eigen3    = get_eigenvalues(3);
    std::vector<double> eigen9    = get_eigenvalues(9);
    std::vector<double> eigen100  = get_eigenvalues(100);

    std::vector<double> eigen3avg   = get_pooled_eigenvalues(3, 50000);
    std::vector<double> eigen9avg   = get_pooled_eigenvalues(9, 20000);
    std::vector<double> eigen100avg = get_pooled_eigenvalues(100, 200);

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

    matplot::save("eigenplot.png");
}