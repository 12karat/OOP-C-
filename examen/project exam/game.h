#pragma once

#include <vector>
#include <string>

// Структура, чтобы удобно хранить инфу о каждом сделанном ходе для истории
struct Cell {
    int x, y;     // Координаты хода (строка и столбец)
    char symbol;  // Кто сходил: 'X' или 'O'
};

class TicTacToe {
private:
    int SIZE = 20; // Размер поля (по заданию 20 на 20)
    std::vector<std::vector<char>> board; // Наша сетка поля (двумерный вектор)
    std::vector<Cell> history;            // Сюда складываем все ходы по порядку

    // Метод-выручалка: считает, сколько одинаковых знаков идет подряд
    int countLine(int r, int c, int dr, int dc, char sym);

public:
    TicTacToe(); // Конструктор, он просто создаст чистое поле
    void printBoard(); // Рисует поле в консоли с красивыми индексами
    bool makeMove(int r, int c, char sym); // Ставит крестик или нолик, если можно
    bool checkWin(char sym); // Проверяет, собрал ли кто-то 5 в ряд
    bool isFull(); // Проверяет, не кончились ли свободные клетки (для ничьей)
    std::pair<int, int> getBestMove(char comp, char player); // Умный метод ИИ
    void saveHistory(const std::string& filename); // Сохранение истории в текстовый файл

    //ДОПОЛНИТЕЛЬНОЕ ЭКЗАМЕНАЦИОННОЕ ЗАДАНИЕ 
    bool undoMove(); // Объявление метода для отмены последнего полного круга ходов
};