#include <iostream>
#include "LineList.h"

using namespace std;

int main(void)
{
    // Проверка шаблона функции поиска максимума
    int a = 2, b = 3;
    cout << "Max(a,b)=" << getMax(a, b) << endl;

    // Использование шаблона класса списка
    LineList<int> list;
    // Указываем, список какого типа
    cout << "Start: " << list << endl;
    list.insertFirst(10);
    LineListElem<int>* ptr = list.getStart();
    list.insertAfter(ptr, 15);
    list.insertAfter(ptr->getNext(), 12);
    list.insertFirst(7);
    cout << "Step 1: " << list << endl;

    // Задача на перебор элементов списка
    int sum = 0;
    // Используем переменную-итератор
    for (LineListElem<int>* it = list.getStart(); it; it = it->getNext())
        sum += it->getData();
    cout << "Sum = " << sum << endl;

    return 0;
}