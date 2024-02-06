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

int sudokuRead(fstream& is, vector<vector<int>> *square)
{
    string              cin;
    int                 cin_int;
    int                 returnVal = 0;

    is >> cin;
    cin_int = stoi(cin);
    if ( (cin_int < 1) ||
         (cin_int > 9)    )
    {
       cin_int = 0;
       cerr << "Found an entry (" 
            << cin 
            << ") not between 1-9... Replacing with 0" << endl;
    }
    cout << cin_int;

    return returnVal;
}

SudokuReader::SudokuReader() : inSquareValid(false)
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
        status = SudokuReader::FoundEntryLongerThanSingleChar;
    }

    // Check for separator
    if ( !cin.compare(SudokuReader::XSeparator)   ||
         !cin.compare(SudokuReader::DotSeparator)    )
    {
        retVal = 0;
    } 
    else
    {
        {
        }

        // Check for non-numeric input
        if ( !isdigit(cin.at(0)) )
        {
            retVal = 0;
            status = SudokuReader::FoundEntryThatIsNotADigit;
        }
        else
        {
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