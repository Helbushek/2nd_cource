#include "salesman.h"
#include <iostream>
#include <random>
#include <time.h>


void printArray(int* array, int length)
{
	for (int i = 0; i < length; i++) {
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
}

void printDArray(int** doubleArray, int linesNumber, int columnsNumber)
{
	for (int i = 0; i < linesNumber; i++)
	{
		printArray(doubleArray[i], columnsNumber);
		std::cout << std::endl;
	}
}

void generateArray(int* array, int length, int startOfRange, int endOfRange)
{
	

	for (int i = 0; i < length; i++) {
		array[i] = rand() % (endOfRange - startOfRange) + startOfRange;
	}

}

void generateDoubleArray(int** doubleArray, int numberOfLines, int numberOfColumns, int startOfRange, int endOfRange)
{
	for (int i = 0; i < numberOfLines; i++)
	{
		generateArray(doubleArray[i], numberOfColumns, startOfRange, endOfRange);
	}
}

int main() {

	srand(time(0));
	int length = 4, startCity=2;

	


	int** doubleArray = new int*[length];
	for (int i = 0; i < length; i++)
	{
		doubleArray[i] = new int[length];
	}

	generateDoubleArray(doubleArray, length, length, 1, 10); // doubleArray - map of distances between cities [i] - start city [j] - end city, is symmetrycal
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{	
			if (i==j) doubleArray[i][i] = 0;
			if (i < j) doubleArray[i][j] = doubleArray[j][i];
		}
		
	}
	printDArray(doubleArray, length, length);
	std::cout << std::endl;

	int* roadMap = new int[length + 1];

	for (int i = 0; i < length + 1; i++)
	{
		roadMap[i] = i + 1;
	}

	roadMap[length] = startCity;
	std::cout << std::endl;
	printArray(roadMap, length);
	std::cout << std::endl;
	while (roadMap[0] != startCity)
	{
		shakeArray(roadMap, length);
		printArray(roadMap, length+1);
		std::cout << std::endl;
	}
	

	

	

	return(0);
}