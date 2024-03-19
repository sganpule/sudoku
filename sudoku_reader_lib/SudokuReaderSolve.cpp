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

//  cout << "The orginal square...\n";
//  cout << *this << endl;

    updatePossLists();
//  cout << "The first possiblity matrix...\n";
//  printPoss();

    do
    {
        squaresUpdated = updateSquare();
        assert(SudokuReader::NoError == isValid());

#if(0)
        if (squaresUpdated)
        {
            cout << "Updated " << squaresUpdated << " square(s)!\n\n";

            cout << "The updated square...\n";
            cout << *this << endl;

            cout << "The latest possiblity matrix...\n";
            printPoss();

        }
#endif

    } while (squaresUpdated);
    
    if (SudokuReader::Solved == isSolved())
    {
        cout << "The square was solved!\n";
        cout << *this << endl;
    }

    return isSolved();
}

int SudokuReader::isSolved()
{
    for ( int sq_col = 0 ; sq_col < Dimension ; sq_col++ )
    {
        for ( int sq_row = 0 ; sq_row < Dimension ; sq_row++ )
        {
            if (0 == square[sq_row][sq_col])
            {
                return NotSolved;
            }
        }
    }    
    return Solved;
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

//cout << "\n\nThe initializdd possiblity matrix...\n";
//printPoss();

    // Then, start on the COLUMNS
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
                    // If the square is not yet known...
                    if (!square[i][sq_col])
                    {
                        // Remove 'thisElement' from [i, sq_col]'s possibility list
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

//cout << "\n\nThe possiblity matrix after the columns...\n";
//printPoss();

    // Then, start on the ROWS
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

//cout << "\n\nThe possiblity matrix after the rows...\n";
//printPoss();



    // Local squares are labelled as:
    // Square Numbers : 0 1 2        Starting at : 0,0 0,3 0,6
    //                  3 4 5                      3,0 3,3 3,6
    //                  6 7 8                      6,0 6,3 6,6 
    // 0 1 2 3 4 5 6 7 8 LocSqNum   == n
    // 0 0 0 3 3 3 6 6 6 Row        == 3 * ( n / 3 )
    // 0 3 6 0 3 6 0 3 6 Col        == 3 * ( n % 3 )

    // Then, start on the LOCAL SQUARES
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
                                // Remove 'thisElement' from [i, j]'s possibility list
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

//cout << "\n\nThe possiblity matrix after the local squares...\n";
//printPoss();


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

            assert(num_poss > 0);
            assert(num_poss <= 9);

            if (!square[row][col])
            {
                cout << num_poss << " ";
            }
            else
            {
                cout << "." << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

int SudokuReader::updateSquare()
{
    int numUpdated = 0;

//  cout << "Reducing based on num_poss == 1.\n";
    numUpdated = doOnePossPass();

    if (0 == numUpdated)
    {
//      cout << "No squares udpated!\n\n";
//      cout << "Reducing based on num_poss == 2.\n";
        numUpdated = doTwoPossPass();
        
        if (0 == numUpdated)
        {
//          cout << "No squares udpated!\n\n";
        }
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
//              cout << "Found that   : " << *it << " must go in square"<<"["<<row<<"]["<<col<<"]\n";
                square[row][col] = *it;
                numUpdated++;
                assert(SudokuReader::NoError == isValid());

                // Update the possibility matrix
                updatePossLists();
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
            // Populate short list vector 'sl' with the possible values
            int num_poss = count_if(poss[row][col].begin(), 
                                    poss[row][col].end(), 
                                    [&](int i) { if (i!=0) sl.push_back(i); return (i!=0); } );

            // If poss[row][col] has two possible values,
            // and the corresponding element in 'square' is unknown
            if ( !square[row][col] )
            {
                // For each of the two possible values 'pval'
                for (auto pval = sl.begin() ; pval != sl.end() ; pval++ )
                {
//                  cout << "Processing *pval: " << *pval << endl;
//                  cout << "posss["<<row<<"]["<<col<<"]["<<*pval<<"]: " << poss[row][col][*pval] << endl;

                    // STEP 1
                    // Go along the ROW...
                    // For each element c in pval's row
                    for ( int c = 0 ; c < Dimension ; c++ )
                    {
                        // For each element in the row, except for 'this' one
                        if (c != col)
                        {
                            // Find if this number is in any other cell c's possibility list
                            num_poss = count_if(poss[row][c].begin(), 
                                                poss[row][c].end(),
                                                [=](int k) { return (poss[row][c][*pval]==*pval); } );
                        }

                        // If *pval is in c's possibility list
                        if (num_poss)
                        {
                            // Stop looking in this row
                          //cout << "*pval: " << *pval << " is in row: " << row << " c: " << c << "'s possibility list" << endl;
                            break;
                        }
                    }
                    if (!num_poss)
                    {
                        // pval is not possible anywhere else, this must be the value
//                      cout << "Found that.  : " << *pval << " must go in square"<<"["<<row<<"]["<<col<<"]\n";
                        square[row][col] = *pval;
                        numUpdated++;
                        assert(SudokuReader::NoError == isValid());

                        // Update the possibility matrix
                        updatePossLists();

                    }

                    // STEP 2
                    // Go along the column...
                    // For each element r in pval's column
                    for ( int r = 0 ; r < Dimension ; r++ )
                    {
                        // For each element in the column, except for 'this' one
                        if (r != row)
                        {
                            // Find if this number is in any other cell r's possibility list
                            num_poss = count_if(poss[r][col].begin(), 
                                                poss[r][col].end(),
                                                [=](int k) { return (poss[r][col][*pval]==*pval); } );
                        }

                        // If *pval is in r's possibility list
                        if (num_poss)
                        {
                            // Stop looking in this row
                            break;
                        }
                    }
                    if (!num_poss)
                    {
                        // pval is not possible anywhere else, this must be the value
//                      cout << "Found that.. : " << *pval << " must go in square"<<"["<<row<<"]["<<col<<"]\n";
                        square[row][col] = *pval;
                        numUpdated++;
                        assert(SudokuReader::NoError == isValid());

                        // Update the possibility matrix
                        updatePossLists();
                    }

                    // STEP 3
                    // Go along each local square...
                    // First determine which local square
                    int rowSnap = (row / 3) * LocalSqDim;
                    int colSnap = (col / 3) * LocalSqDim;

                    // For each element [lr][lc]] in pval's local square
                    bool pvalStillPoss = true;
                    for ( int lr = rowSnap ; lr < rowSnap + LocalSqDim ; lr++ )
                    {
                        for ( int lc = colSnap ; lc < colSnap + LocalSqDim ; lc++ )
                        {
                            if (pvalStillPoss)
                            {
//                              cout << "Processing *pval: " << *pval << endl;
//                              cout << "rowSnap: " << rowSnap << " colSnap: " << colSnap << " lr: " << lr << " lc: " << lc << endl;

                                // For each empty element in this local square, except for 'this' one
                                num_poss = 0;
                                if ( (0 == square[lr][lc]) &&
                                     (!((lr == row) && (lc == col)) ) )
                                {
                                    // Find if this number is in any other cell [lr,lc]'s possibility list
                                    num_poss = count_if(poss[lr][lc].begin(), 
                                                        poss[lr][lc].end(),
                                                        [=](int k) { return (poss[lr][lc][*pval]==*pval); } );
//                                  cout << "searching lr: "<<lr<<" lc: " << lc << endl;
                                }

                                // If *pval is in i's possibility list
                                if (num_poss)
                                {
                                    // Stop looking in this row
//                                  cout << "found *pval at lr: "<<lr<<" lc: " << lc << endl;
                                    pvalStillPoss = false;
                                }
                            }
                        }
                    }
                    if (!num_poss)
                    {
                        // pval is not possible anywhere else, this must be the value
//                      cout << "Found that...: " << *pval << " must go in square"<<"["<<row<<"]["<<col<<"]\n";
                        square[row][col] = *pval;
                        numUpdated++;
                        assert(SudokuReader::NoError == isValid());

                        // Update the possibility matrix
                        updatePossLists();
                    }
                }
            }
        }
    }

    return numUpdated;
}