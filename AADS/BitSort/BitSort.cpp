#include <vector>
#include <iostream>

void BitSort(std::vector<int> &array, int leftBorder, int rightBorder, int level) {
	// int : [−2 147 483 648, +2 147 483 647]
	//  4bytes = 32 bit 
	// 1 bit for sign, 2^31 = 2`147`483`648
	//  means that INT looks like: 
	// [ signBit _ _ _ _ _ _ _ ] [ _ _ _ _ _ _ _ _ ] [ _ _ _ _ _ _ _ _ ] [ _ _ _ _ _ _ _ _ ]

	// signBit = 1 -> INT <= 0, signBit = 0 -> INT >= 0;

	if ((rightBorder < leftBorder && level != 31) || level < 0)
		return;

	if (rightBorder == -1) 
		rightBorder = array.size()-1;

	int i = leftBorder, j = rightBorder;
	if (level == 31) { // По первому разряду разделяем положительные и отрицательные, их будем проверять отдельно
		std::cout << "31 level" << std::endl;
		while (i <= j) {
			while (i <= j && ((array[i] >> 31) & 1) == 1) { // 1 == negative number
				i++;
			}
			while (i <= j && ((array[j] >> 31) & 1) == 0) { // 0 == positive number
				j--;
			}
			if (i < j)
				std::swap(array[i++], array[j--]);
		}
		for (auto iter : array) {
			std::cout << iter << ' ';
		}
		std::cout << std::endl;
	}
	else { // Обычный процесс сортировки по разряду 
		
		while (i <= j) {
			while (i <= j && ((array[i] >> level)&1) == 0)
				i++;
			while (i <= j && ((array[j] >> level)&1) == 1)
				j--;
			if (i < j)
				std::swap(array[i++], array[j--]);
		}

	}

	BitSort(array, leftBorder, j, level - 1);
	BitSort(array, i, rightBorder, level - 1);
}