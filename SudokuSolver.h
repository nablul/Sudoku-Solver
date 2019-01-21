#ifndef SUDOKUSOLVER_SUDOKUSOLVER_H_
#define SUDOKUSOLVER_SUDOKUSOLVER_H_

#include<iostream>
#include <cmath>
#include <utility>
#include"string"
#include"Field.h"

class SudokuSolver {
	std::vector<std::vector<Field*>> matrix = std::vector<std::vector<Field*>>(9, std::vector<Field*>(9));
	std::vector<std::vector<Field*>> squareIDs = std::vector<std::vector<Field*>>(9, std::vector<Field*>(0));

public:
	//Default constructor. Set up Sudoku with 9x9 fields
	SudokuSolver(const std::string &str);

	//Turn user input string into initialized Sudoku board
	void importInput(const std::string &str);

	//For a given value and row, clear all instances of that value in that row
	void clearRow(const int &fieldRow, const int &val);

	//For a given value and column, clear all instances of that value in that column
	void clearCol(const int &fieldCol, const int &val);

	//For a given value and sqaure, clear all instances of that value in that square
	void clearSquare(const int &fieldSquare, const int &val);

	//Function to solve a given row for a given value
	bool solveRow(const int &fieldRow, const int &val);

	//Function to solve a given column for a given value
	bool solveCol(const int &fieldCol, const int &val);

	//Function to solve a given square for a given value
	bool solveSquare(const int &fieldSquare, const int &val);

	//Check if column has a solved state
	bool checkRow(const int &fieldRow);

	//Check if column has a solved state
	bool checkCol(const int &fieldCol);

	//Check if square has a solved state
	bool checkSquare(const int &fieldSquare);

	//Iterate through all rows and check them
	bool checkAllRows();

	//Iterate through all columns and check them
	bool checkAllCols();

	//Iterate through all squares and check them
	bool checkAllSquares();

	//Function to solve Sudoku
	void solve();

	//Function to print matrix
	void printMatrix();

	//Function to print a single square
	void printSquare();

	//Function to output solutions matrix
	void printSolutions();
};

#endif