#include "Array.h"
#include <iostream>

int main() {
	Array<int> array = Array<int>(10, 1);
	array.print();
	std::cout << std::endl;

	//array.generate();
	std::cout << std::endl << "Input Array: ";
	array.set();
	array.print();

	/*
	array.print();*/
	std::cout << std::endl;

	std::cout << "Size: " << array.size() << std::endl;

	array.sort();
	array.print();

	/*array.generateByIncrease();
	array.print();
	std::cout << std::endl;


	array.generateByDecrease();
	array.print();
	std::cout << std::endl;*/

	std::cout << "Array[3] = " << array[3] << std::endl;
	array += 999;
	array.print();
	std::cout << std::endl;
	std::cout << "999 is in: " << array.find(999) << std::endl;

	array.deleteFirst(999);

	std::cout << "Array without first 999: " << std::endl;
	array.print();
	std::cout << std::endl;

	array += 999; array += 999; array += 999;
	std::cout << "Array with 999 new: " << std::endl;
	array.print();
	std::cout << std::endl;

	std::cout << "Array without all 999: " << std::endl;
	array.deleteAll(999);
	array.print();
	std::cout << std::endl;

	/*std::cout << "Max in array: " << array[array.findMax()] << std::endl << "Min in array: " << array[array.findMin()];

	std::cout << std::endl << "Array with [0] deleted and after [1] = 999: " << std::endl;
	array.deleteByIndex(0); 
	array[1] = 999;
	array.print();

	Array<int>::Iterator start(&array, 2), end(&array, 4);
	array.deleteDiaposon(start, end);

	std::cout << std::endl << "Array after deleting diaposon (2, 4): " << std::endl;
	array.print();

	std::cout << std::endl;
	Array<int>::Iterator temp(&array, 2);
	array.insert(888, temp);
	array.insert(0, array.size());
	std::cout << array;

	std::cout << std::endl << "Print you array with size: " << array.size();
	std::cin >> array;
	std::cout << std::endl << array;
	return(0);*/
}