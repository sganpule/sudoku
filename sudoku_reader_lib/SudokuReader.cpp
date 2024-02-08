// Sudoku Reader

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <assert.h>
#include <ctype.h>

#include "SudokuReader.h"

using namespace std;

const int    SudokuReader::Dimension  = 9;
const string SudokuReader::DotSeparator     = ".";
const string SudokuReader::XSeparator       = "x";


SudokuReader::SudokuReader() 
             :inSquareValid(false)
{
    // Resize sudoku square storage to SudokuReader::Dimension x SudokuReader::Dimension
    inSquare.resize( SudokuReader::Dimension, vector<int>(SudokuReader::Dimension) );
    assert(SudokuReader::Dimension == inSquare.size());
    assert(SudokuReader::Dimension == inSquare[0].size());
}

int static getNextInput(fstream& is, int& retVal)
{
    string  cin;
    int     cin_int;
    int     status = 0;

    is >> cin;

    // Entry longer than a single character
    if (cin.length() != 1)
    {
        // Test: inputs/error_not_single_char_input.txt
        status = SudokuReader::FoundEntryLongerThanSingleChar;
    }

    // Check if it a known separator, either '.' or 'x'.
    else if ( !cin.compare(SudokuReader::XSeparator)   ||
              !cin.compare(SudokuReader::DotSeparator)    )
    {
        // Yes it is a separator
        // Test: inputs/x_separator_input.txt
        // Test: inputs/dot_separator_input.txt
        retVal = 0;
        status = SudokuReader::NoError;
    } 

    // Check for non-numeric input
    else if ( !isdigit(cin.at(0)) )
    {
        // It is not a known separator, and not a digit
        // Test: inputs/nonnumeric_input.txt
        status = SudokuReader::FoundEntryThatIsNotADigit;
    }

    // It is a known separator, and a digit. Proceed.
    else
    {
        cin_int = stoi(cin);

        // Update number
        retVal = cin_int;
        status = SudokuReader::NoError;

    }

    return status;
}
int SudokuReader::readFile(fstream& is)
{
    string  cin;
    int     status = 0;
    int     retVal;

    for ( int i = 0 ; i < SudokuReader::Dimension ; i++ )
    {
        for ( int j = 0 ; j < SudokuReader::Dimension ; j++ )
        {
            status = getNextInput(is, retVal);
            if (SudokuReader::NoError == status)
            {
                inSquare[i][j] = retVal;
            }
            else
            {
                // cout << "Found read in issue " << status << " at location " << i << ", " << j << ".\n";
                goto cleanup;
            }
        }
    }

cleanup:
    return status;
}