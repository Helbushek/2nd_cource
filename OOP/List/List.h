#pragma once
#include <iostream>
#include <vector>
#include <assert.h>
#include "/Users/јлександр/2nd_cource/OOP/Array/Array.h"

template<typename TL>
class List {
public:
	class Node;

	template<typename IteratorTemplate>
	class TEMPLATE_iterator;

	using iterator = TEMPLATE_iterator<TL>;
	using const_iterator = TEMPLATE_iterator<const TL>;

	using _iterator = TEMPLATE_iterator<TL>;
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

	void resize();

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
template <typename IteratorType>
class List<TL>::TEMPLATE_iterator {
	friend class List<TL>;
public:
	TEMPLATE_iterator() {
		link = nullptr;
	}
	TEMPLATE_iterator(Node* node) {
		this->link = node;
	}
	TEMPLATE_iterator(const iterator& other) {
		this->link = other.link;
	}

	bool operator==(const TEMPLATE_iterator& other) const;
	bool operator!=(const TEMPLATE_iterator& other) const;

	bool isSibling(const TEMPLATE_iterator& other);

	TEMPLATE_iterator& operator++();
	TEMPLATE_iterator operator++(int);
	TEMPLATE_iterator& operator--();
	TEMPLATE_iterator operator--(int);
	bool operator>(const TEMPLATE_iterator& other);
	bool operator<(const TEMPLATE_iterator& other);

	TL& operator*() const;

	void move(TEMPLATE_iterator& to);

protected:
	Node* getNode() {
		return link;
	}

	Node* link;
};

template<typename TL>
template<typename IT>
void List<TL>::TEMPLATE_iterator<IT>::move(TEMPLATE_iterator<IT>& to) {
	this->link->prev->next = this->link->next;
	this->link->next->prev = this->link->prev;

	this->link->next = to.link;
	this->link->prev = to.link->prev;

	to.link->prev->next = this->link;
	to.link->prev = this->link;
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
	body = TL();
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
template<typename IT>
bool List<TL>::TEMPLATE_iterator<IT>::operator==(const List<TL>::TEMPLATE_iterator<IT>& other) const{
	return link == other.link;
}

template<typename TL>
template<typename IT>
bool List<TL>::TEMPLATE_iterator<IT>::operator!=(const TEMPLATE_iterator<IT>& other) const{
	return (link != other.link);
}

template<typename TL>
template<typename IT>
bool List<TL>::TEMPLATE_iterator<IT>::isSibling(const TEMPLATE_iterator<IT>& other) {
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
template<typename IT> typename
List<TL>::TEMPLATE_iterator<IT>& List<TL>::TEMPLATE_iterator<IT>::operator++() {
	this->link = this->link->next;
	return *this;
}


template<typename TL>  
template<typename IT> typename
List<TL>::TEMPLATE_iterator<IT>& List<TL>::TEMPLATE_iterator<IT>::operator--() {
	this->link = this->link->prev;
	return *this;
}

template<typename TL>  
template<typename IT> typename
List<TL>::TEMPLATE_iterator<IT> List<TL>::TEMPLATE_iterator<IT>::operator++(int) {
	TEMPLATE_iterator temp(*this);
	this->link = this->link->next;
	return temp;
}

template<typename TL>  
template<typename IT> typename
List<TL>::TEMPLATE_iterator<IT> List<TL>::TEMPLATE_iterator<IT>::operator--(int) {
	TEMPLATE_iterator temp(*this);
	this->link = this->link->prev;
	return temp;
}

template <typename TL>
template <typename IT>
TL& List<TL>::TEMPLATE_iterator<IT>::operator*() const {
	return (link->body);
}

template<typename TL>
template<typename IT>
bool List<TL>::TEMPLATE_iterator<IT>::operator>(const List<TL>::TEMPLATE_iterator<IT>& other) {
	assert(isSibling(other));
	TEMPLATE_iterator temp = *this;
	while (temp.link != nullptr) {
		if (temp.link == other.link)
			return false; // other is righter from or on this
		temp.link = temp.link->next;
	}
	return true; // other is lefter 
}

template<typename TL>
template<typename IT>
bool List<TL>::TEMPLATE_iterator<IT>::operator<(const List<TL>::TEMPLATE_iterator<IT>& other) {
	return (!((*this) > other));
}

template<typename TL>  typename
List<TL>::iterator List<TL>::begin(void) {
	return iterator(_head->next);
}

template<typename TL> typename
List<TL>::iterator List<TL>::end() {
	return iterator(_tail);
}

template<typename TL> typename
List<TL>::const_iterator List<TL>::begin() const {
	return const_iterator(_head->next);
}

template<typename TL> typename
List<TL>::const_iterator List<TL>::end() const{
	return const_iterator(_tail);
}

// -=-=-=-=-=-=-

template<typename TL> 
void List<TL>::construct() {
	if (_head!= nullptr && _tail!=nullptr)
		clear();
	size = 0;
	_head = new Node();
	_tail = new Node();
	_head->next = _tail;
	_tail->prev = _head;
}

template<typename TL>
List<TL>::List() {
	_head = _tail = nullptr;
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
	delete temp;
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
		List<TL>::const_iterator temp = other.begin();
		for (int j = 0; j <= i; ++j, ++temp);
		pushBack(temp.link->body);
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
	List<TL>::const_iterator temp = begin();
	for (int i = 0; i < index && temp != end(); ++i, ++temp);
	return *temp;
}

template<typename TL>
std::ostream& operator<<(std::ostream& os, const List<TL>& that) {
	for (auto iterator = that.begin(); iterator != that.end(); ++iterator ) {
		os << *iterator << ' ';
	}
	return os;
}

template<typename TL>
std::istream& operator>>(std::istream& is, List<TL>& that) {
	for (auto iterator = that.begin(); iterator != that.end(); ++iterator) {
		is >> *iterator;
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

template<typename TL>
void List<TL>::resize() {
	size = 0;
	for (List<TL>::iterator runner = begin(); runner != end(); ++runner, ++size);
}