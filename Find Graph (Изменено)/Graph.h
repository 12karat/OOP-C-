#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <map>
#include <set>

// Структура узла графа
struct Node {
    int id;
    std::vector<int> neighbors;

    Node();
    Node(int node_id);
};

// Класс Графа
class Graph {
private:
    std::map<int, Node> nodes;

public:
    Graph();
    Graph(const std::string& file_name);

    void add_edge(int source, int target);

    // ИЗМЕНЕНИЕ 1: Добавлен геттер для внешних функций
    // БЫЛО: Этого метода вообще не было в классе.
    // СТАЛО: Добавлен константный геттер, чтобы внешние функции bfs и find_components 
    //        могли получить доступ к приватной мапе nodes.
    const std::map<int, Node>& get_nodes() const;

    // ИЗМЕНЕНИЕ 2: Функции убраны из класса
    // БЫЛО: Внутри класса (вот здесь) находились объявления:
    //       std::set<int> bfs(int start_id, std::set<int>& visited);
    //       void find_and_save_components(const std::string& base_output_name);
    //
    // СТАЛО: Изнутри класса они полностью удалены.
};

// ИЗМЕНЕНИЕ 3: Объявление внешних функций под классом
// БЫЛО: Функции были частью класса (методами).
// СТАЛО: Теперь это самостоятельные функции. Они принимают объект Graph как параметр.
//        Функция поиска компонент теперь возвращает вектор графов std::vector<Graph> вместо void.

// Внешний BFS (принимает объект graph со стороны)
std::set<int> bfs(int start_id, const Graph& graph, std::set<int>& visited);

// Внешняя функция поиска компонент (возвращает ВЕКТОР ГРАФОВ)
std::vector<Graph> find_components(const Graph& main_graph);

#endif // GRAPH_H