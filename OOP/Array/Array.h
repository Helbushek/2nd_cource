#pragma once
#include <iostream>
class Array {
public:
	class Iterator;

public:


	Array();
	Array(int size=0, int fillNumber = INT_MAX);
	~Array();
	Array(const Array &array);
	Array(Array&& other);

	void swap(Array &other);

	int& operator[] (const int index);
	Array& operator= (const Array arrayToEqualize);
	Array operator+=(int numberToAdd);
	Array operator + (int numberToAdd);
	Array operator+=(Array arrayForConcatenation);
	Array operator+(Array arrayForConcatenation);
	bool operator==(const Array& other);
	bool operator!=(const Array & other);

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

	void increaseSize();

	Iterator begin();
	Iterator end();
	void deleteDiaposon(int startDiaposone, int endDiaposone);
	void insertByIterator(int numberToInsert, Array::Iterator iter);

private:
	int* m_array;
	int m_size;
};


class Array::Iterator {
public:
	Iterator(Array* array, const int pos);
	int& operator*();
	Iterator& operator++();
	Iterator operator++(int);
	Iterator& operator--();
	Iterator operator--(int);
	Iterator operator+(int numeber);
	Iterator operator-(int numeber);

	bool hasNext() const;

	int getPos();

	bool operator==(const Iterator& other) const;
	bool operator!=(const Iterator& other) const;

private:
	Array* m_array = nullptr;
	int m_pos = 0;
};