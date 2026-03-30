//Пример запуска: Допустим после запуска программы мы вписываем: Введите дату 1: 2024 3 30 12 45 10 (это: год, месяц, день, часы, минуты, секунды) 
//Потом также со второй. и тогда булдет все работать коректно: Ввведите дату 2: 2023 12 25 8 30 0

#include <iostream>
#include "DateTime.h"
using namespace std;

int main() {
    DateTime d1, d2;
    setlocale(LC_ALL, "Russian");
    cout << "Введите дату 1 (год месяц день часы минуты секунды): ";
    d1.input();

    cout << "Введите дату 2: ";
    d2.input();

    cout << "\n--- Вывод даты ---\n";
    d1.print1();
    d1.print2();
    d1.print3();

    cout << "\n--- Проверка ---\n";
    if (d1.isValid())
        cout << "Дата корректная\n";
    else
        cout << "Дата некорректная\n";

    cout << "\n--- Разница ---\n";
    cout << d1.difference(d2) << " дней\n";

    cout << "\n--- День недели ---\n";
    const char* days[] = {
        "Суббота", "Воскресенье", "Понедельник",
        "Вторник", "Среда", "Четверг", "Пятница"
    };
    cout << days[d1.dayOfWeek()] << endl;

    cout << "\n--- Пасха ---\n";
    DateTime p = DateTime::easter(2024);
    p.print1();

    return 0;
}