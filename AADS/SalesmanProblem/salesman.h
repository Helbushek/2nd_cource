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

	for (int* j = array + length-1; j >= array; j--)
	{
		if (*j > *pos1) {
			pos2 = j;
			break;
		}
	}

	if (pos1 == nullptr) return(0);
	swapInt(pos2, pos1);

	for (int* k = pos1 + 1, *l = array + length-1; k < l; k++, l--)
	{
		swapInt(k, l);
	}

}

void solveSalesmanByEnumeration(int** distanceMap, int numberOfCities, int startCity) {
	int* roadMap = new int[numberOfCities+ 1];

	for (int i = 0; i < numberOfCities + 1; i++)
	{
		roadMap[i] = i + 1;
	}

	while (roadMap[0] != startCity)
	{
		shakeArray(roadMap, numberOfCities);
	}
	roadMap[numberOfCities + 1] = startCity;

	
}