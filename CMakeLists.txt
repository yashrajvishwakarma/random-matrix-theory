cmake_minimum_required(VERSION 3.15)
project(RMT)
set(CMAKE_CXX_STANDARD 17)


add_subdirectory(matplotplusplus)
find_package(Eigen3 REQUIRED)
find_package(BLAS REQUIRED)
find_package(OpenMP REQUIRED)

add_executable(main main.cpp)
add_executable(eigendist eigendist.cpp)

target_link_libraries(main
    Matplot++::matplot
    Eigen3::Eigen
    ${BLAS_LIBRARIES}
    OpenMP::OpenMP_CXX
)
target_compile_options(main PRIVATE -O3 -march=native)

target_link_libraries(eigendist
    Matplot++::matplot
    Eigen3::Eigen
    ${BLAS_LIBRARIES}
    OpenMP::OpenMP_CXX
)
target_compile_options(eigendist PRIVATE -O3 -march=native)