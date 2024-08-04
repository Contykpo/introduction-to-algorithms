// Samuel Furlanich - Tecnicas de Diseño de Algoritmos 1C 2024 Turno Mañana.
// Geonosis.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>

long findTotalEnergyNeeded(int const &numberOfTowers, std::vector<std::vector<int>>& energyCosts, std::vector<int>& destructionOrder)
{
	long energyNeeded = 0;

	for (int i = numberOfTowers - 1; i >= 0; i--)
	{
		int x = destructionOrder[i];

		for (int j = 0; j < numberOfTowers; j++)
		{
			for (int k = 0; k < numberOfTowers; k++)
			{
				energyCosts[j][k] = std::min(energyCosts[j][k], energyCosts[j][x] + energyCosts[x][k]);
			}
		}

		long temporary = 0;

		for (int j = i; j < numberOfTowers; j++)
		{
			int uVertex = destructionOrder[j];

			for (int k = j + 1; k < numberOfTowers; k++)
			{
				int vVertex = destructionOrder[k];

				temporary += energyCosts[uVertex][vVertex] + energyCosts[vVertex][uVertex];
			}
		}

		energyNeeded += temporary;
	}

	return energyNeeded;
}

int main()
{
	int numberOfTests;
	int numberOfTowers;
	
	std::cin >> numberOfTests;

	while (numberOfTests--)
	{
		std::cin >> numberOfTowers;
	
		std::vector<std::vector<int>> energyCosts(512, std::vector<int>(512));
		std::vector<int> destructionOrder(512);

		for (int i = 0; i < numberOfTowers; i++)
		{
			for (int j = 0; j < numberOfTowers; j++)
			{
				std::cin >> energyCosts[i][j];
			}
		}
		
		for (int i = 0; i < numberOfTowers; i++)
		{
			std::cin >> destructionOrder[i];
		}

		long energyNeeded = findTotalEnergyNeeded(numberOfTowers, energyCosts, destructionOrder);

		std::cout << energyNeeded << '\n';
	}
	
	return 0;
}
