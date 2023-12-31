#include <assert.h>
#include <stdio.h>
#include "Set.h"
const int ASCII_MAX = 256;
const int ASCII_MAX_PRINTABLE = 32;

void Set::construct() {
	if (vector != nullptr)
		delete vector;
	vector = new unsigned char[ASCII_MAX/CELL_SIZE];
	size = ASCII_MAX;
	setAll(false);
}

Set::Set()
	: BoolVector(ASCII_MAX, false)
{}
Set::Set(const char* array)
	: Set()
{
	int arrSize = static_cast<int>(strlen(array));
	for (int i = 0; i < arrSize; ++i) {
		(*this)[static_cast<int>(array[i])] = true;
	}
}

Set::Set(const Set& other) {
	construct();
	for (int i = 0; i < ASCII_MAX/CELL_SIZE ; ++i) {
		vector[i] = other.vector[i];
	}
}

Set::~Set() {}

bool Set::find(const char symbol) const {
	return (*this)[static_cast<int>(symbol)];
}

char Set::max() const {
	for (int i = ASCII_MAX-1; i >= 0; --i) {
		if ((*this)[i])
			return (*this)[i];
	}
	return char();
}
char Set::min() const {
	for (int i = 0; i <ASCII_MAX; ++i) {
		if ((*this)[i])
			return (*this)[i];
	}
	return char();
}

void Set::print(int index) {
	assert(index >= 0 && index <= ASCII_MAX);
	if (index >= 0 && index <= ASCII_MAX_PRINTABLE) {
		std::cout << "spec." << index;
	}
	else if (index > ASCII_MAX_PRINTABLE && index <= ASCII_MAX) {
		std::cout << static_cast<char>(index);
	}
}

int Set::power() const {
	int count = 0;
	for (int i = 0; i < ASCII_MAX; ++i) {
		count += (*this)[i];
	}
	return count;
}

Set& Set::operator=(const Set& other) {
	delete vector;
	vector = new unsigned char[other.cellNumber()];
	for (int i = 0; i < ASCII_MAX/CELL_SIZE; i++) {
		vector[i] = other.vector[i];
	}
	return *this;
}

bool Set::operator==(const Set& other) {
	return ((*this) & (~other)).power() == 0;
}
bool Set::operator!=(const Set& other) {
	return !((*this) == other);
}

Set& Set::operator|=(const Set& other) {
	(*this) = (*this) | other;
	return *this;
}
Set Set::operator|(const Set& other) const {
	Set temp = (*this);
	for (int i = 0; i < ASCII_MAX/CELL_SIZE; ++i) {
		temp.vector[i] |= other.vector[i];
	}
	return temp;
}

Set& Set::operator&=(const Set& other) {
	(*this) = (*this) & other;
	return *this;
}
Set Set::operator&(const Set& other) const {
	Set temp = (*this);
	
	for (int i = 0; i < ASCII_MAX/CELL_SIZE; ++i) {
		temp.vector[i] &= other.vector[i];
	}
	return temp;
}

Set& Set::operator/=(const Set& other) {
	(*this) = ((*this) / other);
	return *this;
}
Set Set::operator/(const Set& other) const {
	return ((*this) & (~other));
}

Set Set::operator~() const{
	Set temp = *this;
	for (int i = 0; i < ASCII_MAX/CELL_SIZE; ++i) {
		temp.vector[i] = ~temp.vector[i];
	}
	return temp;
}

Set& Set::operator+=(const char el) {
	(*this) = (*this) + el;
	return *this;
}
Set Set::operator+(const char element) const {
	
	Set temp(*this);
	temp[static_cast<int>(element)] = true;
	return temp;
}

Set& Set::operator-=(const char el) {
	(*this) = (*this) - el;
	return *this;
}
Set Set::operator-(const char element) const {
	Set temp(*this);
	temp[static_cast<int>(element)] = false;
	return temp;
}

std::ostream& operator<<(std::ostream& os, Set& that) {
	for (int i=0; i<=ASCII_MAX_PRINTABLE; ++i) {
		if (that[i])
		os << "spec." << i << ' ';
	}
	for (int i=ASCII_MAX_PRINTABLE+1; i<ASCII_MAX; ++i) {
		if (that[i])
		os << static_cast<char>(i) << ' ';
	}
	return os;
}

int pow(int first, int second) {
	int result = 1;
	for (int i = 0; i < second; ++i) {
		result *= first;
	}
	return result;
}

int SpecCharToInt(const char* number) {
	int final = 0;
	for (int i = strlen(number) - 1; static_cast<int>(number[i]) >= 48 && static_cast<int>(number[i]) <= 57; --i) {
		final += (static_cast<int>(number[i]) - 48) * pow(10, strlen(number) - 1 - i);
	}
	return final;
}

std::istream& operator>>(std::istream& is, Set &that) {
	char* temp = new char[ASCII_MAX*3]; 
	is.getline(temp, ASCII_MAX*3);
	for (int i = 0; i < strlen(temp); ++i) {
		char unit[5] = {};
		int j = 0;
		while (temp[i] != ' ' && i<strlen(temp) && j<5) {
			unit[j++] += temp[i++];
		}
		if (j >= 5) {
			std::cerr << "TOO LONG FOR SYSTEM SYMBOL, WILL CLEAR DATA";
			that = Set();
			return is;
		}
		if (unit[0] == 's' && unit[1] == 'p') {
			that[SpecCharToInt(unit)] = true;
		}
		else {
			j = strlen(unit) - 1;
			while (j >= 0)
				that[static_cast<int>(unit[j--])] = true;
		}
	}
	return is;
}
