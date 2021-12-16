#include "AdjacencyListGraph.h"

AdjacencyListGraph::AdjacencyListGraph(int verticesCount, bool oriented) :
	Graph(verticesCount, oriented), adjList(verticesCount)
{}

int AdjacencyListGraph::addVertex()
{
	adjList.push_back(list<Edge>());
	verticesCount++;

	return verticesCount - 1;
}
void AdjacencyListGraph::removeVertex(int vertex)
{
	if (!existsVertex(vertex))
		throw "Invalid vertex!";

	adjList.erase(adjList.begin() + vertex);
	verticesCount--;

	for (size_t i = 0; i < verticesCount; i++)
	{
		for (auto it = adjList[i].begin(); it != adjList[i].end();)
		{
			if (it->end == vertex)
				it = adjList[i].erase(it);
			else
			{
				if (it->end > vertex)
					it->end--;
				it++;
			}
		}
	}
}

void AdjacencyListGraph::addEdge(int start, int end, int weight)
{
	if (!existsVertex(start))
		throw "Invalid vertex!";

	adjList[start].push_back({ end, weight });
	if (!oriented)
		adjList[end].push_back({ start, weight });
}
void AdjacencyListGraph::removeEdge(int start, int end)
{
	if (!existsVertex(start) || !existsVertex(end))
		throw "Invalid vertices!";

	for (auto it = adjList[start].begin(); it != adjList[start].end();)
	{
		if (it->end == end)
			it = adjList[start].erase(it);
		else
			it++;
	}

	if (oriented)
		return;

	for (auto it = adjList[end].begin(); it != adjList[end].end();)
	{
		if (it->end == start)
			it = adjList[end].erase(it);
		else
			it++;
	}
}

vector<pair<int, int>> AdjacencyListGraph::getSuccessors(int vertex) const
{
	vector<pair<int, int>> successors;

	for (auto it = adjList[vertex].begin(); it != adjList[vertex].end(); it++)
		successors.push_back(make_pair(it->end, it->weight));

	return successors;
}
vector<pair<int, int>> AdjacencyListGraph::getPredecessors(int vertex) const
{
	vector<pair<int, int>> predecessors;

	for (size_t i = 0; i < verticesCount; i++)
	{
		for (auto it = adjList[i].begin(); it != adjList[i].end(); it++)
		{
			if (it->end == vertex)
				predecessors.push_back(make_pair(i, it->weight));
		}
	}
	return predecessors;
}

bool AdjacencyListGraph::adjacent(int vertex1, int vertex2) const
{
	if (!existsVertex(vertex1) || !existsVertex(vertex2))
		throw "Invalid vertices!";

	for (auto it = adjList[vertex1].begin(); it != adjList[vertex1].end(); it++)
	{
		if (it->end == vertex2)
			return true;
	}
	return false;
}

void AdjacencyListGraph::getEdges(vector<tuple<int, int, int>>& edges) const
{
	for (int i = 0; i < adjList.size(); i++)
	{
		for (auto it = adjList[i].begin(); it != adjList[i].end(); ++it)
			edges.push_back(make_tuple(i, it->end, it->weight));
	}
}

AdjacencyListGraph AdjacencyListGraph::getTransposedGraph() const
{
	AdjacencyListGraph transposedGraph(verticesCount);

	for (size_t i = 0; i < adjList.size(); i++)
	{
		for (auto j = adjList[i].begin(); j != adjList[i].end(); j++)
			transposedGraph.addEdge((*j).end, i, (*j).weight);
	}

	return move(transposedGraph);
}