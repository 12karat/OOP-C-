#include "Graph.h"
#include <iostream>

int main() {
    // Testovaya zadacha IV: TestGraph.txt
    std::cout << "--- Processing Test Graph ---" << std::endl;
    Graph test_graph("TestGraph.txt");
    test_graph.find_and_save_components("test_component");

    std::cout << std::endl;

    // Osnovnaya zadacha V: 1000.csv
    std::cout << "--- Processing Main Graph (1000.csv) ---" << std::endl;
    Graph main_graph("1000.csv");
    main_graph.find_and_save_components("main_component");

    return 0;
}