#include <vector>
#include <assert.h>
#include <iostream>
void swap(long int& first, long int& second) {
	long int temp = first;
	first = second;
	second = temp;
}

bool isHeap(const std::vector<long int> &array) {
	int size = array.size();
	for (int i = 0; i < size / 2-1; i++) {
		if (array[i] < array[2 * i + 1] || array[i] < array[2 * i + 2]) return false;
	}
	return true;
}

void sift(std::vector<long int>& array, int i, int size) { // просеивает один узел 

	int maxIndex=i; // Предок выбранного узла пирамиды 
	{ // Выделяем максимальный элемент в узле 
		if (2 * i + 1 < size ) { // Сравнение предка с левым элементом
			if (array[maxIndex] < array[2 * i + 1]) maxIndex = 2 * i + 1;
		}
		if (2 * i + 2<size) { // Сравнение правого элемента с максимальным из предка и левого элементов 
			if (array[maxIndex] < array[2 * i + 2]) maxIndex = 2 * i + 2;
		}

		// maxIndex - сохранённый индекс наибольшего элемента в узле


		if (maxIndex != i) { // Если предок не максимальный, меняем местами с максимальным и по рекурсии проверяем всё поддерево ниже изменённого
			swap(array[i], array[maxIndex]); // Меняем местами элементы
			sift(array, maxIndex, size);
		}


	}
}

void heapify(std::vector<long int> &array, int size) {
	for (int i = size / 2-1; i>=0 ; i--) { // Просеиваем снизу вверх (в нижних узлах выделяем максимальные числа и двигаем их наверх 
		sift(array, i, size);
	}	
}



void piramidalSort(std::vector<long int> &array) {
	int size = array.size();
	
	heapify(array, size);

	std::cout << std::endl;
	
	for (int i = size-1; i >= 0; i--) {
		swap(array[0], array[i]);
		sift(array, 0, i);
	}
}