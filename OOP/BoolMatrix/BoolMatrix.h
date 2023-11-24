#pragma once
#include <iostream>
#include "BooleanVector.h"

class BoolMatrix {
public:
	BoolMatrix();
	BoolMatrix(int lines, int columns, bool fillValue);
	BoolMatrix(char const * const * const matrix, int lines);
	BoolMatrix(const BoolMatrix& other);

	~BoolMatrix() {
		delete[]matrix;
	}
	           
	int lines() const;
	int columns() const;	

	void swap(BoolMatrix& other);

	BoolVector& getLine(int index);

	void setLine(int index, const BoolVector& other);

	int weight(int i=-1);

	void inverseIn(int lineNumber, int index);
	void inverseInBy(int lineNumber, int index, int number);
	
	void setIn(int lineNumber, int index, int value=1);
	void setInBy(int lineNumber, int index, int value, int number);

	BoolVector conjunction();
	BoolVector disjunction();

	BoolMatrix& operator=(const BoolMatrix& other);

	BoolVector& operator[](int index);
	const BoolVector& operator[](int index) const;


	BoolMatrix& operator|=(const BoolMatrix& other);
	BoolMatrix operator|(const BoolMatrix& other) const;
	
	BoolMatrix& operator&=(const BoolMatrix& other);
	BoolMatrix operator&(const BoolMatrix& other) const;

	BoolMatrix& operator^=(const BoolMatrix& other);
	BoolMatrix operator^(const BoolMatrix& other) const;

	BoolMatrix operator~() const;

	

private:
	BoolVector* matrix;
	int _column;
	int _line;
};

std::ostream& operator<<(std::ostream& os, const BoolMatrix& matrix);

std::istream& operator>>(std::istream& is, BoolMatrix& matrix);