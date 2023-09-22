#include "salesman.h"
#include <iostream>
#include <random>
#include <time.h>
#include <ctime>
#include <fstream>

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
	int length, startCity, numberOfRepeats;

	std::cout << "\t\t\t\t Solving Salesman problem by enumeration" << std::endl << "Input variables: " << std::endl << std::endl << "Number of Cities" << std::endl << "City you want to srart from (Start City) " << std::endl << "Map of distances between cities";

	std::cout << std::endl << std::endl << std::endl << "\t\t Do you want to input Road Price Map by hand or shall it be generated randomly?" << std::endl << "\t\t\t\t\t\tY/N" << std::endl << "\t\t\t\t\tBy Hand/Im too lazy, do it for me" << std::endl;

	char choice;

	std::cin >> choice;

	/*std::cout << std::endl << "Please input Number of cities: ";
	std::cin >> length;*/


	std::cout << std::endl << "Please input number of city you want to start from: ";
	std::cin >> startCity;

	std::cout << std::endl << "Input number of repeats you want to run the programm: ";
	std::cin >> numberOfRepeats;
	if (numberOfRepeats > 20) {
		numberOfRepeats = 20;
		std::cout << "Time of running will be too long, repeats reset to 20 (progress from 4 to 13 including)" << std::endl;
	}
	std::ofstream statistic("statistic.txt");

	if (statistic.is_open()) std::cout << std::endl << "File created";
	else {
		std::cout << std::endl << "File is not created"; return(-1);
	}
	statistic.width(6);

	int summOfTime=0, summOfAccuracy = 0;

	length = 4; 
	int count = 1;

	for (int i = 0; i < numberOfRepeats; i++) {
		if (count % 4 == 0) length += 2;
		count++;
		int** doubleArray = new int* [length];
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



		int* minRoadMap = new int[length + 1];
		int* maxRoadMap = new int[length + 1];

		unsigned int startClock, endClock, executionTime;

		int bestDistance, worstDistance;

		startClock = clock();
		minRoadMap = solveSalesmanByEnumeration(doubleArray, length, startCity, bestDistance, worstDistance, maxRoadMap);
		endClock = clock();
		executionTime = endClock - startClock;

		std::cout << "Min road map and distance: " << std::endl;
		printArray(minRoadMap, length + 1);
		std::cout << " summ: " << bestDistance << std::endl;

		std::cout << std::endl << "Max road map and distance: " << std::endl;
		printArray(maxRoadMap, length + 1);
		std::cout << " summ: " << worstDistance << std::endl;

		std::cout << std::endl << "Time of execution: " << (float)(executionTime / 1000) << " sec" << std::endl << std::endl;

		statistic << "Enumeration method: " << std::endl << "Roadmap: "; 
		for (int i = 0; i < length; i++) {
			statistic << minRoadMap[i] << ' ';
		}

		statistic << std::endl << "Best distance " << bestDistance << std::endl << "Worst distance: " << worstDistance << std::endl << "Time of execution: " << (float)(executionTime / 1000) << std::endl;

		int bestDistanceHeuristic = 0;
		startClock = clock();
		minRoadMap = solveSalesmanByHeuristics(doubleArray, length, startCity, &bestDistanceHeuristic);
		endClock = clock();
		int executionTimeHeuristic = endClock - startClock;

		std::cout << std::endl << "Heuristics method solved problem: " << std::endl;
		printArray(minRoadMap, length + 1);
		std::cout << " summ: " << bestDistanceHeuristic << std::endl;
		std::cout << std::endl << "Time of execution: " << (float)(executionTimeHeuristic / 1000) << " sec";

		int percentTime;
		if (executionTime != 0) percentTime = ((executionTime - executionTimeHeuristic) / executionTime) * 100;
		else percentTime = 0;
		std::cout << std::endl << "Hieristic is faster than enumeration by: " << percentTime << "%" << std::endl;
		std::cout.precision(4);
		std::cout << std::endl << "Hieristic`s accuracy is close to best by: " << (bestDistanceHeuristic - bestDistance) << " which is " << 100-((bestDistanceHeuristic*1.0 - bestDistance) *100/(worstDistance*1.0-bestDistance)) << "%" << std::endl;

		statistic << "Heuristic method: " << std::endl << "Roadmap: ";
		for (int i = 0; i < length; i++) {
			statistic << minRoadMap[i] << ' ';
		}

		statistic << std::endl << "Best distance " << bestDistanceHeuristic << std::endl << "Time of execution: " << (float)(executionTimeHeuristic / 1000) << std::endl;
		statistic << "Speed difference: " << percentTime << "%" << std::endl << "Precision : " << 100-((bestDistanceHeuristic*1.0 - bestDistance) * 100 / (worstDistance*1.0 - bestDistance)) << "%" << std::endl << std::endl;
		
		summOfAccuracy += 100 - ((bestDistanceHeuristic*1.0 - bestDistance) * 100 / (worstDistance*1.0 - bestDistance));
		summOfTime += percentTime;

		delete minRoadMap;
		delete maxRoadMap;
		for (int i = 0; i < length; i++) {
			delete doubleArray[i];
		}
		delete doubleArray;
	}

	statistic << std::endl <<"Arithmetic mean of time difference: " << summOfTime / numberOfRepeats << "%" << std::endl << "Arithmeric mean of prescision: " << summOfAccuracy / numberOfRepeats << "%";
	return(0);
}