#pragma once
#include <vector>
#include <iostream>

class BoolVector;

class BoolRank {
    friend BoolVector;
    int index=0;
    bool value = 0;

    void setValue();
};

class BoolVector {
    friend BoolRank;
public:
    BoolVector();
    BoolVector(int size, int data);
    BoolVector(const char* data);
    BoolVector(const BoolVector& other);


    ~BoolVector() {
       if (vector!=nullptr) delete[] vector;
    }

    void print();

    // Методы для установки и получения битов
    void setBit(int index, bool value=1);

    bool getBit(int index) const;

    int sizeOf() const;

    void swap(BoolVector& other);

   

    void invert(const int index) const;

    void setBits(int index, int count, bool value);

    void setAll(bool value);

    int weight();

    // Реализация побитовых операций

    bool operator[](int index) const;

    BoolVector operator&(const BoolVector& other) const;

    BoolVector operator|(const BoolVector& other) const;

    BoolVector operator^(const BoolVector& other) const;

    BoolVector operator~() const;



private:
    int size;
    unsigned char* vector;
};

