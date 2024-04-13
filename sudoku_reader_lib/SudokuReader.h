
#ifndef SUDOKU_READER_H
#define SUDOKU_READER_H

#include <fstream>
#include <vector>

using namespace std;


class SudokuReader
{

public:

    SudokuReader();
    
    int readFile(fstream& is);
    int isValid(int* error_row = NULL, int *error_col = NULL);
    int solve();

    friend ostream& operator<<(ostream& os, SudokuReader sr);

    enum
    {
        NoError,
        FoundEntryLongerThanSingleChar,
        FoundEntryThatIsNotADigit,
        FoundInvalidSeparator,
        FoundDuplicateEntryRow,
        FoundDuplicateEntryCol,
        FoundDuplicateEntryLocSq 
    } SudokuReaderErrorValues;

    enum
    {
        Solved,
        NotSolved
    } SudokuReaderSolveReturnValues;

    static const int    NumLocalSq;
    static const int    LocalSqDim;
    static const int    Dimension;
    static const string DotSeparator;
    static const string XSeparator;

private:

    bool                              isSquareValid;
    vector< vector< int          > >  square;
    vector< vector< vector <int> > >  poss;

    void updatePossLists();
    int  updateSquare();
    int  doOnePossPass();
    int  doMultiPossPass();
    int  doLocalSquarePossPairsReduce();
    int  doLocalSquareSingleColumnPossReduce();

    void printPoss();
    int  isSolved();
    int  validateInput();

    
};

#endif // SUDOKU_READER_H
