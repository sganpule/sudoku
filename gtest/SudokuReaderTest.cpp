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


// Tests against the SudokuReade file input.

TEST_F(SudokuReaderTest, HappyPath) {

    m_inputFile = "../../inputs/easy_input_1.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);
}

TEST_F(SudokuReaderTest, FirstCellValidXSeparator) {

    m_inputFile = "../../inputs/x_separator_input.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);
}

TEST_F(SudokuReaderTest, FirstCellValidDotSeparator) {

    m_inputFile = "../../inputs/dot_separator_input.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);
}

TEST_F(SudokuReaderTest, DoubleDigitEntry) {

    m_inputFile = "../../inputs/error_not_single_char_input.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::FoundEntryLongerThanSingleChar);
}

TEST_F(SudokuReaderTest, NonNumericEntry1) {

    m_inputFile = "../../inputs/error_nonnumeric_input_1.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::FoundEntryThatIsNotADigit);
}

TEST_F(SudokuReaderTest, NonNumericEntry2) {

    m_inputFile = "../../inputs/error_nonnumeric_input_2.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::FoundEntryThatIsNotADigit);
}

TEST_F(SudokuReaderTest, NonNumericEntry3) {

    m_inputFile = "../../inputs/error_nonnumeric_input_3.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::FoundEntryThatIsNotADigit);
}



// Test against input validation

TEST_F(SudokuReaderTest, ValidateUninitializedInput) {

    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    EXPECT_EQ(12, 11+1);
    EXPECT_FALSE(34 == 34+1);
    EXPECT_TRUE(23 == 22+1);
    EXPECT_GT(45, 45-1);
    EXPECT_LT(45, 45+1);

    // Validate current square state
    bool status = m_sr.isValid();
    ASSERT_TRUE(status);
}

TEST_F(SudokuReaderTest, ValidateErrorVertInput) {

    m_inputFile = "../../inputs/error_invalid_square_vert_input.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    int status;

    // Read file
    status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);

    // Validate current square state
    status = m_sr.isValid();
    ASSERT_FALSE(status);
}

TEST_F(SudokuReaderTest, ValidateErrorHorzInput) {

    m_inputFile = "../../inputs/error_invalid_square_horz_input.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    int status;

    // Read file
    status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);

    // Validate current square state
    status = m_sr.isValid();
    ASSERT_FALSE(status);
}


TEST_F(SudokuReaderTest, ValidateErrorLocSqInput1) {

    // Reduplication error in first local square
    m_inputFile = "../../inputs/error_invalid_square_loc_sq_input_1.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    int status;

    // Read file
    status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);

    // Validate current square state
    status = m_sr.isValid();
    ASSERT_FALSE(status);
}

TEST_F(SudokuReaderTest, ValidateErrorLocSqInput2) {

    // Reduplication error in ninth local square
    m_inputFile = "../../inputs/error_invalid_square_loc_sq_input_2.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    int status;

    // Read file
    status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);

    // Validate current square state
    status = m_sr.isValid();
    ASSERT_FALSE(status);
}
