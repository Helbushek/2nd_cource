#pragma once
#include <iostream>
#include <vector>
#include <assert.h>
#include "Array.h"

template<typename TL>
class List {
public:
	template<typename IT>
	class Iterator;

	class Node;
	class _iterator;

	using iterator = Iterator<TL>;
	using Constiterator = Iterator<const TL>;

public:

	iterator begin();
	iterator end();

	Constiterator begin() const;
	Constiterator end() const;

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

	iterator push(const TL& value, Node* adress);
	void construct();

	Node* _head;
	Node* _tail;
	int size;
};




template<typename TL>
template<typename TI>
class List<TL>::Iterator {
	friend class List<TL>;
public:
	Iterator() {
		link = nullptr;
	}
	Iterator(Node* node) {
		this->link = node;
	}
	Iterator(const Iterator& other) {
		this->link = other.link;
	}

	bool operator==(const Iterator& other) const;
	bool operator!=(const Iterator& other) const;

	bool isSibling(const Iterator& other);

	Iterator<TI>& operator++();
	Iterator operator++(int);
	Iterator& operator--();
	Iterator operator--(int);
	bool operator>(const Iterator& other);
	bool operator<(const Iterator& other);

	const TL& operator*() const;
	TL& operator*();

	Node* getNode() {
		return link;
	}

protected:

	Node* link;
};

template<typename TL>
class List<TL>::_iterator : public Iterator<TL>
{
public:
	_iterator() {
		this->link = nullptr;
	}
	_iterator(const Iterator<TL>& other) {
		this->link = other.link;
	}

	void move(_iterator& to);
};

template<typename TL> 
void List<TL>::_iterator::move(_iterator& to) {
	this->link->prev->next = this->link->next;
	this->link->next->prev = this->link->next;

	to.link->prev->next = this->link;
	to.link->prev = this->link;

	this->link->next = to.link;
	this->link->prev = to.link->prev;
}

template <typename TL>
class List<TL>::Node {
	friend class List<TL>;
	friend class List<TL>::iterator;
public:
	Node();
	Node(const TL value);
	Node(const Node &other);
	
	TL& get();

	const TL& get() const;

	operator TL() const{
		return body;
	}

	void swap(Node& other);

	bool operator>(const Node& other);
	bool operator<(const Node& other);

	bool operator>=(const Node& other);
	bool operator<=(const Node& other);

private:
	TL body;
	Node* next;
	Node* prev;
	std::vector<iterator> connections;
};

template<typename TL>
void List<TL>::Node::swap(List<TL>::Node& other) {
	std::swap(body, other.body);
	std::swap(next, other.next);
	std::swap(prev, other.prev);
}

template<typename TL>
TL& List<TL>::Node::get() {
	return body;
}

template<typename TL>
const TL& List<TL>::Node::get() const{
	return body;
}

template<typename TL>
std::ostream& operator<<(std::ostream& os, const typename List<TL>::Node& that) {
	os << that.body;
}

template<typename TL>
std::istream& operator>>(std::istream& is, typename List<TL>::Node& that) {
	is >> that.body;
}

template<typename TL>
List<TL>::Node::Node() {
	body;
	next = nullptr;
	prev = nullptr;
}

template<typename TL>
List<TL>::Node::Node(TL value) {
	next = prev = nullptr;
	body = value;
}

template<typename TL>
List<TL>::Node::Node(const List<TL>::Node&other) {
	next = other.next;
	prev = other.prev;
	body = other.body;
}

template<typename TL>
bool List<TL>::Node::operator>(const List<TL>::Node& other) {
	if (body > other.body)
		return true;
	return false;
}

template<typename TL>
bool List<TL>::Node::operator<(const List<TL>::Node& other) {
	if (body < other.body)
		return true;
	return false;
}

template<typename TL>
bool List<TL>::Node::operator>=(const List<TL>::Node& other) {
	if (body >= other.body)
		return true;
	return false;
}

template<typename TL>
bool List<TL>::Node::operator<=(const List<TL>::Node& other) {
	if (body <= other.body)
		return true;
	return false;
}

template<typename TL>
template<typename TI>
bool List<TL>::Iterator<TI>::operator==(const List<TL>::Iterator<TI>& other) const{
	return link == other.link;
}

template<typename TL>
template<typename TI>
bool List<TL>::Iterator<TI>::operator!=(const Iterator<TI>& other) const{
	return (link != other.link);
}

template<typename TL>
template<typename TI>
bool List<TL>::Iterator<TI>::isSibling(const Iterator& other) {
	typename List<TL>::Node* temp = link;
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

template<typename TL> 
template<typename TI> typename
List<TL>::Iterator<TI>& List<TL>::Iterator<TI>::operator++() {
	this->link = this->link->next;
	return *this;
}


template<typename TL> 
template<typename TI> typename 
List<TL>::Iterator<TI>& List<TL>::Iterator<TI>::operator--() {
	this->link = this->link->prev;
	return *this;
}

template<typename TL> 
template<typename TI> typename
List<TL>::Iterator<TI> List<TL>::Iterator<TI>::operator++(int) {
	Iterator temp(*this);
	this->link = this->link->next;
	return temp;
}

template<typename TL> 
template<typename TI> typename
List<TL>::Iterator<TI> List<TL>::Iterator<TI>::operator--(int) {
	Iterator temp(*this);
	this->link = this->link->prev;
	return temp;
}

template<typename TL>
template<typename TI>
TL& List<TL>::Iterator<TI>::operator*() {
	return link->get();
}

template<typename TL>
template<typename TI>
const TL& List<TL>::Iterator<TI>::operator*() const {
	return link->get();
}

template<typename TL>
template<typename TI>
bool List<TL>::Iterator<TI>::operator>(const List<TL>::Iterator<TI>& other) {
	assert(isSibling(other));
	Iterator temp = *this;
	while (temp.link != nullptr) {
		if (temp.link == other.link)
			return false; // other is righter from or on this
		temp.link = temp.link->next;
	}
	return true; // other is lefter 
}

template<typename TL>
template<typename TI>
bool List<TL>::Iterator<TI>::operator<(const List<TL>::Iterator<TI>& other) {
	return (!((*this) > other));
}

template<typename TL> 
List<TL>::Iterator<TL> List<TL>::begin(void) {
	Iterator<TL> temp(_head->next);
	return temp;
}

template<typename TL> typename
List<TL>::Iterator<TL> List<TL>::end() {
	return Iterator<TL>(_tail);
}

template<typename TL> typename
List<TL>::Iterator<const TL> List<TL>::begin() const {
	List<TL>::Iterator<const TL> temp = (_head->next);
	return temp;
}

template<typename TL> typename
List<TL>::Iterator<const TL> List<TL>::end() const{
	return List<TL>::Iterator<const TL>(_tail);
}

template<typename TL> 
void List<TL>::construct() {
	if (_head != nullptr || _tail != nullptr) {
		clear();
		if (_head != nullptr)
		delete _head;
		if (_tail != nullptr)
		delete _tail;
	}
	size = 0;
	_head = new Node();
	_tail = new Node();
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
	iterator runner = other._head->next;
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
	Node* runner = _head->next;
	while(runner!=_tail) {
		std::cout << runner->body << ' ';
		runner = runner->next;
	}
}

template<typename TL> 
void List<TL>::set() {
	Node*runner = _head->next;
	while (runner!=_tail){
		std::cin >> runner->body;
		runner = runner->next;
	}
}

template<typename TL> typename
List<TL>::iterator List<TL>::search(const TL& value) const{
	Node* runner = _head->next;
	while (runner != _tail) {
		if (runner->body == value) {
			iterator temp(runner);
			return temp;
		}
		runner = runner->next;
	}
	return nullptr;
}

template<typename TL> typename
List<TL>::iterator List<TL>::push(const TL& value, int index) {
	assert(index >= 0 && index < size);
	iterator temp = _head->next; // 0`th element
	for (int i = 0; i < index; i++) {
		++temp; // index element
	}
	temp = push(value, temp);
	return temp;
}

template<typename TL> typename
List<TL>::iterator List<TL>::push(const TL& value, Node* adress) {
	Node* temp = new Node();
	temp->body = value;
	temp->next = adress;
	temp->prev = adress->prev;
	temp->next->prev = temp;
	temp->prev->next = temp;
	size++;
	return temp;
}

template<typename TL> typename
List<TL>::iterator List<TL>::pushKey(const TL& valueToInsert, const TL& keyToSearch) {
	iterator temp = search(keyToSearch);
	temp = push(valueToInsert, temp);
	return temp;
}


template<typename TL> typename
List<TL>::iterator List<TL>::pushBack(const TL& value) {
	Node* temp = new Node();
	temp->body = value;
	temp->next = _tail;
	temp->prev = _tail->prev;

	_tail->prev->next = temp;
	_tail->prev = temp;
	size++;
	return temp;
}

template<typename TL> typename
List<TL>::iterator List<TL>::push(const TL& value, iterator iter) {
	assert(iter.isSibling(_head->next));
	push(value, iter);
}

template<typename TL>
void List<TL>::deleteBefore(int index) {
	assert(index > 0 && index < size);
	iterator temp = _head->next;
	for (int i = 0; i < index - 1; i++) {
		++temp;
	}
	deleteIn(temp);
}

template<typename TL>
void List<TL>::deleteIn(List<TL>::iterator node) {
	assert(node.isSibling(_head->next));	
	Node* temp = node.link;
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	delete[] temp;
	--size;
}

template<typename TL>
void List<TL>::deleteBack() {
	Node* temp = _tail->prev;
	temp->prev->next = _tail;
	_tail->prev = temp->prev;
	delete temp;
	--size;
}

template<typename TL>
void List<TL>::deleteBefore(iterator iter) {
	assert(iter.isSibling(_head->next));
	Node* temp = iter.link;
	deleteIn(temp->prev);
}

template<typename TL>
void List<TL>::deleteKey(const TL key) {
	Node *temp = search(key).link;
	deleteIn(temp);
}

template<typename TL>
void List<TL>::deleteDiaposon(iterator first, iterator second) {
	assert(first.isSibling(second));
	Node* firstNode, * secondNode;
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

template<typename TL> typename
List<TL>::iterator List<TL>::min() const{
	iterator runner, min;
	runner = min = _head->next;
	while (runner!=nullptr) {
		if (*min > *runner++)
			min = runner;
	}
	return min;
}

template<typename TL> typename
List<TL>::iterator List<TL>::max() const{
	iterator runner, max;
	runner = max = _head->next;
	while (runner!=nullptr) {
		if (*max > *runner++)
			max = runner;
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
	Node* temp = _head->next;
	for (int i = 0; i < index; i++) {
		temp = temp->next;
	}
	return temp->body;
}

template<typename TL>
const TL List<TL>::operator[](int index) const{
	assert(index >= 0 && index < size);
	const Node* temp = _head->next;
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