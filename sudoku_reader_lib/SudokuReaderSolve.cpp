// Sudoku Reader Solve

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <assert.h>
#include <ctype.h>

#include "SudokuReader.h"

using namespace std;


int SudokuReader::solve()
{
    int squaresUpdated;

    cout << "The orginal square...\n";
    cout << *this << endl;

    do
    {
        updatePossLists();
        cout << "The latest possiblity matrix...\n";
        printPoss();

        squaresUpdated = updateSquare();
        if (squaresUpdated)
        {
            cout << "Updated " << squaresUpdated << " squares!\n\n";

            cout << "The updated square...\n";
            cout << *this << endl;
        }

    } while (squaresUpdated);
    

    return CouldNotSolve;
}

void SudokuReader::updatePossLists()
{
    //// Gen possibility matrix

    // Start by going through each element in 'square',
    // find the elements that are known, clear their possibility lists,
    // and set their values to exactly what they are known to be
    for ( int sq_col = 0 ; sq_col < Dimension ; sq_col++ )
    {
        for ( int sq_row = 0 ; sq_row < Dimension ; sq_row++ )
        {
            int thisElement = square[sq_row][sq_col];

            // If the value for this element is known
            if (thisElement)
            {
                // Clear all possibilities from this element's possibility list
                std::fill(poss[sq_row][sq_col].begin(),
                          poss[sq_row][sq_col].end(),
                          0);

                // Since we know this squre, set this one possibiilty
                // -- FYI, this could be '1', but use 'thisElement'
                //    to make it easier to read when debugging
                poss[ sq_row ][ sq_col ][ thisElement ] = thisElement;
            }
        }
    }

    // Start on the columns
    for ( int sq_col = 0 ; sq_col < Dimension ; sq_col++ )
    {
        for ( int sq_row = 0 ; sq_row < Dimension ; sq_row++ )
        {
            int thisElement = square[sq_row][sq_col];

            // If the value for this element is known
            if (thisElement)
            {
                // For each row element in this column
                for ( int i = 0 ; i < Dimension ; i++ )
                {
                    // If this square is not yet known...
                    if (!square[i][sq_col])
                    {
                        // Remove 'thisElement' from [sq_col, i]'s possibility list
                        poss[ i ][ sq_col ][ thisElement ] = 0;
                    }
                }
            }
        }
/**
        for ( int sq_row = 0 ; sq_row < SudokuReader::Dimension ; sq_row++ )
        {
            cout << "The possibility lists for column " << sq_col+1 << "..." << endl << "Row " << sq_row+1 << ": ";
            for ( int i = 0 ; i < Dimension ; i++ )
            {
                cout << poss[ sq_row ][ sq_col ][ i+1 ] << " ";
            }
            cout << endl;
        }
**/
    }

    // Start on the rows
    for ( int sq_row = 0 ; sq_row < Dimension ; sq_row++ )
    {
        for ( int sq_col = 0 ; sq_col < Dimension ; sq_col++ )
        {
            int thisElement = square[sq_row][sq_col];

            // If the value for this element is known
            if (thisElement)
            {
                // For each col element in this row
                for ( int i = 0 ; i < Dimension ; i++ )
                {
                    // If this square is not yet known...
                    if (!square[sq_row][i])
                    {
                        // Remove 'thisElement' from [sq_col, i]'s possibility list
                        poss[ sq_row ][ i ][ thisElement ] = 0;
                    }
                }
            }
        }
/**
        for ( int sq_col = 0 ; sq_col < SudokuReader::Dimension ; sq_col++ )
        {
          //cout << "The possibility lists for row " << sq_row+1 << "..." << endl << "Col " << sq_col+1 << ": ";
            for ( int i = 0 ; i < Dimension ; i++ )
            {
                cout << poss[ sq_row ][ sq_col ][ i+1 ] << " ";
            }
            cout << endl;
        }
**/
    }


    // Local squares are labelled as:
    // Square Numbers : 0 1 2        Starting at : 0,0 0,3 0,6
    //                  3 4 5                      3,0 3,3 3,6
    //                  6 7 8                      6,0 6,3 6,6 
    // 0 1 2 3 4 5 6 7 8 LocSqNum   == n
    // 0 0 0 3 3 3 6 6 6 Row        == 3 * ( n / 3 )
    // 0 3 6 0 3 6 0 3 6 Col        == 3 * ( n % 3 )

    // Start on the local squares
    for ( int locsq = 0 ; locsq < NumLocalSq ; locsq++ )
    {
        int                rstart = 3 * (locsq / LocalSqDim);
        for ( int sq_row = rstart ; sq_row < rstart + LocalSqDim ; sq_row++ )
        {
            int                cstart = 3 * (locsq % LocalSqDim);
            for ( int sq_col = cstart ; sq_col < cstart + LocalSqDim ; sq_col++ )
            {
                int thisElement = square[sq_row][sq_col];

                // If the value for this element is known
                if (thisElement)
                {
                    // Then, search each element in this local square
                    for ( int i = rstart ; i < rstart + LocalSqDim ; i++ )
                    {
                        for ( int j = cstart ; j < cstart + LocalSqDim ; j++ )
                        {
                            // If this search square is not yet known...
                            if (!square[i][j])
                            {
                                // Remove 'thisElement' from [j, i]'s possibility list
                                poss[ i ][ j ][ thisElement ] = 0;
                            }
                        }
                    }
                }
            }
/**
            for ( int sq_col = 0 ; sq_col < SudokuReader::Dimension ; sq_col++ )
            {
                cout << "The possibility lists for row " << sq_row+1 << "..." << endl << "Col " << sq_col+1 << ": ";
                for ( int i = 0 ; i < Dimension ; i++ )
                {
                    cout << poss[ sq_row ][ sq_col ][ i+1 ] << " ";
                }
                cout << endl;
            }
**/
        }
    }

}

void SudokuReader::printPoss()
{
    int numUpdated = 0;

    // For each element in 'square'
    for ( int row = 0 ; row < Dimension ; row++ )
    {
        for ( int col = 0 ; col < Dimension ; col++ )
        {
            // Find the number of elements that are non-zero
            int num_poss = count_if(poss[row][col].begin(), 
                                    poss[row][col].end(), 
                                    [](int i) { return i!=0; } );

            cout << num_poss << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int SudokuReader::updateSquare()
{
    int numUpdated = 0;

    cout << "Reducing based on num_poss == 1.\n";
    numUpdated = doOnePossPass();

    if (0 == numUpdated)
    {
        cout << "No squares udpated!\n\n";
        cout << "Reducing based on num_poss == 2.\n";
        numUpdated = doTwoPossPass();
    }

    return numUpdated;
}

int SudokuReader::doOnePossPass()
{
    int numUpdated = 0;

    // For each element in 'square'
    for ( int row = 0 ; row < Dimension ; row++ )
    {
        for ( int col = 0 ; col < Dimension ; col++ )
        {
            // Find the number of elements that are non-zero; (i.e. still possible)
            int num_poss = count_if(poss[row][col].begin(), 
                                    poss[row][col].end(), 
                                    [](int i) { return i!=0; } );

            // If poss[row][col] has only one possible value,
            // and the corresponding element in 'square' is unknown
            if ( (1 == num_poss) && !square[row][col] )
            {
                // Find the remaining value in the possibility list for this element
                std::vector<int>::iterator it = find_if(poss[row][col].begin(), 
                                                        poss[row][col].end(), 
                                                        [](int i) { return i!=0; } );
                assert(it != poss[row][col].end());

                // Update square with the new confirmed number
                square[row][col] = *it;
              //cout << "setting row: " << row+1 << "col: " << col+1 << " to *it: " << *it << endl;
                numUpdated++;
            }
        }
    }

    return numUpdated;
}

int SudokuReader::doTwoPossPass()
{
    int numUpdated = 0;

    // For each element in 'square'
    for ( int row = 0 ; row < Dimension ; row++ )
    {
        for ( int col = 0 ; col < Dimension ; col++ )
        {
            vector<int> sl; // short list

            // Find the number of elements that are non-zero; (i.e. still possible)
            int num_poss = count_if(poss[row][col].begin(), 
                                    poss[row][col].end(), 
                                    [&](int i) { if (i!=0) sl.push_back(i); return (i!=0); } );

            // If poss[row][col] has two possible values,
            // and the corresponding element in 'square' is unknown
            if ( (2 == num_poss) && !square[row][col] )
            {
                assert(sl.size() == 2);

                // For each possible value 'pval'
                for (auto pval = sl.begin() ; pval != sl.end() ; pval++ )
                {
                  //cout << "Processing *pval: " << *pval << endl;
                  //cout << "posss[row][col][*pval]: " << poss[row][col][*pval] << endl;

                    // Go along the row...
                    // For each element i in pval's row
                    for ( int r = 0 ; r < Dimension ; r++ )
                    {
                        // For each element in the row, except for 'this' one
                        if (r != col)
                        {
                            // Find if this number is in i's possibility list
                            num_poss = count_if(poss[row][r].begin(), 
                                                poss[row][r].end(),
                                                [=](int k) { return (poss[row][r][*pval]==*pval); } );
                        }

                        // If *pval is in i's possibility list
                        if (num_poss)
                        {
                            // Stop looking in this row
                            break;
                        }
                    }
                    if (!num_poss)
                    {
                        // pval is not possible anywhere else, this must be the value
                      //cout << "Found that " << *pval << " must go in square"<<"["<<row<<"]["<<col<<"]\n";
                        square[row][col] = *pval;
                        numUpdated++;
                    }
                }

            }
        }
    }

    return numUpdated;
}