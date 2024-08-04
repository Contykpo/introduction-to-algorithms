#include <iostream>
#include <vector>
#include <climits>

// Function to calculate the maximum net gain
int maxNetGain(const std::vector<int>& prices, int day, int asteroids, std::vector<std::vector<int>>& memo)
{
    // Base case: if day reaches the end or asteroids is out of bounds, return 0
    if (day == prices.size() || asteroids < 0 || asteroids > day)
    {
        return 0;
    }

    // If the result is already calculated, return it
    if (memo[day][asteroids] != INT_MIN)
    {
        return memo[day][asteroids];
    }

    // Calculate the maximum net gain for the current day and asteroids
    int buy = maxNetGain(prices, day + 1, asteroids - 1, memo) - prices[day];
    int sell = maxNetGain(prices, day + 1, asteroids + 1, memo) + prices[day];
    int noOperation = maxNetGain(prices, day + 1, asteroids, memo);

    // Update the memoization table with the maximum of the three options
    memo[day][asteroids] = std::max({ buy, sell, noOperation });

    return memo[day][asteroids];
}

// Function to solve the problem using top-down dynamic programming
int maxNetProfitTopDown(const std::vector<int>& prices)
{
    int n = prices.size();
    std::vector<std::vector<int>> memo(n, std::vector<int>(n + 1, INT_MIN)); // Memoization table

    return maxNetGain(prices, 0, 0, memo);
}

int maxNetProfitBottomUp(const std::vector<int>& prices)
{
    int n = prices.size();
    if (n <= 1) { return 0; }

    std::vector<int> dp(n, 0);

    // Initialize the first two days' profits
    dp[0] = 0;
    dp[1] = std::max(0, prices[1] - prices[0]);

    for (int i = 2; i < n; ++i)
    {
        int maxProfit = 0;
        for (int j = 0; j < i; ++j)
        {
            maxProfit = std::max(maxProfit, dp[j] + std::max(0, prices[i] - prices[j]));
        }

        dp[i] = std::max(dp[i - 1], maxProfit);
    }

    return dp[n - 1];
}

//int main()
//{
//    // Example usage:
//    std::vector<int> prices1 = { 3, 2, 5, 6 };
//    std::vector<int> prices2 = { 3, 6, 10 };
//
//    std::cout << "Maximum net profit for prices1: " << maxNetProfitTopDown(prices1) << std::endl; // Output: 6
//    std::cout << "Maximum net profit for prices2: " << maxNetProfitBottomUp(prices2) << std::endl; // Output: 7
//
//    return 0;
//}


/* A.
* Si Astro Void tiene un número negativo de asteroides al final del día o tiene más asteroides de los que se pueden tener al final del día,
la ganancia neta es indefinida. Y la Maxima Ganancia Neta al final del día j con c asteroides se puede obtener de tres maneras:
1. Finalizar el día j − 1 con c−1 asteroides y comprar uno en el día.
2. Finalizar el día j−1 con c+1 asteroides y vender uno en el día.
3. Finalizar el día j−1 con c asteroides y no realizar ninguna operación en el día.
*/

/* B.
* La formulacion matematica recursiva seria:
*
*	dp[j][c] = max(dp[j - 1][c - 1] + p[j] si 0 <= c <= j; dp[j - 1][c + 1] - p[j] si 0 <= c <= j - 1; dp[j - 1][c] si 0 <= c <= j)
*
* Donde dp[j][c] es la Maxima Ganancia Neta del dia j con c asteroides, y p[j] es el precio del asteroide en el dia j.
*
* Los casos bases son:
*
*	dp[0][0] = 0, ya que al comenzar no tiene asteroides y, por lo tanto, no hay ganancia neta.
*	dp[0][c] = -infinito para c > 0, ya que no puede comenzar con asteroides.
*/

/* C.
* La respuesta al problema con dicha formulacion recursiva seria:
*
*	max(dp[n][0],dp[n][1],...,dp[n][n])
*
* Donde n es el numero de dias.
*/

/* D.
* Algoritmo Top-Down: *Primeras lineas del archivo cpp.*
*
* Complejidad temporal: O(n^2) donde n es el número de días. Esto se debe a que hay n^2 subproblemas distintos que resolver.
*
* Complejidad espacial auxiliar: O(n^2) debido a la matriz memo utilizada para almacenar los resultados de los subproblemas.
*/