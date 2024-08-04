// Samuel Furlanich - Tecnicas de Diseño de Algoritmos 1C 2024 Turno Mañana.
// Argentina.cpp

#include <iostream>
#include <vector>
#include <algorithm>

struct Player
{
    std::string name;

    int attackingSkillPoints;
    int defendingSkillPoints;
};

std::vector<Player> players;

std::vector<std::string> bestAttackers;
std::vector<std::string> bestDefenders;

int maxAttackingPoints = -1;
int maxDefendingPoints = -1;

void findBestPlayerTeamPositions(std::vector<std::string>& attackers, std::vector<std::string>& defenders, int index, int attackingPoints, int defendingPoints)
{
    if (attackers.size() == 5 && defenders.size() == 5)
    {
        if (attackingPoints > maxAttackingPoints)
        {
            maxAttackingPoints = attackingPoints;
            bestAttackers = attackers;

            maxDefendingPoints = defendingPoints;
            bestDefenders = defenders;
        }
        else if (attackingPoints == maxAttackingPoints && defendingPoints > maxDefendingPoints)
        {
            maxDefendingPoints = defendingPoints;
            bestDefenders = defenders;

            bestAttackers = attackers;
        }

        return;
    }

    if (index == 10)
    {
        return;
    }

    // Include player in the attackers formation.
    if (attackers.size() < 5)
    {
        attackers.push_back(players[index].name);

        findBestPlayerTeamPositions(attackers, defenders, index + 1, attackingPoints + players[index].attackingSkillPoints, defendingPoints);

        attackers.pop_back();
    }

    // Include the player in the defenders formation.
    if (defenders.size() < 5)
    {
        defenders.push_back(players[index].name);

        findBestPlayerTeamPositions(attackers, defenders, index + 1, attackingPoints, defendingPoints + players[index].defendingSkillPoints);

        defenders.pop_back();
    }

    // We skip the current index player.
    findBestPlayerTeamPositions(attackers, defenders, index + 1, attackingPoints, defendingPoints);
}

int main()
{
    int numberOfTests;

    std::cin >> numberOfTests;

    for (int t = 1; t <= numberOfTests; ++t)
    {
        players.clear();
        bestAttackers.clear();
        bestDefenders.clear();

        maxAttackingPoints = -1;
        maxDefendingPoints = -1;

        for (int i = 0; i < 10; ++i)
        {
            std::string playerName;

            int attackSkillPoints;
            int defenseSkillPoints;

            std::cin >> playerName >> attackSkillPoints >> defenseSkillPoints;

            players.push_back({ playerName, attackSkillPoints, defenseSkillPoints });
        }

        // Sort players by lexicographically ordered names.
        sort(players.begin(), players.end(), [](const Player& attackers, const Player& defenders) { return attackers.name < defenders.name; });

        std::vector<std::string> emptyAttackers;
        std::vector<std::string> emptyDefenders;

        findBestPlayerTeamPositions(emptyAttackers, emptyDefenders, 0, 0, 0);

        // Print results
        std::cout << "Case " << t << ":" << std::endl; std::cout << "(";

        for (int i = 0; i < 5; ++i)
        {
            if (i > 0)
            {
                std::cout << ", ";
            }

            std::cout << bestAttackers[i];
        }

        std::cout << ")" << std::endl; std::cout << "(";

        for (int i = 0; i < 5; ++i)
        {
            if (i > 0)
            {
                std::cout << ", ";
            }

            std::cout << bestDefenders[i];
        }
        std::cout << ")" << std::endl;
    }

    return 0;
}
