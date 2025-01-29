#pragma once

#include <cstddef>
#include <stack>
#include <utility>
#include <vector>

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
