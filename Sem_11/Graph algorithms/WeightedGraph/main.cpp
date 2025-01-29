#include "GraphAlgorithms.h"
#include <iostream>

int main()
{
    { // Dijkstra
	WeightedGraph g(9, false);
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

	std::vector<unsigned> distances;
	g.dijkstra(0, distances);
		
	for (size_t i = 0; i < distances.size(); i++)
        {
            std::cout << "Distance to vertex " << i << ": " << distances[i] << std::endl;
        }
    }
	
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
	
    { // Bellman-Ford
        WeightedGraph g(6, true);
        g.addEdge(0, 1, 20);
        g.addEdge(0, 2, 10);
        g.addEdge(1, 3, 33);
        g.addEdge(1, 4, 20);
        g.addEdge(2, 3, 10);
        g.addEdge(2, 4, 50);
        g.addEdge(4, 3, -20);
        g.addEdge(3, 5, 1);
        g.addEdge(4, 5, -2);
        
        std::vector<int> distances;
        g.bellmanFord(0, distances);
        
        for (size_t i = 0; i < distances.size(); i++)
        {
            std::cout << "Distance to vertex " << i << ": " << distances[i] << std::endl;
        }
    }
    
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
    
    { // Prim's MST
        WeightedGraph g(6, false);
        g.addEdge(0, 1, 4);
        g.addEdge(0, 2, 4);
        g.addEdge(1, 2, 2);
        g.addEdge(1, 3, 5);
        g.addEdge(2, 3, 8);
        g.addEdge(2, 4, 10);
        g.addEdge(3, 4, 2);
        g.addEdge(3, 5, 6);
        g.addEdge(4, 5, 3);
        
        std::vector<Edge> mst;
        int mstWeight = g.prim(mst);
        
        std::cout << "Minimum Spanning Tree (Prim's Algorithm):\n";
        std::cout << "Total MST weight: " << mstWeight << std::endl;
        for (const auto& [u, v, w] : mst)
        {
            std::cout << "Edge: " << u << " - " << v << " (Weight: " << w << ")\n";
        }
    }
}
