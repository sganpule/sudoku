// Sudoku Solver

#include <fstream>
#include <iostream>
#include "sudoku_lib.h"
#include "SudokuReader.h"

using namespace std;

int main()
{
    cout << "Welcome to the sudoku solver" << endl;

    cout << "Reading in 10: " << read(10) << endl;

    fstream fin;
    fin.open("../inputs/easy_input_1.txt");
    if (!(fin.is_open()))
    {
        cerr << "File open error!" << endl;
        exit(EXIT_FAILURE);
    }

    vector< vector<int> > square;
    sudokuRead(fin, &square);
    
}