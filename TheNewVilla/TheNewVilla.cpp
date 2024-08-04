// Samuel Furlanich - Tecnicas de Diseño de Algoritmos 1C 2024 Turno Mañana.
// TheNewVilla.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <tuple>
#include <queue>
#include <string>

// Breadth first search between transferable states. 
bool canReachLastRoomBFS(int const& r, int const& lastRoomLight, int& steps,
    std::vector<std::vector<int>>& roomsGraph, std::vector<std::vector<int>>& switches,
    std::vector<std::vector<bool>>& visited, std::vector<std::vector<int>>& previousRooms)
{
    std::queue<std::pair<int, int>> queue;

    queue.push(std::make_pair(0, 1));

    int room;
    int light;

    while (!queue.empty())
    {
        int queueLength = queue.size();

        for (int i = 0; i < queueLength; i++)
        {
            // Get the room and light of the first vertex in the queue.
            std::tie(room, light) = queue.front();

            queue.pop();

            if (light == lastRoomLight && room == r - 1)
            {
                // Mr.Black reached the last room with all lights off.
                return true;
            }

            for (auto& lightSwitch : switches[room])
            {
                int nextLight = light ^ (1 << lightSwitch);

                // Not allowed to turn off current room light.
                if (lightSwitch == room)
                {
                    continue;
                }
                if (visited[room][nextLight])
                {
                    continue;
                }

                previousRooms[room][nextLight] = r + lightSwitch;

                visited[room][nextLight] = true;

                queue.push(std::make_pair(room, nextLight));
            }

            for (auto& currentRoom : roomsGraph[room])
            {
                if (visited[currentRoom][light])
                {
                    continue;
                }

                bool lightOn = ((light >> currentRoom) % 2) == 1;

                if (!lightOn)
                {
                    continue;
                }

                previousRooms[currentRoom][light] = room;

                visited[currentRoom][light] = true;

                queue.push(std::make_pair(currentRoom, light));
            }
        }

        steps++;
    }

    return false;
}

void printSteps(int const& rooms, int room, int light, std::vector<std::vector<int>> previousRooms)
{
    if (room == 0 && light == 1)
    {
        return;
    }

    int lightRoom = previousRooms[room][light];

    if (lightRoom >= rooms)
    {
        // Switch event.

        // Encode added rooms to differentiate between light switching and moving to other room.
        lightRoom -= rooms;

        printSteps(rooms, room, light ^ (1 << lightRoom), previousRooms);

        bool lightOn = (light >> lightRoom) % 2;

        if (lightOn)
        {
            std::cout << "- Switch on light in room " << lightRoom + 1 << ".\n";
        }
        else
        {
            std::cout << "- Switch off light in room " << lightRoom + 1 << ".\n";
        }
    }
    else
    {
        // Room event.
        printSteps(rooms, lightRoom, light, previousRooms);

        std::cout << "- Move to room " << room + 1 << ".\n";
    }
}

int main()
{
    int villaNumber = 1;

    while (true)
    {
        int r;
        int d;
        int s;

        std::cin >> r >> d >> s;

        if (r == 0 && d == 0 && s == 0)
        {
            break;
        }

        std::vector<std::vector<int>> roomsGraph(r, std::vector<int>());
        std::vector<std::vector<int>> switches(r, std::vector<int>());

        // Only the last room light must remain on.
        int lastRoomLight = 1 << (r - 1);

        for (int door = 0; door < d; door++)
        {
            int i, j;

            std::cin >> i >> j;

            i--;
            j--;

            roomsGraph[i].push_back(j);
            roomsGraph[j].push_back(i);
        }

        for (int lightSwitch = 0; lightSwitch < s; lightSwitch++)
        {
            int i, j;

            std::cin >> i >> j;

            i--;
            j--;

            switches[i].push_back(j);
        }

        // Visited room combinations with lights on.
        std::vector<std::vector<bool>> visited(r, std::vector<bool>(1 << r, false));
        // All possible convinations room combinations with lights on.
        std::vector<std::vector<int>> previousRooms(r, std::vector<int>(1 << r, -1));

        visited[0][1] = true;

        int steps = 0;

        bool reachedLastRoom = canReachLastRoomBFS(r, lastRoomLight, steps, roomsGraph, switches, visited, previousRooms);

        std::cout << "Villa #" << villaNumber++ << "\n";

        if (reachedLastRoom)
        {
            std::cout << "The problem can be solved in " << steps << " steps:\n";

            printSteps(r, r - 1, lastRoomLight, previousRooms);
        }
        else
        {
            std::cout << "The problem cannot be solved.\n";
        }

        putchar(10);
    }
}
