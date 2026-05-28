set(CMAKE_C_COMPILER   /opt/homebrew/opt/llvm@17/bin/clang)
set(CMAKE_CXX_COMPILER /opt/homebrew/opt/llvm@17/bin/clang++)

set(CMAKE_OSX_SYSROOT
    /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk)

# OpenMP
set(OpenMP_C_FLAGS "-Xpreprocessor -fopenmp")
set(OpenMP_CXX_FLAGS "-Xpreprocessor -fopenmp")

set(OpenMP_C_LIB_NAMES "omp")
set(OpenMP_CXX_LIB_NAMES "omp")

set(OpenMP_omp_LIBRARY
    /opt/homebrew/opt/libomp/lib/libomp.dylib)

include_directories(
    /opt/homebrew/opt/libomp/include
)