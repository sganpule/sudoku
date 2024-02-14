// Sudoku Reader Solve

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <assert.h>
#include <ctype.h>

#include "SudokuReader.h"

using namespace std;


int SudokuReader::solve()
{
    return CouldNotSolve;
}

/*
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

    // Check for duplication in each local squre, local squares are labelled as:
    // Square Numbers : 0 1 2        Starting at : 0,0 0,3 0,6
    //                  3 4 5                      3,0 3,3 3,6
    //                  6 7 8                      6,0 6,3 6,6 
    // 0 1 2 3 4 5 6 7 8 LocSqNum   == n
    // 0 0 0 3 3 3 6 6 6 Row        == 3 * ( n / 3 )
    // 0 3 6 0 3 6 0 3 6 Col        == 3 * ( n % 3 )
    for ( int locsq = 0 ; locsq < SudokuReader::NumLocalSq ; locsq++ )
    {
        // Track which numbers we see, +1 to allow for indexing from 1-9
        vector<int>     sq(SudokuReader::Dimension+1, 0);
        int             rstart = 3 * (locsq / LocalSqDim);
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

*/

