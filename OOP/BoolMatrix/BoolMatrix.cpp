#include <iostream>
#include <assert.h>
#include "BoolMatrix.h"

BoolMatrix::BoolMatrix() {
	matrix = nullptr;
	_column = 0;
	_line = 0;
}

BoolMatrix::BoolMatrix(int lines, int columns, bool fillValue) {
	matrix = new BoolVector[lines];
	for (int i = 0; i < lines; i++) {
		matrix[i] = BoolVector(columns, fillValue);
	}
	_line = lines;
	_column = columns;
}

BoolMatrix::BoolMatrix(const char * const *  otherMatrix, int lines) {
	_line = lines;
	_column = sizeof(otherMatrix[0]) / sizeof(otherMatrix[0][0]);
	matrix = new BoolVector[_line];
	for (int i = 0; i < _line; i++) {
		matrix[i] = BoolVector(otherMatrix[i]);
	}
}

BoolMatrix::BoolMatrix(const BoolMatrix& other){
	_line = other._line;
	_column = other._column;
	matrix = new BoolVector[_line];
	for (int i = 0; i < _line; i++) {
		matrix[i] = other.matrix[i];
	}
}

int BoolMatrix::lines() const{
	return _line;
}
int BoolMatrix::columns() const{
	return _column;
}

void BoolMatrix::swap(BoolMatrix& other){
	std::swap(matrix, other.matrix);
	std::swap(_line, other._line);
	std::swap(_column, other._column);
}

BoolVector& BoolMatrix::getLine(int index){
	assert(index < _line && index > 0);
	return matrix[index];
}

void BoolMatrix::setLine(int index, const BoolVector& other){
	assert(index > 0 && index < _line);
	matrix[index] = other;
}

int BoolMatrix::weight(int i){
	if (i != -1) {
		return matrix[i].weight();
	}
	else {
		int count = 0;
		for (int i = 0; i < _line; i++) {
			count += matrix[i].weight();
		}
		return count;
	}
}

void BoolMatrix::inverseIn(int lineNumber, int index){
	assert(index > 0 && index < _column);
	assert(lineNumber > 0 && lineNumber < _line);
	matrix[lineNumber].invert(index);
}
void BoolMatrix::inverseInBy(int lineNumber, int index, int number){
	assert(index + number > 0 && index + number < _column);
	assert(lineNumber > 0 && lineNumber < _line);
	for (int i = index; i < index + number; i++) {
		matrix[lineNumber].invert(i);
	}
}

void BoolMatrix::setIn(int lineNumber, int index, int value){
	assert(index > 0 && index < _column);
	assert(lineNumber > 0 && lineNumber < _line);
	matrix[lineNumber].setBit(index, value);
}
void BoolMatrix::setInBy(int lineNumber, int index, int value, int number){
	assert(index + number > 0 && index + number < _column);
	assert(lineNumber > 0 && lineNumber < _line);
	matrix[lineNumber].setBits(index, number, value);
}

BoolVector BoolMatrix::conjunction(){
	BoolVector temp = BoolVector(_column, 1);
	for (int i = 0; i < _line; i++) {
		temp &= matrix[i];
	}
	return temp;
}
BoolVector BoolMatrix::disjunction(){
	BoolVector temp = BoolVector(_column, 0);

	for (int i = 0; i < _line; i++) {
		temp |= matrix[i];
	}
	return temp;
}

BoolMatrix& BoolMatrix::operator=(const BoolMatrix& other){
	if (_line != other._line) {
		delete[] matrix;
		matrix = new BoolVector[other._line];
	}
	_line = other._line;
	_column = other._column;
	for (int i = 0; i < _line; i++) {
		matrix[i] = other.matrix[i];
	}
	return *this;
}

BoolVector& BoolMatrix::operator[](int index){
	assert(index >= 0 && index < _line);
	return matrix[index];
}
const BoolVector& BoolMatrix::operator[](int index) const{
	assert(index >= 0 && index < _line);
	return matrix[index];
}

BoolMatrix& BoolMatrix::operator|=(const BoolMatrix& other){
	for (int i = 0; i < _line; i++) {
		matrix[i] |= other.matrix[i];
	}
	return *this;
}
BoolMatrix BoolMatrix::operator|(const BoolMatrix& other) const{
	BoolMatrix temp = (*this);
	temp |= other;
	return temp;
}

BoolMatrix& BoolMatrix::operator&=(const BoolMatrix& other){
	for (int i = 0; i < _line; i++) {
		matrix[i] &= other.matrix[i];
	}
	return *this;
}
BoolMatrix BoolMatrix::operator&(const BoolMatrix& other) const{
	BoolMatrix temp = (*this);
	temp &= other;
	return temp;
}

BoolMatrix& BoolMatrix::operator^=(const BoolMatrix& other){
	for (int i = 0; i < _line; i++) {
		matrix[i] ^= other.matrix[i];
	}
	return *this;
}
BoolMatrix BoolMatrix::operator^(const BoolMatrix& other) const{
	BoolMatrix temp = (*this);
	temp ^= other;
	return temp;
}

BoolMatrix BoolMatrix::operator~() const{
	BoolMatrix temp(*this);
	for (int i = 0; i < temp._line; i++) {
		temp.matrix[i].invert();
	}
	return temp;
}

std::ostream& operator<<(std::ostream& os, const BoolMatrix& matrix) {
	for (int i = 0; i < matrix.lines(); i++) {
		for (int j = 0; j < matrix.columns(); j++) {
			os << matrix[i][j];
		}
		os << std::endl;
	}
	return os;
}

std::istream& operator>>(std::istream& is, BoolMatrix& matrix) {
	for (int i = 0; i < matrix.lines(); i++) {
		is >> matrix[i];
	}

	return is;
}