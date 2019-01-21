#ifndef SUDOKUSOLVER_FIELD_H_
#define SUDOKUSOLVER_FIELD_H_

#include"vector"

struct Field {
	int value;
	int solutions;
	std::vector<int> array = { 1,1,1,1,1,1,1,1,1 };

	//Default constructor
	Field();

	//Clear given number in field and update number of possible solutions
	bool clearNumber(int num);

	//If only one solution is possible in field, solve and set field
	int solveField();

	//Set field value and make number of solutions possible = 0
	void setField(int val);
};

#endif