// Sudoku Solver

#include <fstream>
#include <iostream>
#include "sudoku_lib.h"
#include "SudokuReader.h"

using namespace std;

const int NumArgumentsForApp = 2;

enum
{
    ApplicationName,
    InputFileName
} InputArguments;

enum
{
    NoError,
    IncorrectCommandLineUsage,
    CouldNotOpenInputFile
} SudokuAppErrorValues;

// Forward declarations
int parseInput(int argc, char* argv[], string& inputFile);
int openInputFile(fstream& fin, string& inputFileName);



int main(int argc, char* argv[])
{
    cout << "Welcome to the sudoku solver" << endl;

    // Get input file
    string inputFile;
    if (IncorrectCommandLineUsage == parseInput(argc, argv, inputFile))
    {
        exit(EXIT_FAILURE);
    }

    // Open input file
    fstream fin;
    if (openInputFile(fin, inputFile))
    {
        exit(EXIT_FAILURE);
    }

    cout << "Solving input file '" << inputFile << "'..." << endl;

    // Read in the puzzle
    int          status;
    SudokuReader reader;
    if ( (status = reader.readFile(fin)) )
    {
        cerr << "Error " << status << " found while reading in '" << inputFile << "'.\n";
    }

    int error_row;
    int error_col;
    if ( (status = reader.isValid(&error_row, &error_col)) )
    {
        cerr << "Error: Found input error at row " << error_row+1 << ", col " << error_col+1 << ".\n";
    }

    cout << "This is what we're working on:\n" << reader;
}



int parseInput(int argc, char* argv[], string& inputFile)
{
    int retVal = NoError;

    if (argc != NumArgumentsForApp)
    {
        cout << "Usage: sudoku_app <inputfile>" << endl;
        retVal = IncorrectCommandLineUsage;
    }
    else
    {
        retVal = NoError;
        inputFile = argv[InputFileName];
    }
    return retVal;
}

int openInputFile(fstream& fin, string& inputFileName)
{
    int retVal = NoError;

    fin.open(inputFileName);
    if (!(fin.is_open()))
    {
        cerr << "File open error! Could not open '" 
             << inputFileName << "'."
             << endl;
        retVal = CouldNotOpenInputFile;
    }

    return retVal;
}

