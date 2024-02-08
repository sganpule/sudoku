
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

    enum
    {
        NoError,
        FoundEntryLongerThanSingleChar,
        FoundEntryThatIsNotADigit,
        FoundInvalidSeparator
    } SudokuReaderErrorValues;

    static const int    Dimension;
    static const string DotSeparator;
    static const string XSeparator;

private:

    bool                    inSquareValid;
    vector< vector<int> >   inSquare;

    int validateInput();

    
};

#endif // SUDOKU_READER_H
