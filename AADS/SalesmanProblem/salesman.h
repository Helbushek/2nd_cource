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
	//1. Find location for 1st from right element that has bigger element right from him, wil be pos1

	int* pos1, * pos2;

	for (int* i = array + length-1, i != arary, i--) 
	{
		if (*i < *(i + 1)) {
			pos1 = i;
			break;
		}
	}

	//2. Find location for 1st from right element that is bigger than the pos1, will be pos2, swap pos1 and pos2

	for (int* j = array + length, j != array, j--)
	{
		if (*j > *pos1) {
			pos2 = j;
			break;
		}
	}

	swapInt(pos2, pos1);

	//4. Sort all the elements by increasing.

	for (int* k = pos1 + 1 * l = array + length, k < l, k++, l--)
	{
		swap(k, l);
	}
	return(1);

}

void solveSalesmanByEnumeration() {


}