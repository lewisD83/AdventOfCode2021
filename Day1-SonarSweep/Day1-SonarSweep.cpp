// Sonar Sweep.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

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

	std::vector<int> inputs;

	// Read stream line by line
	for (std::string line; std::getline(source, line);)
	{
		// Make a stream for the line itself
		std::istringstream in(line);

		int currentReading;
		in >> currentReading;

		inputs.push_back(currentReading);
	}

	// Part 1
	{
		int previousReading = inputs[0];
		int answer = 0;

		for (int index = 1; index < inputs.size(); index++)
		{
			int currentReading = inputs[index];

			if (currentReading > previousReading)
				answer++;

			previousReading = currentReading;
		}

		printf("Answer: %d\n", answer);
	}

	// Part 2
	{
		int previousSum = inputs[0] + inputs[1] + inputs[2];
		int answerPart2 = 0;

		for (int index = 1; index < inputs.size() - 2; index++)
		{
			int currentSum = inputs[index] + inputs[index + 1] + inputs[index + 2];

			if (currentSum > previousSum)
				answerPart2++;

			previousSum = currentSum;
		}

		printf("Answer: %d\n", answerPart2);
	}

	// Part 2 - alternate
	{
		int answerPart2 = 0;

		for (int index = 0; index < inputs.size() - 3; index++)
		{
			int currentSum = inputs[index + 3] - inputs[index];

			if (currentSum > 0)
				answerPart2++;
		}

		printf("Answer: %d\n", answerPart2);
	}
}