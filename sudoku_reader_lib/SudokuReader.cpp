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
const int    SudokuReader::NumLocalSq = SudokuReader::Dimension;
const int    SudokuReader::LocalSqDim = 3;
const string SudokuReader::DotSeparator     = ".";
const string SudokuReader::XSeparator       = "x";

int static getNextInput(fstream& is, int& retVal);


SudokuReader::SudokuReader() 
             :isSquareValid(true)
{
    // Resize sudoku square storage to SudokuReader::Dimension x SudokuReader::Dimension
    square.resize( SudokuReader::Dimension, vector<int>(SudokuReader::Dimension) );
    assert(SudokuReader::Dimension == square.size());
    assert(SudokuReader::Dimension == square[0].size());

    for ( int i = 0 ; i < SudokuReader::Dimension ; i++ )
    {
        for ( int j = 0 ; j < SudokuReader::Dimension ; j++ )
        {
            square[i][j] = 0;
        }
    }

}

int SudokuReader::isValid(int* error_row, int* error_col)
{
    int         retStatus = SudokuReader::NoError;
    int         row, col;
    int         retRow, retCol;

    // Check for duplication in the columns
    for ( int col = 0 ; col < SudokuReader::Dimension ; col++ )
    {
        vector<int> v(SudokuReader::Dimension, 0);

        for ( int row = 0 ; row < SudokuReader::Dimension ; row++ )
        {
            if ( ( square[row][col] != 0 )   &&
                 ( v[ square[row][col] ]++ )    )
            {
                isSquareValid   = false;
                retStatus       = SudokuReader::FoundDuplicateEntryCol;
                retRow = row;
                retCol = col;
                cerr << "Found column duplicate entry at row " << row+1 << ", col " << col+1 << ".\n";
                goto cleanup;
            }
        }
    }

    // Check for duplication in the rows
    for ( int row = 0 ; row < SudokuReader::Dimension ; row++ )
    {
        vector<int> h(SudokuReader::Dimension, 0);

        for ( int col = 0 ; col < SudokuReader::Dimension ; col++ )
        {
            if ( ( square[row][col] != 0 )   &&
                 ( h[ square[row][col] ]++ )    )
            {
                retRow = row;
                retCol = col;
                isSquareValid   = false;
                retStatus       = SudokuReader::FoundDuplicateEntryRow;
                cerr << "Found row duplicate entry at row " << row+1 << ", col " << col+1 << ".\n";
                goto cleanup;
            }
        }
    }

    // Check for duplication in each local squre, local squares are labelled as:
    // Square Numbers : 0 1 2        Starting at : 0,0 0,3 0,6
    //                  3 4 5                      3,0 3,3 3,6
    //                  6 7 8                      6,0 6,3 6,6 
    // 0 1 2 3 4 5 6 7 8 LocSqNum   == n
    // 0 0 0 3 3 3 6 6 6 Row        == 3 * ( n / 3 )
    // 0 3 6 0 3 6 0 3 6 Col        == 3 * ( n % 3 )
    for ( int locsq = 0 ; locsq < SudokuReader::NumLocalSq ; locsq++ )
    {
        vector<int>     sq(SudokuReader::Dimension, 0);
        int             rstart = 3 * (locsq / LocalSqDim);
        for ( int row = rstart ; row < rstart + SudokuReader::LocalSqDim ; row++ )
        {
            int             cstart = 3 * (locsq % LocalSqDim);
            for ( int col = cstart ; col < cstart + SudokuReader::LocalSqDim ; col++ )
            {
                if ( ( square[row][col] != 0 )   &&
                     ( sq[ square[row][col] ]++ )    )
                {
                    isSquareValid   = false;
                    retStatus       = SudokuReader::FoundDuplicateEntryLocSq;
                    retRow = row;
                    retCol = col;
                    cerr << "Found loc sq duplicate entry at row " << row+1 << ", col " << col+1 << ".\n";
                    goto cleanup;
                }
            }
        }
    }

cleanup:
    if (retStatus != SudokuReader::NoError)
    {
        if (error_row) *error_row = retRow;
        if (error_col) *error_col = retCol;
    }

    return retStatus;

}


int SudokuReader::readFile(fstream& is)
{
    string  cin;
    int     status = 0;
    int     retVal;

    for ( int row = 0 ; row < SudokuReader::Dimension ; row++ )
    {
        for ( int col = 0 ; col < SudokuReader::Dimension ; col++ )
        {
            status = getNextInput(is, retVal);
            if (SudokuReader::NoError == status)
            {
                square[row][col] = retVal;
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
