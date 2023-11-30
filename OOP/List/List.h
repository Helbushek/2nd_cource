#pragma once
#include <iostream>
#include <vector>
#include <assert.h>
#include "Array.h"
#include "List.cpp"

template<typename TL>
class List;

// ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |

template <typename T>
class Node {
	friend class List<T>;
public:
	Node();
	Node(T value);
	Node(const Node<T> &other);
	
	T& get();

	operator T() const {
		return body;
	}

private:
	T body;
	Node<T>* next;
	Node<T>* prev;
};

// ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |



template<typename T>
T& Node<T>::get() {
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

// ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |

template<typename T>
Node<T>::Node() {
	next = prev = nullptr;
	body = 0;
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

// ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |

template<typename TI>
class Iterator {
	friend class List<TI>
private:
	Iterator(Node<TI>* node);

public: 
	Iterator(const Iterator& other);

	bool operator==(const Iterator& other);
	bool operator!=(const Iterator& other);

	Iterator& operator+= (int value);
	Iterator& operator++();
	Iterator& operator-=(int value);
	Iterator& operator--();

private:
	Node<TI>* link;
};

// ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |

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
Iterator<TI>& Iterator<TI>::operator++() {
	this = this->link->next;
	return this;
}

template<typename TI>
Iterator<TI>& Iterator<TI>::operator--() {
	this = this->link->prev;
	return this;
}

// ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |


template<typename TL>
class List {
public:
	typedef Iterator<TL> iterator;
	typedef Iterator<const TL> const_iterator;

	iterator begin();
	iterator end();

	const_iterator begin() const;
	const_iterator end() const;

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

	int getSize();

	void swap(List<TL>& other);

	void print();
	void set();

	Node<TL>* search(TL value);

	Node<TL>* push(TL value, int index = 0); // index = 0 after head, other index - before that index
	Node<TL>* push(TL value, Node<TL> * adress);
	Node<TL>* pushKey(TL valueToInsert, TL keyToSearch); // inserts before KEY
	Node<TL>* pushBack(TL value); // before tail

	void deleteBefore(int index = 0);
	void deleteBack();
	void deleteKey(TL key);

	Node<TL>* min();
	Node<TL>* max();

	bool isEmpty();

	int clear();

	void sort();

	void operator=(const List<TL>& other);
	bool operator==(const List<TL>& other);
	bool operator!=(const List<TL>& other);
	void operator+=(const List<TL>& other);
	List<TL> operator+(const List<TL>& other);
	Node<TL>* operator[](int index);
	const Node<TL> const* operator[](int index) const;

private:
	void construct();

	Node<TL>* _head;
	Node<TL>* _tail;
	int size;
};

// ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |

template<typename TL>
List<TL>::iterator List<TL>::begin() {
	return Iterator(_head->next);
}

template<typename TL>
List<TL>::iterator List<TL>::end() {
	return Iterator(_tail);
}

template<typename TL>
List<TL>::const_iterator List<TL>::begin() const {
	return const Iterator(_head->next);
}

template<typename TL>
List<TL>::const_iterator List<TL>::end() const {
	return const Iterator(_tail);
}

template<typename TL> 
void List<TL>::construct() {
	if (_head != nullptr || _tail != nullptr) {
		delete(*this);
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

	size = nodesNumber;
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
int List<TL>::getSize() {
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
Node<TL>* List<TL>::search(TL value) {
	Node<TL>* runner = _head->next;
	while (runner != _tail) {
		if (runner->body == value)
			return runner;
	}

	return nullptr;
}

template<typename TL>
Node<TL>* List<TL>::push(TL value, int index) {
	assert(index >= 0 && index < size);
	Node<TL>* temp = _head->next; // 0`th element
	for (int i = 0; i < index; i++) {
		temp = temp->next; // index element
	}
	temp = push(value, temp->next);
	return temp;
}

template<typename TL>
Node<TL>* List<TL>::push(TL value, Node<TL> *adress) {
	assert(index >= 0 && index < size);
	Node<TL>* temp = new Node<TL>();
	temp->body = value;
	temp = adress;
	temp->next->prev = temp;
	temp->prev->next = temp;
	size++;
	return temp;
}

template<typename TL>
Node<TL>* List<TL>::pushKey(TL valueToInsert, TL keyToSearch) {
	Node<TL>* temp = search(keyToSearch);
	temp = push(valueToInsert, temp);
}


template<typename TL>
Node<TL>* List<TL>::pushBack(TL value) {
	Node<TL>* temp = new Node<TL>();
	temp->body = value;
	temp->next = _tail;
	temp->prev = _tail->prev;

	_tail->prev->next = temp;
	_tail->prev = temp;

	return temp;
}

template<typename TL>
void List<TL>::deleteBefore(int index) {\
	assert(index>0 && index<size)
	Node<TL>* temp = [index];
	temp = temp->prev;
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
	delete[] temp;
	--size;
}

template<typename TL>
void List<TL>::deleteKey(TL key) {
	deleteBefore(search(key));
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
int List<TL>::clear() {
	while (size > 0)
		deleteBack();
}

template<typename TL>
int List<TL>::sort() {
	std::sort();
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
		pushBack(other[i].body);
	}
}

template<typename TL>
List<TL> List<TL>::operator+(const List<TL>& other) {
	List<TL> temp(*this);
	temp += other;
	return temp;
}

template<typename TL>
Node<TL>* List<TL>::operator[](int index) {
	Node<TL>* temp = _head->next;
	for (int i = 0; i < index; i++) {
		temp = temp->next;
	}
	return temp;
}

template<typename TL>
const Node<TL> const* List<TL>::operator[](int index) const{
	const Node<TL>* temp = _head->next;
	for (int i = 0; i < index; i++) {
		temp = temp->next;
	}
	return temp;
}

template<typename TL>
void List<TL>::sort() {
	
}

template<typename TL>
std::ostream& operator<<(std::ostream& os, const List<TL>& that) {
	for (int i = 0; i < size; i++) {
		os << that[i] << ' ';
	}
	return os;
}

template<typename TL>
std::istream operator>>(std::istream& is, List<TL>& that) {
	for (int i = 0; i < size; i++) {
		is >> taht[i];
	}
	return is;
}