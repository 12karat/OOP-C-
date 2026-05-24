#include "Field.h"
#include <iostream>

// Конструктор класса
Field::Field(bool isRedFirst)
{
    clear(isRedFirst); // Вызов очистки для инициализации начального состояния
}

// Метод очистки поля и инициализации новой игры
void Field::clear(bool isRedFirst)
{
    isRedTurn = isRedFirst; // Установка очередности первого хода
    winner = EMPTY;         // Сброс победителя
    for (int i = 0; i < FIELD_WIDTH; i++)
    {
        for (int j = 0; j < FIELD_HEIGHT; j++)
        {
            cells[i][j] = EMPTY; // Заполнение всех ячеек пустыми значениями
        }
    }
}

// Внутренний метод для проверки наличия победителя после хода
void Field::checkWinner()
{
    const int DIR_NUMBER = 4;
    // Направления для проверки 4 фишек: горизонталь, вертикаль и две диагонали
    const int di[] = { 1, 0, 1, 1 };
    const int dj[] = { 0, 1, -1, 1 };
    const int WIN_LENGTH = 4;

    for (int i = 0; i < FIELD_WIDTH; i++)
    {
        for (int j = 0; j < FIELD_HEIGHT; j++)
        {
            Cell start = cells[i][j];
            if (start == EMPTY)
                continue; // Пропускаем пустые ячейки

            for (int dir = 0; dir < DIR_NUMBER; dir++)
            {
                int length = 0;
                int iline = i;
                int jline = j;

                while (++length < WIN_LENGTH)
                {
                    iline += di[dir];
                    jline += dj[dir];

                    // Проверка выхода за границы поля
                    if (iline < 0 || iline >= FIELD_WIDTH || jline < 0 || jline >= FIELD_HEIGHT)
                        break;

                    // Если последовательность прервалась фишкой другого цвета
                    if (cells[iline][jline] != start)
                        break;
                }

                // Если нашли 4 фишки в ряд — фиксируем победителя
                if (length == WIN_LENGTH)
                {
                    winner = start;
                    return;
                }
            }
        }
    }
}

// Метод выполнения хода в указанную колонку
bool Field::makeTurn(int column)
{
    // Проверка корректности номера колонки и состояния игры
    if (winner != EMPTY || column < 1 || column > FIELD_WIDTH)
        return false;

    int i = column - 1; // Перевод в 0-индексацию для работы с массивом
    for (int j = 0; j < FIELD_HEIGHT; j++)
    {
        // Ищем самую нижнюю свободную ячейку в выбранной колонке
        if (cells[i][j] == EMPTY)
        {
            cells[i][j] = isRedTurn ? RED : YELLOW; // Ставим фишку текущего игрока
            checkWinner(); // Проверяем, не стал ли этот ход победным
            isRedTurn = !isRedTurn; // Передаем очередь хода следующему игроку
            return true; // Ход успешно выполнен
        }
    }
    return false; // Возвращаем false, если колонка полностью заполнена
}

// Проверка окончания игры (победа или ничья)
bool Field::isOver() const
{
    if (winner != EMPTY)
        return true; // Игра окончена, если есть победитель

    for (int i = 0; i < FIELD_WIDTH; i++)
    {
        for (int j = 0; j < FIELD_HEIGHT; j++)
        {
            // Если есть хоть одна пустая ячейка, игра продолжается
            if (cells[i][j] == EMPTY)
                return false;
        }
    }
    // Все ячейки заняты и победителя нет — объявлена ничья
    return true;
}

// Возвращает true, если сейчас очередь красного игрока
bool Field::isRedTurnNow() const
{
    return isRedTurn;
}

// Вывод игрового поля в консоль (от верхней строчки к нижней)
void Field::print() const
{
    std::cout << "\n  1 2 3 4 5 6 7\n";
    std::cout << " ---------------\n";
    for (int j = FIELD_HEIGHT - 1; j >= 0; j--)
    {
        std::cout << "| ";
        for (int i = 0; i < FIELD_WIDTH; i++)
        {
            if (cells[i][j] == RED)
                std::cout << "R ";
            else if (cells[i][j] == YELLOW)
                std::cout << "Y ";
            else
                std::cout << ". ";
        }
        std::cout << "|\n";
    }
    std::cout << " ---------------\n";
}

// Вывод финального результата игры
void Field::printResult() const
{
    print();
    if (winner == RED)
    {
        std::cout << "Game Over! Red player (R) wins!\n";
    }
    else if (winner == YELLOW)
    {
        std::cout << "Game Over! Yellow player (Y) wins!\n";
    }
    else
    {
        std::cout << "Game Over! It's a draw!\n";
    }
}