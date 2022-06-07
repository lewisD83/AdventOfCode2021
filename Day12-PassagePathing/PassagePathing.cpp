// PassagePathing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <list>
#include <regex>

std::unordered_map<std::string, std::vector<std::string> > caveMappings;

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
		//printf("%s\n", line.c_str());

		std::regex regex("(\\w+)-(\\w+)");

		// Hold matches for searching with the above regex
		std::smatch res;

		// Get us the first bag in the line which holds rules for what it contains
		while (std::regex_search(line, res, regex))
		{
			std::string caveA = res[1];
			std::string caveB = res[2];

			if (caveMappings[caveA].empty() == false)
			{
				auto iter = caveMappings[caveA].begin();

				for (iter; iter != caveMappings[caveA].end(); iter++) 
				{
					if (*iter == caveB)
						break;
				}

				if (iter == caveMappings[caveA].end())
					caveMappings[caveA].push_back(caveB);				
			}
			else
			{
				caveMappings[caveA].push_back(caveB);
			}

			auto iter = caveMappings[caveB].begin();

			for (iter; iter != caveMappings[caveB].end(); iter++)
			{
				if (*iter == caveA)
					break;
			}

			if (iter == caveMappings[caveB].end())
				caveMappings[caveB].push_back(caveA);
			

			line = res.suffix();
		}
	}

	/*for (auto& i : caveMappings)
	{
		for (auto& j : i.second)
		{
			printf("%s-%s\n", i.first.c_str(), j.c_str());
		}

		printf("\n");
	}*/

	std::list<std::string> onGoingPaths;
	std::vector<std::string> completedPaths;

	std::vector<std::string> connectingCaves = caveMappings["start"];
	

	for (int i = 0; i < connectingCaves.size(); i++)
	{
		std::string cave = connectingCaves[i];
		std::string path("start");
		path.append(",");
		path.append(cave);
		onGoingPaths.push_back(path);

	}

	while (!onGoingPaths.empty())
	{
		std::string onGoingPath = *onGoingPaths.begin();
		int delimeter = onGoingPath.find_last_of(",") + 1;
		std::string caveEnd = onGoingPath.substr(delimeter, onGoingPath.length());
		if (caveEnd == "end")
		{
			completedPaths.push_back(onGoingPath);
			onGoingPaths.pop_front();
			continue;
		}

		connectingCaves = caveMappings[caveEnd];

		for (int i = 0; i < connectingCaves.size(); i++)
		{
			std::string cave = connectingCaves[i];

			if (cave == "start")
				continue;

			std::string pathFind(",");
			pathFind.append(cave);

			if (std::all_of(cave.begin(), cave.end(), [](unsigned char c) { return std::islower(c); }) && onGoingPath.find(pathFind) != std::string::npos)
			{
				int count = 0;
				size_t pos = onGoingPath.find(pathFind, 0);
				while (pos != std::string::npos)
				{
					count++;
					pos = onGoingPath.find(pathFind, pos + 1);
				}
				if (count > 1)
					continue;

				for (auto& iter : caveMappings)
				{
					count = 0;
					std::string test = iter.first;

					if (test == "start" || test == "end")
						continue;

					pathFind = ",";
					pathFind.append(test);

					if (std::all_of(test.begin(), test.end(), [](unsigned char c) { return std::islower(c); }))
					{
						pos = onGoingPath.find(pathFind, 0);
						while (pos != std::string::npos)
						{
							count++;
							pos = onGoingPath.find(pathFind, pos + 1);
						}

						if (count > 1)
							break;
					
					}
					
				}

				if (count > 1)
					continue;

			}


			

			std::string path(onGoingPath);
			path.append(",");
			path.append(cave);
			onGoingPaths.push_back(path);

		}

		onGoingPaths.pop_front();

	}

	for (auto& iter : completedPaths)
	{
		printf("%s\n", iter.c_str());
	}

}