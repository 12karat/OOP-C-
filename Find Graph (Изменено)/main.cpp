#include "Graph.h"
#include <iostream>
#include <fstream>
#include <algorithm>

// ИЗМЕНЕНИЕ 7: Добавлена функция сохранения графа в файл
// БЫЛО: Этой функции в main.cpp не было, логика записи строк была внутри класса Graph.
// СТАЛО: Новая функция, которая берёт готовый объект Graph и записывает его структуру в файл.
void save_graph_to_file(const Graph& graph, const std::string& file_name) {
    std::ofstream out_file(file_name);
    if (!out_file.is_open()) {
        std::cerr << "Error: Could not create file " << file_name << std::endl;
        return;
    }

    out_file << "Source,Target\n";
    std::set<std::pair<int, int>> written_edges;

    for (auto const& [u, node_obj] : graph.get_nodes()) {
        for (int v : node_obj.neighbors) {
            int src = std::min(u, v);
            int tgt = std::max(u, v);

            if (written_edges.find({ src, tgt }) == written_edges.end()) {
                out_file << src << "," << tgt << "\n";
                written_edges.insert({ src, tgt });
            }
        }
    }
    out_file.close();
}

int main() {
    // Тестовая задача IV
    std::cout << "--- Processing Test Graph ---" << std::endl;
    Graph test_graph("TestGraph.txt");

    // ИЗМЕНЕНИЕ 8: Изменение логики вызова в main
    // БЫЛО: test_graph.find_and_save_components("test_component");
    //       (метод сам всё искал и сам создавал файлы)
    //
    // СТАЛО: Вызываем внешнюю функцию, получаем вектор графов, а затем в цикле 
    //        сохраняем каждый граф через новую функцию save_graph_to_file.
    std::vector<Graph> test_components = find_components(test_graph);

    for (size_t i = 0; i < test_components.size(); ++i) {
        std::string filename = "test_component_" + std::to_string(i + 1) + ".txt";
        save_graph_to_file(test_components[i], filename);
        std::cout << "Component " << (i + 1) << " saved to " << filename << std::endl;
    }
    std::cout << "Total independent graphs found: " << test_components.size() << "\n" << std::endl; 

    // Основная задача V
    std::cout << "--- Processing Main Graph (1000.csv) ---" << std::endl;
    Graph main_graph("1000.csv");

    // Точно так же обрабатываем основной граф через вектор
    std::vector<Graph> main_components = find_components(main_graph);

    for (size_t i = 0; i < main_components.size(); ++i) {
        std::string filename = "main_component_" + std::to_string(i + 1) + ".txt";
        save_graph_to_file(main_components[i], filename);
    }
    std::cout << "Total independent graphs found: " << main_components.size() << std::endl;

    return 0;
}