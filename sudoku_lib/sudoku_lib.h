// Header code for the Sudoku lib

#include <vector>

using namespace std;

int read(int arg);

class Sudoku
{
    public:

    Sudoku();

    const int SudokuDim = 9;

    private:

    vector< vector< int          > > square;
    vector< vector< vector<int>* > > sqposs;
};