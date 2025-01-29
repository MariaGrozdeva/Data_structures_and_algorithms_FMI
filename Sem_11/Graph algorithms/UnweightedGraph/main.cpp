#include "GraphAlgorithms.h"
#include <iostream>

int main()
{
	Graph g(9, false);
	g.addEdge(0, 1);
	g.addEdge(0, 7);
	g.addEdge(1, 7);
	g.addEdge(1, 2);
	g.addEdge(7, 8);
	g.addEdge(7, 6);
	g.addEdge(8, 6);
	g.addEdge(8, 2);
	g.addEdge(2, 5);
	g.addEdge(6, 5);
	g.addEdge(2, 3);
	g.addEdge(3, 5);
	g.addEdge(3, 4);
	g.addEdge(5, 4);

	g.bfs(0);
}
