#include <queue>
#include <stack>

#include "AdjacencyListGraph.h"

void BFS(const Graph& g, int start)
{
	if (!g.existsVertex(start))
		throw "Invalid vertex!";

	queue<int> q;
	vector<bool> visited(g.getVerticesCount());

	q.push(start);
	visited[start] = true;

	while (!q.empty())
	{
		int current = q.front();
		q.pop();

		cout << current << ' ';

		vector<pair<int, int>> adjacent = g.getSuccessors(current);

		for (size_t i = 0; i < adjacent.size(); i++)
		{
			if (visited[adjacent[i].first])
				continue;

			q.push(adjacent[i].first);
			visited[adjacent[i].first] = true;
		}
	}
}

// Замяната на опашка със стек НЕ НИ ДАВА коректен DFS !!
void DFS(const Graph& g, int start)
{
	if (!g.existsVertex(start))
		throw "Invalid vertex!";

	stack<int> s;
	vector<bool> visited(g.getVerticesCount());

	s.push(start);

	while (!s.empty())
	{
		int current = s.top();
		s.pop();

		if (visited[current])
			continue;
		visited[current] = true;

		cout << current << ' ';

		vector<pair<int, int>> adjacent = g.getSuccessors(current);

		for (size_t i = 0; i < adjacent.size(); i++)
			s.push(adjacent[i].first);
	}
}

void DFS_rec(const Graph& g, vector<bool>& visited, int currentVertex)
{
	visited[currentVertex] = true;
	cout << currentVertex << endl;

	vector<pair<int, int>> adjacent = g.getSuccessors(currentVertex);

	for (int i = 0; i < adjacent.size(); i++)
	{
		if (visited[adjacent[i].first])
			continue;

		DFS_rec(g, visited, adjacent[i].first);
	}
}
void DFSrec(const Graph& g, int start)
{
	if (!g.existsVertex(start))
		return;

	vector<bool> visited(g.getVerticesCount());
	DFS_rec(g, visited, start);
}

int main()
{
	AdjacencyListGraph g(8);

	// Графът от картинката на реализация 3 (Списък на ребра)
	g.addEdge(0, 5);
	g.addEdge(1, 0);
	g.addEdge(1, 3);
	g.addEdge(2, 0);
	g.addEdge(2, 3);
	g.addEdge(2, 4);
	g.addEdge(3, 7);
	g.addEdge(4, 2);
	g.addEdge(4, 5);
	g.addEdge(5, 4);
	g.addEdge(6, 1);
	g.addEdge(6, 3);
	g.addEdge(6, 7);
	g.addEdge(7, 6);

	cout << "The graph traversed with BFS starting with vertex 4:" << endl;
	BFS(g, 4);
	cout << endl << endl;

	cout << "The graph traversed with DFS starting with vertex 4:" << endl;
	DFS(g, 4);
	cout << endl;
}
