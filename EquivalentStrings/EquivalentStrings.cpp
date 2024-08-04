// Samuel Furlanich - Tecnicas de Diseño de Algoritmos 1C 2024 Turno Mañana.
// EquivalentStrings.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <string>
#include <algorithm>

std::string findLeastLexicographicallyString(std::string string)
{
    if (string.size() % 2 != 0)
    {
        return string;
    }

    std::string stringX = findLeastLexicographicallyString(string.substr(0, string.size() / 2));
    std::string stringY = findLeastLexicographicallyString(string.substr(string.size() / 2));

    return std::min(stringX + stringY, stringY + stringX);
}

bool areStringsEquivalent(std::string stringA, std::string stringB)
{
    return findLeastLexicographicallyString(stringA) == findLeastLexicographicallyString(stringB);
}

int main()
{
    std::string stringA;
    std::string stringB;
    
    std::cin >> stringA >> stringB;

    if (areStringsEquivalent(stringA, stringB))
    {
        std::cout << "YES" << std::endl;
    }
    else
    {
        std::cout << "NO" << std::endl;
    }

    return 0;
}
