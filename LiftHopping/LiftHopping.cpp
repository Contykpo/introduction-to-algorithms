// Samuel Furlanich - Tecnicas de Diseño de Algoritmos 1C 2024 Turno Mañana.
// LiftHopping.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <vector>
#include <queue>
#include <string>
#include <sstream>

struct Elevator
{
	 // Elevator identification number.
	 int id;
	 int currentFloor;
	 int destinationFloor;
	 // The "weight" or time that takes the elevator to go from x floor to y floor.
	 int time;
 
	 // Override > comparison operator for std::priorty_queue.
	 bool operator>(const Elevator& e) const
	 {
		 return this->time > e.time;
	 }
};

// Dijkstra's algorithm using a priority queue (min-heap).
void findShortestPathTimeDijkstra(std::vector<std::vector<Elevator>>& elevators, std::vector<int>& elevatorIDs, std::vector<int>& elevatorTimes, std::vector<int>& shortestPathTime)
{
	std::priority_queue<Elevator, std::vector<Elevator>, std::greater<Elevator> > pQueue;

	Elevator defaultElevator;
	defaultElevator.currentFloor = 0;
	defaultElevator.destinationFloor = 0;
	defaultElevator.time = 0;

	shortestPathTime[0] = 0;

	pQueue.push(defaultElevator);

	while (!pQueue.empty())
	{
		Elevator uElevator = pQueue.top();

		pQueue.pop();

		if (shortestPathTime[uElevator.destinationFloor] != uElevator.time)
		{
			continue;
		}

		// Expand the floor.
		for (int i = 0; i < elevators[uElevator.destinationFloor].size(); ++i)
		{
			Elevator vElevator = elevators[uElevator.destinationFloor][i];

			int altTotalTime = shortestPathTime[vElevator.currentFloor] + abs(vElevator.destinationFloor - vElevator.currentFloor) * elevatorTimes[vElevator.id];

			// Switch to another elevator.
			if (elevatorIDs[vElevator.currentFloor] != -1 && elevatorIDs[vElevator.currentFloor] != vElevator.id)
			{
				altTotalTime += 60;
			}

			if (shortestPathTime[vElevator.destinationFloor] == -1 || altTotalTime < shortestPathTime[vElevator.destinationFloor])
			{
				shortestPathTime[vElevator.destinationFloor] = altTotalTime;
				
				vElevator.time = altTotalTime;
				
				elevatorIDs[vElevator.destinationFloor] = vElevator.id;
				
				pQueue.push(vElevator);
			}
		}
	}
}

int main()
{
	int numberOfElevators;
	int targetFloor;

	int const V = 100;

	while (std::cin >> numberOfElevators >> targetFloor)
	{
		std::vector<std::vector<Elevator>> elevators(V);
		std::vector<int> elevatorTimes(numberOfElevators + 1);

		for (int id = 1; id <= numberOfElevators; ++id)
		{
			std::cin >> elevatorTimes[id];
		}

		std::cin.ignore();
  
		for (int id = 1; id <= numberOfElevators; ++id)
		{
			std::vector<int> floors;

			int floor;

			std::string floorStringLine;

			std::getline(std::cin, floorStringLine);

			std::stringstream stringStream(floorStringLine);

			while (stringStream >> floor)
			{
				floors.push_back(floor);
			}

			// Enumerate all pairs of different floors.
			for (int i = 0; i < floors.size(); ++i)
			{
				for (int j = i + 1; j < floors.size(); ++j)
				{
					Elevator elevator;
					elevator.id = id;
					elevator.time = 0;

					// floors[i] to floors[j].
					elevator.currentFloor = floors[i];
					elevator.destinationFloor = floors[j];

					elevators[floors[i]].push_back(elevator);

					// floors[j] to floors[i].
					elevator.currentFloor = floors[j];
					elevator.destinationFloor = floors[i];

					elevators[floors[j]].push_back(elevator);
				}
			}
		}

		// Time of shortest path of elevators for each floor.
		std::vector<int> shortestPathTime(V, -1);
		std::vector<int> elevatorIDs(V, -1);

		// Find shortest path time for each floor.
		findShortestPathTimeDijkstra(elevators, elevatorIDs, elevatorTimes, shortestPathTime);

		if (shortestPathTime[targetFloor] == -1)
		{
			std::cout << "IMPOSSIBLE" << '\n';
		}
		else
		{
			std::cout << shortestPathTime[targetFloor] << '\n';
		}

	}

	return 0;
}
