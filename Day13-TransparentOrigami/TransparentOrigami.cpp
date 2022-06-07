// TransparentOrigami.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>

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

	bool operator == (const Point& p)
	{
		return (this->x == p.x && this->y == p.y);
	}

	int x, y;
};

std::vector<Point> paper;

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
		if (line.empty())
			continue;

		std::regex regex("(\\d+),(\\d+)");

		// Hold matches for searching with the above regex
		std::smatch res;

		

		// Get us the first bag in the line which holds rules for what it contains
		if(std::regex_search(line, res, regex))
		{
			int x = std::stoi(res[1]);
			int y = std::stoi(res[2]);

			paper.push_back(Point(x, y));
		}
		else
		{
			int delimeter = line.find("=");
			char axis = line[delimeter-1];
			std::string coordinate = line.substr(delimeter+1, line.length());
			int coord = std::stoi(coordinate);

			auto point = paper.begin();
			while (point != paper.end())
			{
				bool skip = false;

				if (axis == 'x')
				{
					if ((*point).x == coord)
					{
						point = paper.erase(point);
						continue;
					}

					if ((*point).x > coord)
					{
						Point test = (*point);

						test.x = coord - (test.x - coord);


						auto iter = paper.begin();
						while (iter != paper.end())
						{
							if ((*iter) == test && iter != point && (*iter).x < coord)
							{
								point = paper.erase(point);
								skip = true;
								break;
							}
							else
							{
								iter++;
							}
						}

						if (skip)
						{
							continue;
						}

						(*point) = test;
					}
				}
				else
				{
					if ((*point).y == coord)
					{
						paper.erase(point);
						continue;
					}

					if ((*point).y > coord)
					{
						Point test = (*point);
						test.y = coord - (test.y - coord);
												
						auto iter = paper.begin();
						while (iter != paper.end())
						{
							if ((*iter) == test && iter != point && (*iter).y < coord)
							{
								point = paper.erase(point);
								skip = true;
								break;
							}
							else
							{
								iter++;
							}
						}

						if (skip)
						{
							continue;
						}

						(*point) = test;
						
					}
				}

				point++;
			}


			

		}

	}

	std::vector<std::vector<char> > grid(50, std::vector<char>(50, '.'));

	for (auto& point : paper)
	{
		grid[point.x][point.y] = '#';
	}

	for (int i = 0; i < 50; i++)
	{
		printf("\n");
		for (int j = 0; j < 50; j++)
		{
			printf("%c", grid[j][i]);
		}
	}

	int test;
	test = 5;

}