#include "BMsearch.h"
#include <iostream>
#include <vector>
using namespace std;

int main() {
	
	std::string string("std::move_iterator is an iterator adaptor which behaves exactly like the underlying iterator");
	int len = string.length();
	std::string stringToSearch = ("tor");

	vector<int> includes;
	std::cout << "(0,91): ";
	includes = searchByBm(string, stringToSearch);


	for (auto i : includes) {
	std:; cout << i << ' ';
	}
	
	std::cout << std::endl << "(17,91): ";
	includes = searchByBm(string, stringToSearch, 17);

	for (auto i : includes) {
	std:; cout << i << ' ';
	}
	std::cout << std::endl << "(28, 36): ";
	includes = searchByBm(string, stringToSearch, 28, 36);

	for (auto i : includes) {
	std:; cout << i << ' ';
	}

	std::cout << std::endl;
	includes = searchByBm(string, stringToSearch, 'once');
	std::cout << "First encounter: "; 

	for (auto i : includes) {
	std:; cout << i << ' ';
	}
	return(0);
}