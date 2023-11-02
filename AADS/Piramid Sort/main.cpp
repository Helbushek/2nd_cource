#include "PiramidalSort.h"
#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include <ctime>

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

void vectorFromFile(const char* fileName, std::vector<long int>& array) {
	FILE* openedFile;
	errno_t error_catch = fopen_s(&openedFile, fileName, "r");
	assert(!error_catch);
	while (!feof(openedFile)) {
		long int scannedNumber;
		fscanf_s(openedFile, "%ld", &scannedNumber);
		array.push_back(scannedNumber);
	}
	fclose(openedFile);
}

bool isSorted(std::vector<long int> array) {
	int size = array.size();
	for (int i = 0; i < size - 1; i++) {
		if (array[i] > array[i + 1]) return false;
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
				std::vector <long int> array;
				vectorFromFile(fileName(arraySize, arrayRange).c_str(), array);
				double end, start = clock();
				piramidalSort(array);
				end = clock();

				double time = (end - start) / CLOCKS_PER_SEC;
				avgSum += time;

				/*FILE* openFile; // ������ ������������� ������
				std::string sorted = "sorted" + fileName(arraySize, arrayRange);
				
				fopen_s(&openFile, sorted.c_str(), "w");
				for (auto iter : array) {
					fprintf_s(openFile, "%ld ", iter);
				}
				fclose(openFile);*/

				
				
				std::cout << "REP_NUM: " << i + 1 << " SORTED: " << (isSorted(array) ? "true" : "false") << std::endl;
				fprintf(openedFile, "REP_NUM: %d SORTED : %d \n", i + 1, isSorted(array));
				
			}
			std::cout << std::endl << "SIZE: " << arraySize << " RANGE: " << arrayRange << " REP: " << repeat_number << " AVG_TIME: " << (double)(avgSum+0.)/(repeat_number+0.);
			fprintf(openedFile, "SIZE:%d RANGE:%d REP:%d AVG_TIME:%f \n", arraySize, arrayRange, repeat_number, (double)(avgSum + 0.) / (repeat_number + 0.));
		}
	}
	fclose(openedFile);
	return(0);
}