cmake_minimum_required(VERSION 3.17)
project(sum_reverse)

set(CMAKE_CXX_STANDARD 20)

add_executable(sum_reverse main.cpp test_runner.h test_runner.cpp sum_reverse_sort.h sum_reverse_sort.h.cpp)