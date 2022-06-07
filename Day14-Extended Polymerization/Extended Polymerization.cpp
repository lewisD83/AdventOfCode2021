// Extended Polymerization.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

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

	std::unordered_map<std::string, std::string> rules;
	std::unordered_map<std::string, long long> rulesCount;
	std::string polymer;

	for (std::string line; std::getline(source, line);)
	{
		if (line.empty())
			continue;

		int delimeter = line.find_first_of("->");

		if (delimeter > 0)
		{
			std::string key;
			std::string value;

			key = line.substr(0, delimeter - 1);
			value = line.substr(delimeter + 3, line.length());

			rules[key] = value;
		}
		else
		{
			polymer = line;
		}

	}

	std::vector<long long> charCount(26, 0);

	for (int i = 0; i < (int)polymer.length() - 1; i++)
	{
		std::string rule("");
		rule += polymer[i];
		rule += polymer[i + 1];

		if (rules.find(rule) != rules.end())
		{
			if (rulesCount.find(rule) != rulesCount.end())
			{
				rulesCount[rule]++;
			}
			else
			{
				rulesCount[rule] = 1;
			}
		}

		int c1 = polymer[i];
		charCount[c1 - 65]++;

		if (i + 1 == (int)polymer.length() - 1)
		{
			c1 = polymer[i + 1];
			charCount[c1 - 65]++;
		}
	}

	{
		int step = 0;
		while (step != 40)
		{
			step++;

			std::unordered_map<std::string, long long> prevRulesCount = rulesCount;
			std::unordered_map<std::string, long long> currRulesCount;

			for (auto iter : prevRulesCount)
			{
				std::string key = iter.first;
				long long count = iter.second;

				std::string replaceStr = rules[key];

				std::string rule("");
				rule += key[0];
				rule += replaceStr;

				std::string rule2("");
				rule2 += replaceStr;
				rule2 += key[1];

				charCount[replaceStr[0] - 65] += count;

				if (currRulesCount.find(rule) != currRulesCount.end())
				{
					currRulesCount[rule] += count;
				}
				else
				{
					currRulesCount[rule] = count;
				}

				if (currRulesCount.find(rule2) != currRulesCount.end())
				{
					currRulesCount[rule2] += count;
				}
				else
				{
					currRulesCount[rule2] = count;
				}
			}

			rulesCount = currRulesCount;

			if (step == 10 || step == 40)
			{
				std::vector<long long> temp = charCount;
				sort(temp.begin(), temp.end());

				long long min, max;

				for (int i = 0; i < (int)temp.size(); i++)
				{
					if (temp[i] != 0)
					{
						min = temp[i];
						max = temp[temp.size() - 1];
						break;
					}
				}

				long long answer = max - min;
				printf("Answer = %lld\n", answer);
			}
		}
	}
}