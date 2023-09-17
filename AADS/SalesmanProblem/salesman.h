#pragma once
#include <iostream>


void swapInt(int* first, int* second)
{
	int temp = *first;
	*first = *second;
	*second = temp;
}

int shakeArray(int* array, int length) // generates next position for array, needed for finding every way possible (traveling between cities only once) 
{

	int* pos1 = nullptr, * pos2 = nullptr;

	for (int* i = array + length - 2; i >= array; i--)
	{
		if (*i < *(i + 1)) {
			pos1 = i;
			break;
		}
	}

	if (pos1 == nullptr) return(0);

	for (int* j = array + length - 1; j >= array; j--)
	{
		if (*j > *pos1) {
			pos2 = j;
			break;
		}
	}

	swapInt(pos2, pos1);

	for (int* k = pos1 + 1, *l = array + length - 1; k < l; k++, l--)
	{
		swapInt(k, l);
	}

}

int* solveSalesmanByEnumeration(int** distanceMap, int numberOfCities, int startCity, int& minDistance, int& maxDistance, int* maxRoadMap = nullptr) {

	minDistance = INT_MAX;
	maxDistance = 0;
	int* minRoadMap = new int[numberOfCities + 1];

	int* roadMap = new int[numberOfCities + 1];

	for (int i = 0; i < numberOfCities + 1; i++)
	{
		roadMap[i] = i + 1;
	}

	int returned = 1;
	roadMap[numberOfCities] = startCity;
	while (roadMap[0] != startCity)
	{
		returned = shakeArray(roadMap, numberOfCities);
	}

	int currentDistance = 0;

	while (returned != 0 && roadMap[0] == startCity)
	{

		for (int i = 0; i < numberOfCities; i++)
		{
			currentDistance += distanceMap[roadMap[i] - 1][roadMap[i + 1] - 1];
		}

		if (currentDistance < minDistance)
		{
			minDistance = currentDistance;
			for (int i = 0; i < numberOfCities; i++)
			{
				minRoadMap[i] = roadMap[i];
			}
			minRoadMap[numberOfCities] = startCity;
		}

		if (currentDistance > maxDistance && maxRoadMap != nullptr)
		{
			maxDistance = currentDistance;
			for (int i = 0; i < numberOfCities; i++)
			{
				maxRoadMap[i] = roadMap[i];
			}
			maxRoadMap[numberOfCities] = startCity;
		}

		currentDistance = 0;
		returned = shakeArray(roadMap, numberOfCities);
	}
	delete roadMap;

	return(minRoadMap);
}

int findMinInArray(int* array, int length) {
	int min = INT_MAX, minIndex = -1;
	for (int i = 0; i < length; i++) {
		if (min > array[i] && array[i] != 0) {
			minIndex = i;
			min = array[i];
		}
	}
	return(minIndex);
}

int* solveSalesmanByHeuristics(int** distanceMap, int numberOfCities, int startCity, int* minDistance)
{
	int* minRoadMap = new int[numberOfCities + 1];
	//Choosing the outgoing arc of the minimum cost

	int** copiedDistanceMap = new int* [numberOfCities];
	for (int i = 0; i < numberOfCities; i++) {
		copiedDistanceMap[i] = new int[numberOfCities];
	}

	for (int i = 0; i < numberOfCities; i++) {
		for (int j = 0; j < numberOfCities; j++) {
			copiedDistanceMap[i][j] = distanceMap[i][j];
		}
	}

	int currentCity = startCity;
	int temp = 0;
	for (int j = 0; j < numberOfCities; j++) {
		copiedDistanceMap[j][startCity - 1] = 0;
	}
	for (int i = 0; i < numberOfCities && temp != -1; i++) {
		temp = findMinInArray(copiedDistanceMap[currentCity - 1], numberOfCities);
		minRoadMap[i] = currentCity;
		if (temp == -1) continue;

		*minDistance += copiedDistanceMap[currentCity - 1][temp];
		for (int j = 0; j < numberOfCities; j++) {
			copiedDistanceMap[j][temp] = 0;
			copiedDistanceMap[currentCity - 1][j] = 0;
		}
		copiedDistanceMap[temp][currentCity - 1] = 0;
		currentCity = temp + 1;
	}
	minRoadMap[numberOfCities] = startCity;
	*minDistance += distanceMap[(minRoadMap[numberOfCities - 1]) - 1][startCity - 1]; // 0<MinRoadMap[i]<=numberOfCities; 0<startCity<=numberOfCities; index: -1; 


	return(minRoadMap);
}