#include "BoolMatrix.h"
#include "BooleanVector.h"
#include "BooleanVector.cpp"
#include <iostream>

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
	return matrix[index];
}

void BoolMatrix::setLine(int index, const BoolVector& other){
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
	matrix[lineNumber].invert(index);
}
void BoolMatrix::inverseInBy(int lineNumber, int index, int number){
	for (int i = index; i < index + number; i++) {
		matrix[lineNumber].invert(i);
	}
}

void BoolMatrix::setIn(int lineNumber, int index, int value){
	matrix[lineNumber].setBit(index, value);
}
void BoolMatrix::setInBy(int lineNumber, int index, int value, int number){
	matrix[lineNumber].setBits(index, number, value);
}

BoolVector BoolMatrix::conjunction(){
	BoolVector temp = matrix[0];
	temp.setAll(1);
	for (int i = 0; i < _line; i++) {
		temp &= matrix[i];
	}
	return temp;
}
BoolVector BoolMatrix::disjunction(){
	BoolVector temp = matrix[0];
	temp.setAll(0);

	for (int i = 0; i < _line; i++) {
		temp |= matrix[i];
	}
	return temp;
}

BoolMatrix& BoolMatrix::operator=(const BoolMatrix& other){
	if (this != &other || _line != other._line) {
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
	return matrix[index];
}
const BoolVector& BoolMatrix::operator[](int index) const{
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

BoolMatrix BoolMatrix::operator~(){
	BoolMatrix temp(*this);
	for (int i = 0; i < temp._line; i++) {
		temp.matrix[i] = ~temp.matrix[i];
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
	std::string* temp = new std::string[matrix.lines()];
	for (int i = 0; i < matrix.lines(); i++) {
		is >> temp[i];
	}
	char** temp1 = new char* [matrix.lines()];
	for (int i = 0; i < matrix.lines(); i++) {
		temp1[i] = &temp[i][0];
		matrix[i] = temp1[i];
	}

	return is;
}