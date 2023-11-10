#include "BooleanVector.h"

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
    if (size)
        vector = new unsigned char[size / CELL_SIZE + (ceil(((size % CELL_SIZE) + 0.) / CELL_SIZE))];
    else
        vector = nullptr;

    int i = size-1;
    while (i>=0) {
        if (data[i] == '1') {
            setBit(i, 1);
        }
        else {
            setBit(i, 0);
        }
        i--;
    }
}
BoolVector::BoolVector(const BoolVector& other) {
    size = other.size;
    vector = new unsigned char[size / CELL_SIZE + (ceil(((size % CELL_SIZE) + 0.) / CELL_SIZE))];
    for (int i = 0; i < size; i+=CELL_SIZE) {
        vector[i/CELL_SIZE] = other.vector[i/CELL_SIZE];
    }
}

const void BoolVector::print() const{
    for (int i = 0; i < size; i++) {
        std::cout << getBit(i);
    }
}

// ћетоды дл€ установки и получени€ битов
void BoolVector::setBit(const int index, const bool value) {
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

bool BoolVector::getBit(const int index) const {
    if (index<0 || index>size) {
        std::cerr << "Incorrect index in BoolVector::getBit, I=" << index;
        return 0;
    }
    if ((vector[index / CELL_SIZE] & (1 << index % CELL_SIZE)) == 0)
        return 0;
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
    setBit(index, !getBit(index));
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
        vector[i] = (value == 1 ? ((2<<CELL_SIZE)-1) : 0);
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

//void BoolVector::nullifyInsignificant() {
//    int count =size/ CELL_SIZE + (ceil(((size % CELL_SIZE) + 0.) / CELL_SIZE)); //  ол-во €чеек 
//    for (int i = 7; i > size % CELL_SIZE; i--) {
//        vector[count + size % CELL_SIZE] &= (~(1 << i));
//    }
//}
//
//void BoolVector::setInsignificant() {
//    int count = size / CELL_SIZE + (ceil(((size % CELL_SIZE) + 0.) / CELL_SIZE)); //  ол-во €чеек 
//    for (int i = 7; i > size % CELL_SIZE; i--) {
//        vector[count + size % CELL_SIZE] |= (1 << i);
//    }
//}

// –еализаци€ побитовых операций

const bool BoolVector::operator[](int index) const {
    if (((vector[index / CELL_SIZE]>> (index % CELL_SIZE))&1) == 1)
        return 1;
    return 0;
}

BoolRank BoolVector::operator[](int index){
    if (((vector[index / CELL_SIZE] >> (index % CELL_SIZE)) & 1) == 1)
        return BoolRank(1, (*this).vector, index);
    return BoolRank(0, (*this).vector, index);
}

BoolVector& BoolVector::operator=(const BoolVector& other) {
    if (size != other.size) {
        size = other.size;
        delete[] vector;
        vector = new unsigned char[size / CELL_SIZE + (ceil(((size % CELL_SIZE) + 0.) / CELL_SIZE))];
    }
    for (int i = 0; i < size; i++) {
        vector[i/CELL_SIZE] = other.vector[i/CELL_SIZE];
    }
    return *this;
}

BoolVector BoolVector::operator&(const BoolVector& other) const {
    BoolVector temp = (*this);
    int min = temp.size;
    if (temp.size > other.size) min = other.size;
    for (int i = 0; i <= min; i+=CELL_SIZE) {
        temp.vector[i/CELL_SIZE] &= other.vector[i/CELL_SIZE];
    }
    return temp;
}

BoolVector BoolVector::operator|(const BoolVector& other) const{
    BoolVector temp = (*this);
    int min = temp.size;
    if (temp.size > other.size) min = other.size;
    for (int i = 0; i <= min; i+=CELL_SIZE) {
        temp.vector[i] |= other.vector[i];
    }
    return temp;
}

BoolVector BoolVector::operator^(const BoolVector& other) const{
    BoolVector temp = (*this);
    int min = temp.size;
    if (temp.size > other.size) min = other.size;
    for (int i = 0; i <= min; i+=CELL_SIZE) {
        temp.vector[i] ^= other.vector[i];
    }
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
    return *this;
}

// –еализаци€ побитовых сдвигов

BoolVector BoolVector::operator<<(int number) const{
    BoolVector temp(*this);
    if (number <= 0) {
        std::cerr << "Incorrect number for shift in BoolVector:: operator<<, number= " << number;
        return("0");
    }

    for (int i = 0; i<number/CELL_SIZE; i+=CELL_SIZE) { // —двигаем по €чейкам
        temp.vector[i] = temp.vector[i+number/CELL_SIZE];
    }
    for (int i = size/CELL_SIZE + ceil(((size % CELL_SIZE) + 0.) / CELL_SIZE)-1; i > size / CELL_SIZE + ceil(((size % CELL_SIZE) + 0.) / CELL_SIZE) - number/CELL_SIZE-1; i--) {
        temp.vector[i] =0;
    }

    for (int i = 0; i < size; i+=CELL_SIZE) { // —двигаем внутри €чеек
        temp.vector[i / CELL_SIZE] >>= number%CELL_SIZE;
        if (i / CELL_SIZE + 1 >= temp.size/CELL_SIZE) {
            unsigned char mask = temp.vector[i/CELL_SIZE+1];
            
            temp.vector[i / CELL_SIZE] |= (mask<<(CELL_SIZE-number%CELL_SIZE));
        }
    }
    for (int i = size - number%CELL_SIZE; i < size; i++) {
        temp.setBit(i, 0);
    }
    return temp;
}

BoolVector& BoolVector::operator<<=(int number) {
    (*this) = ((*this) << number);
    return *this;
}

BoolVector BoolVector::operator>>(int number) const {
    BoolVector temp(*this);
    if (number <= 0) {
        std::cerr << "Incorrect number for shift in BoolVector:: operator<<, number= " << number;
        return("0");
    }

    for (int i = size/CELL_SIZE; i > size/CELL_SIZE - number / CELL_SIZE; i -= CELL_SIZE) { // —двигаем по €чейкам
        temp.vector[i] = vector[i - number / CELL_SIZE];
    }
    for (int i = 0; i < number / CELL_SIZE; i += CELL_SIZE) {
        temp.vector[i] = 0;
    }

    for (int i = size; i >=0 ; i -= CELL_SIZE) {
        temp.vector[i / CELL_SIZE] <<= number%CELL_SIZE;
        if (i / CELL_SIZE-1 >= 0) {
            unsigned char mask = temp.vector[i / CELL_SIZE - 1];

            temp.vector[i / CELL_SIZE] |= (mask >> (CELL_SIZE -number%CELL_SIZE));
        }
    }
    for (int i = 0;  i < number%CELL_SIZE; i++) {
        temp.setBit(i, 0);
    }
    return temp;
}

BoolVector& BoolVector::operator>>=(int number) {
    *this = *this >> number;
    return *this;
}

// –еализаци€ необходимых операций дл€ вспомогательного класса

void BoolRank::setValue() {
    if (index<0 || index>(sizeof(ptr) / sizeof(ptr[0]))) {
        std::cerr << "Incorrect index in BoolRank::setValue, I=" << index;
        return;
    }

    if (value == 1) {
        ptr[index / BoolVector::CELL_SIZE] |= (1 << index % BoolVector::CELL_SIZE);
    }
    else {
        ptr[index / BoolVector::CELL_SIZE] &= (~(1 << index % BoolVector::CELL_SIZE));
    }
}

void BoolRank::operator=(bool value) {
    (*this).value = value;
    setValue();
}

BoolRank::operator bool() const {
    return value;
}