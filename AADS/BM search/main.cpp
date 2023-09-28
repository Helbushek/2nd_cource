#include "BMsearch.h"
#include <iostream>
using namespace std;

int main() {
	int len = strlen("std::move_iterator is an iterator adaptor which behaves exactly like the underlying iterator\0");
	char* string = new char[255];
	strcpy_s(string, 255, "std::move_iterator is an iterator adaptor which behaves exactly like the underlying iterator\0");
	char* stringToSearch = new char[4];
	strcpy_s(stringToSearch, 4, "tor");
	int* includes = new int[20];
	std::cout << "(0,91)";
	includes = searchByBmOnce(string, stringToSearch);

	for (int i = 0; includes[i] != -1; i++) {
		std::cout << includes[i] << ' ';
	}
	std::cout << std::endl << "(17,91)";
	includes = searchByBmOnce(string, stringToSearch, 17);

	for (int i = 0; includes[i] != -1; i++) {
		std::cout << includes[i] << ' ';
	}
	std::cout << std::endl << "(28, 36)";
	includes = searchByBmOnce(string, stringToSearch, 28, 36);

	for (int i = 0; includes[i] != -1; i++) {
		std::cout << includes[i] << ' ';
	}
	std::cout << std::endl;
	return(0);
}