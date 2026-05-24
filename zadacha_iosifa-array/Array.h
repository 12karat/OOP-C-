#pragma once
#include <stdexcept>

// Dinamicheskiy konteyner dlya zadachi Iosifa-Flaviya
class Array {
private:
    int* data;       // ukazatel' na massiv elementov
    int  size;       // tekushchiy razmer konteynerа
    int  capacity;   // vydelennaya emkost'

    // Pereraspredelenie pamyati pri neobhodimosti
    void resize(int newCapacity);

public:
    // Konstruktor: sozdaet konteyner s chislami ot 1 do n
    explicit Array(int n);

    // Destruktor: osvobozhdaet pamyat'
    ~Array();

    // Zapret kopirovaniya
    Array(const Array&)            = delete;
    Array& operator=(const Array&) = delete;

    // Tekushchee kolichestvo elementov
    int getSize() const;

    // Dostup k elementu po indeksu (0-based)
    int  get(int index) const;
    void set(int index, int value);

    // Udalenie elementa po indeksu (0-based); sdvigaet ostavshiesya
    void removeAt(int index);
};
