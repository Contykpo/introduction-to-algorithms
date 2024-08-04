// Samuel Furlanich - Tecnicas de Diseño de Algoritmos 1C 2024 Turno Mañana.
// ACORN.cpp.

#include <iostream>
#include <vector>
#include <algorithm>

// Bottom-up calculation.
void findMaxAcornsPath(int numberOfTrees, int treesHeight, int flyingHeight,
    std::vector<std::vector<int>> const& acorns, std::vector<int>& maxAcornsFromHeight, std::vector<std::vector<int>>& MCache)
{
    for (int j = treesHeight - 1; j >= 0; --j)
    {
        for (int i = 0; i < numberOfTrees; ++i)
        {
            // Climb down the tree.
            MCache[i][j] = MCache[i][j + 1] + acorns[i][j];

            // Fly to another tree using precomputed max
            if (j + flyingHeight <= treesHeight)
            {
                MCache[i][j] = std::max(MCache[i][j], maxAcornsFromHeight[j + flyingHeight] + acorns[i][j]);
            }

            // Update the running maximum for this height
            maxAcornsFromHeight[j] = std::max(maxAcornsFromHeight[j], MCache[i][j]);
        }
    }
}

int main()
{
    int cDataSets;

    std::cin >> cDataSets;

    while (cDataSets--)
    {
        int numberOfTrees;
        int treesHeight;
        int flyingHeight;

        std::cin >> numberOfTrees >> treesHeight >> flyingHeight;

        std::vector<std::vector<int>> acorns(numberOfTrees, std::vector<int>(treesHeight + 1, 0));

        // Initialize acorns, store data set.
        for (int i = 0; i < numberOfTrees; ++i)
        {
            int numberOfAcorns;

            std::cin >> numberOfAcorns;

            for (int j = 0; j < numberOfAcorns; ++j)
            {
                int height;

                std::cin >> height;

                acorns[i][height]++;
            }
        }

        // Initialize MCache and maxFromHeight.
        std::vector<std::vector<int>> MCache(numberOfTrees, std::vector<int>(treesHeight + 1, 0));
        // Precomputed maximum acorns that can be collected from any tree at any height.
        std::vector<int> maxAcornsFromHeight(treesHeight + 1, 0);

        for (int i = 0; i < numberOfTrees; ++i)
        {
            MCache[i][treesHeight] = acorns[i][treesHeight];

            maxAcornsFromHeight[treesHeight] = std::max(maxAcornsFromHeight[treesHeight], MCache[i][treesHeight]);
        }

        // Find the maximum acorns that can be collected starting from the top of any tree.
        findMaxAcornsPath(numberOfTrees, treesHeight, flyingHeight, acorns, maxAcornsFromHeight, MCache);

        std::cout << maxAcornsFromHeight[0] << std::endl;
    }
    return 0;
}
