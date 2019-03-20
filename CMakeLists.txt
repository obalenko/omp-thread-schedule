cmake_minimum_required(VERSION 3.13)
project(lab_2_omp)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab_2_omp main.cpp)

SET_TARGET_PROPERTIES(lab_2_omp PROPERTIES COMPILE_FLAGS "-fopenmp"
        LINK_FLAGS "-fopenmp")