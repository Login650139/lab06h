cmake_minimum_required(VERSION 3.10)
project(lab05 VERSION 0.1.0)

option(BUILD_TESTS "Build tests" OFF)

add_subdirectory(banking)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(third-party/gtest)

    target_compile_options(gtest PRIVATE -Wno-error)
    target_compile_options(gtest_main PRIVATE -Wno-error)
    target_compile_options(gmock PRIVATE -Wno-error)
    target_compile_options(gmock_main PRIVATE -Wno-error)

    add_executable(check tests/test_account.cpp tests/test_transaction.cpp)
    target_link_libraries(check banking gmock_main)
    add_test(NAME check COMMAND check)
endif()
