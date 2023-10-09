#include "Array.h"
#include <assert.h>
#include <random>
#include <time.h>

void swapInt(int& first, int& second) {
	int temp = first;
	first = second; 
	second = temp;
}

Array::~Array() {
	delete[] m_array;
}

Array::Array(int size)
{
	if (size > 0) {
		m_array = new int[size];
		m_size = size;
	}
}

Array::Array(int size, int fillNumber)
	: Array(size)
{
	for (int i = 0; i < m_size; i++) {
		m_array[i] = fillNumber;
	}
}



Array::Array(const Array& array)
	: Array(array.m_size)
{
	for (int i = 0; i < m_size; i++) {
		m_array[i] = array.m_array[i];
	}
}

Array::Array(Array&& other) 
{
	m_size = other.m_size;
	m_array = other.m_array;
	other.m_array = nullptr;
}


int& Array::operator[] (const int index) {
	assert(index>=0 && index<m_size);
	return(m_array[index]);
}
Array &Array::operator= (const Array& other) {
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

void Array::swap(Array &other) {
	int* temp = m_array;
	m_array = other.m_array;
	other.m_array = temp;

	int tempSize = m_size;
	m_size = other.m_size;
	other.m_size = tempSize;
}


Array Array::operator+(const Array &arrayForConcatenation) const {
	Array temp(m_size + arrayForConcatenation.m_size);

	for (int i = 0; i < m_size; i++) {
		temp.m_array[i] = m_array[i];
	}
	for (int j = m_size; j < temp.m_size; j++) {
		temp.m_array[j] = arrayForConcatenation.m_array[j - m_size];
	}

	return(temp);
}
Array &Array::operator+=(const Array &arrayForConcatenation) {
	(*this + arrayForConcatenation).swap(*this);
	return(*this);
}

Array Array::operator + (int numberToAdd) const {
	Array temp(1, numberToAdd);
	return(*this + temp);
}

Array& Array::operator+=(int numberToAdd) {
	Array temp(1, numberToAdd);
	(*this + temp).swap(*this);
	return(*this);
}

bool Array::operator==(const Array& other) {
	if (m_size != other.m_size) return(false);
	if (m_size == other.m_size) {
		for (int i = 0; i < m_size; i++) {
			if (m_array[i] != other.m_array[i]) {
				return(false);
			}
		}
	}
	return(true);	
}
bool Array::operator!=(const Array& other) {
	return(!(*this == other));
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


void Array::sort() {
	int countForSwap = 1;
	while (countForSwap != 0) {
		countForSwap = 0;
		for (int i = 0; i < m_size - 1; i++) {

			if (m_array[i] > m_array[i + 1]) {
				swapInt(m_array[i], m_array[i + 1]);
				countForSwap++;
			}
		}
	}
}

void Array::sortDecrease() {
	int countForSwap = 1;
	while (countForSwap != 0) {
		countForSwap = 0;
		for (int i = 0; i < m_size - 1; i++) {

			if (m_array[i] < m_array[i + 1]) {
				swapInt(m_array[i], m_array[i + 1]);
				countForSwap++;
			}
		}
	}
}

void Array::generate(int startOfDiaposone, int endOfDiaposone) {
	srand(time(0));
	for (int i = 0; i < m_size; i++) {
		m_array[i] = rand() % (endOfDiaposone - startOfDiaposone+1) + startOfDiaposone;
	}
}
void Array::generateByIncrease(int startOfDiaposone, int endOfDiaposone) {
	generate();
	sort();
}
void Array::generateByDecrease(int startOfDiaposone, int endOfDiaposone) {
	generate();
	sortDecrease();
}

bool Array::deleteFirst(int numberToDelete) {
	for (int i = 0; i < m_size; i++) {
		if (m_array[i] == numberToDelete) {
			for (int j = i; j < m_size - 1; j++) {
				m_array[j] = m_array[j + 1];
			}
			m_size--;
			return(true);
		}
	}
	return(false);
}
void Array::deleteAll(int numberToDelete) {
	while (deleteFirst(numberToDelete) != false);
}

void Array::deleteByIndex(int indexToDelete) {
	if (indexToDelete < 0 || indexToDelete >= m_size) {
		std::cerr << "Incorrect index in Array::delete, will not be deleted... ";
		return;
	}
	for (int i = indexToDelete; i < m_size - 1; i++) {
		m_array[i] = m_array[i + 1];
	}
	m_size--;
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
	int min = INT_MAX, minIndex = -1;
	for (int i = 0; i < m_size; i++) {
		if (m_array[i] <min) {
			min = m_array[i];
			minIndex = i;
		}
	}
	return(minIndex);
}



Array::Iterator::Iterator(Array* array, const int pos) {
	m_array = array;
	m_pos = pos;
}

int& Array::Iterator::operator*() {
	return((*m_array)[m_pos]);
}
Array::Iterator& Array::Iterator::operator++() {
	m_pos++;
	return(*this);
}
Array::Iterator Array::Iterator::operator++(int) {
	Array::Iterator temp = *this;
	m_pos++;
	return(temp);
}
Array::Iterator& Array::Iterator::operator--() {
	m_pos--;
	return(*this);
}
Array::Iterator Array::Iterator::operator--(int) {
	Array::Iterator temp = *this;
	m_pos--;
	return(temp);
}

bool Array::Iterator::hasNext() const {
	return(m_pos < (*m_array).m_size);
}

bool Array::Iterator::operator==(const Iterator& other) const{
	return(m_array == other.m_array && m_pos == other.m_pos);
}
bool Array::Iterator::operator!=(const Iterator& other) const {
	return(!(*this == other));
}

bool Array::Iterator::isEqual(Array::Iterator& other) {
	return(m_array == other.m_array);
}


Array::Iterator Array::begin() {
	return Iterator(this, 0);

}
Array::Iterator Array::end() {
	return Iterator(this, size());
}

Array::Iterator Array::Iterator::operator+(int number) {
	Array::Iterator temp = *this;
	for (int i = 0; i < number; i++) {
		temp++;
	}
	return(temp);

}

Array::Iterator Array::Iterator::operator-(int number) {
	Array::Iterator temp = *this;

	for (int i = 0; i < number; i++) {
		temp--;
	}
	return(temp);

}

int Array::Iterator::getPos() {
	return(m_pos);
}

void Array::deleteDiaposon(Array::Iterator start, Array::Iterator end) {
	if (start.getPos()<0 || start.getPos()>m_size || end.getPos()<0 || end.getPos()>m_size-1) {
		std::cerr << "Invalid index of diaposon in Array::deleteDiaposon, will be executed from method... ";
		return;
	}
	if (start.getPos() > end.getPos()) {
		std::cerr << "Invalid diaposone, start>=end in Array::deleteDiaposon, will execute from method... ";
		return;
	}
	if (!start.isEqual(end)) {
		std::cerr << "Iterators are not on same array, will execute from method... ";
		return;
	}
	int deleteCount = 0;
	for (Array::Iterator i = start; i != end+1; ++i) {
		deleteByIndex(i.getPos()-deleteCount);
		deleteCount++;
	}
}


void Array::insert(int numberToInsert, Array::Iterator iter) {
	if (iter.getPos()<0 || iter.getPos() > m_size) {
		std::cerr << "Invalid index in Array::insert, will not run... \n";
		return;
	}
	int posIter = iter.getPos();

	{
		Array temp(m_size + 1);
		for (int i = 0; i < m_size; i++) {
			temp.m_array[i] = m_array[i];
		}
		(*this).swap(temp);
	}

	for (Array::Iterator temp = end() - 1; temp!=iter; temp--) {
		*temp = *(temp-1);
	} 
	m_array[posIter] = numberToInsert;
}


void Array::insert(int numberToInsert, int pos) {
	Array::Iterator iter(this, pos);
	insert(numberToInsert, iter);
}

std::ostream &operator<<(std::ostream& out, const Array& array) {
	for (int i = 0; i < array.m_size; i++) {
		out << array.m_array[i] << ' ';
	}
	return(out);
}

std::istream& operator>>(std::istream& in, Array& array) {
	for (int i = 0; i < array.m_size; i++) {
		in >> array.m_array[i];
	}
	return(in);
}