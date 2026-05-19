#define EIGEN_USE_BLAS
#include <iostream>
#include <random>
#include <Eigen/Dense>
#include <matplot/matplot.h>
#include <vector>
#include <cmath>

using Eigen::MatrixXd;

std::mt19937 rng(101);
std::uniform_int_distribution<int> uniform (1000,5000);
std::normal_distribution<double> gaussian(0.0, 1.0);

int main() {
    int size = 5000;
    MatrixXd mat = MatrixXd::Random(size, size);
    for (int i = 0; i < size; i++) {
        mat(i, i) = gaussian(rng);      
        for (int j = i + 1; j < size; j++) {
            double val = gaussian(rng);
            mat(i, j) = val;       
            mat(j, i) = val;             
        }
    }
    mat /= std::sqrt((double)size);
    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> solve(mat, Eigen::EigenvaluesOnly);
    Eigen::VectorXd eigenvalues = solve.eigenvalues(); 
    std::vector<double> eig(eigenvalues.data(), eigenvalues.data() + eigenvalues.size());
    auto h = matplot::hist(eig);
    h->normalization(matplot::histogram::normalization::pdf);
    matplot::hold(true);
    auto curve = matplot::fplot([](double x) { return (2.0 / matplot::pi) * std::sqrt(4 - std::pow(x, 2)) / 4.0; }, std::array<double, 2>{-2, 2});
    curve->line_width(3);
    matplot::show();


}

