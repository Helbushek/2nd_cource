#include "Array.h"
#include <iostream>

int main() {
	Array array = Array(10, 1);
	array.print();
	std::cout << std::endl;

	array.generate();
	array.print();

	/*array.set();
	array.print();*/
	std::cout << std::endl;

	std::cout << "Size: " << array.size() << std::endl;

	/*array.sort();
	array.print();*/

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

	std::cout << "Max in array: " << array[array.findMax()] << std::endl << "Min in array: " << array[array.findMin()];
	array.deleteIndex(0);
	array[1] = 909;
	std::cout << std::endl << "After deleting [0] in array and [1] = 909: ";
	array.print();


	return(0);
}