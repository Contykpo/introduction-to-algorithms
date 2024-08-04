// Samuel Furlanich - Tecnicas de Diseño de Algoritmos 1C 2024 Turno Mañana.
// DownWentTheTitanic.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <vector>
#include <queue>
#include <algorithm>

// Structure to represent an edge in the graph
struct Edge
{
	int destination;
	int capacity;
	int flow;
	int reverse;
};

std::vector<std::vector<Edge>> graph(2000);
std::vector<int> parent(2000);
std::vector<int> parentEdge(2000);
std::vector<bool> visited(2000);

// Directions for moving in the grid.
int directions[4][2] = { {0, 1}, {1, 0}, {-1, 0}, {0, -1} };

// Infinite value to identify undefined values.
const int INF = 1e9;

// Add an edge to the graph.
inline void addEdge(int origin, int destination, int capacity)
{
	graph[origin].push_back({ destination, capacity, 0, static_cast<int>(graph[destination].size()) });
	graph[destination].push_back({ origin, 0, 0, static_cast<int>(graph[origin].size()) - 1 });
}

// Do breadth first search to find augmenting paths.
bool breadthFirstSearch(int source, int sink)
{
	std::fill(visited.begin(), visited.end(), false);

	std::queue<int> queue;

	queue.push(source);

	visited[source] = true;

	while (!queue.empty())
	{
		int current = queue.front();

		queue.pop();

		for (int i = 0; i < graph[current].size(); ++i)
		{
			Edge& edge = graph[current][i];

			if (!visited[edge.destination] && edge.capacity > edge.flow)
			{
				queue.push(edge.destination);

				visited[edge.destination] = true;
				parent[edge.destination] = current;
				parentEdge[edge.destination] = i;

				if (edge.destination == sink)
				{
					return true;
				}
			}
		}
	}
	
	return false;
}

// Function to find maximum flow using Edmonds-Karp (BFS based Ford-Fulkerson).
int maxFlow(int source, int sink)
{
	int totalFlow = 0;

	while (breadthFirstSearch(source, sink))
	{
		int flow = INF;

		for (int vVertex = sink; vVertex != source; vVertex = parent[vVertex])
		{
			int uVertex = parent[vVertex];

			Edge& edge = graph[uVertex][parentEdge[vVertex]];

			flow = std::min(flow, edge.capacity - edge.flow);
		}

		for (int vVertex = sink; vVertex != source; vVertex = parent[vVertex])
		{
			int uVertex = parent[vVertex];

			Edge& edge = graph[uVertex][parentEdge[vVertex]];

			edge.flow += flow;

			graph[vVertex][edge.reverse].flow -= flow;
		}

		totalFlow += flow;
	}

	return totalFlow;
}

int main()
{
	std::ios::sync_with_stdio(false);
	std::cout.tie(nullptr);
	std::cin.tie(nullptr);

	int rows;
	int columns;
	int maxPeoplePerWood;

	char cellType;

	while (std::cin >> columns >> rows >> maxPeoplePerWood)
	{
		// Reset the graph.
		for (auto& edges : graph)
		{
			edges.clear();
		}

		int totalNodes = rows * columns;

		int source = 0;
		int sink = totalNodes * 2 + 1;

		for (int j = 0; j < columns; ++j)
		{
			for (int i = 0; i < rows; ++i)
			{
				int nodeIn = rows * j + i + 1;
				int nodeOut = nodeIn + totalNodes;

				std::cin >> cellType;

				if (cellType == '.')
				{
					addEdge(nodeIn, nodeOut, 1);
				}
				else if (cellType == '@')
				{
					addEdge(nodeIn, nodeOut, INF);
				}
				else if (cellType == '*')
				{
					addEdge(nodeIn, nodeOut, 1);
					addEdge(source, nodeIn, 1);
				}
				else if (cellType == '#')
				{
					addEdge(nodeIn, nodeOut, INF);
					addEdge(nodeOut, sink, maxPeoplePerWood);
				}

				for (int k = 0; k < 4; ++k)
				{
					int newX = i + directions[k][0];
					int newY = j + directions[k][1];

					if (newX >= 0 && newY >= 0 && newX < rows && newY < columns)
					{
						int neighborNodeIn = rows * newY + newX + 1;

						addEdge(nodeOut, neighborNodeIn, INF);
					}
				}
			}
		}

		std::cout << maxFlow(source, sink) << '\n';
	}

	return 0;
}
