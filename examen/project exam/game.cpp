#include "game.h"
#include <iostream>
#include <fstream>

// Конструктор класса: вызывается автоматически при создании новой игры
TicTacToe::TicTacToe() {
    // Изменяем размер двумерного вектора под поле 20х20 и заполняем всё точками
    board.resize(SIZE, std::vector<char>(SIZE, '.'));
}

// Метод для красивого вывода игрового поля в консоль
void TicTacToe::printBoard() {
    // Выводим верхнюю строчку с номерами колонок (индексы от 0 до 19)
    std::cout << "   ";
    for (int i = 0; i < SIZE; i++) std::cout << i << (i < 10 ? "  " : " ");
    std::cout << "\n";

    // Цикл вывода строк поля
    for (int i = 0; i < SIZE; i++) {
        // Левый столбец: выводим номер текущей строки
        std::cout << i << (i < 10 ? "  " : " ");
        // Выводим сами элементы строки (точки, крестики или нолики)
        for (int j = 0; j < SIZE; j++) std::cout << board[i][j] << "  ";
        std::cout << "\n";
    }
}

// Метод для совершения хода (ставит символ на поле и записывает в историю)
bool TicTacToe::makeMove(int r, int c, char sym) {
    // Проверка на корректность: если вышли за границы поля или клетка занята — возвращаем false
    if (r < 0 || r >= SIZE || c < 0 || c >= SIZE || board[r][c] != '.') return false;

    board[r][c] = sym; // Ставим символ на поле
    history.push_back({ r, c, sym }); // Добавляем этот ход в вектор истории ходов
    return true; // Ход успешно сделан
}

// Метод-помощник класса TicTacToe: считает, сколько одинаковых знаков идет подряд в одну сторону
int TicTacToe::countLine(int r, int c, int dr, int dc, char sym) {
    int count = 0;
    // Проверяем до 4 клеток вперед в заданном направлении (dr, dc)
    for (int i = 1; i < 5; i++) {
        int nr = r + dr * i, nc = c + dc * i;
        // Если клетка в границах поля и там стоит нужный символ — увеличиваем счетчик
        if (nr >= 0 && nr < SIZE && nc >= 0 && nc < SIZE && board[nr][nc] == sym) count++;
        else break; // Если встретили пустоту или чужой символ — прерываем подсчет
    }
    return count;
}

// Метод проверки условий победы (ищет комбинацию из 5 символов в ряд)
bool TicTacToe::checkWin(char sym) {
    // Сканируем всё поле 20х20
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // Если нашли ячейку с нужным символом, проверяем линии от нее во все 4 стороны
            if (board[i][j] == sym) {
                // Горизонталь, вертикаль и две диагонали. Если где-то нашли 4 соседа (+1 старт = 5 в ряд) -> победа
                if (countLine(i, j, 0, 1, sym) >= 4 || countLine(i, j, 1, 0, sym) >= 4 ||
                    countLine(i, j, 1, 1, sym) >= 4 || countLine(i, j, 1, -1, sym) >= 4)
                    return true;
            }
        }
    }
    return false; // Никто пока не собрал 5 в ряд
}

// Метод проверки поля на полное заполнение клеток (для определения ничьей)
bool TicTacToe::isFull() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] == '.') return false; // Если нашли хоть одну точку — поле не полное
    return true; // Свободных мест нет, поле забито полностью
}

// Рациональный алгоритм ИИ (ищет лучшую клетку на основе весов атаки и защиты)
std::pair<int, int> TicTacToe::getBestMove(char comp, char player) {
    int bestScore = -1;
    std::pair<int, int> bestMove = { -1, -1 };

    // Перебираем все свободные клетки на поле
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != '.') continue; // Занятые ячейки пропускаем

            int attack = 0, defense = 0;
            int dirs[4][2] = { {0,1}, {1,0}, {1,1}, {1,-1} }; // Направления осей координат

            // Считаем линии в обе стороны для каждой оси направления
            for (auto& d : dirs) {
                int a = countLine(i, j, d[0], d[1], comp) + countLine(i, j, -d[0], -d[1], comp);
                int def = countLine(i, j, d[0], d[1], player) + countLine(i, j, -d[0], -d[1], player);
                attack = (a > attack) ? a : attack;
                defense = (def > defense) ? def : defense;
            }

            // Начисление баллов ценности для текущей свободной клетки
            int total = attack + defense;
            if (defense >= 4) total += 100; // Жёсткий приоритет защиты (блокируем 4 в ряд у соперника)
            if (attack >= 5) total += 500;  // Абсолютный приоритет атаки (ставим победный 5-й знак)

            // Если эта клетка набрала больше очков, чем предыдущие, запоминаем её
            if (total > bestScore) {
                bestScore = total;
                bestMove = { i, j };
            }
        }
    }
    return bestMove; // Возвращаем пару координат лучшего хода
}

// Метод сохранения полной истории сыгранных ходов матча в текстовый файл
void TicTacToe::saveHistory(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "Match Move History:\n";
        // Построчно выгружаем каждый элемент структуры Cell из вектора history
        for (size_t i = 0; i < history.size(); i++)
            file << "Turn " << i + 1 << ": [" << history[i].symbol << "] -> (" << history[i].x << ", " << history[i].y << ")\n";
        file.close();
    }
}

// --- ДОПОЛНИТЕЛЬНОЕ ЭКЗАМЕНАЦИОННОЕ ЗАДАНИЕ: Реализация отмены хода (Undo) ---
bool TicTacToe::undoMove() {
    // Если сделано меньше двух ходов (твой ход + ответ компа), то отменять нечего
    if (history.size() < 2) return false;

    // 1. Стираем последний ход с поля (это ход компьютера 'O')
    board[history.back().x][history.back().y] = '.';
    history.pop_back(); // Удаляем запись о ходе компьютера из истории

    // 2. Стираем предпоследний ход с поля (это твой ход 'X')
    board[history.back().x][history.back().y] = '.';
    history.pop_back(); // Удаляем запись о твоем ходе из истории

    return true; // Отмена успешно выполнена
}