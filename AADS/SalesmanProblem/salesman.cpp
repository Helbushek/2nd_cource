#include "salesman.h"

void printArray(int* array, int length)
{
	for (int i = 0; i < length; i++) {
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
}

int main() {

	int length = 4;

	int* array = new int[length];

	for (int i = 0; i < length; i++)
	{
		array[i] = i+1;
	}
	std::cout << "1. ";
	printArray(array, length);
	std::cout << std::endl;
	int i = 2, returned = 0;
	while ( returned!= 1) 
	{
		returned = shakeArray(array, length);
		std::cout << i << ". ";
		printArray(array, length); 
		std::cout << std::endl;
		i++;
	}

	return(0);
}