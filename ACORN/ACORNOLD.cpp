//#include <iostream>
//#include <vector>
//#include <algorithm>
//
//// Bottom-up calculation
//void getMaxAcorns(int numberOfTrees, int treesHeight, int flyingHeight, std::vector<std::vector<int>> const& acorns, std::vector<std::vector<int>>& MCache)
//{
//	for (int i = 0; i < numberOfTrees; ++i)
//	{
//		MCache[0][i] = acorns[i][0];
//		MCache[0][numberOfTrees] = std::max(MCache[0][i], MCache[0][numberOfTrees]);
//	}
//
//	for (int i = 1; i < MCache.size(); ++i)
//	{
//		for (int j = 0; j < numberOfTrees; ++j)
//		{
//			MCache[i][j] = MCache[i - 1][j] + acorns[j][i];
//			MCache[i][numberOfTrees] = std::max(MCache[i][j], MCache[i][numberOfTrees]);
//		}
//	}
//
//	for (int i = MCache.size(); i < treesHeight; ++i)
//	{
//		std::vector<int> cache(MCache[MCache.size() - 1]);
//
//		int bestJump = MCache[0][numberOfTrees];
//		int newBestJump = 0;
//
//		for (int j = 0; j < numberOfTrees; ++j)
//		{
//			MCache[MCache.size() - 1][j] = std::max(MCache[MCache.size() - 1][j], bestJump) + acorns[j][i];
//
//			if (MCache[MCache.size() - 1][j] > newBestJump)
//			{
//				newBestJump = MCache[MCache.size() - 1][j];
//			}
//		}
//
//		MCache[MCache.size() - 1][numberOfTrees] = newBestJump;
//
//		for (int k = MCache.size() - 2; k >= 0; --k)
//		{
//			std::swap(MCache[k], cache);
//		}
//	}
//
//	//for (int height = treesHeight - 1; height >= 0; --height)
//	//{
//	//	for (int nTree = 0; nTree < numberOfTrees; ++nTree)
//	//	{
//	//		// Climb down the tree.
//	//		MCache[nTree][height] = MCache[nTree][height + 1] + acorns[nTree][height];
//
//	//		// Fly to another tree.
//	//		if (height + flyingHeight <= treesHeight)
//	//		{
//	//			for (int nextTree = 0; nextTree < numberOfTrees; ++nextTree)
//	//			{
//	//				if (nextTree != nTree)
//	//				{
//	//					MCache[nTree][height] = std::max(MCache[nTree][height], MCache[nextTree][height + flyingHeight] + acorns[nTree][height]);
//	//				}
//	//			}
//	//		}
//	//	}
//	//}
//}
//
//int main()
//{
//	int cDataSets;
//
//	std::cin >> cDataSets;
//
//	while (cDataSets--)
//	{
//		int numberOfTrees;
//		int treesHeight;
//		int flyingHeight;
//
//		std::cin >> numberOfTrees >> treesHeight >> flyingHeight;
//
//		std::vector<std::vector<int>> acorns(numberOfTrees, std::vector<int>(treesHeight + 1, 0));
//
//		for (int i = 0; i < numberOfTrees; ++i)
//		{
//			int numberOfAcorns;
//
//			std::cin >> numberOfAcorns;
//
//			for (int j = 0; j < numberOfAcorns; ++j)
//			{
//				int height;
//
//				std::cin >> height;
//
//				acorns[i][height]++;
//			}
//		}
//
//		// Global cache initialization:
//		// --- Base case: the number of acorns that can be directly collected at each height.
//
//		//std::vector<std::vector<int>> MCache(numberOfTrees, std::vector<int>(treesHeight + 1, 0));
//		std::vector<std::vector<int>> MCache(flyingHeight + 1, std::vector<int>(numberOfTrees + 1, 0));
//
//		// Find the maximum acorns that can be collected starting from the top of any tree.
//		getMaxAcorns(numberOfTrees, treesHeight, flyingHeight, acorns, MCache);
//
//		int maxAcorns = 0;
//
//		//for (int nTree = 0; nTree <= numberOfTrees; ++nTree)
//		//{
//		//	maxAcorns = std::max(maxAcorns, MCache[0][nTree]);
//		//}
//
//		maxAcorns = MCache[MCache.size() - 1][numberOfTrees];
//
//		std::cout << maxAcorns << std::endl;
//	}
//
//	return 0;
//}
//
