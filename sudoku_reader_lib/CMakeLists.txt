cmake_minimum_required(VERSION 3.27.9)

add_library(sudoku_reader_lib STATIC
            SudokuReader.cpp
            SudokuReaderSolve.cpp)

## Set options
# Can disabled by 'cmake ... -DCMAKE_COMPILE_WARNING_AS_ERROR=false' at the configure stage
option(CMAKE_COMPILE_WARNING_AS_ERROR "Compile warnings as errors" ON)
