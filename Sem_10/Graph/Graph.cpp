#include "Graph.h"

int Graph::getVerticesCount() const
{
	return verticesCount;
}
bool Graph::isOriented() const
{
	return oriented;
}
bool Graph::existsVertex(int vertex) const
{
	return vertex < verticesCount;
}

vector<pair<int, int>> Graph::adjacent(int vertex) const
{
	if (oriented)
		throw "Use getSuccessors() or getPredecessors()";

	return getSuccessors(vertex);
}