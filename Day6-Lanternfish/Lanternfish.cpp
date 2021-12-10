// Lanternfish.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

	// Keep track  of the number of fishies at certain time intervals
	std::vector<long long> fishies(9);

	for (std::string line; std::getline(source, line);)
	{
		std::regex regex("(\\d+)");

		// Hold matches for searching with the above regex
		std::smatch res;

		// Get starting input
		while (std::regex_search(line, res, regex))
		{
			int fish = std::stoi(res[1]);
			line = res.suffix();
			fishies[fish]++;
		}
	}

	int day = 0;
	int testLengthDays = std::stoi(argv[2]);
	while (day < testLengthDays)
	{
		long long fishesAboutToSpawn = fishies[0];
		fishies[0] = fishies[1];
		fishies[1] = fishies[2];
		fishies[2] = fishies[3];
		fishies[3] = fishies[4];
		fishies[4] = fishies[5];
		fishies[5] = fishies[6];
		fishies[6] = fishies[7];
		fishies[7] = fishies[8];

		// On top of the fishes that were on time 7 and dropped to 6, we also have all the fish that were at 0 who go back to 6 
		fishies[6] += fishesAboutToSpawn;

		// time 0 fishes spawn a new fish at time 8, so there are fishesAboutToSpawn amount of new fish introduced to the population
		fishies[8] = fishesAboutToSpawn;

		long long count = fishies[0] + fishies[1] + fishies[2] + fishies[3] + fishies[4] + fishies[5] + fishies[6] + fishies[7] + fishies[8];
		printf("Day %d\n", day+1);
		printf("(%lld, %lld, %lld, %lld, %lld, %lld, %lld, %lld, %lld)    %lld fishies \n\n", fishies[0], fishies[1], fishies[2], fishies[3], fishies[4], fishies[5], fishies[6], fishies[7], fishies[8], count);
		day++;
 	}
		
}