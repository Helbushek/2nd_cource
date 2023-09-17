#include "salesman.h"
#include <iostream>
#include <random>
#include <time.h>
#include <ctime>


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
	for (int i = 0; i < length; i++) {
		std::cin >> array[i];
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

	int* minRoadMap = new int[length+1];
	int* maxRoadMap = new int[length+1];

	unsigned int startClock, endClock, executionTime;

	int bestDistance, worstDistance;

	startClock = clock();
	minRoadMap = solveSalesmanByEnumeration(doubleArray, length, startCity, bestDistance, worstDistance, maxRoadMap);
	endClock = clock();
	executionTime = endClock - startClock;

	std::cout << "Min road map and distance: " << std::endl;
	printArray(minRoadMap, length+1);
	std::cout << " summ: " << bestDistance << std::endl;

	std::cout << std::endl << "Max road map and distance: " << std::endl;
	printArray(maxRoadMap, length + 1);
	std::cout << " summ: " << worstDistance << std::endl;

	std::cout << std::endl << "Time of execution: " << (float)(executionTime / 1000) << " sec" << std::endl << std::endl;

	int bestDistanceHeuristic=0;
	startClock = clock();
	minRoadMap = solveSalesmanByHeuristics(doubleArray, length, startCity, &bestDistanceHeuristic);
	endClock = clock();
	int executionTimeHeuristic = endClock - startClock;

	std::cout << std::endl << "Heuristics method solved problem: " << std::endl;
	printArray(minRoadMap, length + 1);
	std::cout << " summ: " << bestDistanceHeuristic << std::endl;
	std::cout << std::endl << "Time of execution: " << (float)(executionTimeHeuristic / 1000) << " sec";

	int percentTime;
	if (executionTime != 0) percentTime = ((executionTime - executionTimeHeuristic)  / executionTime) * 100;
	else percentTime = 0;
	std::cout << std::endl << "Hieristic is faster than enumeration by: " << percentTime << "%" << std::endl;
	std::cout.precision(4);
	std::cout << std::endl << "Hieristic`s accuracy is close to best by: " << (bestDistanceHeuristic - bestDistance ) << " which is " << ((bestDistanceHeuristic*1.0)-bestDistance)/(bestDistance*1.0) *100.0 << "%" << std::endl;

	
	delete minRoadMap;
	delete maxRoadMap;
	for (int i = 0; i < length; i++) {
		delete doubleArray[i];
	}
	delete doubleArray;
	return(0);
}