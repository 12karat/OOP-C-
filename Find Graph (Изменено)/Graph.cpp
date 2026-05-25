#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>

// Конструкторы Node
Node::Node() : id(-1) {}
Node::Node(int node_id) : id(node_id) {}

// Конструкторы и методы Graph
Graph::Graph() {}

Graph::Graph(const std::string& file_name) {
    std::ifstream file(file_name);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << file_name << std::endl;
        return;
    }

    std::string line;
    if (!std::getline(file, line)) {
        file.close();
        return;
    }

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        for (size_t i = 0; i < line.length(); ++i) {
            if (line[i] == ',') {
                line[i] = ' ';
            }
        }

        std::stringstream ss(line);
        int source, target;
        if (ss >> source >> target) {
            add_edge(source, target);
        }
    }
    file.close();
}

void Graph::add_edge(int source, int target) {
    if (nodes.find(source) == nodes.end()) {
        nodes[source] = Node(source);
    }
    if (nodes.find(target) == nodes.end()) {
        nodes[target] = Node(target);
    }
    nodes[source].neighbors.push_back(target);
    nodes[target].neighbors.push_back(source);
}

// ИЗМЕНЕНИЕ №4: Реализация геттера
// БЫЛО: Этого метода не существовало.
// СТАЛО: Метод просто возвращает нашу приватную мапу вершин.
const std::map<int, Node>& Graph::get_nodes() const {
    return nodes;
}

// ИЗМЕНЕНИЕ 5: Переделка функции BFS в свободную функцию
// БЫЛО: std::set<int> Graph::bfs(int start_id, std::set<int>& visited) { ... }
//       (функция была методом класса и напрямую использовала приватную мапу nodes)
//
// СТАЛО: Функция больше не принадлежит классу (нет Graph::). 
//        Она принимает const Graph& graph и берёт мапу nodes через геттер.
std::set<int> bfs(int start_id, const Graph& graph, std::set<int>& visited) {
    std::set<int> component_nodes;
    std::queue<int> q;

    q.push(start_id);
    visited.insert(start_id);

    // Получаем мапу вершин через геттер, так как мы теперь вне класса
    const auto& nodes = graph.get_nodes();

    while (!q.empty()) {
        int current_id = q.front();
        q.pop();
        component_nodes.insert(current_id);

        auto it = nodes.find(current_id);
        if (it != nodes.end()) {
            for (int neighbor : it->second.neighbors) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
    }
    return component_nodes;
}

// ИЗМЕНЕНИЕ 6: Полная перестройка функции поиска компонент
// БЫЛО: 
// void Graph::find_and_save_components(const std::string& base_output_name) {
//     ... внутри функции создавался файл std::ofstream out_file(...) и туда писался текст ...
// }
//
// СТАЛО: Функция теперь называется find_components, возвращает std::vector<Graph> 
//        и вместо работы с файлами создает новые объекты Graph и наполняет их ребрами.
std::vector<Graph> find_components(const Graph& main_graph) {
    std::vector<Graph> isolated_graphs; // Вектор, который мы вернем наружу
    std::set<int> visited;

    const auto& main_nodes = main_graph.get_nodes();

    for (auto const& [node_id, node_obj] : main_nodes) {
        if (visited.find(node_id) == visited.end()) {

            // Вызываем наш обновленный внешний BFS
            std::set<int> component_nodes = bfs(node_id, main_graph, visited);

            // Создаем НОВЫЙ изолированный объект Графа для этой компоненты
            Graph component_graph;

            // Заполняем этот новый граф ребрами
            std::set<std::pair<int, int>> processed_edges;
            for (int u : component_nodes) {
                auto it = main_nodes.find(u);
                if (it != main_nodes.end()) {
                    for (int v : it->second.neighbors) {
                        int src = std::min(u, v);
                        int tgt = std::max(u, v);

                        if (processed_edges.find({ src, tgt }) == processed_edges.end()) {
                            // Добавляем ребро в наш новый мини-граф
                            component_graph.add_edge(src, tgt);
                            processed_edges.insert({ src, tgt });
                        }
                    }
                }
            }
            // Кладём готовый изолированный граф в вектор
            isolated_graphs.push_back(component_graph);
        }
    }

    return isolated_graphs; // Возвращаем вектор графов наружу
}