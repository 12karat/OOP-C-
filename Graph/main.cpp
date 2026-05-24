#include <iostream>
#include "graph.h"

int main() {
    Graph g;

    // Создаем вершины графа со слайдов лекции (0, 1, 2, 3, 4, 5)
    Node* n0 = new Node("0");
    Node* n1 = new Node("1");
    Node* n2 = new Node("2");
    Node* n3 = new Node("3");
    Node* n4 = new Node("4");
    Node* n5 = new Node("5");

    g.addNode(n0);
    g.addNode(n1);
    g.addNode(n2);
    g.addNode(n3);
    g.addNode(n4);
    g.addNode(n5);

    // Инициализируем ребра и веса в строгом соответствии со слайдом 10 лекции
    g.addEdge(n0, n1, 10);
    g.addEdge(n0, n3, 20);
    g.addEdge(n0, n5, 50);
    g.addEdge(n1, n3, 10);
    g.addEdge(n1, n2, 15);
    g.addEdge(n2, n4, 5);
    g.addEdge(n2, n5, 30);
    g.addEdge(n3, n4, 25);
    g.addEdge(n4, n5, 15);

    // Проверка работы BFS (выведет 1, если путь есть)
    BFS bfs(g);
    std::cout << "BFS Connected (0 -> 5): " << bfs.connected(n0, n5) << std::endl;

    // Проверка работы DFS (выведет 1, если путь есть)
    DFS dfs(g);
    std::cout << "DFS Connected (0 -> 5): " << dfs.connected(n0, n5) << std::endl;

    // Проверка работы алгоритма Дейкстры
    Dijkstra dijkstra(g);
    Way way = dijkstra.shortestWay(n0, n5);

    // Вывод длины пути и самого маршрута (только латиница и цифры)
    std::cout << "Dijkstra shortest length: " << way.length << std::endl;
    std::cout << "Path: ";
    for (Node* n : way.nodes) {
        std::cout << n->getName() << " ";
    }
    std::cout << std::endl;

    // Освобождение динамической памяти
    delete n0; delete n1; delete n2; delete n3; delete n4; delete n5;

    return 0;
}