#include "shell sort header.h"
#include <iostream>
#include <random>
#include <time.h>
#include <ctime> 
#include <string>
#include <assert.h>

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

void generateFilesForArray(int arraySize,  int arrayRange) {
	FILE* numbers;
	std::string name = fileName(arraySize, arrayRange);
	std::cout << name.c_str() << std::endl;
	errno_t error_catch = fopen_s(&numbers, name.c_str(), "w");
	



	for (int i = 0; i < arraySize; i++) {
		//long int randomNumber = rand() % (2 * arrayRange + 1) - arrayRange;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<long int> dis(-arrayRange, arrayRange);

		long int randomNumber = dis(gen);
		fprintf_s(numbers, "%ld ", static_cast<long>(randomNumber));
	}
	fclose(numbers);
}

void vectorFromFile(const char* fileName, std::vector<long int> & array) {
	FILE *openedFile;
	errno_t error_catch = fopen_s(&openedFile, fileName, "r");
	while (!feof(openedFile)) {
		long int scannedNumber;
		fscanf_s(openedFile, "%ld", &scannedNumber);
		array.push_back(scannedNumber);
	}
	fclose(openedFile);
}

double calculateTime(std::vector<long int> &array, int type) {					// 0 - Shell
	double end;													// 1 - Hibbard
	double start = clock();										// 2 - Marcin Ciur
	switch (type) {
	case 0: {
		sortByShell(array);
	}
	case 1: {
		sortByHibbard(array);
	}
	case 2: {
		sortByMarcinCiur(array);
	}
	}
	end = clock();
	std::cout << "  sorted:" << ifSorted(array) << "  ";
	return((end - start)/CLOCKS_PER_SEC);
}

int main() {
	srand(time(0));
	const int repeatsNumber = 3;
	for (int arraySize = 10000; arraySize <= 1000000; arraySize*=10) {
		for (int arrayRange = 10; arrayRange <= 100000; arrayRange*=100) {
			std::cout << "size: " << arraySize << "; range: " << arrayRange << "; " << std::endl;
			std::string file = fileName(arraySize, arrayRange);
			std::vector<long int> origin;
			vectorFromFile(file.c_str(), origin);
			for (int i=0; i<3; i++) {
				double sumOfTimes = 0;
				for (int j=0; j<repeatsNumber; j++) {
					std::vector<long int> array = origin;
					sumOfTimes += calculateTime(array, i);

				}
				std::cout  << "type: " << i << "; repeats: " << repeatsNumber << "; avgSum: " << sumOfTimes / repeatsNumber <<std::endl;

			/*generateFilesForArray(arraySize, arrayRange);*/
			}
		}
	}
}
