// TheTreacheryOfWhales.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

int main(int argc, char* argv[])
{
	// build a read-Stream
	std::ifstream source;

	// Open the sample problem
	source.open(argv[1], std::ios_base::in);

	// Check if there was a problem opening the file
	if (!source)
	{
		std::cout << "Can't open file!";
	}

	std::vector<int> crabsPositions;

	for (std::string line; std::getline(source, line);)
	{
		std::regex regex("(\\d+)");

		// Hold matches for searching with the above regex
		std::smatch res;

		// Get starting input
		while (std::regex_search(line, res, regex))
		{
			int crabPos = std::stoi(res[1]);
			line = res.suffix();
			
			// We are about to read the first position
			if (crabsPositions.empty())
			{
				crabsPositions.push_back(crabPos);
				continue;
			}

			// As we read in input its much easier to work out the answers if we sort it into ascending order
			for (std::vector<int>::iterator iter = crabsPositions.begin(); ; )
			{
				int currentPos = *iter;

				// If the crabPos we read in is higher than current pos then move up in the vector till we find a place to put it 
				if (crabPos > currentPos)
				{
					iter++;
				}
				else
				{
					crabsPositions.emplace(iter, crabPos);
					break;
				}

				// If we reach the end then this is now the new highest position in the vector so just push it to the back
				if (iter == crabsPositions.end())
				{
					crabsPositions.push_back(crabPos);
					break;
				}
			}
		}
	}

	int prevFuelConsumed = 0;
	int prevFuelConsumed2 = 0;
	int lowestFuelConsumptionPos = -1;
	int lowestFuelConsumptionPos2 = -1;
	bool foundLowestFuel = false;
	bool foundLowestFuel2 = false;

	// Brute force method.
	// For every position attempt to lower every other position to the current one and keep track of the fuel used always keeping track of the position and value of the lowest fuel used
	for (int i = 0; i < (int)crabsPositions.size(); i++)
	{
		int currentPosition = crabsPositions[i];
		int fuelConsumed = 0;
		int fuelConsumed2 = 0;

		for (int j = 0; j < (int)crabsPositions.size(); j++)
		{
			// Don't compare the same crab at one position
			if(i==j)
				continue;

			// The absolute difference is the amount of fuel that it would take to travel this c
			int testPosition = crabsPositions[j];
			int difference = abs(currentPosition - testPosition);
		
			// For part 1 the fuel consumed is just the difference
			fuelConsumed += difference;

			// Part 2 is the sum of all the integers leading up to the difference
			// So if difference is 4 then the actual fuel consumed is 1+2+3+4 formula is (n(n+1))/2 where n is the last number in the sequence
			fuelConsumed2 += (difference * (difference + 1)) / 2;

		}

		if (!foundLowestFuel)
		{
			// We can't assume that its only the positions that the crabs are currently in that could be the potential winning position
			// There could be a psition in between so we need to keep digging, keeping track of the lowest fuel used until the fuelUsed goes back up again
			if (prevFuelConsumed == 0 || fuelConsumed <= prevFuelConsumed)
			{
				if (prevFuelConsumed == fuelConsumed && lowestFuelConsumptionPos != -1)
				{
				}
				else
				{
					lowestFuelConsumptionPos = i;
				}

				prevFuelConsumed = fuelConsumed;
			}
			else
			{
				// The fule consumed has now gone back up
				// We can now ignore the rest of the crab positions as we sorted the list, we know that any positions above will be too much fuel

				int lowestFuelConsumption = crabsPositions[lowestFuelConsumptionPos];	// the lowest fuel used that we worked out
				int maxRange = crabsPositions[i];										// i is the position where the fuel went back up, so we need to check positions in between

				for (int j = lowestFuelConsumption + 1; j < maxRange; j++)
				{
					int testFuel = 0;

					for (int i = 0; i < (int)crabsPositions.size(); i++)
					{
						int testPosition = crabsPositions[i];
						int difference = abs(j - testPosition);

						testFuel += difference;
					}

					if (testFuel < prevFuelConsumed)
					{
						lowestFuelConsumptionPos = i;
						prevFuelConsumed = testFuel;
					}
				}

				foundLowestFuel = true;
			}
		}

		if (!foundLowestFuel2)
		{
			if (prevFuelConsumed2 == 0 || fuelConsumed2 <= prevFuelConsumed2)
			{
				if (prevFuelConsumed2 == fuelConsumed2 && lowestFuelConsumptionPos2 != -1)
				{
				}
				else
				{
					lowestFuelConsumptionPos2 = i;
				}

				prevFuelConsumed2 = fuelConsumed2;
			}
			else
			{
				int lowestFuelConsumption = crabsPositions[lowestFuelConsumptionPos2];
				int maxRange = crabsPositions[i];

				for (int j = lowestFuelConsumption + 1; j < maxRange; j++)
				{
					int testFuel = 0;

					for (int i = 0; i < (int)crabsPositions.size(); i++)
					{
						int testPosition = crabsPositions[i];
						int difference = abs(j - testPosition);

						testFuel += (difference * (difference + 1)) / 2;
					}

					if (testFuel < prevFuelConsumed2)
					{

						lowestFuelConsumptionPos2 = i;
						prevFuelConsumed2 = testFuel;
					}
				}

				foundLowestFuel2 = true;
			}
		}
	}
}