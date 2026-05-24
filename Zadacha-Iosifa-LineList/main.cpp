#include <iostream>
#include <chrono>
#include "LineList.h"

// Решение задачи Иосифа-Флавия
// Из списка [1..N] последовательно удаляется каждый k-й элемент.
// Счёт начинается с 1-го элемента (индекс 0 в кольце).
// Возвращается значение последнего оставшегося элемента.
int josephus(int N, int k) {
    // Заполняем кольцевой список числами 1..N
    LineList list;
    for (int i = 1; i <= N; ++i) {
        list.pushBack(i);
    }

    // prev - узел, стоящий ПЕРЕД тем, который будет удалён.
    // Для удаления k-го с текущей позиции нужно сделать (k-1) шагов от текущего prev->next.
    // Изначально счёт начинается с 1-го элемента (head).
    // Чтобы удалить 1-й, prev должен быть хвостом (элемент перед head).
    // Находим хвост: advance от head на (N-1) шагов.
    Node* prev = list.advance(list.getHead(), N - 1); // prev указывает на tail (перед head)

    while (list.getSize() > 1) {
        // Делаем (k-1) шагов вперёд от prev, чтобы prev оказался
        // прямо перед k-м элементом относительно текущего счёта.
        prev = list.advance(prev, k - 1);

        // Удаляем следующий за prev узел
        list.removeAfter(prev);

        // После удаления prev->next - новый «текущий» (следующий отсчёт)
        // prev остаётся на своём месте, следующая итерация продвинется ещё на (k-1)
    }

    return list.front();
}

int main() {
    int N, k;

    std::cout << "Enter N (number of elements): ";
    std::cin >> N;
    std::cout << "Enter k (step): ";
    std::cin >> k;

    if (N <= 0 || k <= 0) {
        std::cout << "N and k must be positive integers." << std::endl;
        return 1;
    }

    // Замеряем время выполнения
    auto start  = std::chrono::high_resolution_clock::now();
    int  result = josephus(N, k);
    auto end    = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Answer: " << result << std::endl;
    std::cout << "Time:   " << elapsed.count() << " sec" << std::endl;

    return 0;
}
