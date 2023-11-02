#pragma once
#include <vector>

void piramidalSort(std::vector<long int> &array);

bool isHeap(const std::vector<long int>& array);

void heapify(std::vector<long int> &array, int size);

void sift(std::vector<long int> &array , int i, int size);