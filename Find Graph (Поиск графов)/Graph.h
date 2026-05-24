#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <map>
#include <set>

// Struct representing a graph node
struct Node {
    int id;
    std::vector<int> neighbors;

    Node();
    Node(int node_id);
};

// Class representing the Graph
class Graph {
private:
    // Using map to handle arbitrary and non-sequential node IDs easily
    std::map<int, Node> nodes;

public:
    Graph();
    // Constructor to load graph from a file (supports both CSV and TXT)
    Graph(const std::string& file_name);

    void add_edge(int source, int target);

    // BFS algorithm to find all nodes in the same component
    std::set<int> bfs(int start_id, std::set<int>& visited);

    // Method to find all disconnected components and save them to separate files
    void find_and_save_components(const std::string& base_output_name);
};

#endif // GRAPH_H