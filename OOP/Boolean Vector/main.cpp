#include "BooleanVector.h"
#include <iostream>



int main() {
	BoolVector test("1010101000000000");
	test.print();
	BoolVector test2("0011");
	test.swap(test2);
	
	test.setBits(0, 1, 1);
	test.setAll(0);
	test.setAll(1);
	std::cout << std::endl;
	test.print();
	test[1] = 0;
	std::cout << std::endl;
	test.print();
	return(0);
}