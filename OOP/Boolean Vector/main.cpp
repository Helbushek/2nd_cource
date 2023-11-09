#include "BooleanVector.h"
#include <iostream>



int main() {
	BoolVector test("000000001");
	std::cout << !test[0];
	test = test << 1;
	std::cout << std::endl;
	(test).print();
	return(0);
}