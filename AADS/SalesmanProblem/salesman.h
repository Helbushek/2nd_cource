#pragma once

void swapInt(int* first, int* second);

int shakeArray(int* array, int length);

int* solveSalesmanByEnumeration(int** distanceMap, int numberOfCities, int startCity, int& minDistance, int& maxDistance, int* maxRoadMap = nullptr);

int findMinInArray(int* array, int length);

int* solveSalesmanByHeuristics(int** distanceMap, int numberOfCities, int startCity, int* minDistance);