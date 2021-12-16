#include "Graph.h"

class AdjacencyMatrixGraph : public Graph
{
private:
	vector<vector<int>> adjMatrix;

public:
	AdjacencyMatrixGraph(int numOfVertices, bool oriented = true);

	int addVertex();
	void removeVertex(int vertex);

	void addEdge(int start, int end, int weight = 1);
	void removeEdge(int start, int end);

	vector<pair<int, int>> getSuccessors(int vertex) const;
	vector<pair<int, int>> getPredecessors(int vertex) const;

	bool adjacent(int vertex1, int vertex2) const; // O(1)
};