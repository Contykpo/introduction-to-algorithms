#include <iostream>

#include <vector>
#include <assert.h>


int n = 3;
int k = 12;

std::vector<int> X = { 6, 12, 6 };
std::vector<std::vector<bool>> M(n + 1);

bool sumSetTopDown(int n, int k)
{
	if (k == 0)
	{
		return true;
	}
	if (n == 0)
	{
		return k == 0;
	}
	if (!M[n][k])
	{
		M[n][k] = sumSetTopDown(n - 1, k) || sumSetTopDown(n - 1, k - X[n - 1]);
	}

	return M[n][k];
}

bool sumSetBottomUp(int n, int k)
{
	for (int j = 0; j < k; ++j)
	{
		M[0][j] = 0;
	}

	for (int i = 0; i < n + 1; ++i)
	{
		for (int j = 0; j < k + 1; ++j)
		{
			M[i][j] = M[i - 1][j] || (j - X[i] >= 0 && M[i - 1][j - X[i]]);
		}
	}

	return M[n][k];
}

std::vector<int> getSumSet(int n, int k)
{
	std::cout << "n: " << n << "\n";
	std::cout << "k: " << k << "\n";

	assert(k >= 0 && n >= 0);

	std::vector<int> temp;

	if (k == 0)
	{
		return temp;
	}
	else
	{
		if (sumSetTopDown(n - 1, k))
		{
			return getSumSet(n - 1, k);
		}
		else
		{
			if (n > 0)
			{
				temp = getSumSet(n - 1, k - X[n - 1]);
				temp.push_back(X[n - 1]);
			}
			else
			{
				temp = getSumSet(n, k - X[n]);
				temp.push_back(X[n]);
			}

			return temp;
		}
	}
}

//int main()
//{
//	for (int i = 0; i < n + 1; ++i)
//	{
//		M[i] = std::vector<bool>(k + 1);
//	}
//
//	std::vector<int> ss = getSumSet(n, k);
//
//	for (auto elemento : ss)
//	{
//		std::cout << "total sumSet: " << elemento << " ";
//	}
//}

// D. El algoritmo empleando Programacion Dinamica es mejor cuando k << 2^n, ya que su complejidad resulta O(n*k).
// No obstante, cuando k >> 2^n, el algoritmo que emplea Backtracking resulta mas conveniente, a pesar de tener una complejidad O(2^n).
