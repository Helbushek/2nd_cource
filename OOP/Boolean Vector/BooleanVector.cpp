#include "BooleanVector.h"
#define  CELL_SIZE  8


BoolVector::BoolVector() {
    vector = nullptr;
    size = 0;
}
BoolVector::BoolVector(int size, int data) {
    vector = new unsigned char[size / CELL_SIZE];
    (*this).size = size;
}
BoolVector::BoolVector(const char* data) {
    size = strlen(data);
    if (size) vector = new unsigned char[size / CELL_SIZE + (ceil(((size % CELL_SIZE) + 0.) / CELL_SIZE))];
    else vector = nullptr;

    /*for (int i = size / 8, counter; i >0 ; i--) {
        for (int j = 7; j>=0 && (size/8-i)*8+(7-j)<size; j--) {
            vector[i] |= data[(1<<j)
        }
    }*/

    int i = 0;
    while (data[i] != '\0') {
        if (data[i] == '1') {
            //vector[i / CONST_CELL_SIZE] = vector[i / CONST_CELL_SIZE] | (1 << i % CONST_CELL_SIZE);
            setBit(i, 1);
        }
        else {
            //vector[i / CONST_CELL_SIZE] = vector[i / CONST_CELL_SIZE] & (~(1<<i%CONST_CELL_SIZE));
            setBit(i, 0);
        }
        i++;
    }
}
BoolVector::BoolVector(const BoolVector& other) {
    size = other.size;
    for (int i = 0; i < size / CELL_SIZE; i++) {
        vector[i] = other.vector[i];
    }
}

void BoolVector::print() {
    for (int i = size-1; i >=0; i--) {
        std::cout << ((vector[i / CELL_SIZE]>>i% CELL_SIZE) & 1);
    }
}

// Методы для установки и получения битов
void BoolVector::setBit(int index, bool value) {
    if (index<0 || index>size) {
        std::cerr << "Incorrect index in BoolVector::setBit, I=" << index;
        return;
    }
    if (value == 1) {
        vector[index / CELL_SIZE] = vector[index / CELL_SIZE] | (1 << index % CELL_SIZE);
    }
    else {
        vector[index / CELL_SIZE] = vector[index / CELL_SIZE] & (~(1 << index % CELL_SIZE));
    }
}

bool BoolVector::getBit(int index) const {
    if (index<0 || index>size) {
        std::cerr << "Incorrect index in BoolVector::setBit, I=" << index;
        return 0;
    }
    if ((vector[index / CELL_SIZE] & (1 << index % CELL_SIZE)) == 0) return 0;
    return 1;
}

void BoolRank::setValue() {

}

int BoolVector::sizeOf() const {
    return size;
}

void BoolVector::swap(BoolVector& other){
    std::swap(size, other.size);
    std::swap(vector, other.vector);
}



void BoolVector::invert(const int index) const{
    
}

void BoolVector::setBits(int index, int count, bool value){}

void BoolVector::setAll(bool value){}

int BoolVector::weight() {
    return 1;
}

// Реализация побитовых операций

bool BoolVector::operator[](int index) const {
    if (((vector[index / CELL_SIZE]>> (index & CELL_SIZE))&1) == 1) return 1;
    return 0;
}

BoolVector BoolVector::operator&(const BoolVector& other) const {
    return *this;
}

BoolVector BoolVector::operator|(const BoolVector& other) const{
    return *this;
}

BoolVector BoolVector::operator^(const BoolVector& other) const{
    return *this;
}

BoolVector BoolVector::operator~() const{
    return *this;
}