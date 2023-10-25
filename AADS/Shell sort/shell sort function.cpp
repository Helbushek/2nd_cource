#include "shell sort header.h"
#include <vector>
#include <string>
#include <iostream>
#include <random>


void sortByShell(std::vector<long int> &array) {
	
	long int size = array.size();
	for (int step = size / 2; step != 0; step /= 2) { // Уменьшение шага на каждой итерации
		for (int m = 0; m < step; m++) {
			int sorted = m; 
			for (int i = sorted + step; i < size; i += step) { 
				int k = sorted;
				long int temp = array[i];
				bool moved = false;
				
				while (k>=0 && temp < array[k]) {
					array[k + step] = array[k];
					moved = true;
					k -= step;
				}
				if (moved == true) {
					array[k+step] = temp; 
				}

				sorted += step;  
			}
		}
	}
	//	m - ходит между элементами, двигает i вперёд (выбирает новые пары элементов) ; i - ходит по уже заданному step (шаг) по массиву ;  j - ходит по отсортированной части в прямой вставке ;  k ходит тоже по отсортированной, но для сдвига.
}

int pow(int x, int y) {
	int temp = 1;
	for (int i = 0; i < y; i++) {
		temp *= x;
	}
	return temp;
}

void sortByHibbard(std::vector<long int>& array) {
	long int size = array.size();
	for (int h = 0, step = pow(2, h)-1; step>0; ++h, step = pow(2, h+1) - 1) {
		for (int m = 0; m < step; m++) {
			int sorted = m;
			for (int i = sorted + step; i < size; i += step) {
				int k = sorted;
				long int temp = array[i];
				bool moved = false;

				while (k >= 0 && temp < array[k]) {
					array[k + step] = array[k];
					moved = true;
					k -= step;
				}
				if (moved == true) {
					array[k + step] = temp;
				}

				sorted += step;
			}
		}
	}
}

void sortByMarcinCiur(std::vector<long int>& array) {
	std::vector<int>marcin{ 1, 4, 10, 23, 57, 132, 301, 701, 1750 };
	long int size = array.size();
	for (int l=0; l<marcin.size(); ++l) {
		int step = marcin[marcin.size() - 1 - l];
		for (int m = 0; m < step && step< size; m++) {
			int sorted = m;
			for (int i = sorted + step; i < size; i += step) {
				int k = sorted;
				long int temp = array[i];
				bool moved = false;

				while (k >= 0 && temp < array[k]) {
					array[k + step] = array[k];
					moved = true;
					k -= step;
				}
				if (moved == true) {
					array[k + step] = temp;
				}

				sorted += step;
			}
		}
	}
}

void swap(long int& one, long int& two) {
	long int temp = one;
	one = two;
	two = temp;
}

void bubble_sortByShell(std::vector<long int>& array) {
	long int size = array.size();
	for (int step = size / 2; step != 0; step /= 2) {
		for (int i = step; i < size; i++) {
			for (int j = i; j >= step; j -= step) {
				if (array[j] < array[j - step]) {
					swap(array[j], array[j - step]);
				}
			}
		}
	}
}

void bubble_sortByHibbard(std::vector<long int>& array) {
	long int size = array.size();
	for (int h = 0, step = pow(2, h) - 1; step > 0; ++h, step = pow(2, h) - 1) {
		for (int i = step; i < size; i++) {
			for (int j = i; j >= step; j -= step) {
				if (array[j] < array[j - step]) {
					swap(array[j], array[j - step]);
				}
			}
		}
	}
}

void bubble_sortByMarcinCiur(std::vector<long int>& array) {
	long int size = array.size();
	std::vector<int>marcin{ 1, 4, 10, 23, 57, 132, 301, 701, 1750 };
	for (int l = 0; l < marcin.size(); ++l) {
		int step = marcin[marcin.size() - 1 - l];
		for (int i = step; i < size; i++) {
			for (int j = i; j >= step; j -= step) {
				if (array[j] < array[j - step]) {
					swap(array[j], array[j - step]);
				}
			}
		}
	}
}

bool ifSorted(std::vector<long int> array) {
	for (int i = 0; i < array.size() - 1; i++) {
		if (array[i] > array[i + 1]) {
			return(false);
		}
	}
	return(true);
}
