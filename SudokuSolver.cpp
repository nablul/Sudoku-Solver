#include"SudokuSolver.h"

//Default constructor. Set up Sudoku with 9x9 fields
SudokuSolver::SudokuSolver(const std::string &str) {
	int squareID;
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			//Create new field for row and col
			matrix[i][j] = new Field;
			//Create square pointer to already created field
			Field *fieldPtr = matrix[i][j];
			//Determine square number
			squareID = ((floor(i / 3)) * 3) + (floor(j / 3));
			squareIDs[squareID].push_back(fieldPtr);
		};
	};
	importInput(str);
};

//Turn user input string into initialized Sudoku board
void SudokuSolver::importInput(const std::string &str) {
	int stringCounter = 0;
	int integerStr;
	int squareID;
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			//Set field with no input = 0
			integerStr = str[stringCounter] - '0';
			if (integerStr != 0) {
				matrix[i][j]->setField(integerStr);
				//Determine square
				squareID = ((floor(i / 3)) * 3) + (floor(j / 3));

				//Clear corresponding row, column and square
				clearRow(i, integerStr);
				clearCol(j, integerStr);
				clearSquare(squareID, integerStr);
			}
			++stringCounter;
		};
	};
};

//For a given value and row, clear all instances of that value in that row
void SudokuSolver::clearRow(const int &fieldRow, const int &val) {
	for (int j = 0; j < 9; ++j) {
		if (matrix[fieldRow][j]->value == 0) {
			matrix[fieldRow][j]->clearNumber(val);
		};
	};
};

//For a given value and column, clear all instances of that value in that column
void SudokuSolver::clearCol(const int &fieldCol, const int &val) {
	for (int i = 0; i < 9; ++i) {
		if (matrix[i][fieldCol]->value == 0) {
			matrix[i][fieldCol]->clearNumber(val);
		};
	};
};

//For a given value and sqaure, clear all instances of that value in that square
void SudokuSolver::clearSquare(const int &fieldSquare, const int &val) {
	for (int k = 0; k < 9; ++k) {
		if (squareIDs[fieldSquare][k]->value == 0) {
			squareIDs[fieldSquare][k]->clearNumber(val);
		};
	};
};

//Function to solve a given row for a given value
bool SudokuSolver::solveRow(const int &fieldRow, const int &val) {
	int solutionsCounter = 0;
	//Calculate number of possible solutions in row for given value
	for (int j = 0; j < 9; ++j) {
		solutionsCounter = solutionsCounter + matrix[fieldRow][j]->array[val - 1];
	};
	//If only one field has possible solution, solve for that field and clear all respective rows, columns and squares
	if (solutionsCounter == 1) {
		for (int j = 0; j < 9; ++j) {
			if (matrix[fieldRow][j]->array[val - 1] == 1) {
				if (matrix[fieldRow][j]->value == 0) {
					matrix[fieldRow][j]->setField(val);
					int squareID = ((floor(fieldRow / 3)) * 3) + (floor(j / 3));
					clearRow(fieldRow, val);
					clearCol(j, val);
					clearSquare(squareID, val);
					return true;
				};
			};
		};
	};
	//Check each column and matrix within given row for single solution. Clear all respective rows, columns and squares
	for (int j = 0; j < 9; ++j) {
		if ((matrix[fieldRow][j]->solutions == 1) && matrix[fieldRow][j]->array[val - 1] == 1) {
			if (matrix[fieldRow][j]->value == 0) {
				matrix[fieldRow][j]->setField(val);
				int squareID = ((floor(fieldRow / 3)) * 3) + (floor(j / 3));
				clearRow(fieldRow, val);
				clearCol(j, val);
				clearSquare(squareID, val);
				return true;
			};
		};
	};
	return false;
};

//Function to solve a given column for a given value
bool SudokuSolver::solveCol(const int &fieldCol, const int &val) {
	std::pair<int, int> RowCol;
	int solutionsCounter = 0;
	//Calculate number of possible solutions in column for given value
	for (int i = 0; i < 9; ++i) {
		solutionsCounter = solutionsCounter + matrix[i][fieldCol]->array[val - 1];
	};
	//If only one field has possible solution, solve for that field and clear all respective rows, columns and squares
	if (solutionsCounter == 1) {
		for (int i = 0; i < 9; ++i) {
			if (matrix[i][fieldCol]->array[val - 1] == 1) {
				if (matrix[i][fieldCol]->value == 0) {
					matrix[i][fieldCol]->setField(val);
					int squareID = ((floor(i / 3)) * 3) + (floor(fieldCol / 3));
					clearRow(i, val);
					clearCol(fieldCol, val);
					clearSquare(squareID, val);
					return true;
				};
			};
		};
	};
	//Check each row and matrix within given row for single solution. Clear all respective rows, columns and squares
	for (int i = 0; i < 9; ++i) {
		if ((matrix[i][fieldCol]->solutions == 1) && matrix[i][fieldCol]->array[val - 1] == 1) {
			if (matrix[i][fieldCol]->value == 0) {
				matrix[i][fieldCol]->setField(val);
				int squareID = ((floor(i / 3)) * 3) + (floor(fieldCol / 3));
				clearRow(i, val);
				clearCol(fieldCol, val);
				clearSquare(squareID, val);
				return true;
			};
		};
	};
	return false;
};

//Function to solve a given square for a given value
bool SudokuSolver::solveSquare(const int &fieldSquare, const int &val) {
	std::pair<int, int> RowCol;
	int solutionsCounter = 0;
	//Calculate number of possible solutions in squares for given value
	for (int k = 0; k < 9; ++k) {
		solutionsCounter = solutionsCounter + squareIDs[fieldSquare][k]->array[val - 1];
	};
	//If only one field has possible solution, solve for that field and clear all respective rows, columns and squares
	if (solutionsCounter == 1) {
		for (int k = 0; k < 9; ++k) {
			if (squareIDs[fieldSquare][k]->array[val - 1] == 1) {
				if (squareIDs[fieldSquare][k]->value == 0) {
					squareIDs[fieldSquare][k]->setField(val);
					int i = ((floor(fieldSquare / 3)) * 3) + (floor(k / 3));
					int j = ((fieldSquare % 3) * 3) + (k % 3);
					clearRow(i, val);
					clearCol(j, val);
					clearSquare(fieldSquare, val);
					return true;
				};
			};
		};
	};
	//Check each row and column within given row for single solution. Clear all respective rows, columns and squares
	for (int k = 0; k < 9; ++k) {
		if ((squareIDs[fieldSquare][k]->solutions == 1) && squareIDs[fieldSquare][k]->array[val - 1] == 1) {
			if (squareIDs[fieldSquare][k]->value == 0) {
				squareIDs[fieldSquare][k]->setField(val);
				int i = ((floor(fieldSquare / 3)) * 3) + (floor(k / 3));
				int j = ((fieldSquare % 3) * 3) + (k % 3);
				clearRow(i, val);
				clearCol(j, val);
				clearSquare(fieldSquare, val);
				return true;
			};
		};
	};
	return false;
};

//Check if column has a solved state
bool SudokuSolver::checkRow(const int &fieldRow) {
	int solutionCheckArray[9];
	//If a field in the row is not at a solved state, column is not solved
	for (int j = 0; j < 9; ++j) {
		if (matrix[fieldRow][j]->value == 0 || matrix[fieldRow][j]->solutions != 0) {
			return false;
		}
		//Else push solved field value into solutions vector
		solutionCheckArray[(matrix[fieldRow][j]->value) - 1] = (matrix[fieldRow][j]->value) - 1;
	};
	//Check if all values in solutions vector are unique
	for (int m = 0; m < 9; ++m) {
		if (solutionCheckArray[m] != m) {
			return false;
		};
	};
	return true;
};

//Check if column has a solved state
bool SudokuSolver::checkCol(const int &fieldCol) {
	int solutionCheckArray[9];
	//If a field in the column is not at a solved state, column is not solved
	for (int i = 0; i < 9; ++i) {
		if (matrix[i][fieldCol]->value == 0 || matrix[i][fieldCol]->solutions != 0) {
			return false;
		}
		//Else push solved field value into solutions vector
		solutionCheckArray[(matrix[i][fieldCol]->value) - 1] = (matrix[i][fieldCol]->value) - 1;
	};
	//Check if all values in solutions vector are unique
	for (int m = 0; m < 9; ++m) {
		if (solutionCheckArray[m] != m) {
			return false;
		};
	};
	return true;
};

//Check if square has a solved state
bool SudokuSolver::checkSquare(const int &fieldSquare) {
	int solutionCheckArray[9];
	//If a field in the square is not at a solved state, square is not solved
	for (int k = 0; k < 9; ++k) {
		if (squareIDs[fieldSquare][k]->value == 0 || squareIDs[fieldSquare][k]->solutions != 0) {
			return false;
		}
		//Else push solved field value into solutions vector
		solutionCheckArray[(squareIDs[fieldSquare][k]->value) - 1] = (squareIDs[fieldSquare][k]->value) - 1;
	};
	//Check if all values in solutions vector are unique
	for (int m = 0; m < 9; ++m) {
		if (solutionCheckArray[m] != m) {
			return false;
		};
	};
	return true;
};

//Iterate through all rows and check them
bool SudokuSolver::checkAllRows() {
	for (int i = 0; i < 9; ++i) {
		if (!checkRow(i)) {
			return false;
		};
	};
	return true;
};

//Iterate through all columns and check them
bool SudokuSolver::checkAllCols() {
	for (int j = 0; j < 9; ++j) {
		if (!checkCol(j)) {
			return false;
		};
	};
	return true;
};

//Iterate through all squares and check them
bool SudokuSolver::checkAllSquares() {
	for (int k = 0; k < 9; ++k) {
		if (!checkSquare(k)) {
			return false;
		};
	};
	return true;
};

//Function to solve Sudoku
void SudokuSolver::solve() {
	int solutionsThisRun;
	int checkErrors = 0;

	do {
		solutionsThisRun = 0;

		//Iterate through each row for each number and see if row can be solved
		for (int i = 0; i < 9; ++i) {
			for (int m = 0; m < 9; ++m) {
				if (solveRow(i, m + 1)) {
					++solutionsThisRun;
				};
			};
		};

		//Iterate through each column for each number and see if column can be solved
		for (int j = 0; j < 9; ++j) {
			for (int m = 0; m < 9; ++m) {
				if (solveCol(j, m + 1)) {
					++solutionsThisRun;
				};
			};
		};

		//Iterate through each square for each number and see if square can be solved
		for (int k = 0; k < 9; ++k) {
			for (int m = 0; m < 9; ++m) {
				if (solveSquare(k, m + 1)) {
					++solutionsThisRun;
				};
			};
		};
	//Exit if two consequtive interations yielded no additional solution
	} while (solutionsThisRun != 0);

	//Check row
	for (int i = 0; i < 9; ++i) {
		if (!checkRow(i)) {
			++checkErrors;
		};
	};

	//Check column
	for (int j = 0; j < 9; ++j) {
		if (!checkCol(j)) {
			++checkErrors;
		};
	};

	//Check square
	for (int k = 0; k < 9; ++k) {
		if (!checkSquare(k)) {
			++checkErrors;
		};
	};

	//If no error for rows, columns and squares, Sudoku solved.
	if (checkErrors == 0) {
		std::cout << "Congrats! Sudoku was solved:\n\n";
		printMatrix();
	}
	//No solution
	else {
		std::cout << "Sorry! Sudoku could not be solved without guessing or advanced techniques that are not yet supported in this solver :(\n\n";
	};
};

//Function to print matrix
void SudokuSolver::printMatrix() {
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			std::cout << matrix[i][j]->value << " ";
			if ((j % 3) == 2) {
				std::cout << " ";
			};
		}
		std::cout << std::endl;
		if ((i % 3) == 2) {
			std::cout << "\n";
		};
	};
};

//Function to print a single square
void SudokuSolver::printSquare() {
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			std::cout << squareIDs[i][j]->value << " ";
		};
		std::cout << std::endl;
	};
};

//Function to output solutions matrix
void SudokuSolver::printSolutions() {
	std::vector<std::vector<int>> solutionMatrix = std::vector<std::vector<int>>(27, std::vector<int>(27, -1));

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			solutionMatrix[(i * 3)][(j * 3)] = matrix[i][j]->array[0];
			solutionMatrix[(i * 3)][(j * 3) + 1] = matrix[i][j]->array[1];
			solutionMatrix[(i * 3)][(j * 3) + 2] = matrix[i][j]->array[2];
			solutionMatrix[(i * 3) + 1][(j * 3)] = matrix[i][j]->array[3];
			solutionMatrix[(i * 3) + 1][(j * 3) + 1] = matrix[i][j]->array[4];
			solutionMatrix[(i * 3) + 1][(j * 3) + 2] = matrix[i][j]->array[5];
			solutionMatrix[(i * 3) + 2][(j * 3)] = matrix[i][j]->array[6];
			solutionMatrix[(i * 3) + 2][(j * 3) + 1] = matrix[i][j]->array[7];
			solutionMatrix[(i * 3) + 2][(j * 3) + 2] = matrix[i][j]->array[8];
		};
	};

	for (int i = 0; i < 27; ++i) {
		for (int j = 0; j < 27; ++j) {
			std::cout << solutionMatrix[i][j];
			if ((j % 3) == 2) {
				std::cout << " ";
			};
			if ((j % 9) == 8) {
				std::cout << "| ";
			};
		};
		std::cout << std::endl;
		if ((i % 3) == 2) {
			std::cout << "\n";
		};
		if ((i % 9) == 8) {
			std::cout << "-----------------------------------------";
			std::cout << "\n";
		};
	};
};
