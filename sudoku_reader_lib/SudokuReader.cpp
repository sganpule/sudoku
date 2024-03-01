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
    square.resize( Dimension, vector<int>(Dimension) );
    assert(Dimension == square.size());
    assert(Dimension == square[0].size());

    for ( int i = 0 ; i < Dimension ; i++ )
    {
        for ( int j = 0 ; j < Dimension ; j++ )
        {
            square[i][j] = 0;
        }
    }

    // Resize poss square storage. (Dimension x Dimension x Dimension)
    poss.resize(Dimension);
    for (int i = 0; i < Dimension; i++)
    {
        poss[i].resize(Dimension);

        for (int j = 0; j < Dimension; j++)
        {
            // Need to add +1 to make indexing via square values easy
            poss[i][j].resize(Dimension+1);
        }
    }

    for ( int i = 0 ; i < Dimension ; i++ )
    {
        for ( int j = 0 ; j < Dimension ; j++ )
        {
            int fill = 0;
            for ( auto k = poss[i][j].begin() ; k != poss[i][j].end() ; k++ )
            {
                // All values are possible at init time
                // -- FYI, this could be '1', but using the element
                //    to make it easier to read while debugging   
                *k = fill++;
            }
        }
    }
}

int SudokuReader::isValid(int* error_row, int* error_col)
{
    int         retStatus = SudokuReader::NoError;
    int         row, col;

    // Check for duplication in the columns
    for ( col = 0 ; col < SudokuReader::Dimension ; col++ )
    {
        // Track which numbers we see, +1 to allow for indexing from 1-9
        vector<int> v(SudokuReader::Dimension+1, 0);

        for ( row = 0 ; row < SudokuReader::Dimension ; row++ )
        {
            assert(square[row][col] <= SudokuReader::Dimension);

            if ( ( square[row][col] != 0 )   &&
                 ( v[ square[row][col] ]++ )    )
            {
                isSquareValid   = false;
                retStatus       = SudokuReader::FoundDuplicateEntryCol;
//              cerr << "Found column duplicate entry at row " << row+1 << ", col " << col+1 << ".\n";
                goto cleanup;
            }
        }
    }

    // Check for duplication in the rows
    for ( row = 0 ; row < SudokuReader::Dimension ; row++ )
    {
        // Track which numbers we see, +1 to allow for indexing from 1-9
        vector<int> h(SudokuReader::Dimension+1, 0);

        for ( col = 0 ; col < SudokuReader::Dimension ; col++ )
        {
            assert(square[row][col] <= SudokuReader::Dimension);

            if ( ( square[row][col] != 0 )   &&
                 ( h[ square[row][col] ]++ )    )
            {
                isSquareValid   = false;
                retStatus       = SudokuReader::FoundDuplicateEntryRow;
//              cerr << "Found row duplicate entry at row " << row+1 << ", col " << col+1 << ".\n";
                goto cleanup;
            }
        }
    }

    // Local squares are labelled as:
    // Square Numbers : 0 1 2        Starting at : 0,0 0,3 0,6
    //                  3 4 5                      3,0 3,3 3,6
    //                  6 7 8                      6,0 6,3 6,6 
    // 0 1 2 3 4 5 6 7 8 LocSqNum   == n
    // 0 0 0 3 3 3 6 6 6 Row        == 3 * ( n / 3 )
    // 0 3 6 0 3 6 0 3 6 Col        == 3 * ( n % 3 )
    for ( int locsq = 0 ; locsq < SudokuReader::NumLocalSq ; locsq++ )
    {
        // Track which numbers we see, +1 to allow for indexing from 1-9
        vector<int> sq(SudokuReader::Dimension+1, 0);

        int         rstart = 3 * (locsq / LocalSqDim);
        for ( row = rstart ; row < rstart + SudokuReader::LocalSqDim ; row++ )
        {
            int         cstart = 3 * (locsq % LocalSqDim);
            for ( col = cstart ; col < cstart + SudokuReader::LocalSqDim ; col++ )
            {
                assert(square[row][col] <= SudokuReader::Dimension);

                if ( ( square[row][col] != 0 )   &&
                     ( sq[ square[row][col] ]++ )    )
                {
                    isSquareValid   = false;
                    retStatus       = SudokuReader::FoundDuplicateEntryLocSq;
//                  cerr << "Found loc sq duplicate entry at row " << row+1 << ", col " << col+1 << ".\n";
                    goto cleanup;
                }
            }
        }
    }

cleanup:
    if (retStatus != SudokuReader::NoError)
    {
        if (error_row) *error_row = row;
        if (error_col) *error_col = col;
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


ostream& operator<<(ostream& os, SudokuReader sr)
{
    for ( int row = 0 ; row < SudokuReader::Dimension ; row++ )
    {
        // Track which numbers we see, +1 to allow for indexing from 1-9
        vector<int> h(SudokuReader::Dimension+1, 0);

        for ( int col = 0 ; col < SudokuReader::Dimension ; col++ )
        {
            int         val = sr.square[row][col];
            
            if (val)
                cout << val << " ";
            else
                cout << "." << " ";
        }
        cout << endl;
    }

    return os;
}

