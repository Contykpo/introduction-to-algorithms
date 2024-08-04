// Samuel Furlanich - Tecnicas de Diseño de Algoritmos 1C 2024 Turno Mañana.
// King.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <string>
#include <vector>
#include <algorithm>
#include <limits.h>

struct Edge
{
    // Source and destination vertices.
    int uVertex;
    int vVertex;

    int weight;

    // Constructors:
    Edge() : uVertex(-1), vVertex(-1), weight(-1) {}
    Edge(int u, int v, int weight) : uVertex(u), vVertex(v), weight(weight) {}
};

// Bellman-Ford's shortest path algorithm starts from the special vertex (n + 1).
bool bellmanFord(int numberOfVertices, int sourceVertex, const std::vector<Edge>& graph)
{
    // Initialize the graph.

    std::vector<int> distances(numberOfVertices, INT_MAX);
    
    distances[sourceVertex] = 0;
    
    // Relax all the edges (numberOfVertices - 1) times.
    // This guarantees that the algorithm has explored all possible paths of length up to (numberOfVertices - 1).
    for (int i = 0; i < numberOfVertices - 1; i++)
    {
        for (auto const& edge : graph)
        {        
            if (distances[edge.uVertex] + edge.weight < distances[edge.vVertex])
            {
                distances[edge.vVertex] = distances[edge.uVertex] + edge.weight;
            }
        }
    }
    
    // Check for negative weight cycles.
    for (auto const& edge : graph)
    {
        // Graph contains negative weight cycle.
        if (distances[edge.uVertex] + edge.weight < distances[edge.vVertex])
        {
            return true;
        }
    }

    return false;
}

int main()
{
    int sequenceSLength;

    while (std::cin >> sequenceSLength)
    {
        if (!sequenceSLength)
        {
            break;
        }
        
        int numberOfSubsequences;
        
        std::cin >> numberOfSubsequences;
        
        std::vector<Edge> graph(sequenceSLength + numberOfSubsequences + 1);

        for (int i = 0; i < sequenceSLength + 1; i++)
        {
            graph[i] = Edge(sequenceSLength + 1, i, 0);
        }
        
        // Edges from specical vertex (n + 1) to any other vertex.
        for (int i = sequenceSLength + 1; i < sequenceSLength + numberOfSubsequences + 1; i++)
        {
            int s;
            int n;
            int k;
            
            std::string op;
            
            // Quadruples.
            std::cin >> s >> n >> op >> k;
            
            n += s;
            s--;
            
            if (op == "gt")
            {
                std::swap(s, n);
                
                k++;
                k = -k;
            }
            else
            {
                k--;
            }

            graph[i] = Edge(s, n, k);
        }

        std::cout << (bellmanFord(sequenceSLength + 2, sequenceSLength + 1, graph) ? "successful conspiracy" : "lamentable kingdom") << '\n';
    }

    return 0;
}
