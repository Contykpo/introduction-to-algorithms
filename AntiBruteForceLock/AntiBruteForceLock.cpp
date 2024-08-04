// Samuel Furlanich - Tecnicas de Diseño de Algoritmos 1C 2024 Turno Mañana.
// AntiBruteForceLock.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <cmath>
#include <climits>

// Calculates the number of rolls needed to go from s1 to s2.
int calculateRolls(const std::string& s1, const std::string& s2)
{
    int rolls = 0;

    for (int i = 0; i < 4; ++i)
    {
        int digit1 = s1[i] - '0';
        int digit2 = s2[i] - '0';
        
        int diff = abs(digit1 - digit2);
    
        rolls += std::min(diff, 10 - diff);
    }

    return rolls;
}

// Prim's algorithm to find the minimum spanning tree cost.
// The weight of the edge between two nodes (combinations) is the number of rolls needed to transition from one combination to the other.
// This can be calculated as the sum of the minimum digit-wise rolls for all four digits.
int findMinimumCostPrim(const std::vector<std::string>& keys)
{
    int numberOfKeys = keys.size();
    
    std::vector<int> minEdge(numberOfKeys, INT_MAX);
    std::vector<bool> inMST(numberOfKeys, false);
    
    minEdge[0] = 0;

    // Priority queue to select the minimum edge weight.
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pQueue;
    
    // {weight, node}.
    pQueue.push({ 0, 0 });

    int totalCost = 0;
    
    while (!pQueue.empty())
    {
        int weight = pQueue.top().first;
        int uKey = pQueue.top().second;
        
        pQueue.pop();

        if (inMST[uKey])
        {
            continue;
        }

        inMST[uKey] = true;

        totalCost += weight;

        for (int vKey = 1; vKey < numberOfKeys; ++vKey)
        {
            if (!inMST[vKey])
            {
                int newWeight = calculateRolls(keys[uKey], keys[vKey]);
            
                if (newWeight < minEdge[vKey])
                {
                    minEdge[vKey] = newWeight;
                    
                    pQueue.push({ newWeight, vKey });
                }
            }
        }
    }

    return totalCost;
}

int main()
{
    int numberOfTests;

    std::cin >> numberOfTests;

    while (numberOfTests--)
    {
        int numberOfKeys;
        
        std::cin >> numberOfKeys;

        // Each node in the graph represents a 4-digit combination (key).
        // Edges between nodes represent the cost (number of rolls) to transition from one combination to another.
        std::vector<std::string> keys(numberOfKeys + 1);
        
        // Initial state.
        keys[0] = "0000";

        for (int i = 1; i <= numberOfKeys; ++i)
        {
            std::cin >> keys[i];
        }

        // Calculate the cost to move from "0000" to the first key
        int initialCost = INT_MAX;
        
        for (int i = 1; i <= numberOfKeys; ++i)
        {
            initialCost = std::min(initialCost, calculateRolls("0000", keys[i]));
        }

        int result = initialCost + findMinimumCostPrim(std::vector<std::string>(keys.begin() + 1, keys.end()));
    
        std::cout << result << '\n';
    }

    return 0;
}
