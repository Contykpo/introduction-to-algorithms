// Samuel Furlanich - Tecnicas de Diseño de Algoritmos 1C 2024 Turno Mañana.
// DovesAndBombs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <vector>
#include <string>
#include <algorithm>

// stationsGraph represented as an adjacency matrix.
// Depth-First-Search which starts at the root (first station) and explores as far as possible along each branch before backtracking.
int calculatePigeonValue(int stationX, int parentStation, int visitedStation, 
	std::vector<std::vector<int>>& stationsGraph, std::vector<int>& pigeonValues, std::vector<int>& visited)
{
	int vertexStationX = visited[stationX] = ++visitedStation;
	
	pigeonValues[stationX] = 1;
	
	for (int i = 0; i < stationsGraph[stationX].size(); i++)
	{
		int stationY = stationsGraph[stationX][i];
		
		if (stationY == parentStation)
		{
			continue;
		}
		
		if (visited[stationY])
		{
			vertexStationX = std::min(vertexStationX, visited[stationY]);
		}
		else
		{
			int vertexStationY = calculatePigeonValue(stationY, stationX, visitedStation, stationsGraph, pigeonValues, visited);
			
			vertexStationX = std::min(vertexStationX, vertexStationY);
		
			if (vertexStationY >= visited[stationX])
			{
				pigeonValues[stationX]++;
			}
		}
	}

	return vertexStationX;
}
bool isMaximumPair(const std::pair<int, int> pairA, const std::pair<int, int> pairB)
{
	if (pairA.second > pairB.second)
	{
		return true;
	}

	if (pairA.second == pairB.second && pairA.first < pairB.first)
	{
		return true;
	}

	return false;
}

int main()
{
	// The number of railway stations in the empire.
	int n;
	// The number of stations to be identified as candidate bombing targets.
	int m;

	while (std::cin >> n >> m && (n + m))
	{	
		std::vector<std::vector<int>> stationsGraph(10001, std::vector<int>());
		std::vector<int> pigeonValues(10001);
		std::vector<int>visited(10001, 0);
		
		int x;
		int y;

		while (std::cin >> x >> y && (x + y) > 0)
		{
			stationsGraph[x].push_back(y);
			stationsGraph[y].push_back(x);
		}
		
		// Calculate pigeon values for each station with a depth-first-search over the stationsGraph:

		calculatePigeonValue(0, 0, 0, stationsGraph, pigeonValues, visited);
		
		pigeonValues[0]--;
		
		// Sort stations based on pigeon value and station number into bombStations:

		std::vector<std::pair<int, int> > bombStations;
		
		for (int i = 0; i < n; i++)
		{
			bombStations.push_back(std::make_pair(i, pigeonValues[i]));
		}
		
		std::sort(bombStations.begin(), bombStations.end(), isMaximumPair);
		
		// Output m most desirable railway stations to bomb:

		for (int i = 0; i < m; i++)
		{
			std::cout << bombStations[i].first << " " << bombStations[i].second << "\n";
		}

		// TODO: Wonder wether std::cout << "\n" is faster than putchar(10);
		putchar(10);
	}

	return 0;
}
