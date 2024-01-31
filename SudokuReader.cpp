// Sudoku Reader

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int sudokuRead(fstream& is, vector<vector<int>> *square)
{
    char                cin;
    int                 cin_int;
    int                 returnVal = 0;

    is >> cin;
    cin_int = stoi(&cin);
    if ( (cin_int < 1) ||
         (cin_int > 9)    )
    {
       cin_int = 0;
    }
    cout << cin_int;

    return returnVal;
}