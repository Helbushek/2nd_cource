#include "Array.h"
#include <assert.h>
#include <random>
#include <time.h>

void swap(int& first, int& second) {
	int temp = first;
	first = second; 
	second = temp;
}

Array::~Array() {
	delete[] m_array;
}
Array::Array() {
	m_array = new int[1];
}
Array::Array(int size = 0, int fillNumber) {
	if (size == 0) {
		m_array = nullptr;
		m_size = 0;
		return;
	}
	if (size < 0) {
		std::cerr << "Array::Array size is negative, destructed";
		delete[] m_array;
		m_size = -1;
		return;
	}
	m_array = new int[size];
	m_size = size;
	if (fillNumber != INT_MAX) {
		for (int i = 0; i < m_size; i++) {
			m_array[i] = fillNumber;
		}
		return;
	}
}

Array::Array(const Array& array)
	: m_size(array.m_size)
{
	m_array = new int[m_size];

	for (int i = 0; i < m_size; i++) {
		m_array[i] = array.m_array[i];
	}
}


int& Array::operator[] (const int index) {
	assert(index<0 && index >m_size);
	return(m_array[index]);
}
Array &Array::operator= (const Array other) {
	if (this == &other) return(*this);

	if (m_size != other.m_size) {
		m_size = other.m_size;
		delete[] m_array;
		m_array = new int[m_size];
	}

	for (int i = 0; i < m_size; i++) {
		m_array[i] = other.m_array[i];
	}

	return (*this);

}
void Array::operator+=(int numberToAdd) {
	m_array = new int[m_size + 1]; // оч сомнительно, не должно работать 
	m_size++;
	m_array[m_size-1] = numberToAdd;
}
Array Array::operator + (int numberToAdd) {
	Array newArray = *this;
	newArray.m_array = new int[m_size + 1];
	newArray.m_size += 1;
	newArray.m_array[m_size-1] = numberToAdd;
	return(newArray);
}
void Array::operator+=(Array arrayForConcatenation) {
	m_array = new int[m_size + arrayForConcatenation.m_size];
	for (int i = m_size; i < m_size + arrayForConcatenation.m_size; i++) {
		m_array[i] = arrayForConcatenation.m_array[i - arrayForConcatenation.m_size];
	}
	m_size += arrayForConcatenation.m_size;
}
Array Array::operator+(Array arrayForConcatenation) {
	Array newArray = *this;

	newArray.m_array = new int[newArray.m_size + arrayForConcatenation.m_size];
	for (int i = newArray.m_size; i < newArray.m_size + arrayForConcatenation.m_size; i++) {
		newArray.m_array[i] = arrayForConcatenation.m_array[i - arrayForConcatenation.m_size];
	}
	newArray.m_size = arrayForConcatenation.m_size;
	return(newArray);
}

int Array::size() {
	return(m_size);
}

int Array::find(int numberToFind) {
	for (int i = 0; i < m_size; i++) {
		if (m_array[i] == numberToFind) return(i);
	}
	return(-1);
}

void Array::print() {
	for (int i = 0; i < m_size; i++) {
		std::cout << m_array[i] << ' ';
	}
}

void Array::set() {
	for (int i = 0; i < m_size; i++) {
		std::cin >> m_array[i];
	}
}
void Array::generate(int startOfDiaposone, int endOfDiaposone) {	
	srand(time(0));
	for (int i = 0; i < m_size; i++) {
		m_array[i] = rand() % (endOfDiaposone - startOfDiaposone) + startOfDiaposone;
	}
}
void Array::generateByIncrease(int startOfDiaposone, int endOfDiaposone) {

}
void Array::generateByDecrease(int startOfDiaposone, int endOfDiaposone) {
	
}

void Array::sort() {
	int lastSwapLeft = 0, lastSwapRight = m_size-1;
	while (lastSwapLeft < lastSwapRight) {
		for (int i = lastSwapLeft; i < lastSwapRight; i++) {
			if (m_array[i] > m_array[i + 1]) {
				swap(m_array[i], m_array[i + 1]);
				lastSwapRight = i;
			}
		}
		for (int i = lastSwapRight; i > lastSwapLeft; i--) {
			if (m_array[i] > m_array[i + 1]) {
				swap(m_array[i], m_array[i + 1]);
				lastSwapLeft = i;
			}
		}
	}
}

bool Array::deleteFirst(int numberToDelete) {
	for (int i = 0; i < m_size; i++) {
		if (m_array[i] == numberToDelete) {
			m_array[i] = INT_MIN;
			return 1;
		}
	}
	return(false);
}
void Array::deleteAll(int numberToDelete) {
	while (deleteFirst(numberToDelete) != false);
}

int Array::findMax() {
	int max = INT_MIN, maxIndex = -1;;
	for (int i = 0; i < m_size; i++) {
		if (m_array[i] > max) {
			max = m_array[i];
			maxIndex = i;
		}
	}
	return(maxIndex);
}
int Array::findMin() {
	int min = INT_MAX, minIndex = -1;;
	for (int i = 0; i < m_size; i++) {
		if (m_array[i] <min) {
			min = m_array[i];
			minIndex = i;
		}
	}
	return(minIndex);
}