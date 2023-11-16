#include <vector>
#include <iostream>

bool testCase(float pos, float compared, int type, char comparison) {
	switch (type) {
	case 1: {
		switch (comparison) {
		case '<': {
			return pos*1.0 < compared;
		}
		case '>': {
			return pos * 1.0 >= compared;
		}
		}
	}
	case 2: {
		switch (comparison) {
		case '<': {
			return pos * 1.0 <= compared;
		}
		case '>': {
			return pos * 1.0 > compared;
		}
		}
	}
	case 3: {
		switch (comparison) {
		case '<': {
			return pos * 1.0 < compared;
		}
		case '>': {
			return pos * 1.0 > compared;
		}
		}
	}	 
	}
	return false;
}

struct elem {
	int left, right;
};

int HoarSort(std::vector<int> &array,  int type, int leftBorder, int rightBorder, int leftValue, int rightValue ) {
	int count = 1;

	elem* stack = new elem[array.size()];

	// Инициализация вспомогательных переменных
	if (rightBorder == -1) {
		rightBorder = array.size() - 1;
	}

	int maxValue, minValue = maxValue = array[0];

	if (type == 1) {
		if (leftValue==-1 || rightValue==-1) { // Для первого вызова, выбрать мин и макс числа
			for (int i = leftBorder; i <= rightBorder; i++) {
				if (array[i] > maxValue && rightValue == -1) {
					maxValue = array[i];
				}
				if (array[i] < minValue && leftValue == -1) {
					minValue = array[i];
				}
			}
		}
		if (leftValue != -1 && rightValue != -1) { // Если указан диапозон, то его и укажем для сортировки
			maxValue = rightValue;
			minValue = leftValue;
		}

	}

	else if(type == 2) {
		for (int i = leftBorder; i <= rightBorder; i++) {
			if (array[i] > maxValue) {
				maxValue = array[i];
			}
			if (array[i] < minValue) {
				minValue = array[i];
			}
		}
	}



	// Условие выхода из рекурсии: 
	if (type == 1) {
		if (leftBorder >= rightBorder || minValue == maxValue)
			return count;
	}
	else if (type > 1 && leftBorder >= rightBorder) {
		return count;
	}


	int left = leftBorder, right = rightBorder;
	if (type == 2) {
		left++;
	}

	float median;
	if (type == 1)
		median = (minValue + maxValue) * 1.0 / 2;
	if (type == 2) {
		median = array[leftBorder];
	}
	if (type == 3) {
		median = array[(left + right) / 2];
	}

	// Сортировка

	while (left <= right) {

		while (left <= right && testCase(array[left], median, type, '<')) {
			left++;
		}

		while (right >= left && testCase(array[right], median, type, '>')) {
			right--;
		}

		if (type < 3 && left < right) {
			std::swap(array[left++], array[right--]);
		}
		if (type == 3 && left <= right) {
			std::swap(array[left++], array[right--]);
		}
	}
	if (type == 2) {
		std::swap(array[leftBorder], array[right--]);
	}

	// Вызов рекурсии 

	count += HoarSort(array, type, leftBorder, right, minValue, median - 0.5);

	count += HoarSort(array, type, left, rightBorder, median + 0.5, maxValue);
}

void NotRecHoarSort(std::vector<int>& array) {

	elem* stack = new elem[array.size()];

	// Инициализация вспомогательных переменных

	stack[0].left = 0;
	stack[0].right = array.size()-1;

	int stackSize = 0;

	int leftBorder, rightBorder, left, right, median;

	// Сортировка
	while (stackSize >= 0) {
		leftBorder = stack[stackSize].left, rightBorder = stack[stackSize].right;
		stackSize--;

		if (leftBorder < rightBorder) {
			left = leftBorder, right = rightBorder;

			median = array[(left + right) / 2];

			while (left < right) {

				while (left <= right && array[left] < median) {
					left++;
				}

				while (right >= left && array[right] > median) {
					right--;
				}


				if (left < right) {
					std::swap(array[left++], array[right--]);
				}
			}
		}
		if (rightBorder-leftBorder>1) {
			stackSize++;
			stack[stackSize].left = left; stack[stackSize].right = rightBorder;
		
			stackSize++;
			stack[stackSize].left = leftBorder; stack[stackSize].right = right;
		}

		/*	std::cout << std::endl; // Debug
			for (auto iter: array) {
				std::cout << iter << ' ';
			}*/
	}
	
	delete[] stack;
}