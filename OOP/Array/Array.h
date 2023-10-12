#pragma once
#include <iostream>
class Array {
public:
	class Iterator;
	class ConstIterator;

public:


	Array(int size = 0);
	Array(int size, int fillNumber);
	~Array();
	Array(const Array &array);
	Array(Array&& other);

	void swap(Array &other);

	int& operator[] (const int index);

	const int& operator[] (const int index) const;

	Array& operator= (const Array &arrayToEqualize);
	Array& operator+=(int numberToAdd);
	Array operator + (int numberToAdd) const;
	Array& operator+=(const Array &arrayForConcatenation);
	Array operator+(const Array &arrayForConcatenation) const;
	bool operator==(const Array& other);
	bool operator!=(const Array& other);

	friend std::ostream& operator<<(std::ostream& out, const Array& array);
	friend std::istream& operator>>(std::istream& out, Array& array);

	int size() const;

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

	Iterator begin();
	Iterator end();

	ConstIterator begin() const;
	ConstIterator end() const;

	void deleteDiaposon(Array::Iterator begin, Array::Iterator end); //range
	void insert(int numberToInsert, Array::Iterator iter);
	void insert(int numberToInsert, int pos);

private:
	int* m_array = nullptr;
	int m_size = 0;
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
	bool isEqual(Iterator& other);

	bool operator==(const Iterator& other) const;
	bool operator!=(const Iterator& other) const;

private:
	Array* m_array = nullptr;
	int m_pos = 0;
};

class Array::ConstIterator {
public:
	ConstIterator(const Array* array, int pos);
	const int& operator*();
	ConstIterator& operator++();
	ConstIterator operator++(int);
	ConstIterator& operator--();
	ConstIterator operator--(int);
	ConstIterator operator+(int numeber);
	ConstIterator operator-(int numeber);

	bool hasNext() const;

	int getPos();
	bool isEqual(const ConstIterator& other) const;

	bool operator==(const ConstIterator& other) const;
	bool operator!=(const ConstIterator& other) const;

private:
	const Array* m_array = nullptr;
	int m_pos = 0;
};