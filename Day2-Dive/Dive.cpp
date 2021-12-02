// Dive.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <fstream>

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

	// Part 1 positions
	int horPos1 = 0, horPos2 = 0;

	// Part 2 positions
	int verPos1 = 0, verPos2 = 0;
	int aim = 0;

	// Read stream line by line
	for (std::string line; std::getline(source, line);)
	{
		std::istringstream in(line);

		std::string operation;
		int value;

		// Read in the operation and the value to travel by
		in >> operation;
		in >> value;

		if (operation == "forward")
		{
			horPos1 += value;
			horPos2 += value;
			verPos2 += aim * value;
		}
		else if (operation == "up")
		{
			verPos1 -= value;
			aim -= value;
		}
		else if (operation == "down")
		{
			verPos1 += value;
			aim += value;
		}
		else
		{
			// Unknown operation
		}
	}

	int answer1= horPos1 * verPos1;
	int answer2 = horPos2 * verPos2;

	printf("Answer1: %d\n", answer1);
	printf("Answer2: %d\n", answer2);

}