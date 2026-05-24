#pragma once

// Узел однонаправленного списка
struct Node {
    int value;
    Node* next;

    Node(int val) : value(val), next(nullptr) {}
};

// Контейнер LineList - однонаправленный кольцевой список
class LineList {
private:
    Node* head;   // указатель на первый элемент
    int   size;   // текущее кол-во элементов

public:
    LineList();
    ~LineList();

    // Добавить элемент в конец списка
    void pushBack(int val);

    // Удалить узел, следующий за указанным (next after given node)
    // Возвращает значение удалённого узла
    int removeAfter(Node* prev);

    // Получить указатель на узел, отступив steps шагов от current
    // Используется для продвижения по кольцу
    Node* advance(Node* current, int steps) const;

    // Вернуть единственный оставшийся элемент (вызывать когда size == 1)
    int front() const;

    int getSize() const;

    // Вернуть указатель на голову (нужен для начального позиционирования в main)
    Node* getHead() const;
};
