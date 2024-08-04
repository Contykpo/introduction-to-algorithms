// Samuel Furlanich - Tecnicas de Diseño de Algoritmos 1C 2024 Turno Mañana.
// AntiBruteForceLock.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <string>
#include <vector>
#include <queue>

int find_w(const std::string& a, const std::string& b)
{
	int w = 0;

	for (int i = 0; i < 4; ++i)
	{
		w += std::min(abs(a[i] - b[i]), 10 - abs(a[i] - b[i]));
	}
	return w;
}

int mst(std::vector<std::vector<std::pair<int, int>>>& graphG)
{
	std::priority_queue<std::pair<int, int> > queue;
	
	std::vector<bool> seen(graphG.size());
	
	queue.push(std::make_pair(0, 0));
	
	int c = 0;
	int result = 0;
	
	while (c < graphG.size())
	{
		int u = queue.top().second;
		int	w = -queue.top().first;

		queue.pop();
		
		if (!seen[u])
		{
			seen[u] = true;
			
			++c;
			
			result += w;
			
			for (int i = 0; i < graphG[u].size(); ++i)
			{
				queue.push(std::make_pair(-graphG[u][i].second, graphG[u][i].first));
			}
		}
	}
	return result;
}

//int main()
//{
//	int numberOfTests;
//	int numberOfKeys;
//	
//	std::cin >> numberOfTests;
//	
//	const std::string initialState = "0000";
//
//	while (numberOfTests--)
//	{
//		std::cin >> numberOfKeys;
//	
//		std::vector<std::string> keys(numberOfKeys);
//		
//		int initial = 0x7fffffff;
//		
//		for (int i = 0; i < numberOfKeys; ++i)
//		{
//			std::cin >> keys[i];
//		
//			initial = std::min(initial, find_w(keys[i], initialState));
//		}
//
//		std::vector<std::vector<std::pair<int, int>>> G(numberOfKeys);
//		
//		for (int i = 0; i < numberOfKeys; ++i)
//		{
//			for (int j = i + 1; j < numberOfKeys; ++j)
//			{
//				int w = find_w(keys[i], keys[j]);
//			
//				G[i].push_back(std::make_pair(j, w));
//				G[j].push_back(std::make_pair(i, w));
//			}
//		}
//
//		std::cout << mst(G) + initial << '\n';
//	}
//}
