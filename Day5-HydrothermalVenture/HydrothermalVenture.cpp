// HydrothermalVenture.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <regex>

#include <SFML/Graphics.hpp>
#include <Windows.h>

class Point
{
public:

	Point()
		: x(0)
		, y(0)
		, visited(1)
	{

	}

	Point(int x, int y)
		: x(x)
		, y(y)
		, visited(1)
	{

	}

	int x;
	int y;
	int visited;
};

class Line
{
public:
	Line()
		: x1(0)
		, y1(0)
		, x2(0)
		, y2(0)
	{

	}

	Line(Point start, Point end)
		: start(start)
		, end(end)
	{
		x1 = start.x;
		y1 = start.y;
		x2 = end.x;
		y2 = end.y;
	}

	int x1, y1;
	int x2, y2;
	Point start, end;
};

int main(int argc, char* argv[])
{
	// build a read-Stream
	std::ifstream source;

	// Open the sample problem
	source.open(argv[1], std::ios_base::in);

	std::vector<Line> lines;

	std::vector<std::vector<int>> grid(1000, std::vector<int>(1000, 0));

	// Check if there was a problem opening the file
	if (!source)
	{
		std::cout << "Can't open file!";
	}

	::ShowWindow(::GetConsoleWindow(), SW_HIDE);

	// Prepare window
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Toboggan Trajectory");
	window.setFramerateLimit(60);

	{
		for (std::string line; std::getline(source, line);)
		{
			std::regex regex("(\\d+)");

			// Hold matches for searching with the above regex
			std::smatch res;

			bool subRules = false;

			int i = 0;
			Point start, end;

			// Get us the first bag in the line which holds rules for what it contains
			while (std::regex_search(line, res, regex))
			{
				int coord = std::stoi(res[1]);
				if (i == 0)
				{
					start.x = coord;
				}
				else if (i == 1)
				{

					start.y = coord;
				}
				else if (i == 2)
				{
					end.x = coord;
				}
				else if (i == 3)
				{
					end.y = coord;
				}
				i++;
				line = res.suffix();
			}

			lines.push_back(Line(start, end));

			if (start.x == end.x)
			{
				int direction = 1;

				if (start.y > end.y)
					direction = -1;

				int x = start.x;
				int y = start.y;

				while (y != (end.y + 1 * direction))
				{
					grid[x][y]++;
					y += 1 * direction;
				}
			}
			else if (start.y == end.y)
			{
				int direction = 1;

				if (start.x > end.x)
					direction = -1;

				int x = start.x;
				int y = start.y;

				while (x != (end.x + 1 * direction))
				{
					grid[x][y]++;
					x += 1 * direction;
				}
			}
			else
			{
				int directionX = 1;
				int directionY = 1;

				if (start.x > end.x)
					directionX = -1;

				if (start.y > end.y)
					directionY = -1;

				int x = start.x;
				int y = start.y;

				while (x != (end.x + 1 * directionX) && y != (end.y + 1 * directionY))
				{

					grid[x][y]++;
					x += 1 * directionX;
					y += 1 * directionY;
				}
			}
		}

		int answer = 0;

		for (int i = 0; i < 1000; i++)
		{
			for (int j = 0; j < 1000; j++)
			{
				if (grid[i][j] > 1)
				{
					answer++;
				}
			}
		}

		printf("Answer: %d\n", answer);
	}

	int foo = 1;
	bool render = false;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			render = true;
		}

		window.clear();
			
		if (render)
		{
			for (int i = 0; i < foo; i++)
			{
				sf::Vertex SFLine[2];
				SFLine[0].position = sf::Vector2f(lines[i].x1, lines[i].y1);
				SFLine[0].color = sf::Color::White;
				//SFLine[0].color.a = 50;
				SFLine[1].position = sf::Vector2f(lines[i].x2, lines[i].y2);
				SFLine[1].color = sf::Color::White;
				//SFLine[1].color.a = 50;


				window.draw(SFLine, 2, sf::Lines);
			}
			foo++;

			if (foo == lines.size())
				foo = lines.size() - 1;
		}

		window.display();
		Sleep(10);
	}
}






//// HydrothermalVenture.cpp : This file contains the 'main' function. Program execution begins and ends there.
////
//
//#include <iostream>
//#include <sstream>
//#include <fstream>
//#include <vector>
//#include <regex>
//
//class Point
//{
//public:
//
//	Point()
//		: x(0)
//		, y(0)
//		, visited(1)
//	{
//
//	}
//
//	Point(int x, int y)
//		: x(x)
//		, y(y)
//		, visited(1)
//	{
//
//	}
//
//	int x;
//	int y;
//	int visited;
//};
//
//class Line
//{
//public:
//	Line()
//		: x1(0)
//		, y1(0)
//		, x2(0)
//		, y2(0)
//	{
//
//	}
//
//	Line(Point start, Point end)
//		: start(start)
//		, end(end)
//	{
//		x1 = start.x;
//		y1 = start.y;
//		x2 = end.x;
//		y2 = end.y;
//	}
//
//	int x1, y1;
//	int x2, y2;
//	Point start, end;
//};
//
//int main(int argc, char* argv[])
//{
//	// build a read-Stream
//	std::ifstream source;
//
//	// Open the sample problem
//	source.open(argv[1], std::ios_base::in);
//
//	std::vector<Line> lines;
//	std::vector<Point> points;
//
//	std::vector<std::vector<int>> grid(1000, std::vector<int>(1000, 0));
//
//	// Check if there was a problem opening the file
//	if (!source)
//	{
//		std::cout << "Can't open file!";
//	}
//
//	for (std::string line; std::getline(source, line);)
//	{
//		std::regex regex("(\\d+)");
//
//		// Hold matches for searching with the above regex
//		std::smatch res;
//
//		bool subRules = false;
//
//		int i = 0;
//		Point start, end;
//
//		// Get us the first bag in the line which holds rules for what it contains
//		while (std::regex_search(line, res, regex))
//		{
//			int coord = std::stoi(res[1]);
//			if (i == 0)
//			{
//				start.x = coord;
//			}
//			else if (i == 1)
//			{
//
//				start.y = coord;
//			}
//			else if (i == 2)
//			{
//				end.x = coord;
//			}
//			else if (i == 3)
//			{
//				end.y = coord;
//			}
//			i++;
//			line = res.suffix();
//		}
//
//		lines.push_back(Line(start, end));
//
//		if (start.x == end.x)
//		{
//			int direction = 1;
//
//			if (start.y > end.y)
//				direction = -1;
//
//			Point currentPos;
//
//			int x = start.x;
//			int y = start.y;
//
//			while (y != (end.y + 1 * direction))
//			{
//				bool added = false;
//				currentPos.x = x;
//				currentPos.y = y;
//
//				for (auto& point : points)
//				{
//					if (point.x == currentPos.x && point.y == currentPos.y)
//					{
//						added = true;
//						point.visited++;
//						break;
//					}
//				}
//				y += 1 * direction;
//
//				if (!added)
//					points.push_back(currentPos);
//			}
//		}
//		else if (start.y == end.y)
//		{
//			int direction = 1;
//
//			if (start.x > end.x)
//				direction = -1;
//
//			Point currentPos;
//
//			int x = start.x;
//			int y = start.y;
//
//			while (x != (end.x + 1 * direction))
//			{
//				bool added = false;
//				currentPos.x = x;
//				currentPos.y = y;
//
//				for (auto& point : points)
//				{
//					if (point.x == currentPos.x && point.y == currentPos.y)
//					{
//						added = true;
//						point.visited++;
//						break;
//					}
//				}
//				x += 1 * direction;
//
//				if (!added)
//					points.push_back(currentPos);
//			}
//		}
//		else
//		{
//			int directionX = 1;
//			int directionY = 1;
//
//			if (start.x > end.x)
//				directionX = -1;
//
//			if (start.y > end.y)
//				directionY = -1;
//
//			Point currentPos;
//
//			int x = start.x;
//			int y = start.y;
//
//			while (x != (end.x + 1 * directionX) && y != (end.y + 1 * directionY))
//			{
//				bool added = false;
//				currentPos.x = x;
//				currentPos.y = y;
//
//				for (auto& point : points)
//				{
//					if (point.x == currentPos.x && point.y == currentPos.y)
//					{
//						added = true;
//						point.visited++;
//						break;
//					}
//				}
//				x += 1 * directionX;
//				y += 1 * directionY;
//
//				if (!added)
//					points.push_back(currentPos);
//			}
//		}
//	}
//
//	int answer = 0;
//	for (auto& point : points)
//	{
//		if (point.visited > 1)
//		{
//			answer++;
//		}
//	}
//
//	printf("Answer: %d\n", answer);
//
//	/*for (int i = 0; i < (int)lines.size()-1; i++)
//	{
//		if(lines[i].x1 == lines[i].x2 || lines[i].y1 == lines[i].y2)
//		{
//			printf("%d,%d -> %d,%d\n\t", lines[i].x1, lines[i].y1, lines[i].x2, lines[i].y2);
//
//			for (int j = i + 1; j < (int)lines.size(); j++)
//			{
//				if (lines[j].x1 == lines[j].x2 || lines[j].y1 == lines[j].y2)
//				{
//					printf("%d,%d -> %d,%d\n\t", lines[j].x1, lines[j].y1, lines[j].x2, lines[j].y2);
//				}
//			}
//
//			printf("\n\n");
//		}
//	}*/
//
//}
//
//
//
