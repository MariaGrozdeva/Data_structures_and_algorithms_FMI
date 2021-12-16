#include "EdgeListGraph.h"

EdgeListGraph::EdgeListGraph(int verticesCount, bool oriented) : Graph(verticesCount, oriented)
{}

int EdgeListGraph::addVertex()
{
	verticesCount++;
	return verticesCount - 1;
}
void EdgeListGraph::removeVertex(int vertex)
{
	if (!existsVertex(vertex))
		throw "Invalid vertex!";

	for (auto it = edgeList.begin(); it != edgeList.end();)
	{
		if (it->start == vertex || it->end == vertex)
			it = edgeList.erase(it);
		else
		{
			if (it->start > vertex)
				it->start--;
			if (it->end > vertex)
				it->end--;

			++it;
		}
	}
	verticesCount--;
}

void EdgeListGraph::addEdge(int start, int end, int weight)
{
	if (!existsVertex(start) || !existsVertex(end))
		throw "Invalid vertices!";

	edgeList.push_back({ start, end, weight });
	if (!oriented)
		edgeList.push_back({ end, start, weight });
}
void EdgeListGraph::removeEdge(int start, int end)
{
	for (auto it = edgeList.begin(); it != edgeList.end();)
	{
		if (it->start == start && it->end == end)
			it = edgeList.erase(it);
		else
			++it;
	}
}

vector<pair<int, int>> EdgeListGraph::getSuccessors(int vertex) const
{
	vector<pair<int, int>> successors;

	for (auto it = edgeList.begin(); it != edgeList.end(); ++it)
	{
		if (it->start == vertex)
			successors.push_back(make_pair(it->end, it->weight));
	}
	return successors;
}
vector<pair<int, int>> EdgeListGraph::getPredecessors(int vertex) const
{
	vector<pair<int, int>> predecessors;

	for (auto it = edgeList.begin(); it != edgeList.end(); ++it)
	{
		if (it->end == vertex)
			predecessors.push_back(make_pair(it->start, it->weight));
	}
	return predecessors;
}

bool EdgeListGraph::adjacent(int vertex1, int vertex2) const
{
	for (auto it = edgeList.begin(); it != edgeList.end(); ++it)
	{
		if (it->start == vertex1 && it->end == vertex2)
			return true;
	}
	return false;
}
