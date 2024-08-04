// Samuel Furlanich - Tecnicas de Diseño de Algoritmos 1C 2024 Turno Mañana.
// MyTshirtSuitsMe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <vector>
#include <queue>
#include <unordered_map>

const std::vector<std::string> sizes = { "XXL", "XL", "L", "M", "S", "XS" };
std::unordered_map<std::string, int> sizeIndex = { {"XXL", 0}, {"XL", 1}, {"L", 2}, {"M", 3}, {"S", 4}, {"XS", 5} };

struct MaxFlow
{
	int numberOfNodes;

	std::vector<std::vector<int>> capacity;
	std::vector<std::vector<int>> adjacencies;

	std::vector<int> parent;

	MaxFlow(int nodes) : numberOfNodes(nodes), capacity(nodes, std::vector<int>(nodes, 0)), adjacencies(nodes), parent(nodes) {}

	void addEdge(int uVertex, int vVertex, int eCapacity)
	{
		capacity[uVertex][vVertex] = eCapacity;

		adjacencies[uVertex].push_back(vVertex);
		adjacencies[vVertex].push_back(uVertex);
	}

	// Do breadth first search to find augmenting paths.
	bool breadthFirstSearch(int source, int sink)
	{
		std::fill(parent.begin(), parent.end(), -1);

		parent[source] = -2;

		std::queue<std::pair<int, int>> queue;

		queue.push({ source, 1e9 });

		while (!queue.empty())
		{
			int current = queue.front().first;

			int flow = queue.front().second;

			queue.pop();

			for (int next : adjacencies[current])
			{
				if (parent[next] == -1 && capacity[current][next])
				{
					parent[next] = current;

					int newFlow = std::min(flow, capacity[current][next]);

					if (next == sink)
					{
						return true;
					}

					queue.push({ next, newFlow });
				}
			}
		}

		return false;
	}

	// Calculate max flow with Edmonds Karp algorithm.
	int edmondsKarp(int source, int sink)
	{
		int flow = 0;

		while (breadthFirstSearch(source, sink))
		{
			int current = sink;

			while (current != source)
			{
				int previous = parent[current];

				capacity[previous][current] -= 1;
				capacity[current][previous] += 1;

				current = previous;
			}

			flow += 1;
		}

		return flow;
	}
};

int main()
{
	int numberOfTests;

	std::cin >> numberOfTests;

	while (numberOfTests--)
	{
		int numberOfTshirts;
		int numberOfVolunteers;

		std::cin >> numberOfTshirts >> numberOfVolunteers;

		// Bipartite graph.
		// Nodes 0 to 5 represent the T-shirt sizes.
		// Nodes 6 to 6 + M - 1 represent the volunteers.
		MaxFlow maxFlow(numberOfTshirts + numberOfVolunteers + 2);

		int source = numberOfTshirts + numberOfVolunteers;
		int sink = numberOfTshirts + numberOfVolunteers + 1;

		// Add edges from source to T-shirt sizes.
		for (int i = 0; i < 6; ++i)
		{
			maxFlow.addEdge(source, i, numberOfTshirts / 6);
		}

		// Read preferences and create edges.
		for (int i = 0; i < numberOfVolunteers; ++i)
		{
			std::string size1, size2;

			std::cin >> size1 >> size2;

			int volunteerNode = 6 + i;

			maxFlow.addEdge(sizeIndex[size1], volunteerNode, 1);
			maxFlow.addEdge(sizeIndex[size2], volunteerNode, 1);
			maxFlow.addEdge(volunteerNode, sink, 1);
		}

		// Calculate max flow to determine if there is a valid distribution.
		int maxFlowValue = maxFlow.edmondsKarp(source, sink);

		std::cout << (maxFlowValue == numberOfVolunteers ? "YES" : "NO") << '\n';
	}

	return 0;
}

