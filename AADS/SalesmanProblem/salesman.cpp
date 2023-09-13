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
		//std::cout << std::endl;
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

void inputArray(int* array, int length)
{
	int temp;

	for (int i = 0; i < length; i++) {
		std::cin >> temp;
		array[i] = temp;
	}

}

void inputDoubleArray(int** doubleArray, int numberOfLines, int numberOfColumns)
{
	for (int i = 0; i < numberOfLines; i++)
	{
		inputArray(doubleArray[i], numberOfColumns);
	}
}

int main() {

	srand(time(0));

	// Work with user, input all variables
	int length, startCity;

	std::cout << "\t\t\t\t Solving Salesman problem by enumeration" << std::endl << "Input variables: " << std::endl << std::endl << "Number of Cities" << std::endl << "City you want to srart from (Start City) " << std::endl << "Map of distances between cities";

	std::cout << std::endl << std::endl << std::endl << "\t\t Do you want to input Road Price Map by hand or shall it be generated randomly?" << std::endl << "\t\t\t\t\t\tY/N" << std::endl << "\t\t\t\t\tBy Hand/Im too lazy, do it for me" << std::endl;

	char choice;

	std::cin >> choice;

	std::cout << std::endl << "Please input Number of cities: ";
	std::cin >> length;


	std::cout << std::endl << "Please input number of city you want to start from: ";
	std::cin >> startCity;

	int** doubleArray = new int*[length];
	for (int i = 0; i < length; i++)
	{
		doubleArray[i] = new int[length];
	}

	if (choice == 'N')
	{
		std::cout << std::endl << "Generating your price map" << std::endl;
		generateDoubleArray(doubleArray, length, length, 1, 10); // doubleArray - map of distances between cities [i] - start city [j] - end city, is symmetrycal
	}
	if (choice == 'Y') 
	{
		std::cout << std::endl << "Please input your price map: " << std::endl;
		inputDoubleArray(doubleArray, length, length);
	}
	
	for (int i = 0; i < length; i++)
	{
		doubleArray[i][i] = 0;
	}

	std::cout << "Your final road map:" << std::endl;
	printDArray(doubleArray, length, length);
	std::cout << std::endl;

	/*int* roadMap = new int[length + 1];

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
	}*/
	int* minRoadMap = new int[length];
	int summDistance;
	minRoadMap = solveSalesmanByEnumeration(doubleArray, length, startCity, summDistance);
	
	printArray(minRoadMap, length+1);
	std::cout <<  " summ: " <<summDistance;
	

	return(0);
}