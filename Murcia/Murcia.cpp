// Samuel Furlanich - Tecnicas de Diseño de Algoritmos 1C 2024 Turno Mañana.
// Murcia.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>

#include <string>
#include <vector>
#include <limits.h>

std::vector<std::vector<int>> MCache;

int getIncreasingSubsequenceLength(std::vector<int> const& heights, std::vector<int> const& widths, int index, int previousHeight)
{
	if (index == MCache.size())
	{
		return 0;
	}

	if (MCache[index][previousHeight] != -1e6)
	{
		return MCache[index][previousHeight];
	}

	if (heights[index] > heights[previousHeight] || heights[previousHeight] == -1)
	{
		int includeCurrent = widths[index] + getIncreasingSubsequenceLength(heights, widths, index + 1, index);
		int excludeCurrent = getIncreasingSubsequenceLength(heights, widths, index + 1, previousHeight);

		MCache[index][previousHeight] = std::max(includeCurrent, excludeCurrent);
	}
	else
	{
		MCache[index][previousHeight] = getIncreasingSubsequenceLength(heights, widths, index + 1, previousHeight);
	}

	return MCache[index][previousHeight];
}

int getDecreasingSubsequenceLength(std::vector<int> const& heights, std::vector<int> const& widths, int index, int previousHeight)
{
	if (index == MCache.size())
	{
		return 0;
	}

	if (MCache[index][previousHeight] != -1e6)
	{
		return MCache[index][previousHeight];
	}

	if (heights[index] < heights[previousHeight] || heights[previousHeight] == -1)
	{
		int includeCurrent = widths[index] + getDecreasingSubsequenceLength(heights, widths, index + 1, index);
		int excludeCurrent = getDecreasingSubsequenceLength(heights, widths, index + 1, previousHeight);

		MCache[index][previousHeight] = std::max(includeCurrent, excludeCurrent);
	}
	else
	{
		MCache[index][previousHeight] = getDecreasingSubsequenceLength(heights, widths, index + 1, previousHeight);
	}

	return MCache[index][previousHeight];
}

void showSkylineView(int caseNumber, int const& numberOfBuildings, std::vector<int> const& heights, std::vector<int> const& widths)
{
	MCache.assign(numberOfBuildings, std::vector<int>(numberOfBuildings + 1, -1e6));

	int increasing = getIncreasingSubsequenceLength(heights, widths, 0, numberOfBuildings);

	MCache.assign(numberOfBuildings, std::vector<int>(numberOfBuildings + 1, -1e6));

	int decreasing = getDecreasingSubsequenceLength(heights, widths, 0, numberOfBuildings);

	std::cout << "Case " << caseNumber << ".";

	if (increasing >= decreasing)
	{
		std::cout << " Increasing (" << increasing << "). Decreasing (" << decreasing << ")." << std::endl;
	}
	else
	{
		std::cout << " Decreasing (" << decreasing << "). Increasing (" << increasing << ")." << std::endl;
	}
}

int main()
{
	int tests;

	std::cin >> tests;

	for (int test = 1; test <= tests; ++test)
	{
		int numberOfBuildings;

		std::cin >> numberOfBuildings;

		std::vector<int> buildingsHeights(numberOfBuildings + 1);
		std::vector<int> buildingsWidths(numberOfBuildings);

		for (int i = 0; i < numberOfBuildings; ++i)
		{
			std::cin >> buildingsHeights[i];
		}

		buildingsHeights[numberOfBuildings] = -1;

		for (int i = 0; i < numberOfBuildings; ++i)
		{
			std::cin >> buildingsWidths[i];
		}

		showSkylineView(test, numberOfBuildings, buildingsHeights, buildingsWidths);
	}

	return 0;
}
