#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>

class Graph
{
public:
    unsigned n;
    unsigned number_of_edges;
    std::string graph_name;
    std::vector<std::pair<int, int>> edges;

    explicit Graph(std::string file_name);
    void filename(std::string &path);
    void print_stat() const;

    int calculate_antibandwidth(const std::vector<int> &node_labels) const;
    int calculate_bandwidth(const std::vector<int> &node_labels) const;
    int calculate_cyclic_antibandwidth(const std::vector<int> &node_labels) const;

    unsigned find_greatest_outdegree_node() const;
    unsigned find_smallest_outdegree_node() const;
};

#endif // GRAPH_H