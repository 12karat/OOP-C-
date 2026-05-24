#include "Array.h"
#include <stdexcept>

// ---- vspomogatel'naya: uvelichenie bufera ----
void Array::resize(int newCapacity) {
    int* newData = new int[newCapacity];
    for (int i = 0; i < size; ++i)
        newData[i] = data[i];
    delete[] data;
    data     = newData;
    capacity = newCapacity;
}

// ---- konstruktor ----
Array::Array(int n) {
    if (n <= 0)
        throw std::invalid_argument("n must be positive");

    capacity = n;
    size     = n;
    data     = new int[capacity];

    // Zapolnyaem posledovatel'nost'yu 1..n
    for (int i = 0; i < n; ++i)
        data[i] = i + 1;
}

// ---- destruktor ----
Array::~Array() {
    delete[] data;
}

// ---- razmer ----
int Array::getSize() const {
    return size;
}

// ---- chtenie elementa ----
int Array::get(int index) const {
    if (index < 0 || index >= size)
        throw std::out_of_range("Array::get — index out of range");
    return data[index];
}

// ---- zapis' elementa ----
void Array::set(int index, int value) {
    if (index < 0 || index >= size)
        throw std::out_of_range("Array::set — index out of range");
    data[index] = value;
}

// ---- udalenie elementa po indeksu ----
// Vse elementy pravee sdvigayutsya vlevo na 1 poziciyu
void Array::removeAt(int index) {
    if (index < 0 || index >= size)
        throw std::out_of_range("Array::removeAt — index out of range");

    for (int i = index; i < size - 1; ++i)
        data[i] = data[i + 1];

    --size;
}
