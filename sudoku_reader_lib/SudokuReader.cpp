// Sudoku Reader

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <assert.h>

#include "SudokuReader.h"

using namespace std;

int sudokuRead(fstream& is, vector<vector<int>> *square)
{
    string              cin;
    int                 cin_int;
    int                 returnVal = 0;

    is >> cin;
    cin_int = stoi(cin);
    if ( (cin_int < 1) ||
         (cin_int > 9)    )
    {
       cin_int = 0;
       cerr << "Found an entry (" 
            << cin 
            << ") not between 1-9... Replacing with 0" << endl;
    }
    cout << cin_int;

    return returnVal;
}

SudokuReader::SudokuReader() : inSquareValid(false)
{
    // Resize sudoku square storage to SudokuReaderDim x SudokuReaderDim
    inSquare.resize( SudokuReaderDim, vector<int>(SudokuReaderDim) );
    assert(SudokuReaderDim == inSquare.size());
    assert(SudokuReaderDim == inSquare[0].size());
}

int SudokuReader::readFile(fstream& is)
{
    string  cin;
    int     cin_int;
    int     returnVal = 0;

    is >> cin;
    if (cin.length() != 1)
    {
       cerr << "Found an entry (" 
            << cin 
            << ") longer than a single character" << endl;
        returnVal = 1;
    }
    cin_int = stoi(cin);
    if ( (cin_int < 1) ||
         (cin_int > 9)    )
    {
       cin_int = 0;
       cerr << "Found an entry (" 
            << cin 
            << ") not between 1-9... Replacing with 0" << endl;

        returnVal = 1;
    }
    cout << cin_int;

    return returnVal;
}