#pragma once
#include <iostream>
#include <assert.h>
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
	
	/*Node<T> getNext();
	Node<T> getPrev();

	Node<T> setNext();
	Node<T> setPrev();*/

private:
	T body;
	Node<T>* next;
	Node<T>* prev;
};

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

//template<typename T>
//Node<T> Node<T>::getNext(){
//
//}
//template<typename T>
//Node<T> getPrev();
//template<typename T>
//Node<T> setNext();
//template<typename T>	
//Node<T> setPrev();

// ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |

template<typename TL>
class List {
public:
	List();

	List(int nodesNumber, TL value);

	List(const List<TL> &other);

	~List() {
		clear();

		delete[] fictiveHead;
		delete[] fictiveTail;

	}

	int getSize();

	void swap(List<TL>& other);

	void print();
	void set();

	Node<TL>* search(TL value);

	Node<TL>* push(TL value, int index = 0); // index = 0 after head, other index - before that index
	Node<TL>* pushKey(TL valueToInsert, TL keyToSearch); // inserts before KEY
	Node<TL>* pushBack(TL value); // before tail

	void deleteBefore(int index = 0);
	void deleteBack();
	void deleteKey(TL key);

	Node<TL>* min();
	Node<TL>* max();

	bool isEmpry();

	int clear();

	int sort();

	void operator=(const List<TL>& other);

	Node<TL>* opeartor[](int index);

	bool operator==(const List<TL>& other);
	bool operator!=(const List<TL>& other);

	void operator+=(const List<TL>& other);
	List<TL> operator+(const List<TL>& other);

private:
	Node<TL>* fictiveHead;
	Node<TL>* fictiveTail;
	int size;
};

// ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |

template<typename TL>
List<TL>::List() {
	size = 0;
	fictiveHead = new Node<TL> ();
	fictiveTail = new Node<TL> ();
	fictiveHead->next = fictiveTail; // Вопрос: стоит ли связывать голову и хвост между собой, если мы всегда в списке храним их адрес? 
	fictiveTail->prev = fictiveHead; // Скорее всего да, для методов push и pushBack необходима связь, но можно ли без неё
}

template<typename TL>
List<TL>::List(int nodesNumber, TL value) {

	fictiveHead = new Node<TL> ();
	fictiveTail = new Node<TL> ();
	fictiveHead->next = fictiveTail;
	fictiveTail->prev = fictiveHead;

	size = nodesNumber;
	for (int i = 0; i < nodesNumber; i++) {
		pushBack(value);
	}
}

template<typename TL>
List<TL>::List(const List<TL> &other) {
	size = other.size;
	(*this) = List(size, 0);
	for (int i = 0; i < size; i++) {

	}
}


template<typename TL>
int List<TL>::getSize() {
	return size;
}

template<typename TL>
Node<TL>* List<TL>::push(TL value, int index) {
	assert(index >= 0 && index < size);
	Node<TL>* temp = new Node<TL>();
	temp->body = value;
	temp = fictiveHead->next; // 0`th element
	for (int i = 0; i < index; i++) { 
		temp = temp->next; // index element
	}

	temp->next->prev = temp;
	temp->prev->next = temp;
	size++;
	return temp;
}

template<typename TL>
Node<TL>* List<TL>::pushBack(TL value) {
	Node<TL>* temp = new Node<TL> ();
	temp->body = value;
	temp->next = fictiveTail;
	temp->prev = fictiveTail->prev;

	fictiveTail->prev->next = temp; 
	fictiveTail->prev = temp;

	return temp; 
}

template<typename TL>
void List<TL>::print() {
	Node<TL>* runner = fictiveHead->next;
	for (int i = 0; i < size; i++) {
		std::cout << runner->body << ' ';
		runner = runner->next;
	}
}

template<typename TL> 
void List<TL>::set() {
	Node<TL> *runner = fictiveHead->next;
	for (int i = 0; i < size; i++) {
		std::cin >> runner->body;
		runner = runner->next;
	}
}