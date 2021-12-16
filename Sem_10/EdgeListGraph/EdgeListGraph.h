#include "Graph.h"

class EdgeListGraph : public Graph
{
private:
	struct Edge
	{
		int start;
		int end;
		int weight;
	};

	list<Edge> edgeList;

public:
	EdgeListGraph(int numOfVertices, bool oriented = true);

	int addVertex();
	void removeVertex(int vertex);

	void addEdge(int start, int end, int weight = 1);
	void removeEdge(int start, int end);

	vector<pair<int, int>> getSuccessors(int vertex) const;
	vector<pair<int, int>> getPredecessors(int vertex) const;

	bool adjacent(int vertex1, int vertex2) const; // O(m)
};