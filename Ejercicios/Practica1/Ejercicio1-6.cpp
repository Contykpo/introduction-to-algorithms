#include <iostream>
#include <vector>
#include <cstring>

struct Payment
{
    int minimumCost;
    int minimumBills;
};

void cc(std::vector<int>& B, int C, int start, std::vector<int>& current, std::vector<int>& result, int& minDiff, int& minSize, int currentSum)
{
    // Only consider sums that are equal to or greater than C
    if (currentSum >= C)
    {
        int diff = abs(C - currentSum);

        // Update result if this subset is closer to C or equally close but smaller
        if (diff < minDiff || (diff == minDiff && current.size() < minSize))
        {
            minDiff = diff;
            minSize = current.size();
            result = current;
        }
    }

    if (start >= B.size() || currentSum >= C)
    {
        return;
    }

    for (int i = start; i < B.size(); i++)
    {
        current.push_back(B[i]);

        cc(B, C, i + 1, current, result, minDiff, minSize, currentSum + B[i]);

        current.pop_back();
    }
}


// Function to find the subset of B that is closest to C
std::vector<int> findClosestSubset(std::vector<int>& B, int C)
{
    std::vector<int> result;
    std::vector<int> current;

    int minDiff = INT_MAX;
    int minSize = INT_MAX;

    cc(B, C, 0, current, result, minDiff, minSize, 0);

    return result;
}

//int main()
//{
//    int cPrice = 14;
//
//    std::vector<int> bWallet = { 2, 3, 5, 10, 20, 20 };
//    std::vector<int> payment = findClosestSubset(bWallet, cPrice);
//
//    Payment mostAffordablePayment = { 0, 0 };
//    mostAffordablePayment.minimumBills = payment.size();
//
//    for (int i = 0; i < payment.size(); ++i)
//    {
//        mostAffordablePayment.minimumCost += payment[i];
//    }
//
//    std::cout << "Minimum cost: " << mostAffordablePayment.minimumCost << " Minimum Bills: " << mostAffordablePayment.minimumBills;
//}