#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <set>
#include <queue>
#include <vector>
#include <map>

class Node;
typedef std::set<Node*>::const_iterator node_iterator;

// Класс Графа из лекции
class Graph {
    std::set<Node*> nodes;
public:
    void addNode(Node* node);
    void removeNode(Node* node);
    void addEdge(Node* begin, Node* end, int weight = 1);
    void removeEdge(Node* begin, Node* end);
    node_iterator begin() const { return nodes.begin(); }
    node_iterator end() const { return nodes.end(); }
};

// Класс Вершины (Узла)
class Node {
    std::string name;
    std::set<Node*> neighbours;
    std::map<Node*, int> weights; // Контейнер для хранения весов ребер
    void addNeighbour(Node* neighbour);
    void removeNeighbour(Node* neighbour);
public:
    Node(const std::string& aname) : name(aname) {}
    const std::string& getName() const { return name; }
    int getWeight(Node* neighbour) { return weights[neighbour]; }
    node_iterator nb_begin() const { return neighbours.begin(); }
    node_iterator nb_end() const { return neighbours.end(); }
    friend class Graph;
};

// Поиск в ширину (BFS)
class BFS {
    const Graph& graph;
public:
    BFS(const Graph& agraph) : graph(agraph) {}
    bool connected(Node* begin, Node* end);
};

// Поиск в глубину (DFS)
class DFS {
    const Graph& graph;
    std::set<Node*> visited;
    bool connected(Node* begin, Node* end, int depth);
public:
    DFS(const Graph& agraph) : graph(agraph) {}
    bool connected(Node* begin, Node* end);
};

// Структура для маркировки вершин в Дейкстре
struct MarkedNode {
    Node* node;
    int mark;
    Node* prev;
    MarkedNode(Node* anode = 0, int amark = 0, Node* aprev = 0) : node(anode), mark(amark), prev(aprev) {}
};

// Очередь с приоритетами для Дейкстры
class PriorityQueue {
    std::vector<MarkedNode> nodes;
public:
    MarkedNode pop();
    void push(Node* node, int mark, Node* prev);
    bool empty() const { return nodes.empty(); }
};

// Структура результирующего пути
struct Way {
    std::vector<Node*> nodes;
    int length;
    Way() : length(-1) {}
};

// Алгоритм Дейкстры
class Dijkstra {
    const Graph& graph;
public:
    Dijkstra(const Graph& agraph) : graph(agraph) {}
    Way shortestWay(Node* begin, Node* end);
};

#endif