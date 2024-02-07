// Sudoku Reader

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <assert.h>
#include <ctype.h>

#include "SudokuReader.h"

using namespace std;

const string SudokuReader::DotSeparator = ".";
const string SudokuReader::XSeparator   = "x";


SudokuReader::SudokuReader() 
             :inSquareValid(false)
{
    // Resize sudoku square storage to SudokuReaderDim x SudokuReaderDim
    inSquare.resize( SudokuReaderDim, vector<int>(SudokuReaderDim) );
    assert(SudokuReaderDim == inSquare.size());
    assert(SudokuReaderDim == inSquare[0].size());
}

int static getNextInput(fstream& is, int& retVal)
{
    string  cin;
    int     cin_int;
    int     status = 0;

    is >> cin;
    if (cin.length() != 1)
    {
        // Entry longer than a single character
        // Test: inputs/error_not_single_char_input.txt
        status = SudokuReader::FoundEntryLongerThanSingleChar;
    }

    // Check if it a known separator, either '.' or 'x'.
    if ( !cin.compare(SudokuReader::XSeparator)   ||
         !cin.compare(SudokuReader::DotSeparator)    )
    {
        // Yes it is a separator
        // Test: inputs/x_separator_input.txt
        // Test: inputs/dot_separator_input.txt
        retVal = 0;
        status = SudokuReader::NoError;
    } 
    else
    {
        // Check for non-numeric input
        if ( !isdigit(cin.at(0)) )
        {
            // It is not a known separator, and not a digit
            // Test: inputs/nonnumeric_input.txt
            retVal = 0;
            status = SudokuReader::FoundEntryThatIsNotADigit;
        }
        else
        {
            // It is a known separator, and a digit. Proceed.
            cin_int = stoi(cin);

            // Update number
            retVal = cin_int;
            status = SudokuReader::NoError;

        }
    }

    return status;
}
int SudokuReader::readFile(fstream& is)
{
    string  cin;
    int     status = 0;
    int     retVal;

    status = getNextInput(is, retVal);

    return status;
}