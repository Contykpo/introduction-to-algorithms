// Samuel Furlanich - Tecnicas de Diseño de Algoritmos 1C 2024 Turno Mañana.
// DovesAndBombs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include <iostream>
//
//#include <vector>
//#include <map>
//
//void calculatePigeonValue(int station, int root, int counter, int childNodes,
//	std::vector<int>& parent, std::vector<int>& low, std::vector<int>& num, std::vector<std::vector<int>>& graph, std::vector<int>& pigeonValues)
//{
//	low[station] = counter;
//	num[station] = counter++;
//
//	int size = graph[station].size();
//
//	for (int i = 0; i < size; ++i)
//	{
//		int vertex = graph[station][i];
//
//		if (num[vertex] == -1e6)
//		{
//			parent[vertex] = station;
//
//			if (station == root)
//			{
//				++childNodes;
//			}
//
//			calculatePigeonValue(vertex, root, counter, childNodes, parent, low, num, graph, pigeonValues);
//
//			if (low[vertex] >= num[station])
//			{
//				++pigeonValues[station];
//			}
//
//			low[station] = std::min(low[station], low[vertex]);
//		}
//		else if (vertex != parent[station])
//		{
//			low[station] = std::min(low[station], num[vertex]);
//		}
//	}
//
//	return;
//}
//
//int main(void)
//{
//	// The number of railway stations in the empire.
//	int n;
//	// The number of stations to be identified as candidate bombing targets.
//	int m;
//
//	std::vector<int> parent;
//	std::vector<int> low;
//	std::vector<int> num;
//
//	std::vector<std::vector<int>> graph;
//
//	std::vector<int> pigeonValues;
//
//	while (std::cin >> n >> m && (n != 0 || m != 0))
//	{
//		parent.assign(n, -1e6);
//		low.assign(n, -1e6);
//		num.assign(n, -1e6);
//
//		graph.assign(n, std::vector<int>());
//
//		pigeonValues.assign(n, 0);
//
//		int x;
//		int y;
//
//		while (std::cin >> x >> y && x != -1 && y != -1)
//		{
//			graph[x].push_back(y);
//			graph[y].push_back(x);
//		}
//
//		// Calculate pigeon values for each station:
//
//		int root;
//		int childNodes;
//
//		for (int station = 0; station < n; ++station)
//		{
//			if (num[station] == -1e6)
//			{
//				root = station;
//				childNodes = 0;
//
//				calculatePigeonValue(station, root, 0, childNodes, parent, low, num, graph, pigeonValues);
//
//				pigeonValues[station] = (childNodes > 1);
//			}
//		}
//
//		// Sort stations based on pigeon value and station number:
//
//		std::multimap<int, int> bombStations;
//
//		for (int i = 0; i < n; ++i)
//		{
//			++pigeonValues[i];
//
//			bombStations.insert(std::make_pair(-pigeonValues[i], i));
//		}
//
//		// Output m most desirable railway stations to bomb:
//
//		int i = 0;
//		for (std::multimap<int, int>::iterator iterator = bombStations.begin(); iterator != bombStations.end() && i < m; ++iterator, ++i)
//		{
//			std::cout << iterator->second << " " << -iterator->first << std::endl;
//		}
//
//		std::cout << std::endl;
//	}
//
//	return 0;
//}
