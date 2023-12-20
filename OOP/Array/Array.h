#pragma once
#include <iostream>
#include <assert.h>
#include <random>
#include <time.h>
#include <limits>

template <typename ItemType>
class Array {
public:
	template<typename IteratorTemplate, typename ArrayTemplate>
	class TemplateIterator;
	using iterator= TemplateIterator<ItemType, Array>;
	using ConstIterator = TemplateIterator<const ItemType, const Array>;
public:


	explicit Array(const int _size = 0);
	Array(const int _size, const ItemType &fillNumber);
	~Array();
	Array(const Array &array);
	Array(Array&& other);

	void swap(Array &other);

	ItemType& operator[] (const int index);

	const ItemType& operator[] (const int index) const;

	Array& operator= (const Array &arrayToEqualize);
	Array& operator+=(const ItemType &numberToAdd);
	Array operator + (const ItemType &numberToAdd) const;
	Array& operator+=(const Array &arrayForConcatenation);
	Array operator+(const Array &arrayForConcatenation) const;
	bool operator==(const Array& other) const;
	bool operator!=(const Array& other) const;

	int _size() const;

	int find(const ItemType &numberToFind) const;

	void print() const;
	void set();

	void sort();
	void sortDecrease();

	bool deleteFirst(const ItemType &numberToDelete);
	void deleteAll(const ItemType &numberToDelete);
	void deleteByIndex(const int indexToDelete);

	int findMax() const;
	int findMin() const;

	iterator begin();
	iterator end();

	ConstIterator begin() const;
	ConstIterator end() const;

	void deleteDiaposon(Array::iterator begin, Array::iterator end); //range
	void insert(const ItemType &numberToInsert, iterator iter);
	void insert(const ItemType &numberToInsert, const int pos);

protected:
	ItemType* m_array = nullptr;
	int m_size = 0;
};

template <typename ItemType>
std::ostream& operator<<(std::ostream& out, const Array<ItemType>& array) {
	for (auto iter : array) {
		out << iter << ' ';
	}
	return(out);
}

template <typename ItemType>
std::istream& operator>>(std::istream& in, Array<ItemType>& array) {
	for (int i = 0; i < array._size(); i++) {
		in >> array[i];
	}
	return(in);
}

template <typename ItemType>
template <typename IT, typename AT>
class Array<ItemType>::TemplateIterator {
public:
	TemplateIterator(AT * array, const int pos);
	IT& operator*() const;
	TemplateIterator& operator++();
	TemplateIterator operator++(int);
	TemplateIterator& operator--();
	TemplateIterator operator--(int);
	TemplateIterator& operator+=(int number);
	TemplateIterator& operator-=(int number);
	TemplateIterator operator+(int number) const;
	TemplateIterator operator-(int number) const;

	bool hasNext() const;

	int getPos() const;
	bool isEqual(const TemplateIterator& other) const;

	bool operator==(const TemplateIterator& other) const;
	bool operator!=(const TemplateIterator& other) const;

private:
	AT* m_array = nullptr;
	int m_pos = 0;
};

template <typename ItemType>
void swapInt(ItemType& first, ItemType& second) {
	ItemType temp = first;
	first = second;
	second = temp;
}

template <typename ItemType>
Array<ItemType>::~Array() {
	delete[] m_array;
}

template <typename ItemType>
Array<ItemType>::Array(const int _size)
{
	if (_size > 0) {
		m_array = new ItemType[_size];
		m_size = _size;
	}
}

template <typename ItemType>
Array<ItemType>::Array(const int _size, const ItemType &fillNumber)
	: Array(_size)
{
	for (int i = 0; i < m_size; i++) {
		m_array[i] = fillNumber;
	}
}


template <typename ItemType>
Array<ItemType>::Array(const Array& array)
	: Array(array.m_size)
{
	for (int i = 0; i < m_size; i++) {
		m_array[i] = array.m_array[i];
	}
}

template <typename ItemType>
Array<ItemType>::Array(Array&& other)
{
	m_size = other.m_size;
	m_array = other.m_array;
	other.m_array = nullptr;
}

template <typename ItemType>
ItemType& Array<ItemType>::operator[] (const int index) {
	assert(index >= 0 && index < m_size);
	return(m_array[index]);
}

template <typename ItemType>
const ItemType& Array<ItemType>::operator[] (const int index) const {
	assert(index >= 0 && index < m_size);
	return(m_array[index]);
}


template <typename ItemType>
Array<ItemType>& Array<ItemType>::operator=(const Array& other) {
	if (this == &other) return(*this);

	if (m_size != other.m_size) {
		m_size = other.m_size;
		delete[] m_array;
		m_array = new ItemType[m_size];
	}

	for (int i = 0; i < m_size; i++) {
		m_array[i] = other.m_array[i];
	}

	return (*this);

}

template <typename ItemType>
void Array<ItemType>::swap(Array& other) {
	ItemType* temp = m_array;
	m_array = other.m_array;
	other.m_array = temp;

	int tempSize = m_size;
	m_size = other.m_size;
	other.m_size = tempSize;
}

template <typename ItemType>
Array<ItemType> Array<ItemType>::operator+(const Array& arrayForConcatenation) const {
	Array temp(m_size + arrayForConcatenation.m_size);

	for (int i = 0; i < m_size; i++) {
		temp.m_array[i] = m_array[i];
	}
	for (int j = m_size; j < temp.m_size; j++) {
		temp.m_array[j] = arrayForConcatenation.m_array[j - m_size];
	}

	return(temp);
}

template <typename ItemType>
Array<ItemType>& Array<ItemType>::operator+=(const Array& arrayForConcatenation) {
	(*this + arrayForConcatenation).swap(*this);
	return(*this);
}


template <typename ItemType>
Array<ItemType> Array<ItemType>::operator + (const ItemType &numberToAdd) const {
	Array temp(1, numberToAdd);
	return(*this + temp);
}

template <typename ItemType>
Array<ItemType>& Array<ItemType>::operator+=(const ItemType &numberToAdd) {
	Array temp(1, numberToAdd);
	(*this + temp).swap(*this);
	return(*this);
}

template <typename ItemType>
bool Array<ItemType>::operator==(const Array& other) const{
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

template <typename ItemType>
bool Array<ItemType>::operator!=(const Array& other) const{
	return(!(*this == other));
}

template <typename ItemType>
int Array<ItemType>::_size() const{
	return(m_size);
}

template <typename ItemType>
int Array<ItemType>::find(const ItemType &numberToFind) const{
	for (int i = 0; i < m_size; i++) {
		if (m_array[i] == numberToFind) return(i);
	}
	return(-1);
}

template <typename ItemType>
void Array<ItemType>::print() const{
	for (int i = 0; i < m_size; i++) {
		std::cout << m_array[i] << ' ';
	}
}

template <typename ItemType>
void Array<ItemType>::set() {
	for (int i = 0; i < m_size; i++) {
		std::cin >> m_array[i];
	}
}

template <typename ItemType>
void Array<ItemType>::sort() {
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

template <typename ItemType>
void Array<ItemType>::sortDecrease() {
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

template <typename ItemType>
bool Array<ItemType>::deleteFirst(const ItemType &numberToDelete) {
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

template <typename ItemType>
void Array<ItemType>::deleteAll(const ItemType &numberToDelete) {
	while (deleteFirst(numberToDelete) != false);
}

template <typename ItemType>
void Array<ItemType>::deleteByIndex(const int indexToDelete) {
	if (indexToDelete < 0 || indexToDelete >= m_size) {
		std::cerr << "Incorrect index in Array::delete, will not be deleted... ";
		return;
	}
	for (int i = indexToDelete; i < m_size - 1; i++) {
		m_array[i] = m_array[i + 1];
	}
	m_size--;
}

template <typename ItemType>
int Array<ItemType>::findMax() const{
	ItemType max = m_array[0];
	int maxIndex = -1;
	for (int i = 0; i < m_size; i++) {
		if (m_array[i] >= max) {
			max = m_array[i];
			maxIndex = i;
		}
	}
	return(maxIndex);
}

template <typename ItemType>
int Array<ItemType>::findMin() const{
	ItemType min = m_array[0];
	int minIndex = -1;
	for (int i = 0; i < m_size; i++) {
		if (m_array[i] <= min) {
			min = m_array[i];
			minIndex = i;
		}
	}
	return(minIndex);
}

template <typename ItemType>
template <typename IT, typename AT>
Array<ItemType>::TemplateIterator<IT, AT>::TemplateIterator(AT* array, const int pos) {
	m_array = array;
	m_pos = pos;
}

template <typename ItemType>
template <typename IT, typename AT>
IT& Array<ItemType>::TemplateIterator<IT, AT>::operator*() const{
	return((*m_array)[m_pos]);
}

template <typename ItemType>
template <typename IT, typename AT>
Array<ItemType>::TemplateIterator<IT, AT>& Array<ItemType>::TemplateIterator<IT, AT>::operator++() {
	m_pos++;
	return(*this);
}

template <typename ItemType>
template <typename IT, typename AT>
Array<ItemType>::TemplateIterator<IT, AT> Array<ItemType>::TemplateIterator<IT, AT>::operator++(int) {
	Array<ItemType>::TemplateIterator<IT, AT> temp = *this;
	m_pos++;
	return(temp);
}

template <typename ItemType>
template <typename IT, typename AT>
Array<ItemType>::TemplateIterator<IT, AT>& Array<ItemType>::TemplateIterator<IT, AT>::operator--() {
	m_pos--;
	return(*this);
}

template <typename ItemType>
template <typename IT, typename AT>
Array<ItemType>::TemplateIterator<IT, AT> Array<ItemType>::TemplateIterator<IT, AT>::operator--(int) {
	Array<ItemType>::TemplateIterator<IT, AT> temp = *this;
	m_pos--;
	return(temp);
}

template <typename ItemType>
template <typename IT, typename AT>
bool Array<ItemType>::TemplateIterator<IT, AT>::hasNext() const {
	return(m_pos < (*m_array).m_size);
}

template <typename ItemType>
template <typename IT, typename AT>
bool Array<ItemType>::TemplateIterator<IT, AT>::operator==(const TemplateIterator<IT, AT>& other) const {
	return(m_array == other.m_array && m_pos == other.m_pos);
}

template <typename ItemType>
template <typename IT, typename AT>
bool Array<ItemType>::TemplateIterator<IT, AT>::operator!=(const TemplateIterator<IT, AT>& other) const {
	return(!(*this == other));
}

template <typename ItemType>
template <typename IT, typename AT>
bool Array<ItemType>::TemplateIterator<IT, AT>::isEqual(const Array<ItemType>::TemplateIterator<IT, AT>& other) const{
	return(m_array == other.m_array);
}

template <typename ItemType> typename
Array<ItemType>::iterator Array<ItemType>::begin() {
	return iterator(this, 0);
}

template <typename ItemType> typename
Array<ItemType>::iterator Array<ItemType>::end() {
	return iterator(this, _size());
}

template <typename ItemType> typename
Array<ItemType>::ConstIterator Array<ItemType>::begin() const{
	return ConstIterator(this, 0);
}

template <typename ItemType> typename
Array<ItemType>::ConstIterator Array<ItemType>::end() const{
	return ConstIterator(this, _size());
}

template <typename ItemType>
template <typename IT, typename AT>
Array<ItemType>::TemplateIterator<IT, AT>& Array<ItemType>::TemplateIterator<IT, AT>::operator+=(int number) {
	*this = Array<ItemType>::TemplateIterator<IT, AT>(m_array, m_pos + number);
	return(*this);
}

template <typename ItemType>
template <typename IT, typename AT>
Array<ItemType>::TemplateIterator<IT, AT>& Array<ItemType>::TemplateIterator<IT, AT>::operator-=(int number) {
	*this = Array<ItemType>::TemplateIterator<IT, AT>(m_array, m_pos - number);
	return(*this);
}

template <typename ItemType>
template <typename IT, typename AT>
Array<ItemType>::TemplateIterator<IT, AT> Array<ItemType>::TemplateIterator<IT, AT>::operator+(int number) const{
	Array<ItemType>::TemplateIterator<IT, AT> temp = Array<ItemType>::TemplateIterator<IT, AT>(m_array, (*this).m_pos + number);
	return(temp);
}

template <typename ItemType>
template <typename IT, typename AT>
Array<ItemType>::TemplateIterator<IT, AT> Array<ItemType>::TemplateIterator<IT, AT>::operator-(int number) const{
	Array<ItemType>::TemplateIterator<IT, AT> temp = Array<ItemType>::TemplateIterator<IT, AT>(m_array, (*this).m_pos - number);
	return(temp);
}

template <typename ItemType>
template <typename IT, typename AT>
int Array<ItemType>::TemplateIterator<IT, AT>::getPos() const{
	return(m_pos);
}

template <typename ItemType>
void Array<ItemType>::deleteDiaposon(Array<ItemType>::iterator start, Array<ItemType>::iterator end) {
	if (start.getPos() < 0 || start.getPos() > m_size || end.getPos() < 0 || end.getPos() > m_size - 1) {
		std::cerr << "Invalid index of diaposon in Array::deleteDiaposon, will be executed from method... ";
		return;
	}
	if (start.getPos() > end.getPos()) {
		std::cerr << "Invalid diaposon, start>=end in Array::deleteDiaposon, will execute from method... ";
		return;
	}
	if (!start.isEqual(end)) {
		std::cerr << "Iterators are not on same array, will execute from method... ";
		return;
	}
	int deleteCount = 0;
	for (Array<ItemType>::iterator i = start; i != end + 1; ++i) {
		deleteByIndex(i.getPos() - deleteCount);
		deleteCount++;
	}
}

template <typename ItemType>
void Array<ItemType>::insert(const ItemType &numberToInsert, iterator iter) {
	if (iter.getPos() < 0 || iter.getPos() > m_size) {
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

	for (auto temp = end() - 1; temp != iter; temp--) {
		*temp = *(temp - 1);
	}
	m_array[posIter] = numberToInsert;
}

template <typename ItemType>
void Array<ItemType>::insert(const ItemType &numberToInsert, const int pos) {
	Array<ItemType>::iterator iter(this, pos);
	insert(numberToInsert, iter);
}