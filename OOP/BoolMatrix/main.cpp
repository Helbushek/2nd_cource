#include "BoolMatrix.h"
#include <string>

int main() {
	char** testChar = new char* [4];
	for (int i = 0; i < 3; i++) {
		testChar[i] = new char[9];
	}
	
	strcpy_s(testChar[0], 9, "11110000");
	strcpy_s(testChar[1], 9, "00100010");
	strcpy_s(testChar[2], 9, "00001111");
	
	BoolMatrix test(testChar, 3);
	std::cout << test;

	for (int i = 0; i < 3; i++) {
		delete[] testChar[i];
	}
	delete[] testChar;
	std::cout << std::endl;

	std::cout << std::endl << test;
	return(0);
}