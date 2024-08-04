//Samuel Furlanich - Tecnicas de Diseño de Algoritmos - Practica 2 - Ejercicio 1.

#include <iostream>
#include <vector>
#include <algorithm>

bool isItMoreOfALeftie(std::vector<int> vector)
{
	int vectorLength = vector.size();
	int halfVectorLength = vector.size() / 2;
	// O(n / 2).
	std::vector<int> leftVectorHalf(vector.begin(), vector.begin() + halfVectorLength);
	// O(n / 2).
	std::vector<int> rightVectorHalf(vector.begin() + halfVectorLength, vector.end());

	int leftSum = 0;
	// O(n / 2).
	for (int i = 0; i < halfVectorLength; i++)
	{
		leftSum += leftVectorHalf[i];
	}

	int rightSum = 0;
	// O(n / 2).
	for (int i = 0; i < halfVectorLength; i++)
	{
		rightSum += rightVectorHalf[i];
	}

	if (leftSum > rightSum)
	{
		if (vectorLength == 2)
		{
			return true;
		}
		else
		{
			bool result = isItMoreOfALeftie(leftVectorHalf) && isItMoreOfALeftie(rightVectorHalf);

			return result;
		}
	}
	else
	{
		return false;
	}
}

//int main()
//{
//	std::vector<int> vectorA = { 8, 6, 7, 4, 5, 1, 3, 2 };
//
//	if (isItMoreOfALeftie(vectorA))
//	{
//		std::cout << "True" << std::endl;
//	}
//	else
//	{
//		std::cout << "False" << std::endl;
//	}
//
//	return 0;
//}

// Complexity:
// T(n) = 2 * T(n / 2) + n.
// Given a = 2; b = 2; f(n) = n.
// f(n) belongs to O-(n ^ log_b(a)) = O-(n ^ log_2(2)) = O-(n).
// => T(n) = O-((n ^ log_b(a)) * log(n)) = O-(n * log(n))