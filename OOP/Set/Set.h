#pragma once
#include <iostream>
#include "BooleanVector.h"

class Set : public BoolVector {
public:
	Set();
	Set(const char*);
	Set(const Set&);
	~Set();

	bool find(const char) const;

	char max() const;
	char min() const;

	int power() const;

	Set& operator=(const Set& other);
	
	bool operator==(const Set& other);
	bool operator!=(const Set& other);
	
	Set& operator|=(const Set& other);
	Set operator|(const Set& other) const;

	Set& operator&=(const Set& other);
	Set operator&(const Set& other) const;

	Set& operator/=(const Set& other);
	Set operator/(const Set& other) const;

	Set operator~() const;

	Set& operator+=(const char);
	Set operator+(const char) const;

	Set& operator-=(const char);
	Set operator-(const char) const;	
private:
	void construct();
};

std::ostream& operator<<(std::ostream& os, Set& that);

std::istream& operator>>(std::istream& is, Set& that);
	