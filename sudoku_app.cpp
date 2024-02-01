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

int parse_input(int argc, char* argv[], string& inputFile)
{
    if (argc != NumArgumentsForApp)
    {
        cout << "Usage: sudoku_app <inputfile>" << endl;
        return -1;
    }
    else
    {
        inputFile = argv[InputFileName];
    }
    return 0;
}

int main(int argc, char* argv[])
{
    cout << "Welcome to the sudoku solver" << endl;

    string inputFile;
    if (-1 == parse_input(argc, argv, inputFile))
    {
        exit(1);
    }
    cout << "Solving input file '" << inputFile << "'..." << endl;

    cout << "Reading in 10: " << read(10) << endl;

    fstream fin;
    fin.open(inputFile);
    if (!(fin.is_open()))
    {
        cerr << "File open error! Could not open '" 
             << inputFile << "'."
             << endl;
        exit(EXIT_FAILURE);
    }

    SudokuReader reader;
    reader.readFile(fin);
    
}