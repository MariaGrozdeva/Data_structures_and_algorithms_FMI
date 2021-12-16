#pragma once

#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Graph
{
protected:
	int verticesCount;
	bool oriented;

public:
	Graph(int verticesCount, bool oriented) : verticesCount(verticesCount), oriented(oriented) 
	{}

	int getVerticesCount() const;
	bool isOriented() const;
	bool existsVertex(int vertex) const;

	virtual int addVertex() = 0;
	virtual void removeVertex(int vertex) = 0;

	virtual void addEdge(int start, int end, int weight = 1) = 0;
	virtual void removeEdge(int start, int end) = 0;

	virtual vector<pair<int, int>> getSuccessors(int vertex) const = 0;
	virtual vector<pair<int, int>> getPredecessors(int vertex) const = 0;
	virtual vector<pair<int, int>> adjacent(int vertex) const;
};