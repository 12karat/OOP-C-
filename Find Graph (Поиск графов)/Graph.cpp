#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>

// Node constructors
Node::Node() : id(-1) {}
Node::Node(int node_id) : id(node_id) {}

// Graph constructors
Graph::Graph() {}

Graph::Graph(const std::string& file_name) {
    std::ifstream file(file_name);
    if (!file.is_open()) {
        // Vyvod oshibki, esli fajl ne najden
        std::cerr << "Error: Could not open file " << file_name << std::endl;
        return;
    }

    std::string line;
    // Propuskaem pervuyu stroku (zagolovok), chto by tam ni bylo: tabs, spaces ili commas
    if (!std::getline(file, line)) {
        file.close();
        return;
    }

    // Chtenie par reber
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        // Zamenyaem zapyatye na probely, esli eto CSV, dlya edinogo formata chteniya
        for (size_t i = 0; i < line.length(); ++i) {
            if (line[i] == ',') {
                line[i] = ' ';
            }
        }

        std::stringstream ss(line);
        int source, target;
        // Stringstream prekrasno chitaet i cherez probely, i cherez taby
        if (ss >> source >> target) {
            add_edge(source, target);
        }
    }
    file.close();
}

void Graph::add_edge(int source, int target) {
    // Esli vershiny net v mape, sozdaem ee
    if (nodes.find(source) == nodes.end()) {
        nodes[source] = Node(source);
    }
    if (nodes.find(target) == nodes.end()) {
        nodes[target] = Node(target);
    }

    // Neorientirovannyj graf: dobavlyaem svyazi v obe storony
    nodes[source].neighbors.push_back(target);
    nodes[target].neighbors.push_back(source);
}

std::set<int> Graph::bfs(int start_id, std::set<int>& visited) {
    std::set<int> component_nodes;
    std::queue<int> q;

    q.push(start_id);
    visited.insert(start_id);

    while (!q.empty()) {
        int current_id = q.front();
        q.pop();
        component_nodes.insert(current_id);

        // Proverka sosedej
        for (int neighbor : nodes[current_id].neighbors) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                q.push(neighbor);
            }
        }
    }

    return component_nodes;
}

void Graph::find_and_save_components(const std::string& base_output_name) {
    std::set<int> visited;
    int component_count = 0;

    // Prohodim po vsem vershinam grafa
    for (auto const& [node_id, node_obj] : nodes) {
        // Esli vershina esche ne posessena, eto nachalo novogo neperesekayuschegosya grafa
        if (visited.find(node_id) == visited.end()) {
            component_count++;

            // Zapuskaem BFS dlya sbora vsej komponenty svyaznosti
            std::set<int> component_nodes = bfs(node_id, visited);

            // Formiruem imya vyhodnogo fajla (naprimer, test_component_1.txt)
            std::string output_file_name = base_output_name + "_" + std::to_string(component_count) + ".txt";
            std::ofstream out_file(output_file_name);

            if (!out_file.is_open()) {
                std::cerr << "Error: Could not create output file " << output_file_name << std::endl;
                continue;
            }

            // Zapisyvaem standartnyj zagolovok
            out_file << "Source,Target\n";

            // Set dlya otslezhivaniya uzhe zapisannyh reber (chtoby izbezhat' dublej u-v i v-u)
            std::set<std::pair<int, int>> written_edges;

            // Zapisyvaem tol'ko te rebra, kotorye prinadlezhat etoj komponente
            for (int u : component_nodes) {
                for (int v : nodes[u].neighbors) {
                    int src = std::min(u, v);
                    int tgt = std::max(u, v);

                    if (written_edges.find({ src, tgt }) == written_edges.end()) {
                        out_file << src << "," << tgt << "\n";
                        written_edges.insert({ src, tgt });
                    }
                }
            }

            out_file.close();
            std::cout << "Component " << component_count << " saved with " << component_nodes.size() << " nodes to " << output_file_name << std::endl;
        }
    }
    std::cout << "Total independent graphs found: " << component_count << std::endl;
}