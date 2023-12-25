#include "Set.h"

void Set::construct() {
	if (vector != nullptr)
		delete vector;
	vector = new unsigned char[32];
	size = 256;
	setAll(false);
}

Set::Set() {
	construct();
}
Set::Set(const char* array) {
	construct();
	int arrSize = strlen(array);
	for (int i = 0; i < arrSize; ++i) {
		(*this)[static_cast<int>(array[i])] = true;
	}
}

Set::Set(const Set& other) {
	construct();
	for (int i = 0; i<32; ++i) {
		vector[i] = other.vector[i];
	}
}

Set::~Set() {}

bool Set::find(const char symbol) const {
	return (*this)[static_cast<int>(symbol)];
}

char Set::max() const {
	for (int i = 255; i >= 0; --i) {
		if ((*this)[i])
			return (*this)[i];
	}
	return char();
}
char Set::min() const {
	for (int i = 0; i <255; ++i) {
		if ((*this)[i])
			return (*this)[i];
	}
	return char();
}

int Set::power() const {
	int count = 0;
	for (int i = 0; i < 256; ++i) {
		count += (*this)[i];
	}
	return count;
}

Set& Set::operator=(const Set& other) {
	delete vector;
	vector = new unsigned char[other.cellNumber()];
	for (int i = 0; i < 32; i++) {
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
	for (int i = 0; i < 32; ++i) {
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
	
	for (int i = 0; i <32; ++i) {
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
	for (int i = 0; i < cellNumber(); ++i) {
		temp.vector[i] = ~temp.vector[i];
	}
	return temp;
}

Set& Set::operator+=(const char) {

}
Set Set::operator+(const char) const {

}

Set& Set::operator-=(const char) {

}
Set Set::operator-(const char) const {

}



std::ostream& operator<<(std::ostream& os, Set& that) {
	for (int i = 0; i < 256; ++i) {
		if (that[i]==true)
			os << static_cast<char>(i) << ' ';
	}
	return os;
}

std::istream& operator>>(std::istream& is, Set& that) {
	std::string temp;
	is >> temp;
	for (int i = 0; i < temp.size(); ++i) {
		that[static_cast<int>(temp[i])] = true;
	}
	return is;
}