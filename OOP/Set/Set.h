#pragma once
#include <iostream>
#include "/Users/Александр/2nd_cource/OOP/Boolean Vector/BooleanVector.h"

// Expluatation rules: 
// 
// For inputing Set with >> operator for inputing printable symbols you can just type them in. "ab" will input 'a' and 'b' in set. 
//																							
// If you want to input unprintable, system, or any other symbol by its code, input "sp" before typing code. sp50 will input 50-th ASCII symbol (character: 2)  
// 
// Thus, if you want to inter 's' and 'p' symbols, input them through space or in order "ps" to work, or it may cause input of 0 code symbol
// 
// Any unproper use of sp will input in set symbol with code 0 or occure error and clear all data in set
// 
// Error will be occured if you enter more than 3 symbols after sp
// 
// Inputing symbol code larger than 255 will occure BoolVector operator[] error

// Output characteritic:
// 
// Every printable symbol is printed
// 
// Unprintable symbols will be printed with special word spec. and their code number, so 32-nd symbol will be spec. 32, and 33rd symbol will be '!'

class Set : BoolVector {
public:
	Set();
	Set(const char*);
	Set(const Set&);
	~Set();

	using BoolVector::operator[];

	bool find(const char) const;

	char max() const;
	char min() const;

	void print(int index);

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
	