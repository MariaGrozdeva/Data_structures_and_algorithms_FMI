#include "GraphAlgorithms.h"
#include "UnionFind/UnionFind.h"

#include <climits>
#include <iostream>
#include <queue>
#include <stdexcept>

WeightedGraph::WeightedGraph(size_t verticesCount, bool oriented) : adjList(verticesCount), oriented(oriented)
{}

void WeightedGraph::addEdge(unsigned start, unsigned end, int weight)
{
    if (start >= adjList.size() || end >= adjList.size())
    {
        return;
    }
    adjList[start].push_back(std::make_pair(end, weight));
    if (!oriented)
    {
        adjList[end].push_back(std::make_pair(start, weight));
    }
}

void WeightedGraph::dijkstra(unsigned start, std::vector<unsigned>& distances) const
{
    distances.resize(adjList.size(), UINT_MAX);
    distances[start] = 0;

    auto comparator = [&distances](const unsigned& lhs, const unsigned& rhs) {
        return distances[lhs] > distances[rhs];
    };
    std::priority_queue<unsigned, std::vector<unsigned>, decltype(comparator)> q(comparator);

    q.push(start);

    while (!q.empty())
    {
	unsigned currVertex = q.top();
	q.pop();
	    
	for (const auto& [currNeighbor, currEdgeWeight] : adjList[currVertex])
	{
	    if (distances[currNeighbor] > distances[currVertex] + currEdgeWeight)
	    {
		    distances[currNeighbor] = distances[currVertex] + currEdgeWeight;
		    q.push(currNeighbor);
	    }
	}
    }
}

void WeightedGraph::bellmanFord(unsigned start, std::vector<int>& distances) const
{
    distances.resize(adjList.size(), INT_MAX);
    distances[start] = 0;
    
    for (size_t phase = 0; phase < adjList.size(); phase++)
    {
        bool isLastPhase = phase == adjList.size() - 1;
        
        for (size_t i = 0; i < adjList.size(); i++)
        {
            if (distances[i] == INT_MAX)
            {
                continue;
            }
            
            unsigned currVertex = i;
            for (size_t j = 0; j < adjList[currVertex].size(); j++)
            {
                unsigned currNeighbor = adjList[currVertex][j].first;
                int currEdgeWeight = adjList[currVertex][j].second;
                if (distances[currNeighbor] > distances[currVertex] + currEdgeWeight)
                {
                    if (isLastPhase)
                    {
                        distances[currNeighbor] = INT_MAX;
                        throw std::logic_error("Negative cycle detected!");
                    }
                    distances[currNeighbor] = distances[currVertex] + currEdgeWeight;
                }
            }
        }
    }
}

int WeightedGraph::prim(std::vector<Edge>& mst) const
{
	int mstWeight = 0;
	size_t addedEdges = 0;

	std::vector<bool> visited(adjList.size(), false);

	auto comp = [](const Edge& lhs, const Edge& rhs) { return std::get<2>(lhs) > std::get<2>(rhs); };
	std::priority_queue<Edge, std::vector<Edge>, decltype(comp)> q(comp);

	q.push(std::make_tuple(0, 0, 0)); // virtual edge for the start

	while (addedEdges < adjList.size() - 1)
	{
		auto currentEdge = q.top();
		q.pop();

		unsigned currentEdgeStart = std::get<0>(currentEdge);
		unsigned currentEdgeEnd = std::get<1>(currentEdge);
		int currentEdgeWeight = std::get<2>(currentEdge);

		if (visited[currentEdgeEnd])
		{
			continue;
		}

		mstWeight += currentEdgeWeight;

		if (currentEdgeStart != currentEdgeEnd) // in order not to count the virtual edge
		{
			addedEdges++;
			mst.emplace_back(currentEdgeStart, currentEdgeEnd, currentEdgeWeight);
		}
		visited[currentEdgeEnd] = true;

                for (const auto& [currNeighbor, currEdgeWeight] : adjList[currentEdgeEnd])
                {
                        q.push({ currentEdgeEnd, currNeighbor, currEdgeWeight });
                }
	}
	return mstWeight;
}

int WeightedGraph::kruskal(std::vector<Edge>& mst) const
{
	int mstWeight = 0;
	size_t addedEdges = 0;

	std::vector<Edge> edges;
        for (size_t i = 0; i < adjList.size(); ++i)
        {
                for (const auto& [neighbor, weight] : adjList[i])
                {
                        edges.emplace_back(i, neighbor, weight);
                }
        }
	std::sort(edges.begin(), edges.end(), [](const Edge& lhs, const Edge& rhs) { return std::get<2>(lhs) < std::get<2>(rhs); });

	UnionFind uf(adjList.size());

	for (size_t i = 0; addedEdges < adjList.size() - 1; i++)
	{
		auto currentEdge = edges[i];
		
		unsigned currentEdgeStart = std::get<0>(currentEdge);
		unsigned currentEdgeEnd = std::get<1>(currentEdge);
		int currentEdgeWeight = std::get<2>(currentEdge);

		if (!uf.Union(currentEdgeStart, currentEdgeEnd)) // If edge "start---end" is added, it will form a cycle
		{
			continue;
		}

		mst.emplace_back(currentEdgeStart, currentEdgeEnd, currentEdgeWeight);
		mstWeight += currentEdgeWeight;
		addedEdges++;
	}

	return mstWeight;
}
