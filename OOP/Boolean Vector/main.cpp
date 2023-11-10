#include "BooleanVector.h"
#include <iostream>

int main() {
	BoolVector test("1000000000000000");

	test >>= 8;
	
	test.print();

	return(0);
}