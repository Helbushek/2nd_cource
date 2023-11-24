#include <vector>

void BitSort(std::vector<int> array, int leftBorder, int rightBorder, int level) {
	// int : [−2 147 483 648, +2 147 483 647]
	//  4bytes = 32 bit 
	// 1 bit for sign, 2^31 = 2`147`483`648
	//  means that INT looks like: 
	// [ signBit _ _ _ _ _ _ _ ] [ _ _ _ _ _ _ _ _ ] [ _ _ _ _ _ _ _ _ ] [ _ _ _ _ _ _ _ _ ]

	// signBit = 1 -> INT <= 0, signBit = 0 -> INT >= 0;

	if (rightBorder == -1) rightBorder = array.size();

	if (level == 0) { // По первому разряду разделяем положительные и отрицательные, их будем проверять отдельно
		int median = array[leftBorder + rightBorder / 2];
		int i = leftBorder, int j = rightBorder;
		while (i <= j) {

		}
	}
	else { // Обычный процесс сортировки по разряду 

	}
}