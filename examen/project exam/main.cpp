#include <iostream>
#include "game.h"

int main() {
    TicTacToe game; // Создаем объект нашей игры
    char player = 'X', comp = 'O'; // Задаем символы: человек играет крестиками, ИИ — ноликами

    // Выводим в консоль приветствие и доступные служебные команды
    std::cout << "=== TIC-TAC-TOE ===\nHint: enter -1 -1\nUndo: enter -2 -2\n\n";

    // Главный игровой интерактивный цикл
    while (true) {
        game.printBoard(); // Каждый ход заново отрисовываем актуальное поле
        int r, c;
        std::cout << "\nYour turn (row col): ";
        std::cin >> r >> c; // Ждем от пользователя ввод координат строки и столбца

        // Если пользователь ввел буквы или символы вместо цифр — предотвращаем зависание
        if (std::cin.fail()) {
            std::cin.clear(); // Сбрасываем флаг ошибки ввода
            std::string ignore;
            std::cin >> ignore; // Сжираем некорректный мусор из потока
            std::cout << "Invalid input! Enter numbers.\n";
            continue; // Возвращаем на начало цикла, просим ввести нормально
        }

        // ПРОВЕРКА КОМАНДЫ №1: Подсказка оптимального хода
        if (r == -1 && c == -1) {
            // Передаем в ИИ аргументы наоборот (player, comp), чтобы алгоритм просчитал веса ЗА человека
            std::pair<int, int> hint = game.getBestMove(player, comp);
            std::cout << ">>> Hint: (" << hint.first << ", " << hint.second << ")\n";
            continue; // Возвращаемся в начало цикла, чтобы дать сделать нормальный ход
        }

        // ПРОВЕРКА КОМАНДЫ №2: Отмена ошибочного действия (Экзаменационное задание)
        if (r == -2 && c == -2) {
            // Вызываем метод отмены. Если он вернул true — откатываемся
            if (game.undoMove()) {
                std::cout << ">>> Move undone! Going 1 step back.\n";
            }
            else {
                // Если вернул false (например, поле еще пустое), выводим предупреждение
                std::cout << ">>> Nothing to undo yet! Make a real move first.\n";
            }
            continue; // Обязательно уходим на начало цикла, чтобы заново нарисовать поле и ждать ввод
        }

        // ОБЫЧНЫЙ РЕЖИМ: Пробуем сделать ход игрока. 
        // Если makeMove вернул false — ячейка занята или координаты вылезли за пределы поля 20х20
        if (!game.makeMove(r, c, player)) {
            std::cout << "Invalid move! Try again.\n";
            continue; // Просим повторить ввод ячейки
        }

        // Проверяем условия завершения матча после хода человека
        if (game.checkWin(player)) { std::cout << "\nYou win!\n"; break; } // Победа игрока
        if (game.isFull()) { std::cout << "\nDraw!\n"; break; }            // Ничья (поле забито)

        // ХОД КОМПЬЮТЕРА: Вычисляем лучшую эвристическую клетку для ИИ
        std::pair<int, int> cMove = game.getBestMove(comp, player);
        game.makeMove(cMove.first, cMove.second, comp); // Ставим нолик на поле
        std::cout << "Computer moved to: (" << cMove.first << ", " << cMove.second << ")\n";

        // Проверяем условия завершения матча после ответа компьютера
        if (game.checkWin(comp)) { std::cout << "\nComputer wins!\n"; break; } // Победа ИИ
        if (game.isFull()) { std::cout << "\nDraw!\n"; break; }               // Ничья
    }

    // Финальный аккорд: выводим итоговое поле, сохраняем лог в историю и выходим
    game.printBoard();
    game.saveHistory("history.txt");
    std::cout << "Match history saved to history.txt\n";

    return 0;
}