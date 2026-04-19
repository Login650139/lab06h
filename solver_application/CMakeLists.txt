cmake_minimum_required(VERSION 3.4)
project(solver)

add_executable(solver solver.cpp)
target_link_libraries(solver formatter_ex solver_lib)
