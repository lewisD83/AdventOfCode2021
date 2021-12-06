// BinaryDiagnostic.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

void FilterRatings(std::vector<std::string>& rating, bool filterMostCommon)
{
	int currentIndex = 0;

	while (rating.size() != 1)
	{
		std::vector<std::string> ones;
		std::vector<std::string> zeros;

		for (auto& iter : rating)
		{
			if (iter[currentIndex] == '1')
			{
				ones.push_back(iter);
			}
			else
			{
				zeros.push_back(iter);
			}
		}

		if(filterMostCommon)
		{
			if (ones.size() > zeros.size())
			{
				rating = ones;
			}
			else if (ones.size() == zeros.size())
			{
				rating = ones;
			}
			else
			{
				rating = zeros;
			}
		}
		else
		{
			if (ones.size() > zeros.size())
			{
				rating = zeros;
			}
			else if (ones.size() == zeros.size())
			{
				rating = zeros;
			}
			else
			{
				rating = ones;
			}
		}

		currentIndex++;
	}
}

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

	std::vector<std::string> numbers;
	std::vector<int> counts;

	// Read stream line by line
	for (std::string line; std::getline(source, line);)
	{
		numbers.push_back(line);

		if (counts.empty())
		{
			for (int i = 0; i < (int)line.length(); i++)
			{
				if (line[i] == '1')
				{
					counts.push_back(1);
				}
				else
				{
					counts.push_back(0);
				}
			}
			continue;
		}

		// As we read in the input keep track of all the ones in each position
		// If we know the ones then we also know the zeros by default 
		for (int i = 0; i < (int)line.length(); i++)
		{
			if (line[i] == '1')
			{
				counts[i]++;
			}
		}
	}

	std::string gammaRate("");
	std::string epsilonRate("");

	// In each position check which is more abundant 1 or 0? 
	// Gamma always takes the most common and epsilon takes the least common
	for (auto& iter : counts)
	{
		// Iter will be the count of 1's in any given position. If we have a binary number that is of 10 length then if the count of 1's is over 5 then its the most abundant bit
		// This code assumes that there can never be an equal amount of 1's and 0's, problem never mentions what should happen in this case

		// 1 is most common
		if (iter > (int)(numbers.size() / 2))
		{
			gammaRate.push_back('1');
			epsilonRate.push_back('0');
		}
		// 0 is most common 
		else
		{
			gammaRate.push_back('0');
			epsilonRate.push_back('1');
		}
	}

	// We have gamma and epsilon rating as binary string number so converet to decimal int
	int gammaRating = std::stoi(gammaRate, 0, 2);
	int epsilonRating = std::stoi(epsilonRate, 0, 2);
	
	int answer = gammaRating * epsilonRating;

	printf("Answer: %d\n", answer);

	// Hold a vector of binary string numebrs which will eventuall filter down to give the correct CO2 and O2 ratings
	std::vector<std::string> O2 = numbers;
	std::vector<std::string> CO2 = numbers;
	
	FilterRatings(O2, true);
	FilterRatings(CO2, false);

	// Again we have the rating as a binary string number so convert to decimal
	int O2Rating = std::stoi(O2[0], 0, 2);
	int CO2Rating = std::stoi(CO2[0], 0, 2);

	answer = O2Rating * CO2Rating;

	printf("Answer: %d\n", answer);

}