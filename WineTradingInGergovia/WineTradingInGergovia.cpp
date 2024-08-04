// Samuel Furlanich - Tecnicas de Diseño de Algoritmos 1C 2024 Turno Mañana.
// WineTradingInGergovia.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <vector>

int main()
{
	int numberOfInhabitants;

	while (std::cin >> numberOfInhabitants && numberOfInhabitants != 0)
	{
		std::vector<int> demands(numberOfInhabitants);

		for (int i = 0; i < numberOfInhabitants; ++i)
		{
			std::cin >> demands[i];
		}

		long long totalWork = 0;
		long long accumulatedDemand = 0;

		for (int i = 0; i < numberOfInhabitants; ++i)
		{
			accumulatedDemand += demands[i];
			totalWork += std::abs(accumulatedDemand);
		}

		std::cout << totalWork << std::endl;
	}

	return 0;
}
