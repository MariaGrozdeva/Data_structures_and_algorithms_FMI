#include "GraphAlgorithms.h"

#include <climits>
#include <iostream>
#include <queue>
#include <stdexcept>

Graph::Graph(size_t verticesCount, bool oriented) : adjList(verticesCount), oriented(oriented)
{}

void Graph::addEdge(unsigned start, unsigned end)
{
    if (start >= adjList.size() || end >= adjList.size())
    {
        return;
    }
    adjList[start].push_back(end);
    if (!oriented)
    {
        adjList[end].push_back(start);
    }
}

void Graph::bfs(unsigned start) const
{
    if (start >= adjList.size())
    {
        return;
    }
    
    std::vector<bool> visited(adjList.size(), false);
    std::queue<unsigned> q;
    
    q.push(start);
    visited[start] = true;
    
    while (!q.empty())
    {
        unsigned currVertex = q.front();
        q.pop();
        
        for (unsigned neighbor : adjList[currVertex])
        {
            if (visited[neighbor])
            {
                continue;
            }
            std::cout << neighbor << std::endl;
            q.push(neighbor);
            visited[neighbor] = true;
        }
    }
}

void Graph::bfsShortestPaths(unsigned start) const
{
    if (start >= adjList.size())
    {
        return;
    }
    std::vector<bool> visited(adjList.size(), false);
    std::queue<unsigned> q;
    
    q.push(start);
    visited[start] = true;
    
    unsigned dist = 0;
    
    while (!q.empty())
    {
        const size_t currentLevelSize = q.size();
        for (size_t i = 0; i < currentLevelSize; i++)
        {
            unsigned currVertex = q.front();
            q.pop();
        
            for (unsigned neighbor : adjList[currVertex])
            {
                if (visited[neighbor])
                {
                    continue;
                }
                std::cout << "Vertex: " << currVertex << ", path length: " << dist << std::endl;
                q.push(neighbor);
                visited[neighbor] = true;
            }
        }
        dist++;
    }
}

void Graph::dfsIter(unsigned start) const
{
    if (start >= adjList.size())
    {
        return;
    }
    std::vector<bool> visited(adjList.size(), false);
    std::stack<unsigned> s;
    
    s.push(start);
    
    while (!s.empty())
    {
        unsigned currVertex = s.top();
        s.pop();
            
        if (visited[currVertex])
        {
            continue;
        }
        visited[currVertex] = true;
        
        std::cout << "Vertex: " << currVertex << std::endl;
        
        for (unsigned neighbor : adjList[currVertex])
        {
            s.push(neighbor);
        }
    }
}

void Graph::dfsRec(unsigned start) const
{
    if (start >= adjList.size())
    {
        return;
    }
    std::vector<bool> visited(adjList.size(), false);
    dfsRec(start, visited);
}

void Graph::dfsRec(unsigned currVertex, std::vector<bool>& visited) const
{
    visited[currVertex] = true;
    std::cout << "Vertex: " << currVertex << std::endl;
    for (unsigned neighbor : adjList[currVertex])
    {
        if (!visited[neighbor])
        {
            dfsRec(neighbor, visited);
        }
    }
}

bool Graph::containsCycle() const
{
    std::vector<bool> visited(adjList.size(), false);
    std::vector<bool> inStack(adjList.size(), false);

    for (size_t i = 0; i < adjList.size(); i++)
    {
        if (!visited[i] && containsCycleRec(i, visited, inStack))
        {
            return true;
        }
    }
    return false;
}

bool Graph::containsCycleRec(unsigned currVertex, std::vector<bool>& visited, std::vector<bool>& s) const
{
    visited[currVertex] = true;
    s[currVertex] = true;
     
    for (unsigned neighbor : adjList[currVertex])
    {
        if (s[neighbor])
        {
            return true;
        }
        if (!visited[neighbor] && containsCycleRec(neighbor, visited, s))
        {
            return true;
        }
    }
    s[currVertex] = false;
    return false;
}
