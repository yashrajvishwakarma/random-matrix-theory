cmake_minimum_required(VERSION 3.15)
project(RMT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -ffast-math")

find_package(Eigen3 REQUIRED)
find_package(OpenMP REQUIRED)

add_subdirectory(matplotplusplus)

add_executable(main main.cpp)
add_executable(eigendist eigendist.cpp)

target_link_libraries(main PRIVATE
    Matplot++::matplot
    Eigen3::Eigen
    OpenMP::OpenMP_CXX
    "-framework Accelerate"
)

target_link_libraries(eigendist PRIVATE
    Matplot++::matplot
    Eigen3::Eigen
    OpenMP::OpenMP_CXX
    "-framework Accelerate"
)