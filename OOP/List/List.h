#pragma once
#include <iostream>
#include <vector>
#include <assert.h>
#include <random>
#include <time.h>
#include "Array.h"


template<typename TL>
class List;

template<typename TL>
class Iterator;

// ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |

template <typename T>
class Node {
	friend class List<T>;
	friend class Iterator<T>;
public:
	Node();
	Node(const T value);
	Node(const Node<T> &other);
	
	T& get();

	T get() const;

	operator T() const{
		return body;
	}

	void swap(Node& other);

	bool operator>(const Node<T>& other);
	bool operator<(const Node<T>& other);

	bool operator>=(const Node<T>& other);
	bool operator<=(const Node<T>& other);

private:
	T body = 0;
	Node<T>* next;
	Node<T>* prev;
};

template <typename T>
class Node<const T> {
	friend class List<const T>;
	friend class Iterator<const T>;
public:
	Node();
	Node(const T value);
	Node(const Node<T>& other);

	T get() const;

	operator T() const {
		return body;
	}

	void swap(Node& other);

	bool operator>(const Node<T>& other);
	bool operator<(const Node<T>& other);

	bool operator>=(const Node<T>& other);
	bool operator<=(const Node<T>& other);

private:
	const T body = 0;
	Node<const T>* next;
	Node<const T>* prev;
};

// ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |

template<typename T>
void Node<T>::swap(Node& other) {
	std::swap(body, other.body);
	std::swap(next, other.next);
	std::swap(prev, other.prev);
}

template<typename T>
T& Node<T>::get() {
	return body;
}

template<typename T>
T Node<T>::get() const{
	return body;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Node<T>& that) {
	os << that.body;
}

template<typename T>
std::istream& operator>>(std::istream& is, Node<T>& that) {
	is >> that.body;
}

template<typename T>
Node<T>::Node() {
	next = prev = nullptr;
}

template<typename T>
Node<T>::Node(T value) {
	next = prev = nullptr;
	body = value;
}

template<typename T>
Node<T>::Node(const Node<T> &other) {
	next = other.next;
	prev = other.prev;
	body = other.body;
}

template<typename T>
bool Node<T>::operator>(const Node<T>& other) {
	if (body > other.body)
		return true;
	return false;
}

template<typename T>
bool Node<T>::operator<(const Node<T>& other) {
	if (body < other.body)
		return true;
	return false;
}

template<typename T>
bool Node<T>::operator>=(const Node<T>& other) {
	if (body >= other.body)
		return true;
	return false;
}

template<typename T>
bool Node<T>::operator<=(const Node<T>& other) {
	if (body <= other.body)
		return true;
	return false;
}

// ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |

template<typename TI>
class Iterator {
	friend class List<TI>;

public: 
	Iterator(const Iterator& other);

	Iterator(Node<TI>* node) {
		this->link = node;
	}

	bool operator==(const Iterator& other);
	bool operator!=(const Iterator& other);

	bool isSibling(const Iterator& other);

	Iterator& operator+= (int value);
	Iterator& operator++();
	Iterator operator++(int);
	Iterator& operator-=(int value);
	Iterator& operator--();
	Iterator operator--(int);
	bool operator>(const Iterator& other);
	bool operator<(const Iterator& other);

	TI& operator*();
	TI operator*() const;

private:
	Node<TI>* link = nullptr;
};

template<typename TI>
class Iterator<const TI> {
	friend class List<const TI>;

public:
	Iterator(const Iterator& other);

	Iterator(Node<const TI>* node) {
		this->link = node;
	}

	bool operator==(const Iterator& other);
	bool operator!=(const Iterator& other);

	bool isSibling(const Iterator& other);

	Iterator& operator+= (int value);
	Iterator& operator++();
	Iterator operator++(int);
	Iterator& operator-=(int value);
	Iterator& operator--();
	Iterator operator--(int);
	bool operator>(const Iterator& other);
	bool operator<(const Iterator& other);

	TI& operator*();
	TI operator*() const;

private:
	Node<const TI>* link = nullptr;
};

// ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |

template<typename TI>
Iterator<TI>::Iterator(const Iterator& other) {
	link = other.link;
}

template<typename TI>
bool Iterator<TI>::operator==(const Iterator& other) {
	if (link == other.link)
		return true;
	return false;
}

template<typename TI>
bool Iterator<TI>::operator!=(const Iterator& other) {
	return (!(*this == other));
}

template<typename TI>
bool Iterator<TI>::isSibling(const Iterator& other) {
	Node<TI>* temp = link;
	while (temp->prev != nullptr) {
		temp = temp->prev; // travel to head
	}
	while (temp->next != nullptr) {
		if (other.link == temp)
			return true; // if other points to element in the same list
		temp = temp->next; // travel through list
	}
	return false;
}

template<typename TI>
Iterator<TI>& Iterator<TI>::operator++() {
	*this = Iterator(this->link->next);
	return *this;
}

template<typename TI>
Iterator<TI>& Iterator<TI>::operator--() {
	*this = Iterator(this->link->prev);
	return *this;
}

template<typename TI>
Iterator<TI> Iterator<TI>::operator++(int) {
	Iterator temp(*this);
	*this = Iterator(this->link->next);
	return temp;
}

template<typename TI>
Iterator<TI> Iterator<TI>::operator--(int) {
	Iterator temp(*this);
	*this = Iterator(this->link->prev);
	return temp;
}

template<typename TI>
TI& Iterator<TI>::operator*() {
	return link->get();
}

template<typename TI>
TI Iterator<TI>::operator*() const {
	return link->get();
}

template<typename TI>
bool Iterator<TI>::operator>(const Iterator<TI>& other) {
	assert(isSibling(other));
	Iterator temp = *this;
	while (temp.link != nullptr) {
		if (temp.link == other.link)
			return false; // other is righter from or on this
		temp.link = temp.link->next;
	}
	return true; // other is lefter 
}

template<typename TI>
	bool Iterator<TI>::operator<(const Iterator<TI>& other) {
		return (!((*this) > other));
}

// ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |


template<typename TL>
class List {
	typedef Iterator<TL> iterator;
	typedef Iterator<const TL> const_iterator;

public:

	iterator begin();
	iterator end();
	iterator randAccess();

	const_iterator begin() const;
	const_iterator end() const;
	const_iterator randAccess() const;

public:
	List();
	List(int nodesNumber, TL value);
	List(const std::vector<TL>& other);
	List(const Array<TL>& other);
	List(const List<TL> &other);

	~List() {
		clear();

		delete[] _head;
		delete[] _tail;
	}

	int getSize() const;

	void swap(List<TL>& other);

	void print();
	void set();

	iterator search(TL value);

	Node<TL>* push(const TL value, int index = 0); // index = 0 after head, other index - before that index
	Node<TL>* push(const TL value, Node<TL> * adress);
	Node<TL>* pushKey(TL valueToInsert, TL keyToSearch); // inserts before KEY
	Node<TL>* pushBack(TL value); // before tail
	iterator push(TL value, iterator iter);

	void deleteBefore(int index = 0);
	void deleteIn(Node<TL>* node);
	void deleteBack();
	void deleteKey(TL key);
	void deleteBefore(iterator iter);
	void deleteDiaposon(iterator first, iterator second);

	Node<TL>* min();
	Node<TL>* max();

	bool isEmpty();

	void clear();

	void sort(List<TL>& array, int leftBorder=0, int rightBorder=-1, int level=31);

	void operator=(const List<TL>& other);
	bool operator==(const List<TL>& other);
	bool operator!=(const List<TL>& other);
	void operator+=(const List<TL>& other);
	List<TL> operator+(const List<TL>& other);
	TL& operator[](int index);
	const TL operator[](int index) const;

private:
	void construct();

	Node<TL>* _head;
	Node<TL>* _tail;
	int size;
};

// ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |


template<typename TL>
Iterator<TL> List<TL>::begin() {
	return Iterator<TL>(_head->next);
}

template<typename TL>
Iterator<TL> List<TL>::end() {
	return Iterator<TL>(_tail);
}

template<typename TL> 
Iterator<TL> List<TL>::randAccess() {
	srand(time(0));
	Iterator<TL> temp = begin();
	for (int r = rand() % size, i = 0; i < r; i++) {
		temp++;
	}

	return temp;
}

template<typename TL>
Iterator<const TL> List<TL>::begin() const {
	return Iterator<const TL>(_head->next);
}

template<typename TL>
Iterator<const TL> List<TL>::end() const{
	return Iterator<const TL>(_tail);
}

template<typename TL>
Iterator<const TL> List<TL>::randAccess() const{
	srand(time(0));
	Iterator<const TL> temp = begin() + rand() % size;

	return temp;
}

template<typename TL> 
void List<TL>::construct() {
	if (_head != nullptr || _tail != nullptr) {
		clear();
		delete[] _head;
		delete[] _tail;
	}
	size = 0;
	_head = new Node<TL>();
	_tail = new Node<TL>();
	_head->next = _tail;
	_tail->prev = _head;
}

template<typename TL>
List<TL>::List() {
	construct();
}

template<typename TL>
List<TL>::List(int nodesNumber, TL value) {
	construct();

	for (int i = 0; i < nodesNumber; i++) {
		pushBack(value);
	}
}

template<typename TL>
List<TL>::List(const std::vector<TL>& other) {
	construct();

	for (int i = 0; i < size; i++) {
		pushBack(other[i]);
	}
}

template<typename TL>
List<TL>::List(const Array<TL>& other) {
	construct();

	for (int i = 0; i < size; i++) {
		pushBack(other[i]);
	}
}

template<typename TL>
List<TL>::List(const List<TL> &other) {
	construct();
	for (int i = 0; i < size; i++) {

	}
}


template<typename TL>
int List<TL>::getSize() const{
	return size;
}

template<typename TL>
void List<TL>::swap(List<TL>& other) {
	std::swap(size, other.size);
	std::swap(_head, other._head);
	std::swap(_tail, other._tail);
}

template<typename TL>
void List<TL>::print() {
	Node<TL>* runner = _head->next;
	while(runner!=_tail) {
		std::cout << runner->body << ' ';
		runner = runner->next;
	}
}

template<typename TL> 
void List<TL>::set() {
	Node<TL> *runner = _head->next;
	while (runner!=_tail){
		std::cin >> runner->body;
		runner = runner->next;
	}
}

template<typename TL>
Iterator<TL> List<TL>::search(TL value) {
	Node<TL>* runner = _head->next;
	while (runner != _tail) {
		if (runner->body == value) {
			Iterator<TL> temp(runner);
			return temp;
		}
		runner = runner->next;
	}
	return nullptr;
}

template<typename TL>
Node<TL>* List<TL>::push(const TL value, int index) {
	assert(index >= 0 && index < size);
	Node<TL>* temp = _head->next; // 0`th element
	for (int i = 0; i < index; i++) {
		temp = temp->next; // index element
	}
	temp = push(value, temp);
	return temp;
}

template<typename TL>
Node<TL>* List<TL>::push(const TL value, Node<TL> *adress) {
	Node<TL>* temp = new Node<TL>();
	temp->body = value;
	temp->next = adress;
	temp->prev = adress->prev;
	temp->next->prev = temp;
	temp->prev->next = temp;
	size++;
	return temp;
}

template<typename TL>
Node<TL>* List<TL>::pushKey(TL valueToInsert, TL keyToSearch) {
	Node<TL>* temp = search(keyToSearch);
	temp = push(valueToInsert, temp);
	return temp;
}


template<typename TL>
Node<TL>* List<TL>::pushBack(TL value) {
	Node<TL>* temp = new Node<TL>();
	temp->body = value;
	temp->next = _tail;
	temp->prev = _tail->prev;

	_tail->prev->next = temp;
	_tail->prev = temp;
	size++;
	return temp;
}

template<typename TL>
Iterator<TL> List<TL>::push(TL value, iterator iter) {
	Node<TL>* temp = iter.link;
	push(value, temp);
}

template<typename TL>
void List<TL>::deleteBefore(int index) {
	assert(index > 0 && index < size);
	Node<TL>* temp = _head->next;
	for (int i = 0; i < index - 1; i++) {
		temp = temp->next;
	}
	deleteIn(temp);
}

template<typename TL>
void List<TL>::deleteIn(Node<TL>* node) {
	Node<TL>* temp = node;
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	delete[] temp;
	--size;
}

template<typename TL>
void List<TL>::deleteBack() {
	Node<TL>* temp = _tail->prev;
	temp->prev->next = _tail;
	_tail->prev = temp->prev;
	delete temp;
	--size;
}

template<typename TL>
void List<TL>::deleteBefore(iterator iter) {
	Node<TL>* temp = iter.link;
	deleteIn(temp->prev);
}

template<typename TL>
void List<TL>::deleteKey(TL key) {
	Node<TL> *temp = search(key).link;
	deleteIn(temp);
}

template<typename TL>
void List<TL>::deleteDiaposon(iterator first, iterator second) {
	assert(first.isSibling(second));
	Node<TL>* firstNode, * secondNode;
	if (first < second) {
		firstNode = first.link;
		secondNode = second.link;
	}
	else {
		secondNode = first.link;
		firstNode = second.link;
	}
	while (firstNode != secondNode) {
		firstNode = firstNode->next;
		deleteIn(firstNode->prev);
	}
}

template<typename TL>
Node<TL>* List<TL>::min() {
	Node<TL> min = _head->next;
	for (int i = 1; i < size; i++) {
		if (min.body > (*this)[i].body)
			min = this;
	}
	return min;
}

template<typename TL>
Node<TL>* List<TL>::max() {
	Node<TL> max = _head->next;
	for (int i = 1; i < size; i++) {
		if (max.body < (*this)[i].body)
			max = this;
	}
	return max;
}

template<typename TL>
bool List<TL>::isEmpty() {
	return (size == 0) ? true : false;
}

template<typename TL>
void List<TL>::clear() {
	while (size > 0)
		deleteBack();
}

	

template<typename TL>
void List<TL>::operator=(const List<TL>& other) {
	if (size != other.size) {
		clear();
	}
	for (int i = 0; i < other.size; i++) {
		pushBack(other[i].body);
	}
}

template<typename TL>
bool List<TL>::operator==(const List<TL>& other) {
	if (size != other.size)
		return false;
	for (int i = 0; i < size; i++) {
		if ((*this)[i].body != other[i].body)
			return false;
	}
	return true;
}

template<typename TL>
bool List<TL>::operator!=(const List<TL>& other) {
	return(!((*this) == other));
}

template<typename TL>
void List<TL>::operator+=(const List<TL>& other) {
	for (int i = 0; i < other.size; i++) {
		pushBack(other[i]);
	}
}

template<typename TL>
List<TL> List<TL>::operator+(const List<TL>& other) {
	List<TL> temp(*this);
	temp += other;
	return temp;
}

template<typename TL>
TL& List<TL>::operator[](int index) {
	Node<TL>* temp = _head->next;
	for (int i = 0; i < index; i++) {
		temp = temp->next;
	}
	return temp->body;
}

template<typename TL>
const TL List<TL>::operator[](int index) const{
	const Node<TL>* temp = _head->next;
	for (int i = 0; i < index; i++) {
		temp = temp->next;
	}
	return temp->body;
}

template<typename TL>
std::ostream& operator<<(std::ostream& os, const List<TL>& that) {
	for (int i = 0; i < that.getSize(); i++) {
		os << that[i] << ' ';
	}
	return os;
}

template<typename TL>
std::istream& operator>>(std::istream& is, List<TL>& that) {
	for (int i = 0; i < that.getSize(); i++) {
		is >> that[i];
	}
	return is;
}

template<typename TL>
void List<TL>::sort(List<TL>& array, int leftBorder, int rightBorder, int level) {

	if ((rightBorder < leftBorder && level != 31) || level < 0)
		return;

	if (rightBorder == -1)
		rightBorder = array.size - 1;

	int i = leftBorder, j = rightBorder;
	if (level == 31) { // По первому разряду разделяем положительные и отрицательные, их будем проверять отдельно
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
		std::cout << std::endl;
	}
	else { // Обычный процесс сортировки по разряду 

		while (i <= j) {
			while (i <= j && ((array[i] >> level) & 1) == 0)
				i++;
			while (i <= j && ((array[j] >> level) & 1) == 1)
				j--;
			if (i < j)
				std::swap(array[i++], array[j--]);
		}

	}

	sort(array, leftBorder, j, level - 1);
	sort(array, i, rightBorder, level - 1);
}