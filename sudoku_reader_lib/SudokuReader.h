
#ifndef SUDOKU_READER_H
#define SUDOKU_READER_H

#include <fstream>
#include <vector>

using namespace std;

int sudokuRead(fstream& is, vector<vector<int>> *square);

const int SudokuReaderDim = 9;

class SudokuReader
{

public:

    SudokuReader();
    
    int readFile(fstream& is);

    enum
    {
        NoError,
        FoundEntryLongerThanSingleChar,
        FoundEntryThatIsNotADigit,
        FoundInvalidSeparator
    } SudokuReaderErrorValues;

    static const string DotSeparator;
    static const string XSeparator;

private:

    bool                    inSquareValid;
    vector< vector<int> >   inSquare;

    int validateInput();

    
};

#endif // SUDOKU_READER_H
