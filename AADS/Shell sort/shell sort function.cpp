#include "shell sort header.h"
#include <vector>
#include <string>
#include <iostream>
#include <random>


void sortByShell(std::vector<long int> &array) {
	for (int step = array.size() / 2; step != 0; step /= 2) { // ���������� ���� �� ������ ��������
		for (int m = 0; m < step; m++) {
			int sorted = 0; // ������ ���� ���������������� �������
			for (int i = sorted + step + m; i < array.size(); i += step) { // �������� �� ������� ������ ����� c� ������� �������� (��� ������� m-�� ������ (����� m ������� step ���� �����);;; 
				for (int j = m; j <= sorted; j += step) { // �������� �� ��������������� ����� �������, j ���������� � m ����� ���������� � ����� ������������������ �� ������, ����� ������ �� ����� ������ 
					if (array[i] < array[j]) { // ���� � ��������������� ����� ����� ����� ��� ��������� �������
						long int temp = array[i]; // ���������� ����� ��� �������
						for (int k = i; k >= j+step; k -= step) { // �������� �� "������" �� ������� �������� ����� ��������������� ����� �������
							array[k] = array[k - step]; // �������� ������ � ��������, � ������� ����� �������� �� ��������, ������� ���������
						}
						array[j] = temp; // ��������� ����������� �������
						j = sorted; // �����  ����� ��� ��������, ������� �� �������, ���� ��������� (j ������ ������ ��� �������);;; 
					}
				}
				sorted += step; // ��������� ������� �������� 
			}
		}
	}
	//	m - ����� ����� ����������, ������� i ����� (�������� ����� ���� ���������) ; i - ����� �� ��� ��������� step (���) �� ������� ;  j - ����� �� ��������������� ����� � ������ ������� ;  k ����� ���� �� ���������������, �� ��� ������.
}


int pow(int x, int y) {
	for (int i = 0; i < y; i++) {
		x *= x;
	}
	return x;
}

void sortByHibbard(std::vector<long int>& array) {
	for (int h = 0, step = pow(2, h)-1; step>0; ++h, step = pow(2, h) - 1) {
		for (int m = 0; m < step; m++) {
			int sorted = 0; 
			for (int i = sorted + step + m; i < array.size(); i += step) { 
				for (int j = m; j <= sorted; j += step) { 
					if (array[i] < array[j]) { 
						long int temp = array[i]; 
						for (int k = i; k >= j + step; k -= step) { 
							array[k] = array[k - step]; 
						}
						array[j] = temp; 
						j = sorted; 
					}
				}
				sorted += step; 
			}
		}
	}
}

void sortByMarcinCiur(std::vector<long int>& array) {
	std::vector<int>marcin{ 1, 4, 10, 23, 57, 132, 301, 701, 1750 };
	for (int l=0; l<marcin.size(); ++l) {
		int step = marcin[marcin.size() - 1 - l];
		for (int m = 0; m < step && step<array.size(); m++) {
			int sorted = 0;
			for (int i = sorted + step + m; i < array.size(); i += step) {
				for (int j = m; j <= sorted; j += step) {
					if (array[i] < array[j]) {
						long int temp = array[i];
						for (int k = i; k >= j + step; k -= step) {
							array[k] = array[k - step];
						}
						array[j] = temp;
						j = sorted;
					}
				}
				sorted += step;
				
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
