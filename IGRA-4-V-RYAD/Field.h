#ifndef FIELD_H
#define FIELD_H

// Константы для размеров игрового поля
const int FIELD_WIDTH = 7;  // Ширина поля (7 колонок)
const int FIELD_HEIGHT = 6; // Высота поля (6 строк)

// Перечисление для состояний ячейки
enum Cell
{
    EMPTY = 0, // Пустая ячейка
    RED = 1,   // Фишка красного игрока
    YELLOW = 2 // Фишка желтого игрока
};

// Класс игрового поля
class Field
{
private:
    // Двумерный массив для хранения игрового поля
    Cell cells[FIELD_WIDTH][FIELD_HEIGHT];

    // Очередь хода: true - ходит красный, false - желтый
    bool isRedTurn;

    // Кто на данный момент выиграл
    Cell winner;

    // Внутренний метод для проверки наличия победителя после хода
    void checkWinner();

public:
    // Конструктор класса
    Field(bool isRedFirst);

    // Метод очистки поля и инициализации новой игры
    void clear(bool isRedFirst);

    // Метод выполнения хода в указанную колонку
    bool makeTurn(int column);

    // Проверка окончания игры (победа или ничья)
    bool isOver() const;

    // Возвращает true, если сейчас очередь красного игрока
    bool isRedTurnNow() const;

    // Вывод игрового поля в консоль
    void print() const;

    // Вывод финального результата игры
    void printResult() const;
};

#endif // FIELD_H