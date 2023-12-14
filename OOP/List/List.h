#pragma once
#include <iostream>
#include <vector>
#include <assert.h>
#include "Array.h"

template<typename TL>
class List {
public:
	template<typename TL>
	class Iterator;

	template<typename TL>
	class Node;

	using iterator = Iterator<TL>;
	using const_iterator = Iterator<const TL>;

public:

	iterator begin();
	iterator end();

	const_iterator begin() const;
	const_iterator end() const;

public:
	List();
	List(int nodesNumber, TL value);
	List(const std::vector<TL>& other);
	List(const Array<TL>& other);
	List(const List<TL>& other);

	~List() {
		clear();

		delete _head;
		delete _tail;
	}

	int getSize() const;

	void swap(List<TL>& other);

	void print() const;
	void set();

	iterator search(const TL& value) const;

	iterator push(const TL& value, int index = 0); // index = 0 after head, other index - before that index
	iterator pushKey(const TL& valueToInsert, const TL& keyToSearch); // inserts before KEY
	iterator pushBack(const TL& value); // before tail
	iterator push(const TL& value, iterator iter);

	void deleteBefore(int index = 0);
	void deleteIn(iterator node);
	void deleteBack();
	void deleteKey(const TL key);
	void deleteBefore(iterator iter);
	void deleteDiaposon(iterator first, iterator second);

	iterator min() const;
	iterator max() const;

	bool isEmpty() const;

	void clear();

	void sort();

	void operator=(const List<TL>& other);
	bool operator==(const List<TL>& other) const;
	bool operator!=(const List<TL>& other) const;
	void operator+=(const List<TL>& other);
	List<TL> operator+(const List<TL>& other);
	TL& operator[](int index);
	const TL operator[](int index) const;

private:

	iterator push(const TL& value, Node<TL>* adress);
	void construct();

	Node<TL>* _head;
	Node<TL>* _tail;
	int size;
};


template<typename TI>
template<typename TL>
class List<TL>::Iterator {

public:
	Iterator(const Node<TI>* node) {
		this->link = node;
	}
	Iterator(const Iterator& other) {
		this->link = node;
	}

	bool operator==(const Iterator& other);
	bool operator!=(const Iterator& other);

	bool isSibling(const Iterator& other);

	Iterator& operator++();
	Iterator operator++(int);
	Iterator& operator--();
	Iterator operator--(int);
	bool operator>(const Iterator& other);
	bool operator<(const Iterator& other);

	const TI& operator*() const;
	TI& operator*();

private:
	Node<TI>* link = nullptr;
};

template <typename TL>
class Node {
	friend class List<TL>;
	friend class Iterator<TL>;
	friend class Iterator<const TL>;
public:
	Node();
	Node(const TL value);
	Node(const Node<TL> &other);
	
	TL& get();

	const TL& get() const;

	operator TL() const{
		return body;
	}

	void swap(Node& other);

	bool operator>(const Node<TL>& other);
	bool operator<(const Node<TL>& other);

	bool operator>=(const Node<TL>& other);
	bool operator<=(const Node<TL>& other);

private:
	TL body;
	Node<TL>* next;
	Node<TL>* prev;
};

template<typename TL>
void Node<TL>::swap(Node& other) {
	std::swap(body, other.body);
	std::swap(next, other.next);
	std::swap(prev, other.prev);
}

template<typename TL>
TL& Node<TL>::get() {
	return body;
}

template<typename TL>
const TL& Node<TL>::get() const{
	return body;
}

template<typename TL>
std::ostream& operator<<(std::ostream& os, const Node<TL>& that) {
	os << that.body;
}

template<typename TL>
std::istream& operator>>(std::istream& is, Node<TL>& that) {
	is >> that.body;
}

template<typename TL>
Node<TL>::Node() {
	body;
	next = nullptr;
	prev = nullptr;
}

template<typename TL>
Node<TL>::Node(TL value) {
	next = prev = nullptr;
	body = value;
}

template<typename TL>
Node<TL>::Node(const Node<TL> &other) {
	next = other.next;
	prev = other.prev;
	body = other.body;
}

template<typename TL>
bool Node<TL>::operator>(const Node<TL>& other) {
	if (body > other.body)
		return true;
	return false;
}

template<typename TL>
bool Node<TL>::operator<(const Node<TL>& other) {
	if (body < other.body)
		return true;
	return false;
}

template<typename TL>
bool Node<TL>::operator>=(const Node<TL>& other) {
	if (body >= other.body)
		return true;
	return false;
}

template<typename TL>
bool Node<TL>::operator<=(const Node<TL>& other) {
	if (body <= other.body)
		return true;
	return false;
}

template<typename TI>
Iterator<TI>::Iterator(const Iterator& other) {
	link = other.link;
}

template<typename TI>
bool Iterator<TI>::operator==(const Iterator& other) {
	return link == other.link;
}

template<typename TI>
bool Iterator<TI>::operator!=(const Iterator& other) {
	return (link != other.link);
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
	this->link = this->link->next;
	return *this;
}

template<typename TI>
Iterator<TI>& Iterator<TI>::operator--() {
	this->link = this->link->prev;
	return *this;
}

template<typename TI>
Iterator<TI> Iterator<TI>::operator++(int) {
	Iterator temp(*this);
	this->link = this->link->next;
	return temp;
}

template<typename TI>
Iterator<TI> Iterator<TI>::operator--(int) {
	Iterator temp(*this);
	this->link = this->link->prev;
	return temp;
}

template<typename TI>
TI& Iterator<TI>::operator*() {
	return link->get();
}

template<typename TI>
const TI& Iterator<TI>::operator*() const {
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

template<typename TL> typename
List<TL>::iterator List<TL>::begin() {
	iterator temp(_head->next);
	return temp;
}

template<typename TL> typename
List<TL>::iterator List<TL>::end() {
	return iterator(_tail);
}

template<typename TL> typename
Iterator<const TL> List<TL>::begin() const {
	Iterator<const TL> temp = (_head->next);
	return temp;
}

template<typename TL> typename
List<TL>::const_iterator List<TL>::end() const{
	return const_iterator(_tail);
}

template<typename TL> 
void List<TL>::construct() {
	if (_head != nullptr || _tail != nullptr) {
		clear();
		delete _head;
		delete _tail;
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

	for (int i = 0; i < other.size(); i++) {
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
	Iterator<TL> runner = other._head->next;
	while (runner != other._tail) {
		(*this).pushBack(*(runner++));
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
void List<TL>::print() const{
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
Iterator<TL> List<TL>::search(const TL& value) const{
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
Iterator<TL> List<TL>::push(const TL& value, int index) {
	assert(index >= 0 && index < size);
	Node<TL>* temp = _head->next; // 0`th element
	for (int i = 0; i < index; i++) {
		temp = temp->next; // index element
	}
	temp = push(value, temp);
	return temp;
}

template<typename TL>
Iterator<TL> List<TL>::push(const TL& value, Node<TL>* adress) {
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
Iterator<TL> List<TL>::pushKey(const TL& valueToInsert, const TL& keyToSearch) {
	Node<TL>* temp = search(keyToSearch);
	temp = push(valueToInsert, temp);
	return temp;
}


template<typename TL>
Iterator<TL> List<TL>::pushBack(const TL& value) {
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
Iterator<TL> List<TL>::push(const TL& value, iterator iter) {
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
void List<TL>::deleteIn(List<TL>::iterator node) {
	assert(node.isSibling(_head->next));
	Node<TL>* temp = node->link;
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
	assert(iter.isSibling(_head->next));
	Node<TL>* temp = iter.link;
	deleteIn(temp->prev);
}

template<typename TL>
void List<TL>::deleteKey(const TL key) {
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
Iterator<TL> List<TL>::min() const{
	Node<TL> min = _head->next;
	for (int i = 1; i < size; i++) {
		if (min.body > (*this)[i].body)
			min = this;
	}
	return min;
}

template<typename TL>
Iterator<TL> List<TL>::max() const{
	Node<TL> max = _head->next;
	for (int i = 1; i < size; i++) {
		if (max.body < (*this)[i].body)
			max = this;
	}
	return max;
}

template<typename TL>
bool List<TL>::isEmpty() const{
	return (size == 0) ? true : false;
}

template<typename TL>
void List<TL>::clear() {
	while (size > 0)
		deleteBack();
}

	

template<typename TL>
void List<TL>::operator=(const List<TL>& other) {
	if (this == &other) {
		return;
	}
	clear();
	for (int i = 0; i < other.size; i++) {
		pushBack(other[i]);
	}
}

template<typename TL>
bool List<TL>::operator==(const List<TL>& other) const{
	if (size != other.size)
		return false;
	for (int i = 0; i < size; i++) {
		if ((*this)[i] != other[i])
			return false;
	}
	return true;
}

template<typename TL>
bool List<TL>::operator!=(const List<TL>& other) const{
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
	assert(index >= 0 && index < size);
	Node<TL>* temp = _head->next;
	for (int i = 0; i < index; i++) {
		temp = temp->next;
	}
	return temp->body;
}

template<typename TL>
const TL List<TL>::operator[](int index) const{
	assert(index >= 0 && index < size);
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
void List<TL>::sort() {
	int count = getSize();
	int left = 0, right = count - 1; // лева€ и права€ границы сортируемой области массива
	int flag = 1;  // флаг наличи€ перемещений
	// ¬ыполнение цикла пока лева€ граница не сомкнЄтс€ с правой
	// и пока в массиве имеютс€ перемещени€
	while ((left < right) && flag > 0)
	{
		flag = 0;
		for (int i = left; i < right; i++)  //двигаемс€ слева направо
		{
			if ((*this)[i] > (*this)[i + 1]) // если следующий элемент меньше текущего,
			{             // мен€ем их местами
				TL t = (*this)[i];
				(*this)[i] = (*this)[i + 1];
				(*this)[i + 1] = t;
				flag = 1;      // перемещени€ в этом цикле были
			}
		}
		right--; // сдвигаем правую границу на предыдущий элемент
		for (int i = right; i > left; i--)  //двигаемс€ справа налево
		{
			if ((*this)[i - 1] > (*this)[i]) // если предыдущий элемент больше текущего,
			{            // мен€ем их местами
				TL t = (*this)[i];
				(*this)[i] = (*this)[i - 1];
				(*this)[i - 1] = t;
				flag = 1;    // перемещени€ в этом цикле были
			}
		}
		left++; // сдвигаем левую границу на следующий элемент
	}
}