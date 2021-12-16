#include "AdjacencyMatrixGraph.h"

AdjacencyMatrixGraph::AdjacencyMatrixGraph(int verticesCount, bool oriented) : Graph(verticesCount, oriented), adjMatrix(verticesCount)
{
	vector<int> templateVector(verticesCount);

	for (size_t i = 0; i < verticesCount; i++)
		adjMatrix[i] = templateVector;
}

int AdjacencyMatrixGraph::addVertex()
{
	adjMatrix.push_back(vector<int>(++verticesCount));

	for (size_t i = 0; i < verticesCount - 1; i++)
		adjMatrix[i].push_back(0);

	return verticesCount - 1;
}
void AdjacencyMatrixGraph::removeVertex(int vertex)
{
	if (!existsVertex(vertex))
		throw "Invalid vertex!";

	adjMatrix.erase(adjMatrix.begin() + vertex);

	verticesCount--;

	for (size_t i = 0; i < verticesCount; i++)
		adjMatrix[i].erase(adjMatrix[i].begin() + vertex);
}

void AdjacencyMatrixGraph::addEdge(int start, int end, int weight)
{
	if (!existsVertex(start) || !existsVertex(end))
		throw "Invalid vertices!";

	adjMatrix[start][end] = weight;
	if (!oriented)
		adjMatrix[end][start] = weight;
}
void AdjacencyMatrixGraph::removeEdge(int start, int end)
{
	if (!existsVertex(start) || !existsVertex(end))
		throw "Invalid vertices!";

	adjMatrix[start][end] = 0;
	if (!oriented)
		adjMatrix[end][start] = 0;
}

vector<pair<int, int>> AdjacencyMatrixGraph::getSuccessors(int vertex) const
{
	if (!existsVertex(vertex))
		throw "Invalid vertex!";

	vector<pair<int, int>> successors;

	for (size_t i = 0; i < verticesCount; i++)
	{
		if (adjMatrix[vertex][i] > 0)
			successors.push_back(make_pair(i, adjMatrix[vertex][i]));
	}
	return successors;
}
vector<pair<int, int>> AdjacencyMatrixGraph::getPredecessors(int vertex) const
{
	if (!existsVertex(vertex))
		throw "Invalid vertex!";

	vector<pair<int, int>> predecessors;

	for (size_t i = 0; i < verticesCount; i++)
	{
		if (adjMatrix[i][vertex] > 0)
			predecessors.push_back(make_pair(i, adjMatrix[i][vertex]));
	}
	return predecessors;
}

bool AdjacencyMatrixGraph::adjacent(int vertex1, int vertex2) const
{
	if (!existsVertex(vertex1) || !!existsVertex(vertex2))
		throw "Invalid vertices!";

	return adjMatrix[vertex1][vertex2] > 0;
}