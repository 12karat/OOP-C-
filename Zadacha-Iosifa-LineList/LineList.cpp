#include "LineList.h"
#include <stdexcept>

// --- Конструктор / деструктор ---

LineList::LineList() : head(nullptr), size(0) {}

LineList::~LineList() {
    if (!head) return;

    // Список кольцевой, поэтому разрываем кольцо перед удалением
    Node* tail = head;
    while (tail->next != head) {
        tail = tail->next;
    }
    tail->next = nullptr; // разрываем кольцо

    Node* cur = head;
    while (cur) {
        Node* tmp = cur->next;
        delete cur;
        cur = tmp;
    }
}

// --- Добавление элемента в конец ---

void LineList::pushBack(int val) {
    Node* newNode = new Node(val);
    if (!head) {
        head = newNode;
        head->next = head; // кольцо из одного элемента
    } else {
        // Находим хвост (тот, чей next == head)
        Node* tail = head;
        while (tail->next != head) {
            tail = tail->next;
        }
        tail->next = newNode;
        newNode->next = head; // замыкаем кольцо
    }
    ++size;
}

// --- Удаление узла, следующего за prev ---

int LineList::removeAfter(Node* prev) {
    if (!prev || size == 0) {
        throw std::runtime_error("Cannot remove: list is empty or prev is null");
    }

    Node* toDelete = prev->next;  // узел, который нужно удалить
    int   retVal   = toDelete->value;

    if (size == 1) {
        // Единственный элемент - удаляем и обнуляем head
        delete toDelete;
        head = nullptr;
    } else {
        prev->next = toDelete->next; // «перепрыгиваем» удаляемый узел
        if (toDelete == head) {
            head = toDelete->next;   // если удалили head, переносим голову
        }
        delete toDelete;
    }
    --size;
    return retVal;
}

// --- Продвижение по кольцу на steps шагов от current ---

Node* LineList::advance(Node* current, int steps) const {
    for (int i = 0; i < steps; ++i) {
        current = current->next;
    }
    return current;
}

// --- Возврат значения единственного оставшегося элемента ---

int LineList::front() const {
    if (!head) {
        throw std::runtime_error("List is empty");
    }
    return head->value;
}

// --- Размер списка ---

int LineList::getSize() const {
    return size;
}

// --- Возврат указателя на голову ---

Node* LineList::getHead() const {
    return head;
}
