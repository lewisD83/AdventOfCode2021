// DumboOctopus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <deque>

class Point
{
public:
	Point()
		: x(0)
		, y(0)
	{

	}

	Point(int _x, int _y)
		: x(_x)
		, y(_y)
	{

	}

	int x, y;
};


std::vector<std::string> octopi;
int length = 0;
int breadth = 0;

int GetNeighbour(int x, int y)
{
	// Make sure we are not out of bounds
	if (x < 0 || x >= length || y < 0 || y >= breadth)
	{
		return 10;
	}

	// Return the integer value at position
	return (octopi[y][x] - '0');
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
		octopi.push_back(line);
		//printf("%s\n", line.c_str());
	}
	//printf("\n");

	length = octopi[0].length();
	breadth = octopi.size();

	std::vector<std::vector<bool> > visitedOctopi(length, std::vector<bool>(breadth, false));
	std::vector<std::vector<bool> > pulsedOctopi(length, std::vector<bool>(breadth, false));

	visitedOctopi = std::vector<std::vector<bool> >(length, std::vector<bool>(breadth, false));
	pulsedOctopi = std::vector<std::vector<bool> >(length, std::vector<bool>(breadth, false));

	std::deque<Point> neighbours;

	int step = 0;
	int flashes = 0;

	while (true)
	{
		step++;
		int flashesAtStep = 0;
		pulsedOctopi = std::vector<std::vector<bool> >(length, std::vector<bool>(breadth, false));

		for (int y = 0; y < breadth; y++)
		{
			for (int x = 0; x < length; x++)
			{
				if (x == 0 && y == 0)
				{
					int test;
					test = 5;
				}

				char& octopus = octopi[y][x];
				if (pulsedOctopi[x][y] == false)
				{
					octopus++;
				}

				if ( (octopus - '0') > 9 && pulsedOctopi[x][y] == false)
				{
					octopus = '0';
					pulsedOctopi[x][y] = true;
					flashesAtStep++;

					neighbours.push_back(Point(x, y - 1));		// up
					neighbours.push_back(Point(x, y + 1));		// down
					neighbours.push_back(Point(x - 1, y));		// left 
					neighbours.push_back(Point(x + 1, y));		// right 
					neighbours.push_back(Point(x + 1, y - 1));	// up-right
					neighbours.push_back(Point(x + 1, y + 1));	// down-right
					neighbours.push_back(Point(x - 1, y + 1));	// down-left
					neighbours.push_back(Point(x - 1, y - 1));	// up-left

					while (!neighbours.empty())
					{
						Point n = neighbours[0];
						if (n.x < 0 || n.x >= length || n.y < 0 || n.y >= breadth)
						{
							neighbours.pop_front();
							continue;
						}

						if (n.x == 0 && n.y == 0)
						{
							int test;
							test = 5;
						}

						char& neighbour = octopi[n.y][n.x];
						if (pulsedOctopi[n.x][n.y] == false)
						{
							neighbour++;
						}

						if ( (neighbour - '0') > 9 && pulsedOctopi[n.x][n.y] == false)
						{
							neighbour = '0';
							pulsedOctopi[n.x][n.y] = true;
							flashesAtStep++;
							
							neighbours.push_back(Point(n.x, n.y - 1));		// up
							neighbours.push_back(Point(n.x, n.y + 1));		// down
							neighbours.push_back(Point(n.x - 1, n.y));		// left 
							neighbours.push_back(Point(n.x + 1, n.y));		// right 
							neighbours.push_back(Point(n.x + 1, n.y - 1));	// up-right
							neighbours.push_back(Point(n.x + 1, n.y + 1));	// down-right
							neighbours.push_back(Point(n.x - 1, n.y + 1));	// down-left
							neighbours.push_back(Point(n.x - 1, n.y - 1));	// up-left
						}

						neighbours.pop_front();
					}
				}
			}
		}

		flashes += flashesAtStep;
		if (flashesAtStep == (length * breadth))
		{
			int test;
			test = 5;
		}
	}

	printf("flashes: %d", flashes);
}