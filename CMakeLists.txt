cmake_minimum_required(VERSION 3.10)

project(lab06h VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(solver
    solver_application/solver.cpp
)

install(TARGETS solver
    RUNTIME DESTINATION bin
    BUNDLE DESTINATION .
)

include(CPackConfig.cmake)
