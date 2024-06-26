// Source code for the Sudoku lib

#include "sudoku_lib.h"
#include <assert.h>


Sudoku::Sudoku(void)
{
    // Resize sudoku square storage to SudokuDim x SudokuDim
    square.resize( SudokuDim, vector<int>(SudokuDim) );
    assert(SudokuDim == square.size());
    assert(SudokuDim == square[0].size());

    for (int i = 0; i < SudokuDim ; i++)
    {
        for (int j = 0 ; j < SudokuDim ; j++ )
        {
            square[i][j] = 0;
        }
    }
}