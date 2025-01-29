#pragma once

#include <cstddef>
#include <stack>
#include <tuple>
#include <utility>
#include <vector>

using Edge = std::tuple<unsigned, unsigned, int>;

class WeightedGraph
{
public:
    WeightedGraph(size_t verticesCount, bool oriented);
    void addEdge(unsigned start, unsigned end, int weight);

    void dijkstra(unsigned start, std::vector<unsigned>& distances) const;
    
    void bellmanFord(unsigned start, std::vector<int>& distances) const;
    
    int prim(std::vector<Edge>& mst) const;
    
    int kruskal(std::vector<Edge>& mst) const;

private:
    std::vector<std::vector<std::pair<unsigned, int>>> adjList;
    bool oriented;
};
