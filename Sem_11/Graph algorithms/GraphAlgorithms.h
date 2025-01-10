#pragma once

#include <vector>
#include <stack>
#include <queue>
#include <utility>

class Graph
{
public:
    Graph(size_t verticesCount, bool oriented);
    void addEdge(unsigned start, unsigned end);

    void bfs(unsigned start) const;

    void bfsShortestPaths(unsigned start) const;
    
    void dfsIter(unsigned start) const;
    void dfsRec(unsigned start) const;

    bool containsCycle() const;

private:
    void dfsRec(unsigned currVertex, std::vector<bool>& visited) const;
    bool containsCycleRec(unsigned currVertex, std::vector<bool>& visited, std::vector<bool>& s) const;
    
    std::vector<std::vector<unsigned>> adjList;
    bool oriented;
};

class WeightedGraph
{
public:
    WeightedGraph(size_t verticesCount, bool oriented);
    void addEdge(unsigned start, unsigned end, int weight);

    void dijkstra(unsigned start, std::vector<unsigned>& distances) const;
    
    void bellmanFord(unsigned start, std::vector<int>& distances) const;

private:
    std::vector<std::vector<std::pair<unsigned, int>>> adjList;
    bool oriented;
};

