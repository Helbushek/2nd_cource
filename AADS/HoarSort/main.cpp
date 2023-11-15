#include "HoarSort.h"
#include <iostream>

int main() {
	std::vector<int> array{ 9, 5, 1, 8, 0, 2 };
	std::cout << HoarSort(array, 3) << std::endl; 

	for (auto iter : array) {
		std::cout << iter << ' ';	
	}
	return(0);
}