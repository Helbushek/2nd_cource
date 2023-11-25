#include <iostream>
#include <assert.h>
#include <string>
#include <vector>
#include "BitSort.h"

std::string fileName(int arraySize, int arrayRange) {
	std::string name = "number_";
	std::string thousandsCount;
	while (arraySize / 1000 > 0) {
		thousandsCount += 'k';
		arraySize /= 1000;
	}

	name += std::to_string(arraySize) + thousandsCount + '_' + std::to_string(arrayRange) + ".txt";
	return name;
}

void vectorFromFile(const char* fileName, std::vector<int>& array) {
	FILE* openedFile;
	errno_t error_catch = fopen_s(&openedFile, fileName, "r");
	assert(!error_catch);
	while (!feof(openedFile)) {
		int scannedNumber;
		fscanf_s(openedFile, "%ld", &scannedNumber);
		array.push_back(scannedNumber);
	}
	fclose(openedFile);
}

bool isSorted(std::vector<int> array) {
	int size = array.size();
	for (int i = 0; i < size - 1; i++) {
		if (array[i] > array[i + 1])
			return false;
	}
	return true;
}

int main() {
	const int repeat_number = 3;
	FILE* openedFile;
	fopen_s(&openedFile, "report.txt", "w");
	for (int arraySize = 10000; arraySize <= 1000000; arraySize *= 10) {
		for (int arrayRange = 10; arrayRange <= 100000; arrayRange *= 100) {
			double avgSum = 0;
			for (int i = 0; i < repeat_number; i++) {
				std::vector <int> array;
				vectorFromFile(fileName(arraySize, arrayRange).c_str(), array);
				double end, start = clock();
				BitSort(array);
				end = clock();

				double time = (end - start) / CLOCKS_PER_SEC;
				avgSum += time;

				if (!isSorted) {
					FILE* openFile; // Печать сортированных файлов
					const char* isSort = "sorted";
					if (!isSorted(array)) isSort = "unsorted";
					std::string sorted = isSort + fileName(arraySize, arrayRange);

					fopen_s(&openFile, sorted.c_str(), "w");
					for (auto iter : array) {
						fprintf_s(openFile, "%ld ", iter);
					}
					fclose(openFile);
				}

				std::cout << "REP_NUM: " << i + 1 << " SORTED: " << (isSorted(array) ? "true" : "false") << std::endl;
				fprintf(openedFile, "REP_NUM: %d SORTED : %d \n", i + 1, isSorted(array));
			}
			std::cout << std::endl << "SIZE: " << arraySize << " RANGE: " << arrayRange << " REP: " << repeat_number << " AVG_TIME: " << (double)(avgSum + 0.) / (repeat_number + 0.) << std::endl;
			fprintf(openedFile, "SIZE:%d RANGE:%d REP:%d AVG_TIME:%f \n", arraySize, arrayRange, repeat_number, (double)(avgSum + 0.) / (repeat_number + 0.));

		}
	}
	fclose(openedFile); 

	/*std::vector<int> array{ -1, -2, -3, 9, 8, 0 , 1, 2, 2, 2, 6, 10, 97};

	BitSort(array);

	for (auto iter : array) {
		std::cout << iter << ' ';
	}*/

	return(0);
}