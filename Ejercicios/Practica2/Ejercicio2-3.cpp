//Samuel Furlanich - Tecnicas de Diseño de Algoritmos - Practica 2 - Ejercicio 3.

#include <iostream>
#include <vector>
#include <algorithm>

int powerOf(int a, int b)
{
	if (b == 0)
	{
		return 1;
	}
	else if (b % 2 == 0)
	{
		int power = powerOf(a, b / 2);

		return power * power;
	}
	else
	{
		int power = powerOf(a, (b - 1) / 2);

		return power * power * a;
	}
}

//int main()
//{
//	int A = 2;
//	int B = 4;
//
//	std::cout << powerOf(A, B) << std::endl;
//
//	return 0;
//}

// Complexity:
// T(b) = T(b / 2) + cte.
// Given a = 1; c = 2; f(b) = cte belongs to O(1).
// f(b) belongs to O-(n ^ log_c(a)) = O-(n ^ log_2(1)) = O-(n ^ 0) = O-(1).
// => T(b) = O-((n ^ log_c(a)) * log(b)) = O-(log(b))