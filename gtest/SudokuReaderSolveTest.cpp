// Test app for sudoku library

#include <gtest/gtest.h>
#include <iostream>
#include "SudokuReader.h"

using namespace std;


// The fixture for testing class Foo.
class SudokuReaderSolveTest : public testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  SudokuReaderSolveTest() {
     // You can do set-up work for each test here.
  }

  ~SudokuReaderSolveTest() override {
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



static int openInputFile(fstream& fin, string& inputFileName)
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

TEST_F(SudokuReaderSolveTest, EasyInput1) {

    m_inputFile = "../../inputs/easy_input_1.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);

    // Solve File
    status = m_sr.solve();
    ASSERT_EQ(status, SudokuReader::Solved);
}

TEST_F(SudokuReaderSolveTest, EasyInput2) {

    m_inputFile = "../../inputs/easy_input_2.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);

    // Solve File
    status = m_sr.solve();
    ASSERT_EQ(status, SudokuReader::Solved);
}

TEST_F(SudokuReaderSolveTest, EasyInput3) {

    m_inputFile = "../../inputs/easy_input_3.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);

    // Solve File
    status = m_sr.solve();
    ASSERT_EQ(status, SudokuReader::Solved);
}

TEST_F(SudokuReaderSolveTest, EasyInput4) {

    m_inputFile = "../../inputs/easy_input_4.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);

    // Solve File
    status = m_sr.solve();
    ASSERT_EQ(status, SudokuReader::Solved);
}

TEST_F(SudokuReaderSolveTest, EasyInput5) {

    m_inputFile = "../../inputs/easy_input_5.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);

    // Solve File
    status = m_sr.solve();
    ASSERT_EQ(status, SudokuReader::Solved);
}

TEST_F(SudokuReaderSolveTest, MediumInput1) {

    m_inputFile = "../../inputs/medium_input_1.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);

    // Solve File
    status = m_sr.solve();
    ASSERT_EQ(status, SudokuReader::Solved);
}

TEST_F(SudokuReaderSolveTest, MediumInput2) {

    m_inputFile = "../../inputs/medium_input_2.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);

    // Solve File
    status = m_sr.solve();
    ASSERT_EQ(status, SudokuReader::Solved);
}

TEST_F(SudokuReaderSolveTest, MediumInput3) {

    m_inputFile = "../../inputs/medium_input_3.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);

    // Solve File
    status = m_sr.solve();
    ASSERT_EQ(status, SudokuReader::Solved);
}

TEST_F(SudokuReaderSolveTest, MediumInput4) {

    m_inputFile = "../../inputs/medium_input_4.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);

    // Solve File
    status = m_sr.solve();
    ASSERT_EQ(status, SudokuReader::Solved);
}

TEST_F(SudokuReaderSolveTest, MediumInput5) {

    m_inputFile = "../../inputs/medium_input_5.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);

    // Solve File
    status = m_sr.solve();
    ASSERT_EQ(status, SudokuReader::Solved);
}

TEST_F(SudokuReaderSolveTest, HardInput1) {

    m_inputFile = "../../inputs/hard_input_1.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);

    // Solve File
    status = m_sr.solve();
    ASSERT_EQ(status, SudokuReader::Solved);
}

TEST_F(SudokuReaderSolveTest, HardInput2) {

    m_inputFile = "../../inputs/hard_input_2.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);

    // Solve File
    status = m_sr.solve();
    ASSERT_EQ(status, SudokuReader::Solved);
}

TEST_F(SudokuReaderSolveTest, HardInput3) {

    m_inputFile = "../../inputs/hard_input_3.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);

    // Solve File
    status = m_sr.solve();
    ASSERT_EQ(status, SudokuReader::Solved);
}

TEST_F(SudokuReaderSolveTest, HardInput4) {

    m_inputFile = "../../inputs/hard_input_4.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);

    // Solve File
    status = m_sr.solve();
    ASSERT_EQ(status, SudokuReader::Solved);
}

TEST_F(SudokuReaderSolveTest, HardInput5) {

    m_inputFile = "../../inputs/hard_input_5.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);

    // Solve File
    status = m_sr.solve();
    ASSERT_EQ(status, SudokuReader::Solved);
}

TEST_F(SudokuReaderSolveTest, HardInput6) {

    m_inputFile = "../../inputs/hard_input_6.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);

    // Solve File
    status = m_sr.solve();
    ASSERT_EQ(status, SudokuReader::Solved);
}

TEST_F(SudokuReaderSolveTest, HardInput7) {

    m_inputFile = "../../inputs/hard_input_7.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);

    // Solve File
    status = m_sr.solve();
    ASSERT_EQ(status, SudokuReader::Solved);
}

TEST_F(SudokuReaderSolveTest, ExpertInput1) {

    m_inputFile = "../../inputs/expert_input_1.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);

    // Solve File
    status = m_sr.solve();
    ASSERT_EQ(status, SudokuReader::Solved);
}

TEST_F(SudokuReaderSolveTest, ExpertInput2) {

    m_inputFile = "../../inputs/expert_input_2.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);

    // Solve File
    status = m_sr.solve();
    ASSERT_EQ(status, SudokuReader::Solved);
}

TEST_F(SudokuReaderSolveTest, ExpertInput3) {

    m_inputFile = "../../inputs/expert_input_3.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);

    // Solve File
    status = m_sr.solve();
    ASSERT_EQ(status, SudokuReader::Solved);
}

TEST_F(SudokuReaderSolveTest, ExpertInput4) {

    m_inputFile = "../../inputs/expert_input_4.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);

    // Solve File
    status = m_sr.solve();
    ASSERT_EQ(status, SudokuReader::Solved);
}

TEST_F(SudokuReaderSolveTest, ExpertInput5) {

    m_inputFile = "../../inputs/expert_input_5.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);

    // Solve File
    status = m_sr.solve();
    ASSERT_EQ(status, SudokuReader::Solved);
}

TEST_F(SudokuReaderSolveTest, ExpertInput6) {

    m_inputFile = "../../inputs/expert_input_6.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);

    // Solve File
    status = m_sr.solve();
    ASSERT_EQ(status, SudokuReader::Solved);
}

TEST_F(SudokuReaderSolveTest, MasterInput1) {

    m_inputFile = "../../inputs/master_input_1.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);

    // Solve File
    status = m_sr.solve();
    ASSERT_EQ(status, SudokuReader::Solved);
}

TEST_F(SudokuReaderSolveTest, MasterInput2) {

    m_inputFile = "../../inputs/master_input_2.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);

    // Solve File
    status = m_sr.solve();
    ASSERT_EQ(status, SudokuReader::Solved);
}

TEST_F(SudokuReaderSolveTest, MasterInput3) {

    m_inputFile = "../../inputs/master_input_3.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);

    // Solve File
    status = m_sr.solve();
    ASSERT_EQ(status, SudokuReader::Solved);
}

TEST_F(SudokuReaderSolveTest, MasterInput4) {

    m_inputFile = "../../inputs/master_input_4.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);

    // Solve File
    status = m_sr.solve();
    ASSERT_EQ(status, SudokuReader::Solved);
}

TEST_F(SudokuReaderSolveTest, MasterInput5) {

    m_inputFile = "../../inputs/master_input_5.txt";
    ASSERT_EQ(0, openInputFile(m_fin, m_inputFile));

    // Read file
    int status = m_sr.readFile(m_fin);
    ASSERT_EQ(status, SudokuReader::NoError);

    // Solve File
    status = m_sr.solve();
    ASSERT_EQ(status, SudokuReader::Solved);
}

