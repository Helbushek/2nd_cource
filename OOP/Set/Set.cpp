#include "Set.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include <sstream>

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

Set::Set(const char* temp)
	: Set()
{
	int j = static_cast<int>(strlen(temp)) - 1;
	while (j >= 0) {
		(*this)[static_cast<int>(temp[j--])] = true;
	}
}

Set::Set(const Set& other)
	: BoolVector(other)
{}

bool Set::find(const char symbol) const {
	return (*this)[static_cast<int>(symbol)];
}

char Set::max() const {
	for (int i = ASCII_MAX-1; i >= 0; --i) {
		if ((*this)[i])
			return static_cast<char>(i);
	}
	return char();
}
char Set::min() const {
	for (int i = 0; i <ASCII_MAX; ++i) {
		if ((*this)[i])
			return static_cast<char>(i);
	}
	return char();
}

void Set::print(int index) const{
	assert(index >= 0 && index <= ASCII_MAX);
	if (index >= 0 && index <= ASCII_MAX_PRINTABLE) {
		std::cout << "sp" << index;
	}
	else if (index > ASCII_MAX_PRINTABLE && index < ASCII_MAX) {
		std::cout << static_cast<char>(index);
	}
}

Set& Set::operator=(const Set& other) {
	BoolVector::operator=(other);
	return *this;
}

bool Set::operator==(const Set& other) const{
	return ((*this) & (~other)).power() == 0;
}

bool Set::operator!=(const Set& other) const{
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
	for (int i=0; i<=Set::ASCII_MAX_PRINTABLE; ++i) {
		if (that[i])
		os << "sp" << i << ' ';
	}
	for (int i= Set::ASCII_MAX_PRINTABLE+1; i< Set::ASCII_MAX; ++i) {
		if (that[i])
		os << static_cast<char>(i) << ' ';
	}
	return os;
}

std::istream& operator>>(std::istream& is, Set &that) {
	that = Set();
	std::string temp; 
	std::getline(is, temp);
	std::istringstream string_stream(temp);
	std::string unit;
	while (std::getline(string_stream, unit, ' ')) {
		if (unit[0] == 's' && unit[1] == 'p') {
			if (unit.size()>=5) {
				continue;
			}
			that[Set::SpecCharToInt(unit)] = true;
		}
		else {
			int j = unit.size() - 1;
			while (j >= 0)
				that[static_cast<int>(unit[j--])] = true;
		}
	}
	return is;
}

int Set::SpecCharToInt(const std::string& number){
	int final = 0;
	for (int i = static_cast<int>(number.size()) - 1; static_cast<int>(number[i]) >= 48 && static_cast<int>(number[i]) <= 57; --i) {
		final += (static_cast<int>(number[i]) - 48) * pow(10, static_cast<int>(number.size()) - 1 - i);
	}
	return final;
}