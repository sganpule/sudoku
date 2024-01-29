cmake_minimum_required(VERSION 3.28)

add_executable(
  hello_test
  SudokuTest.cpp
)

target_include_directories(hello_test PUBLIC
                           "${PROJECT_SOURCE_DIR}/sudoku_lib")

target_link_libraries(
  hello_test
  PUBLIC
  sudoku_lib
  GTest::gtest_main
)
include(GoogleTest)

gtest_discover_tests(hello_test)
