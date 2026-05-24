#include "Field.h"
#include <iostream>

// Главная функция программы
int main(void)
{
    // Инициализация игры (Красный игрок ходит первым)
    Field field(true);

    // Основной игровой цикл
    while (!field.isOver())
    {
        field.print();

        // Информирование о текущем ходе
        std::cout << "Turn: " << (field.isRedTurnNow() ? "Red (R)" : "Yellow (Y)")
            << " player. Enter column (1-7): ";

        int column;
        std::cin >> column;

        // Попытка сделать ход. Если ход некорректен — выводим ошибку и запрашиваем заново
        if (!field.makeTurn(column))
        {
            std::cout << "Invalid move! Column is full or out of bounds. Try again.\n";
        }
    }

    // Вывод результатов по окончании игры
    field.printResult();

    return 0;
}