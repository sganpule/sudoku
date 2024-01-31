cmake_minimum_required(VERSION 3.27.9)

project(SudokuApp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## Main Application
add_executable(sudoku_app sudoku_app.cpp SudokuReader.cpp)

## Sudoku Library
add_subdirectory(sudoku_lib)
target_include_directories(sudoku_app PUBLIC
                           "${PROJECT_SOURCE_DIR}/sudoku_lib")

## Linking
target_link_libraries(sudoku_app PUBLIC sudoku_lib gtest gtest_main gmock gmock_main)

## Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
   set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()
add_subdirectory(gtest)
include(GoogleTest)
