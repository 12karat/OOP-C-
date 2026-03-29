#pragma once

#include <iostream>

class ArrayException {};

class Array {
    int* ptr;
    int size;
    int capacity;

    void increaseCapacity(int newCapacity);

public:
    explicit Array(int startCapacity = 10);
    Array(const Array& arr);
    ~Array();

    Array& operator=(const Array& arr);
    int& operator[](int index);
    int operator[](int index) const;

    void insert(int elem, int index);
    void insert(int elem);
    void remove(int index);
    int getSize() const;

    friend std::ostream& operator<<(std::ostream& out, const Array& arr);
};
