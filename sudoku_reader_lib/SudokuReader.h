
#ifndef SUDOKU_READER_H
#define SUDOKU_READER_H

#include <fstream>
#include <vector>

using namespace std;

int sudokuRead(fstream& is, vector<vector<int>> *square);

class SudokuReader
{
    public:

    SudokuReader();
    
    int readFile(fstream& is);

    private:

    bool                    inSquareValid;
    vector< vector<int> >   inSquare;

    int validateInput();

    
};

#endif // SUDOKU_READER_H