#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph
{
private:
	vector<vector<int>> adjList;

public:
	Graph(int n) : adjList(n) {}

	void addEdge(int start, int end)
	{
		adjList[start].push_back(end);
		adjList[end].push_back(start);
	}
	vector<int> getSuccessors(int vertex) const
	{
		return adjList[vertex];
	}
	int getVerticesCount() const
	{
		return adjList.size();
	}
};

int BFS_maxElInConnectedCompOfGraph(const Graph& g, int start, vector<bool>& visited)
{
	queue<int> q;
	int maxVertex = start;

	q.push(start);
	visited[start] = true;

	while (!q.empty())
	{
		int currentVertex = q.front();
		q.pop();

		if (currentVertex > maxVertex)
			maxVertex = currentVertex;

		vector<int> successors = g.getSuccessors(currentVertex);
		for (size_t i = 0; i < successors.size(); i++)
		{
			if (visited[successors[i]])
				continue;
			visited[successors[i]] = true;

			q.push(successors[i]);
		}
	}

	return maxVertex;
}
int getSumOfMaxElInConnectedCompOfGraph(const Graph& g)
{
	int sum = 0;
	vector<bool> visited(g.getVerticesCount(), false);

	for (size_t i = 0; i < visited.size(); i++)
	{
		if (visited[i])
			continue;

		sum += BFS_maxElInConnectedCompOfGraph(g, i, visited);
	}

	return sum;
}

int main()
{
	// Графът от картинката.
	Graph g(13);

	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(0, 5);
	g.addEdge(0, 6);
	g.addEdge(3, 4);
	g.addEdge(3, 5);
	g.addEdge(4, 6);
	g.addEdge(7, 8);
	g.addEdge(9, 10);
	g.addEdge(9, 11);
	g.addEdge(9, 12);
	g.addEdge(11, 12);

	cout << getSumOfMaxElInConnectedCompOfGraph(g);
}