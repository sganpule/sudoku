// Test app for sudoku library

#include <gtest/gtest.h>
#include "sudoku_lib.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {

    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");

}

// Tests against the sudoku_lib.
TEST(HelloTest, SudokuLibTests) {

    // Expect the read function to return (arg+1)
    EXPECT_EQ(12, read(11));
}