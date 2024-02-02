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
    if (-1 == parseInput(argc, argv, inputFile))
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

    cout << "Reading in 10: " << read(10) << endl;


    SudokuReader reader;
    reader.readFile(fin);
    
}

int parseInput(int argc, char* argv[], string& inputFile)
{
    if (argc != NumArgumentsForApp)
    {
        cout << "Usage: sudoku_app <inputfile>" << endl;
        return IncorrectCommandLineUsage;
    }
    else
    {
        inputFile = argv[InputFileName];
    }
    return 0;
}

int openInputFile(fstream& fin, string& inputFileName)
{
    int returnVal = 0;

    fin.open(inputFileName);
    if (!(fin.is_open()))
    {
        cerr << "File open error! Could not open '" 
             << inputFileName << "'."
             << endl;
        returnVal = CouldNotOpenInputFile;
    }

    return returnVal;
}

