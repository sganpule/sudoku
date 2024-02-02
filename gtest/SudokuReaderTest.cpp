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

int openInputFile(fstream& fin, string& inputFileName)
{
    int returnVal = 0;

    fin.open(inputFileName);
    if (!(fin.is_open()))
    {
        cerr << "File open error! Could not open '" 
             << inputFileName << "'."
             << endl;
        returnVal = -1;
    }

    return returnVal;
}



// Tests against the sudoku_lib.
TEST(SudokuReaderTest, EmptyFirstCell) {

    fstream fin;
    string  inputFile("../inputs/easy_input_2.txt");
    ASSERT_EQ(0, openInputFile(fin, inputFile));

    // Make an instance
    SudokuReader sr;

    // Read file
    sr.readFile(fin);
}

// Tests against the sudoku_lib.
TEST(SudokuReaderTest, InvalidEntry) {

    fstream fin;
    string  inputFile("../inputs/error_easy_input_1.txt");
    ASSERT_EQ(0, openInputFile(fin, inputFile));

    // Make an instance
    SudokuReader sr;

    // Read file
    sr.readFile(fin);
}