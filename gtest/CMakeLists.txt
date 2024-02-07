cmake_minimum_required(VERSION 3.27.9)

add_executable(
  hello_test
  SudokuTest.cpp
  SudokuReaderTest.cpp
)

target_include_directories(hello_test PUBLIC
                           "${PROJECT_SOURCE_DIR}/sudoku_lib"
                           "${PROJECT_SOURCE_DIR}/sudoku_reader_lib")

target_link_libraries(
  hello_test
  PUBLIC
      sudoku_lib
      sudoku_reader_lib
      GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)
