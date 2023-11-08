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
        vector[index / CELL_SIZE] |= (1 << index % CELL_SIZE);
    }
    else {
        vector[index / CELL_SIZE] &= (~(1 << index % CELL_SIZE));
    }
}

bool BoolVector::getBit(int index) const {
    if (index<0 || index>size) {
        std::cerr << "Incorrect index in BoolVector::getBit, I=" << index;
        return 0;
    }
    if ((vector[index / CELL_SIZE] & (1 << index % CELL_SIZE)) == 0) return 0;
    return 1;
}

int BoolVector::sizeOf() const {
    return size;
}

void BoolVector::swap(BoolVector& other){
    std::swap(size, other.size);
    std::swap(vector, other.vector);
}



void BoolVector::invert(const int index){
    if (getBit(index) == 1) {
        setBit(index, 0);
    }
    else {
        setBit(index, 1);
    }
}

void BoolVector::setBits(int index, int count, bool value) {
    if (index<0 || index>size || count <= 0 || index + count >= size) {
        std::cerr << "Incorrect index in BoolVector::getBits, I=" << index;
        return;
    }
    for (int i = index; i <= index + count; i++) {
        setBit(i, value);
    }
}

void BoolVector::setAll(bool value) {
    for (int i = 0; i <= size / CELL_SIZE; i++) {
        vector[i] = (value == 1 ? (pow(2, CELL_SIZE)-1) : 0);
    }
}

int BoolVector::weight() {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (((vector[i/ CELL_SIZE] >> (i% CELL_SIZE)) & 1) == 1) {
            count++;
        }
    }
    return count;
}

void BoolVector::nullifyInsignificant() {
    int count =size/ CELL_SIZE + (ceil(((size % CELL_SIZE) + 0.) / CELL_SIZE)); // Кол-во ячеек 
    for (int i = 7; i > size % CELL_SIZE; i--) {
        vector[count + size % CELL_SIZE] &= (~(1 << i));
    }
}

void BoolVector::setInsignificant() {
    int count = size / CELL_SIZE + (ceil(((size % CELL_SIZE) + 0.) / CELL_SIZE)); // Кол-во ячеек 
    for (int i = 7; i > size % CELL_SIZE; i--) {
        vector[count + size % CELL_SIZE] |= (1 << i);
    }
}

// Реализация побитовых операций

BoolRank BoolVector::operator[](int index) const {
    if (((vector[index / CELL_SIZE]>> (index % CELL_SIZE))&1) == 1) return BoolRank(1, (*this).vector , index);
    return BoolRank(0, (*this).vector, index);
}

BoolVector& BoolVector::operator=(const BoolVector& other) {
    BoolVector temp(other);
    swap(temp);
    return *this;
}

BoolVector BoolVector::operator&(const BoolVector& other) const {
    BoolVector temp = (*this);
    int min = temp.size;
    if (temp.size > other.size) min = other.size;
    for (int i = 0; i <= min; i++) {
        temp.vector[i/CELL_SIZE] &= other.vector[i/CELL_SIZE];
    }
    temp.nullifyInsignificant();
    return temp;
}

BoolVector BoolVector::operator|(const BoolVector& other) const{
    BoolVector temp = (*this);
    int min = temp.size;
    if (temp.size > other.size) min = other.size;
    for (int i = 0; i <= min; i++) {
        temp.vector[i] |= other.vector[i];
    }
    temp.nullifyInsignificant();
    return temp;
}

BoolVector BoolVector::operator^(const BoolVector& other) const{
    BoolVector temp = (*this);
    int min = temp.size;
    if (temp.size > other.size) min = other.size;
    for (int i = 0; i <= min; i++) {
        temp.vector[i] ^= other.vector[i];
    }
    temp.nullifyInsignificant();
    return temp;
}

BoolVector& BoolVector::operator&=(const BoolVector& other) {
    (*this) = (*this) & other;
    return *this;
}

BoolVector& BoolVector::operator|=(const BoolVector& other) {
    (*this) = (*this) | other;
    return *this;
}

BoolVector& BoolVector::operator^=(const BoolVector& other) {
    (*this) = (*this) ^ other;
    return *this;
}

BoolVector& BoolVector::operator~(){
    for (int i = 0; i < size; i++) {
        vector[i / CELL_SIZE] = ~vector[i / CELL_SIZE];
    }
    nullifyInsignificant();
    return *this;
}

// Реализация побитовых сдвигов

BoolVector& BoolVector::operator<<(int number) {

}

BoolVector& BoolVector::operator<<=(int number) {

}

BoolVector& BoolVector::operator>>(int number) {

}

BoolVector& BoolVector::operator>>=(int number) {

}

// Реализация необходимых операций для вспомогательного класса

void BoolRank::setValue() {
    if (index<0 || index>(sizeof(ptr) / sizeof(ptr[0]))) {
        std::cerr << "Incorrect index in BoolRank::setValue, I=" << index;
        return;
    }

    if (value == 1) {
        ptr[index / CELL_SIZE] |= (1 << index % CELL_SIZE);
    }
    else {
        ptr[index / CELL_SIZE] &= (~(1 << index % CELL_SIZE));
    }
}

void BoolRank::operator=(bool value) {
    (*this).value = value;
    setValue();
}

BoolRank::operator bool() const {
    return value;
}