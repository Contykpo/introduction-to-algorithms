// Samuel Furlanich - Tecnicas de Diseño de Algoritmos 1C 2024 Turno Mañana.
// SwapLetters.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <vector>
#include <string>

int main()
{
	int stringLength;

	std::cin >> stringLength;

	std::string stringS;
	std::string stringT;

	std::cin >> stringS >> stringT;

	std::vector<std::pair<int, int>> abMismatches;
	std::vector<std::pair<int, int>> baMismatches;

	for (int i = 0; i < stringLength; i++)
	{
		if (stringS[i] == 'a' && stringT[i] == 'b')
		{
			// Since the indexes are 1-based, +1 is summed to the index.
			abMismatches.emplace_back(i + 1, i + 1);
		}
		else if (stringS[i] == 'b' && stringT[i] == 'a')
		{
			baMismatches.emplace_back(i + 1, i + 1);
		}
	}

	int abMismatchCount = abMismatches.size();
	int baMismatchCount = baMismatches.size();

	// If the sum of unpaired mismatches is odd, it's impossible to make the strings equal.
	if ((abMismatchCount + baMismatchCount) % 2 != 0)
	{
		std::cout << -1 << std::endl;
		return 0;
	}

	std::vector<std::pair<int, int>> swapOperations;

	// Pair up the ab and ba mismatches directly.
	for (int i = 0; i < abMismatchCount - 1; i += 2)
	{
		swapOperations.emplace_back(abMismatches[i].first, abMismatches[i + 1].second);
	}
	for (int i = 0; i < baMismatchCount - 1; i += 2)
	{
		swapOperations.emplace_back(baMismatches[i].first, baMismatches[i + 1].second);
	}

	// If there's one unpaired ab and ba, two moves are enough to correct it.
	if (abMismatchCount % 2 == 1 && baMismatchCount % 2 == 1)
	{
		swapOperations.emplace_back(abMismatches.back().first, abMismatches.back().second);
		swapOperations.emplace_back(abMismatches.back().first, baMismatches.back().second);
	}

	std::cout << swapOperations.size() << std::endl;

	for (auto& indexes : swapOperations)
	{
		std::cout << indexes.first << " " << indexes.second << std::endl;
	}

	return 0;
}
