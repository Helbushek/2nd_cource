#pragma once
#include <iostream>

void swapInt(int* first, int*second) 
{
	int temp = *first;
	*first = *second;
	*second = temp;
}

int shakeArray(int* array, int length) // generates next position for array, needed for finding every way possible (traveling between cities only once) 
{

	int* pos1=nullptr, * pos2=nullptr;

	for (int* i = array + length-2; i >= array; i--) 
	{
		if (*i < *(i + 1)) {
			pos1 = i;
			break;
		}
	}

	if (pos1 == nullptr) return(0);

	for (int* j = array + length-1; j >= array; j--)
	{
		if (*j > *pos1) {
			pos2 = j;
			break;
		}
	}

	swapInt(pos2, pos1);

	for (int* k = pos1 + 1, *l = array + length-1; k < l; k++, l--)
	{
		swapInt(k, l);
	}

}
 
int * solveSalesmanByEnumeration(int** distanceMap, int numberOfCities, int startCity, int &minDistance) {
	
	minDistance=99999;
	int* minRoadMap = new int[numberOfCities+1];
	
	int* roadMap = new int[numberOfCities+ 1];

	for (int i = 0; i < numberOfCities + 1; i++)
	{
		roadMap[i] = i + 1;
	}

	int returned=1;
	roadMap[numberOfCities] = startCity;
	while (roadMap[0] != startCity)
	{
		returned = shakeArray(roadMap, numberOfCities);
	}
	
	int currentDistance = 0;

	while (returned!=0)
	{

		for (int i = 0; i < numberOfCities; i++) 
		{
			currentDistance += distanceMap[roadMap[i]-1][roadMap[i+1]-1];
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

		currentDistance = 0;
		returned = shakeArray(roadMap, numberOfCities);
	}
	
	return(minRoadMap);
}