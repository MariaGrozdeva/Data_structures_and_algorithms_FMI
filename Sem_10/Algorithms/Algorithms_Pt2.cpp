#include <queue>
#include "AdjacencyListGraph.h"

bool BFS_isBipartite(const Graph& g, vector<int>& visited, int start)
{
	queue<int> q;
	q.push(start);
	visited[start] = true;

	while (!q.empty())
	{
		int current = q.front();
		q.pop();

		vector<pair<int, int>> adjacent = g.getSuccessors(current);
		size_t currentColour = visited[current];

		for (int i = 0; i < adjacent.size(); i++)
		{
			if (visited[adjacent[i].first] == currentColour)
				return false;

			if (visited[adjacent[i].first])
				continue;

			q.push(adjacent[i].first);
			visited[adjacent[i].first] = currentColour == 1 ? 2 : 1;
		}
	}

	return true;
}
bool isBipartite(const Graph& g)
{
	if (g.isOriented())
		throw "The graph should NOT be oriented!";

	vector<int> visited(g.getVerticesCount());

	for (int i = 0; i < visited.size(); i++)
	{
		if (!visited[i] && !BFS_isBipartite(g, visited, i))
			return false;
	}

	return true;
}

int Dijkstra(const Graph& g, int start, int end, vector<size_t>& shortestPath)
{
	vector<int> distances(g.getVerticesCount(), INT_MAX);
	vector<int> previous(g.getVerticesCount());

	distances[start] = 0;

	struct temp
	{
		int vertex;
		int distFromStart;

		bool operator<(const temp& other) const
		{
			return distFromStart > other.distFromStart;
		}
	};

	priority_queue<temp> q;
	q.push({ start, 0 });

	while (!q.empty())
	{
		int currentVertex = q.top().vertex;
		int currentVertexDistFromStart = q.top().distFromStart;

		if (currentVertex == end)
		{
			int current = end;

			while (current != start)
			{
				shortestPath.push_back(current);
				current = previous[current];
			}

			shortestPath.push_back(start);
			reverse(shortestPath.begin(), shortestPath.end());

			return currentVertexDistFromStart;
		}

		q.pop();

		vector<pair<int, int>> adjacent = g.getSuccessors(currentVertex);

		for (size_t i = 0; i < adjacent.size(); i++)
		{
			int currentSuccessor = adjacent[i].first;
			int currentWeight = adjacent[i].second;

			if (distances[currentVertex] + currentWeight < distances[currentSuccessor])
			{
				distances[currentSuccessor] = distances[currentVertex] + currentWeight;
				q.push({ currentSuccessor, distances[currentSuccessor] });
				previous[currentSuccessor] = currentVertex;
			}
		}
	}

	return INT_MAX;
}

int main()
{
	{ // Bipartite
		AdjacencyListGraph g(4, false);
		g.addEdge(0, 1);
		g.addEdge(1, 2);
		g.addEdge(2, 3);
		g.addEdge(3, 0);

		cout << (isBipartite(g) ? "It's bipartite!" : "It's NOT bipartite!") << endl << endl;
	}

	{ // Dijkstra
		AdjacencyListGraph g(9, false);
		g.addEdge(0, 1, 4);
		g.addEdge(0, 7, 8);
		g.addEdge(1, 7, 11);
		g.addEdge(1, 2, 8);
		g.addEdge(7, 8, 7);
		g.addEdge(7, 6, 1);
		g.addEdge(8, 6, 6);
		g.addEdge(8, 2, 2);
		g.addEdge(2, 5, 4);
		g.addEdge(6, 5, 2);
		g.addEdge(2, 3, 7);
		g.addEdge(3, 5, 14);
		g.addEdge(3, 4, 9);
		g.addEdge(5, 4, 10);

		vector<size_t> shortestPath;
		cout << "Shortest path from 0 to 4 is with weight " << Dijkstra(g, 0, 4, shortestPath) << '.' << endl;
		cout << "Path: ";

		for (size_t i = 0; i < shortestPath.size(); i++)
			cout << shortestPath[i] << ' ';
		cout << endl;
	}
}