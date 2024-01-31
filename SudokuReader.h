
#ifndef SUDOKU_READER_H
#define SUDOKU_READER_H

#include <fstream>
#include <vector>

using namespace std;

int sudokuRead(fstream& is, vector<vector<int>> *square);

#endif // SUDOKU_READER_H
