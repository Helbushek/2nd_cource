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

int HoarSort(std::vector<int> &array,  int type, int leftBorder, int rightBorder, int leftValue, int rightValue ) {
	int count = 1;

	// ������������� ��������������� ����������
	if (rightBorder == -1) {
		rightBorder = array.size() - 1;
	}

	int maxValue, minValue = maxValue = array[0];

	if (type == 1) {
		if (leftValue==-1 || rightValue==-1) { // ��� ������� ������, ������� ��� � ���� �����
			for (int i = leftBorder; i <= rightBorder; i++) {
				if (array[i] > maxValue && rightValue == -1) {
					maxValue = array[i];
				}
				if (array[i] < minValue && leftValue == -1) {
					minValue = array[i];
				}
			}
		}
		if (leftValue != -1 && rightValue != -1) { // ���� ������ ��������, �� ��� � ������ ��� ����������
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


	
	// ������� ������ �� ��������: 
	if (type == 1) {
		if (leftBorder >= rightBorder || minValue == maxValue)
			return count;
	}
	else if (type >1 && leftBorder >= rightBorder) {
		return count;
	}


	int left = leftBorder, right = rightBorder;
	if(type == 2) {
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

	// ����������

	while (left <= right) {

		while (left <= right && testCase(array[left], median, type, '<')) {
			left++;
		}

		while (right >= left && testCase(array[right], median, type, '>')) {
			right--;
		}
		
		if (type <3 && left < right) {
			std::swap(array[left++], array[right--]);
		}
		if (type == 3 && left <= right) {
			std::swap(array[left++], array[right--]);
		}
	}
	if (type == 2) {
		std::swap(array[leftBorder], array[right--]);
	}

	// ����� �������� 

	count+=HoarSort(array, type, leftBorder, right, minValue, median-0.5);

	count+=HoarSort(array, type, left, rightBorder, median+0.5, maxValue);
}