#include "Graph.h"

class AdjacencyListGraph : public Graph
{
private:
	struct Edge
	{
		int end;
		int weight;
	};

	vector<list<Edge>> adjList;

public:
	AdjacencyListGraph(int numOfVertices, bool oriented = true);

	int addVertex();
	void removeVertex(int vertex);

	void addEdge(int start, int end, int weight = 1);
	void removeEdge(int start, int end);

	vector<pair<int, int>> getSuccessors(int vertex) const;
	vector<pair<int, int>> getPredecessors(int vertex) const;

	bool adjacent(int vertex1, int vertex2) const; // O(n)

	AdjacencyListGraph getTransposedGraph() const; // O(n+m)
};