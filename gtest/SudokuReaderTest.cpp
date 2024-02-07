// Test app for sudoku library

#include <gtest/gtest.h>
#include <iostream>
#include "SudokuReader.h"

using namespace std;


// The fixture for testing class Foo.
class SudokuReaderTest : public testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  SudokuReaderTest() {
     // You can do set-up work for each test here.
  }

  ~SudokuReaderTest() override {
     // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
     // Code here will be called immediately after the constructor (right
     // before each test).
     
  }

  void TearDown() override {
     // Code here will be called immediately after each test (right
     // before the destructor).
  }

  // Class members declared here can be used by all tests in the test suite
  // for Foo.

    fstream         m_fin;
    string          m_inputFile;
    SudokuReader    m_sr;

};



// Demonstrate some basic assertions.
TEST_F(SudokuReaderTest, BasicAssertions) {

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

TEST_F(SudokuReaderTest, HappyPath) {

    m_inputFile = "../../inputs/easy_input_1.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    m_sr.readFile(m_fin);
}

TEST_F(SudokuReaderTest, FirstCellUnknownValidDotSeparator) {

    m_inputFile = "../../inputs/easy_input_2.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    m_sr.readFile(m_fin);
}

TEST_F(SudokuReaderTest, DoubleDigitEntry) {

    m_inputFile = "../../inputs/error_easy_input_1.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    m_sr.readFile(m_fin);
}

TEST_F(SudokuReaderTest, NonNumericEntry) {

    m_inputFile = "../../inputs/nonnumeric_input.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    m_sr.readFile(m_fin);
}

