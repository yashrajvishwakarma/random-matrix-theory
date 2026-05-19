cmake_minimum_required(VERSION 3.15)
project(RMT)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(matplotplusplus)
find_package(Eigen3 REQUIRED)

add_executable(RMT main.cpp)
target_link_libraries(RMT Matplot++::matplot Eigen3::Eigen)

target_compile_options(RMT PRIVATE -stdlib=libc++)
target_link_options(RMT PRIVATE -stdlib=libc++)

target_compile_options(RMT PRIVATE -O3 -march=native)

find_package(BLAS REQUIRED)
target_link_libraries(RMT Matplot++::matplot Eigen3::Eigen ${BLAS_LIBRARIES})