// Sudoku Reader Solve

#include <vector>
#include <tuple>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <assert.h>
#include <ctype.h>

#include "SudokuReader.h"

using namespace std;

#define PRINT_INFO 0

int SudokuReader::solve()
{
    int squaresUpdated;

#if(PRINT_INFO)
    cout << "The orginal square...\n";
    cout << *this << endl;
#endif

    updatePossLists();

#if(PRINT_INFO)
    cout << "The first possiblity matrix...\n";
    printPoss();
#endif

    do
    {
        squaresUpdated = updateSquare();
        assert(SudokuReader::NoError == isValid());

#if(PRINT_INFO)
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
#if(PRINT_INFO)
        cout << "The square was solved!\n";
        cout << *this << endl;
#endif
    }
    else
    {
#if(PRINT_INFO)
        cout << "The square couldn't be solved!\n";
        cout << *this << endl;

        cout << "The latest possiblity matrix...\n";
        printPoss();


#endif
    
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

                // Since we know this square, set this one possibiilty
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

//  cout << "Technique 1 : Reducing based on num_poss == 1.\n";
    numUpdated = doOnePossPass();

    if (0 == numUpdated)
    {
//      cout << "No squares udpated!\n\n";
//      cout << "Technique 2 : Reducing based on num_poss > 1.\n";
        numUpdated = doMultiPossPass();
        
        if (0 == numUpdated)
        {
//          cout << "No squares udpated!\n\n";
//          cout << "Technique 3 : Reducing based on local square possibility pairs.\n";
            numUpdated = doLocalSquarePossPairsReduce();

            if (0 == numUpdated)
            {
//              cout << "No squares udpated!\n\n";
//              cout << "Technique 4 : Reducing based on local square / single column possibility configurations.\n";
                numUpdated = doLocalSquareSingleColumnPossReduce();

                if (0 == numUpdated)
                {
//                  cout << "No squares udpated!\n\n";
//                  cout << "Technique 5 : Reducing based on singular remaining possibility over a row / column / local square.\n";
                    numUpdated = doOnlyPossPass();

                    if (0 == numUpdated)
                    {
//                      cout << "No squares udpated!\n\n";
                    }
                }
            }

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
            }
        }
    }

    // Update the possibility matrix
    updatePossLists();

    return numUpdated;
}

int SudokuReader::doMultiPossPass()
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

            // STEP 1
            // Go along the ROW...
            // If the corresponding element in 'square' is unknown
            if ( !square[row][col] )
            {
                // For each of the possible values 'pval'
                for (auto pval = sl.begin() ; pval != sl.end() ; pval++ )
                {
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
                }
            }


            // STEP 2
            // Go along the column...
            // If the corresponding element in 'square' is unknown
            if ( !square[row][col] )
            {
                // For each of the possible values 'pval'
                for (auto pval = sl.begin() ; pval != sl.end() ; pval++ )
                {

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
                }
            }


            // STEP 3
            // Go along each local square...
            // If the corresponding element in 'square' is unknown
            if ( !square[row][col] )
            {
                // For each of the possible values 'pval'
                for (auto pval = sl.begin() ; pval != sl.end() ; pval++ )
                {
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
                                    pvalStillPoss = false;
                                }
                            }
                        }
                    }
                    if (!num_poss)
                    {
                        // pval is not possible anywhere else, this must be the value
                        //ut << "Found that...: " << *pval << " must go in square"<<"["<<row<<"]["<<col<<"]\n";
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

int SudokuReader::doLocalSquarePossPairsReduce()
{
    int numUpdated = 0;

    // Local squares are labelled as:
    // Square Numbers : 0 1 2        Starting at : 0,0 0,3 0,6
    //                  3 4 5                      3,0 3,3 3,6
    //                  6 7 8                      6,0 6,3 6,6 
    // 0 1 2 3 4 5 6 7 8 LocSqNum   == n
    // 0 0 0 3 3 3 6 6 6 Row        == 3 * ( n / 3 )
    // 0 3 6 0 3 6 0 3 6 Col        == 3 * ( n % 3 )

    // Analyze each LOCAL SQUARE
    for ( int locsq = 0 ; locsq < NumLocalSq ; locsq++ )
    {
//      if (locsq != 5)
//          continue;

        int sq_num;

        vector<int> temp;

        int                rstart = 3 * (locsq / LocalSqDim);
        int                cstart = 3 * (locsq % LocalSqDim);

        sq_num = 0;
/*
        for ( int sq_row = rstart ; sq_row < rstart + LocalSqDim ; sq_row++ )
        {
            for ( int sq_col = cstart ; sq_col < cstart + LocalSqDim ; sq_col++, sq_num++ )
            {
                cout << "Poss list for ["<<sq_row<<"]["<<sq_col<<"]: ";
                for (auto it = poss[sq_row][sq_col].begin(); it != poss[sq_row][sq_col].end() ; it++)
                {
                    cout << *it << " ";
                }
                cout << endl;
            }
        }
        cout << endl;
*/

        // Find which (if any) numbers have only two possible locations
        // and then create a list with those numbers
        int num_poss;
        vector< int > pairs;
        for ( int val = 0 ; val < 1 + SudokuReader::Dimension ; val++ )
        {
            sq_num = 0;
            num_poss = 0;
            for ( int r = rstart ; r < rstart + LocalSqDim ; r++ )
            {
                for ( int c = cstart ; c < cstart + LocalSqDim ; c++, sq_num++ )
                {
//                  cout << "Poss val for ["<<r<<"]["<<c<<"]["<<val<<"]: ";
//                  cout << poss[r][c][val] << " ";
//                  cout << endl;

                    if (poss[r][c][val] != 0) num_poss++;
                }
            }
            if (num_poss == 2)
            {
                // Add this one to list of numbers that have only two possible locations
//              cout << "Found a number that has only two possible locations " << val << endl;
                pairs.push_back(val);
            }
        }

        // Move to the next local square if there aren't
        // at least two numbers with two possible locations
        if (pairs.size() < 2)
            continue;

        // For each number, use the list of numbers with only two possible locations
        // to create a list of the squares that are candidates for the number
        vector< vector< tuple<int,int> > > squares;
        squares.resize( 1 + SudokuReader::Dimension );
        for ( auto it = pairs.begin() ; it < pairs.end(); it++ )
        {
            for ( int r = rstart ; r < rstart + LocalSqDim ; r++ )
            {
                for ( int c = cstart ; c < cstart + LocalSqDim ; c++ )
                {
                    // If the square is still unsolved
                    if (0 == square[r][c])
                    {
                        // Find if the value is in the possibility list
                        std::vector<int>::iterator aa = find_if(poss[r][c].begin(), 
                                                                poss[r][c].end(), 
                                                                [&](int i) { return i==*it; } );
                        if (aa != poss[r][c].end())
                        {
                            // Found the value, store this location
//                          cout << "Value "<<*it<<" is possible in square ["<<r<<"]["<<c<<"]." << endl;
                            assert(*it < squares.size());
                            squares[*it].push_back( make_tuple(r,c) );
                        }

                    }
                }
            }
        }

        // For each number with only two possible locations,
        // compare the lists of possible squares to see if any of them are identical
        int val1 = 0;
        vector<int> locat;
        vector< tuple<int,int> > locations;
        for ( auto it1 = squares.begin() ; it1 < squares.end(); it1++, val1++  )
        {
            if ((*it1).size())
            {
                assert(it1->size() == 2);
            }
            int val2 = val1+1;
            for ( auto it2 = it1+1 ; it2 < squares.end(); it2++, val2++ )
            {
                if (it1 != it2)
                {
                    // Check if it1 and it2 are identical (and not empty)
                    if ( (*it1 == *it2) && (it1->size()) )
                    {
                        // Success! it1 and it2 are identical (and not empty)!!

                        assert(it2->size() == 2);
//                      cout << "Found possibility lists that are identical values: " << val1 << " and " << val2 << endl;

                        // Since we have two numbers, with the same two possible locations
                        // for each, we still don't know which goes where. BUT we do know
                        // that no other numbers in that location's possibility list can work,
                        // so we can remove those numbers from that location's possibility list.

                        int r;
                        int c;
                        int val;

                        // Store it1's row and column info
                        r   = get<0>((*it1)[0]);
                        c   = get<1>((*it1)[0]);
                        val = 0;

                        // For every element in it1's possiblity list
                        for ( auto it3 = poss[r][c].begin() ; it3 != poss[r][c].end() ; it3++, val++ )
                        {
                            if (   (0 != *it3) &&
                                 ( (val1 != *it3) && (val2 != *it3) )
                               )
                            {
//                              cout << "Clearing a possibility. Setting poss["<<r<<"]["<<c<<"]["<<val<<"] = 0." << endl;
                                poss[r][c][val] = 0;
                                numUpdated++;
                            }
                        }

                        r   = get<0>((*it1)[1]);
                        c   = get<1>((*it1)[1]);
                        val = 0;
                        for ( auto it3 = poss[r][c].begin() ; it3 != poss[r][c].end() ; it3++, val++ )
                        {
                            if (   (0!= *it3) &&
                                 ( (val1 != *it3) && (val2 != *it3) )
                               )
                            {
//                              cout << "Clearing a possibility. Setting poss["<<r<<"]["<<c<<"]["<<val<<"] = 0." << endl;
                                poss[r][c][val] = 0;
                                numUpdated++;
                            }
                        }
                    }
                }
            }   
        }
    }

    return numUpdated;

}

static int whichLocalSquare(int row, int col)
{
    // Local squares are labelled as:
    // Square Numbers : 0 1 2        Starting at : 0,0 0,3 0,6
    //                  3 4 5                      3,0 3,3 3,6
    //                  6 7 8                      6,0 6,3 6,6 
    // 0 1 2 3 4 5 6 7 8 LocSqNum   == n
    // 0 0 0 3 3 3 6 6 6 Row        == 3 * ( n / 3 )
    // 0 3 6 0 3 6 0 3 6 Col        == 3 * ( n % 3 )

    int rowStart = 3 * ( row / 3 );
    int colStart = 3 * ( col / 3 );

    int locSQ    = rowStart + (colStart / 3);

    return locSQ;
}

int  SudokuReader::doLocalSquareSingleColumnPossReduce()
{
    int numUpdated = 0;

    // Local squares are labelled as:
    // Square Numbers : 0 1 2        Starting at : 0,0 0,3 0,6
    //                  3 4 5                      3,0 3,3 3,6
    //                  6 7 8                      6,0 6,3 6,6 
    // 0 1 2 3 4 5 6 7 8 LocSqNum   == n
    // 0 0 0 3 3 3 6 6 6 Row        == 3 * ( n / 3 )
    // 0 3 6 0 3 6 0 3 6 Col        == 3 * ( n % 3 )

    // Analyze each LOCAL SQUARE
    for ( int locsq = 0 ; locsq < NumLocalSq ; locsq++ )
    {
//      if (( locsq != 5) && (locsq != 2))
//      if (( locsq != 2) && (locsq != 2))
//          continue;

        int sq_num;

        vector<int> temp;

        int                rstart = 3 * (locsq / LocalSqDim);
        int                cstart = 3 * (locsq % LocalSqDim);

        sq_num = 0;
/*
        for ( int sq_row = rstart ; sq_row < rstart + LocalSqDim ; sq_row++ )
        {
            for ( int sq_col = cstart ; sq_col < cstart + LocalSqDim ; sq_col++, sq_num++ )
            {
                cout << "Poss list for ["<<sq_row<<"]["<<sq_col<<"]: ";
                for (auto it = poss[sq_row][sq_col].begin(); it != poss[sq_row][sq_col].end() ; it++)
                {
                    cout << *it << " ";
                }
                cout << endl;
            }
        }
        cout << endl;
*/

        // Find which (if any) numbers have only two or three possible locations
        // and then create a list with those numbers

        int num_poss;
        vector< int > two_three_poss;

        // For each possible value 1 - 9
        for ( int val = 1 ; val < 1 + SudokuReader::Dimension ; val++ )
        {
            sq_num = 0;
            num_poss = 0;
            // Search for that value in each element's possibility list
            for ( int r = rstart ; r < rstart + LocalSqDim ; r++ )
            {
                for ( int c = cstart ; c < cstart + LocalSqDim ; c++, sq_num++ )
                {
//                  cout << "Poss val for ["<<r<<"]["<<c<<"]["<<val<<"]: ";
//                  cout << poss[r][c][val] << " ";
//                  cout << endl;

                    if (poss[r][c][val] != 0) num_poss++;
                }
            }

            // If this list of numbers has only two or three possible locations
            if ( (num_poss == 2) || (num_poss == 3) )
            {
                // Add this one to list
//               cout << "Found a number that has only two or three possible locations " << val << endl;
                two_three_poss.push_back(val);
            }
        }

        // For each number, use the list of numbers with only two or three possible
        // locations to create a list of the squares that are candidates for the number
        vector< vector< tuple<int,int> > > squares;
        squares.resize( 1 + SudokuReader::Dimension );
        for ( auto it = two_three_poss.begin() ; it < two_three_poss.end(); it++ )
        {
            for ( int r = rstart ; r < rstart + LocalSqDim ; r++ )
            {
                for ( int c = cstart ; c < cstart + LocalSqDim ; c++ )
                {
                    // If the square is still unsolved
                    if (0 == square[r][c])
                    {
                        // Find if the value is in the possibility list
                        std::vector<int>::iterator aa = find_if(poss[r][c].begin(), 
                                                                poss[r][c].end(), 
                                                                [&](int i) { return i==*it; } );
                        if (aa != poss[r][c].end())
                        {
                            // Found the value, store this location
//                          cout << "Value "<<*it<<" is possible in square ["<<r<<"]["<<c<<"].." << endl;
                            assert(*it < squares.size());
                            squares[*it].push_back( make_tuple(r,c) );
                        }

                    }
                }
            }
        }

        // For each number with only two or three possible locations,
        // see if they are only possible within a single column
        int val = 0;
        vector< tuple<int,int> > locations;
        for ( auto it1 = squares.begin() ; it1 < squares.end(); it1++, val++  )
        {
            if (!(*it1).size())
            {
                continue;
            }
            assert(it1->size() >= 2);
            assert(it1->size() <= 3);
//          cout << "Determining if " << val << " is only in one column...\n";

//          cout << "Coordinates for " << val << endl;
            int row = -1;
            int col = -1;
            bool same_col = true;
            bool same_row = true;
            for ( auto it2 = squares[val].begin(); it2 < squares[val].end(); it2++ )
            {
                int this_row = get<0>((*it2));
                int this_col = get<1>((*it2));
//              cout << "[" << this_row << "," << this_col << "]\n";

                if (same_row != false)
                {
                    if (row == -1)
                    {
                        row = this_row;
                    }
                    
                    if (row != this_row)
                    {
                        same_row = false;
//                      cout << "Possible locations for " << val << " are in different rows.\n";
                    }
                }

                if (same_col != false)
                {
                    if (col == -1)
                    {
                        col = this_col;
                    }
                    
                    if (col != this_col)
                    {
                        same_col = false;
//                      cout << "Possible locations for " << val << " are in different columns.\n";
                    }
                }

                if ( (same_row == false) && (same_col == false) )
                {
//                  cout << "Possible locations for " << val << " are in different rows AND columns.\n";
                    break;
                }
            }

            if (same_row == true)
            {
//              cout << "Possible locations for " << val << " are only in row " << row << "!\n";

                // Since val1 can only be in this local square in row 'row', we can remove
                // it from all other possibility lists for this row
                for ( int col = 0 ; col < Dimension ; col++ )
                {
                    // Only do this for rows not in this local square
                    if (locsq == whichLocalSquare(row, col))
                    {
                        continue;
                    }

                    // This element isn't known yet
                    if ( !square[row][col] )
                    {
                        // If this value is still a possibility
                        if (poss[row][col][val] == val)
                        {
//                          cout << "Removing " << val 
//                                              << " from row " << row 
//                                              << ", col " << col 
//                                              << "'s possibility list.\n";
                            poss[row][col][val] = 0;
                            numUpdated++;
                        }
                    }
                }
            }

            if (same_col == true)
            {
//              cout << "Possible locations for " << val << " are only in column " << col << "!\n";

                // Since val1 can only be in this local square in column 'col', we can remove
                // it from all other possibility lists for this column
                for ( int row = 0 ; row < Dimension ; row++ )
                {
                    // Only do this for rows not in this local square
                    if (locsq == whichLocalSquare(row, col))
                    {
                        continue;
                    }

                    // This element isn't known yet
                    if ( !square[row][col] )
                    {
                        // If this value is still a possibility
                        if (poss[row][col][val] == val)
                        {
//                          cout << "Removing " << val 
//                                              << " from row " << row 
//                                             << ", col " << col 
//                                              << "'s possibility list.\n";
                            poss[row][col][val] = 0;
                            numUpdated++;
                        }
                    }
                }
            }
        }
    }

    return numUpdated;

}

int SudokuReader::doOnlyPossPass()
{
    int numUpdated = 0;

    // For each row
    for (int row = 0 ; row < SudokuReader::Dimension ; row++ )
    {
        // For each possible number (1-9), find the number of
        // occurrances in all the possibility lists
        for (int num = 1 ; num <= SudokuReader::Dimension ; num++ )
        {
            int col = 0;            // column iterator
            int ffc = 0;            // first found column
            int num_occurances = 0;
            bool unknown = true;
            do
            {
                // If this number has already been solved, don't bother
                if (num == square[row][col])
                {
                    unknown = false;
                    break;
                }
                
                // Find if 'num' occurs in this possibility
                // list, mark the first list it occurs in 
                num_occurances += count_if(poss[row][col].begin(),
                                           poss[row][col].end(),
                                           [&](const auto& e) { 
                                                                if ( e == num ) { ffc = col; }
                                                                return e == num;                    
                                                              });
                col++;

            } while ( (col < SudokuReader::Dimension) && (num_occurances < 2) );

            if ( unknown && (num_occurances == 1) )
            {
//              cout << num << " is possible " << num_occurances << " time(s) in row: " 
//                   << row << ", at [" << row << "][" << ffc << "].\n";
                std::fill(poss[row][ffc].begin(), poss[row][ffc].end(), 0);
                poss[row][ffc][num] = num;
                numUpdated++;
            }
            
        }
    }

    return numUpdated;
}