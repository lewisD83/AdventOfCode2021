// SmokeBasin.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

std::vector<std::string> heightMap;
std::vector<std::string> heightMapCpy;
int length = 0;
int breadth = 0;


int GetNeighbour(int x, int y, int xDelta, int yDelta)
{
	// Get neughbour in direction of xDelta and yDelta
	int newX = x + xDelta;
	int newY = y + yDelta;

	// Make sure we are not out of bounds
	if (newX < 0 || newX >= length || newY < 0 || newY >= breadth)
	{
		return 10;
	}

	// Return the integer value at position
	return (heightMap[newY][newX] - '0');
}

int GetNeighbourRecursve(int x, int y)
{
	if (x < 0 || x >= length || y < 0 || y >= breadth)
	{
		return 0;
	}

	if (heightMapCpy[y][x] == '#')
		return 0;

	int height = heightMap[y][x] - '0';

	if (height == 9)
		return 0;

	heightMapCpy[y][x] = '#';

	int test = 0;

	test += GetNeighbourRecursve(x, y - 1);
	test += GetNeighbourRecursve(x, y + 1);
	test += GetNeighbourRecursve(x - 1, y);
	test += GetNeighbourRecursve(x + 1, y);

	return test + 1;
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

	for (std::string line; std::getline(source, line);)
	{
		heightMap.push_back(line);
		heightMapCpy.push_back(line);
	}

	length = heightMap[0].length();
	breadth = heightMap.size();
	int riskLevel = 0;

	std::vector<int> basinSizes;

	for (int y = 0; y < breadth; y++)
	{
		for (int x = 0; x < length; x++)
		{
			int testHeight = heightMap[y][x] - '0';

			int u = GetNeighbour(x, y, 0, -1);	// up 
			int d = GetNeighbour(x, y, 0, 1);	// down
			int l = GetNeighbour(x, y, -1, 0);	// left
			int r = GetNeighbour(x, y, 1, 0);	// right


			if ((testHeight < u) &&
				(testHeight < d) &&
				(testHeight < l) &&
				(testHeight < r))
			{
				riskLevel += 1 + testHeight;
				heightMapCpy[y][x] = '#';

				int test = 1; 
				test += GetNeighbourRecursve(x, y);
				test += GetNeighbourRecursve(x, y + 1);
				test += GetNeighbourRecursve(x - 1, y);
				test += GetNeighbourRecursve(x + 1, y);

				basinSizes.push_back(test);

				printf("%d\n", test);
			}
		}
	}

	

	std::sort(basinSizes.begin(), basinSizes.end(), std::greater<int>());

	int answer = basinSizes[0] * basinSizes[1] * basinSizes[2];
	//sort(basinSizes.begin(), basinSizes.end());

	for (auto& iter : heightMapCpy)
	{
		printf(iter.c_str());
		printf("\n");
	}


}