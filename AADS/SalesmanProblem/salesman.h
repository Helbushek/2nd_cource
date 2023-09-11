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

	for (int* j = array + length; j >= array; j--)
	{
		if (*j > *pos1) {
			pos2 = j;
			break;
		}
	}

	if (pos1 == nullptr) return(3);
	swapInt(pos2, pos1);

	for (int* k = pos1 + 1, *l = array + length-1; k < l; k++, l--)
	{
		swapInt(k, l);
	}
	
}

void solveSalesmanByEnumeration() {


}