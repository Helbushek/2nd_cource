#include "BooleanVector.h"
#include <iostream>

int main() {
	BoolVector test("00000010100000");
	const bool temp = test[0];
	std::cout << temp;
	std::cout << std::endl;
	test = test << 2;
	test.print();
	test >>= 2;
	std::cout << std::endl;
	test.print();
	return(0);
}