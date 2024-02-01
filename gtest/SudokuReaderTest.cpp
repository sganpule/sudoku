// Test app for sudoku library

#include <gtest/gtest.h>
#include "SudokuReader.h"

// Demonstrate some basic assertions.
TEST(SudokuReaderTest, BasicAssertions) {

    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    EXPECT_EQ(12, 11+1);
    EXPECT_FALSE(34 == 34+1);
    EXPECT_TRUE(23 == 22+1);
    EXPECT_GT(45, 45-1);
    EXPECT_LT(45, 45+1);

}

// Tests against the sudoku_lib.
TEST(SudokuReaderTest, SudokuReaderTests) {

    // Expect the read function to return (arg+1)
    EXPECT_EQ(12, 12);

    // Make an instance
    SudokuReader sr;

    //s.read_in();
}