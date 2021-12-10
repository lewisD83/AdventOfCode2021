// Seven Segment Search.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>
#include <algorithm>
#include <string>

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

	std::vector<std::string> outputStrs;
	int answerP1 = 0;
	int answerP2 = 0;

	for (std::string line; std::getline(source, line);)
	{
		int delimerter = line.find_first_of('|');
		std::string input = line.substr(0, delimerter);
		std::string output = line.substr(delimerter + 2, line.length());

		std::istringstream in(input);
		std::istringstream out(output);

		int result = 0;

		std::string reading;

		while (out >> reading)
		{
			if (reading.length() == 2 ||
				reading.length() == 3 ||
				reading.length() == 4 ||
				reading.length() == 7)
			{
				answerP1++;
			}
			outputStrs.push_back(reading);
		}


		std::vector<std::string> segmentNumbers(10, "");
		std::vector<std::string> tempHolding;
		while (in >> reading)
		{
			if (reading.length() == 2)
			{
				segmentNumbers[1] = reading;
			}
			else if (reading.length() == 3)
			{
				segmentNumbers[7] = reading;
			}
			else if (reading.length() == 4)
			{
				segmentNumbers[4] = reading;
			}
			else if (reading.length() == 7)
			{
				segmentNumbers[8] = reading;
			}
			else
			{
				tempHolding.push_back(reading);
			}
		}

		// Find number 9
		//  contains everything of 4 and 7

		std::string filter = segmentNumbers[4] + segmentNumbers[7];
		for (std::vector<std::string>::const_iterator iter = tempHolding.begin(); iter != tempHolding.end(); iter++)
		{
			std::string test = *iter;

			std::size_t found = test.find_first_of(filter);
			int count = 0;

			while (found != std::string::npos)
			{
				count++;
				found = test.find_first_of(filter, found + 1);
			}

			if (count == 5)
			{
				segmentNumbers[9] = test;
				tempHolding.erase(iter);
				break;
			}
		}

		// Find 2
		// 2 contains 4 of the letters in 9
		filter = segmentNumbers[9];
		for (std::vector<std::string>::const_iterator iter = tempHolding.begin(); iter != tempHolding.end(); iter++)
		{
			std::string test = *iter;

			std::size_t found = test.find_first_of(filter);
			int count = 0;

			while (found != std::string::npos)
			{
				count++;
				found = test.find_first_of(filter, found + 1);
			}

			if (count == 4)
			{
				segmentNumbers[2] = test;
				tempHolding.erase(iter);
				break;
			}
		}

		// Find 3
		// 3 contains only 3 letters in 7
		filter = segmentNumbers[7];
		for (std::vector<std::string>::const_iterator iter = tempHolding.begin(); iter != tempHolding.end(); iter++)
		{
			std::string test = *iter;

			std::size_t found = test.find_first_of(filter);
			int count = 0;

			while (found != std::string::npos)
			{
				count++;
				found = test.find_first_of(filter, found + 1);
			}

			if (count == 3 && test.length() == 5)
			{
				segmentNumbers[3] = test;
				tempHolding.erase(iter);
				break;
			}
		}

		// 5 is the remaing 5 length string
		for (std::vector<std::string>::const_iterator iter = tempHolding.begin(); iter != tempHolding.end(); iter++)
		{
			std::string test = *iter;
			if (test.length() == 5)
			{
				segmentNumbers[5] = test;
				tempHolding.erase(iter);
				break;
			}
		}

		// find 6
		// 5 appears in six with 5 letters 
		filter = segmentNumbers[5];
		for (std::vector<std::string>::const_iterator iter = tempHolding.begin(); iter != tempHolding.end(); iter++)
		{
			std::string test = *iter;

			std::size_t found = test.find_first_of(filter);
			int count = 0;

			while (found != std::string::npos)
			{
				count++;
				found = test.find_first_of(filter, found + 1);
			}

			if (count == 5)
			{
				segmentNumbers[6] = test;
				tempHolding.erase(iter);
				break;
			}
		}

		// last number is zero 
		segmentNumbers[0] = tempHolding[0];

		for (int i = 0; i < (int)segmentNumbers.size(); i++)
		{
			sort(segmentNumbers[i].begin(), segmentNumbers[i].end());
			printf("%s: %d\n", segmentNumbers[i].c_str(), i);
		}

		printf("\n");

		int outputRes = 0;

		for (int i = 0; i < (int)outputStrs.size(); i++)
		{
			std::string output = outputStrs[i];

			for (int j = 0; j < (int)segmentNumbers.size(); j++)
			{
				std::string filter = segmentNumbers[j];

				// Now that we have all the strings all we need to do is for each string in the output do a find_first_not_of
				// if match is at the end of the string this means that the output string we are dealing with matches the filter perfectly 
				int match = output.find_first_not_of(filter);
				if (match == std::string::npos && filter.length() == output.length())
				{
					outputRes *= 10;
					outputRes += j;
					break;
				}
			}
		}

		answerP2 += outputRes;
		tempHolding.clear();
		segmentNumbers.clear();
		outputStrs.clear();
	}

	printf("\n");
	outputStrs.clear();

	printf("Answer: %d\n", answerP1);
	printf("Answer: %d\n", answerP2);

}