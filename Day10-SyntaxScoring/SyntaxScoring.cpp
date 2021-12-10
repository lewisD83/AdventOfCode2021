// SyntaxScoring.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
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
	
	std::vector<std::string> corruptLines;
	long long points1 = 0;
	long long points2 = 0;

	std::vector<long long> pointsTotal;

	for (std::string line; std::getline(source, line);)
	{
		printf("%s\n", line.c_str());

		std::stringstream in(line);

		std::vector<char> characters;
		char character;
		bool lineCorrupt = false;
		
		while (in >> character)
		{
			if (character == '[' ||
				character == '(' ||
				character == '{' ||
				character == '<')
			{
				characters.push_back(character);
			}
			else
			{
				char test = characters[characters.size() - 1];
				
				if ((test == '(') && character == ')' ||
					(test == '[') && character == ']' ||
					(test == '{') && character == '}' ||
					(test == '<') && character == '>')
				{
					characters.pop_back();
				}
				else
				{
					lineCorrupt = true;
					corruptLines.push_back(line);
					if		(character == ')') points1 += 3;
					else if (character == ']') points1 += 57;
					else if (character == '}') points1 += 1197;
					else if (character == '>') points1 += 25137;

					break;
				}
			}
			
		}
		
		if (lineCorrupt == false)
		{
			for (auto iter = characters.rbegin(); iter != characters.rend(); iter++)
			{
				char c = *iter;
				points2 *= 5;

				if		(c == '(') points2 += 1;
				else if (c == '[') points2 += 2;
				else if (c == '{') points2 += 3;
				else if (c == '<') points2 += 4;
			}

			pointsTotal.push_back(points2);
		}
		points2 = 0;
	}

	sort(pointsTotal.begin(), pointsTotal.end());

	int foo = pointsTotal.size() / 2;

	long long answer = pointsTotal[foo];
	printf("%lld", answer);
}

