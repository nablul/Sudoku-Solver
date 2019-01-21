#include"Field.h"

//Default constructor
Field::Field() {
	value = 0;
	solutions = 9;
};

//Clear given number in field and update number of possible solutions
bool Field::clearNumber(int num) {
	if (array[num - 1] == 1) {
		array[num - 1] = 0;
		--solutions;
		return true;
	}
	else {
		return false;
	};
};

//If only one solution is possible in field, solve and set field
int Field::solveField() {
	if (solutions == 1) {
		for (int i = 0; i < 9; ++i) {
			if (array[i] == 1) {
				setField(i + 1);
				return i + 1;
			};
		};
	};
	return 0;
};

//Set field value and make number of solutions possible = 0
void Field::setField(int val) {
	array = { 0,0,0,0,0,0,0,0,0 };
	array[val - 1] = 1;
	value = val;
	solutions = 0;
	return;
};
