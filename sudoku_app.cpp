// Sudoku Solver

#include <fstream>
#include <iostream>
#include "sudoku_lib.h"
#include "SudokuReader.h"

using namespace std;

int parse_input(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Usage: sudoku_app <inputfile>" << endl;
        return -1;
    }
    return 0;
}

int main(int argc, char* argv[])
{
    cout << "Welcome to the sudoku solver" << endl;
    if (-1 == parse_input(argc, argv))
    {
        exit(1);
    }

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