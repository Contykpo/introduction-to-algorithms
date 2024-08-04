//Samuel Furlanich - Tecnicas de Diseño de Algoritmos - Practica 1 - Ejercicio 1

#include <iostream>
#include <vector>

void subSetSum(const std::vector<int>& set, int index, int sum, std::vector<int> subset)
{

	// If sum becomes 0 print the subset 
	if (sum == 0)
	{
		for (auto elem : subset)
		{
			std::cout << elem << " ";
		}

		std::cout << "\n";

		return;
	}

	// If there are no more elements to include but sum is not zero, then there is
	// No solution. 
	if (index == 0 && sum != 0)
	{
		return;
	}

	// If sum becomes less than 0 
	if (sum < 0)
	{
		return;
	}

	// Do not include the current element  
	subSetSum(set, index - 1, sum, subset);

	// Include the current element to subset 
	subset.push_back(set[index - 1]);

	subSetSum(set, index - 1, sum - set[index - 1], subset);
}

//int main()
//{
//	int sum = 12;
//
//	std::vector<int> set = { 6, 12, 6 };
//	std::vector<int> subset;
//
//	if (sum == 0) {
//		std::cout << " ";
//	}
//	else
//	{
//		subSetSum(set, set.size(), sum, subset);
//	}
//
//	return 0;
//}

//int sum(std::vector<int>& subset)
//{
//    int sum = 0;
//    for (int i = 0; i < subset.size(); i++)
//    {
//        sum += subset[i];
//    }
//
//    return sum;
//}