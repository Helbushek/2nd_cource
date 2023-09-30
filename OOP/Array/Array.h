#pragma once
#include <iostream>
class Array {
public:
	Array();
	Array(int size=0, int fillNumber = INT_MAX);
	~Array();
	Array(const Array &array);

	void swap(Array other);

	int& operator[] (const int index);
	Array& operator= (const Array arrayToEqualize);
	Array operator+=(int numberToAdd);
	Array operator + (int numberToAdd);
	Array operator+=(Array arrayForConcatenation);
	Array operator+(Array arrayForConcatenation);

	int size();

	int find(int numberToFind);

	void print();
	void set();
	void generate(int startOfDiaposone=0, int endOfDiaposone=100);
	void generateByIncrease(int startOfDiaposone=0, int endOfDiaposone=100);
	void generateByDecrease(int startOfDiaposone=0, int endOfDiaposone=100);

	void sort();
	void sortDecrease();

	bool deleteFirst(int numberToDelete);
	void deleteAll(int numberToDelete);
	void deleteByIndex(int indexToDelete);

	int findMax();
	int findMin();

private:
	int* m_array;
	int m_size;
};