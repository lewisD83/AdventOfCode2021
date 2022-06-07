

// Chiton.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <deque>
#include <algorithm>
#include <queue>

class Point
{
public:
	Point()
		: x(0)
		, y(0)
		, value(0)
	{

	}

	Point(int _x, int _y, int _value)
		: x(_x)
		, y(_y)
		, value(_value)
	{

	}

	int x, y;
	int value;
};

int maxX;
int maxY;

bool isSafe(int x, int y)
{
	return x >= 0 && x < maxX&& y >= 0 && y < maxY;
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

	std::vector<std::vector<int> > cost;

	for (std::string line; std::getline(source, line);)
	{
		std::vector<int> temp;

		for (int i = 0; i < line.length(); i++)
		{
			temp.push_back(line[i] - '0');
		}

		cost.push_back(temp);
	}

	maxY = cost[0].size();
	maxX = cost.size();

	{
		std::vector<std::vector<int> > dp(maxX, std::vector<int>(maxY, INT_MAX));
		std::vector<std::vector<bool> > visited(maxX, std::vector<bool>(maxY, false));

		auto comp = [](const Point& a, const Point& b) { return a.value > b.value; };
		std::priority_queue< Point, std::vector<Point>, decltype(comp) > pq(comp);

		dp[0][0] = cost[0][0];
		pq.push(Point(0, 0, cost[0][0]));

		std::vector<Point> path;

		while (!pq.empty())
		{
			Point p = pq.top();
			pq.pop();

			int x = p.x;
			int y = p.y;
			int value = p.value;

			if (visited[x][y])
				continue;

			/* mark the current unit as visited */
			visited[x][y] = true;

			int dx[] = { 1,-1, 0, 0 };
			int dy[] = { 0, 0, 1,-1 };

			for (int i = 0; i < 4; i++)
			{
				int nextX = x + dx[i];
				int nextY = y + dy[i];

				if (isSafe(nextX, nextY) && !visited[nextX][nextY])
				{
					int nextValue = cost[nextX][nextY];

					dp[nextX][nextY] = std::min(dp[nextX][nextY], value + nextValue);
					pq.push(Point(nextX, nextY, dp[nextX][nextY]));
				}
			}
		}

		printf("Answer: %d\n", dp[maxX - 1][maxY - 1] - cost[0][0]);

		for (auto& i : dp)
		{
			for (auto& j : i)
			{
				printf("%d\t", j);
			}
			printf("\n");
		}
	}

	int tileMax = maxX;
	maxX *= 5;
	maxY *= 5;

	{
		std::vector<std::vector<int> > dp(maxX, std::vector<int>(maxY, INT_MAX));
		std::vector<std::vector<bool> > visited(maxX, std::vector<bool>(maxY, false));

		auto comp = [](const Point& a, const Point& b) { return a.value > b.value; };
		std::priority_queue< Point, std::vector<Point>, decltype(comp) > pq(comp);

		dp[0][0] = cost[0][0];
		pq.push(Point(0, 0, cost[0][0]));

		while (!pq.empty())
		{
			Point p = pq.top();
			pq.pop();

			int x = p.x;
			int y = p.y;
			int value = p.value;

			if (visited[x][y])
				continue;

			/* mark the current unit as visited */
			visited[x][y] = true;

			int dx[] = { 1,-1, 0, 0 };
			int dy[] = { 0, 0, 1,-1 };

			for (int i = 0; i < 4; i++)
			{
				int nextX = x + dx[i];
				int nextY = y + dy[i];

				if (isSafe(nextX, nextY) && !visited[nextX][nextY])
				{
					int adjNextX = nextX;
					int adjNextY = nextY;
					
					if (adjNextX >= (maxX / 5))
					{
						adjNextX = adjNextX % tileMax;
					}

					if (adjNextY >= (maxY / 5))
					{
						adjNextY = adjNextY % tileMax;
					}

					int nextValue = cost[adjNextX][adjNextY] + (nextX / tileMax) + (nextY / tileMax);

					if (nextValue > 9)
						nextValue -= 9;

					dp[nextX][nextY] = std::min(dp[nextX][nextY], value + nextValue);
					pq.push(Point(nextX, nextY, dp[nextX][nextY]));
				}
			}
		}

		printf("Answer: %d\n", dp[maxX - 1][maxY - 1] - cost[0][0]);
	}
}
