cmake_minimum_required(VERSION 3.10)
project(lab05 VERSION 0.1.0)

option(BUILD_TESTS "Build tests" OFF)

add_subdirectory(banking)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(third-party/gtest)
    add_executable(check tests/test_account.cpp tests/test_transaction.cpp)
    target_link_libraries(check banking gtest_main)
    add_test(NAME check COMMAND check)
endif()
