// GiantSquid.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <regex>
#include <bitset>

#include <SFML/Graphics.hpp>
#include <Windows.h>

class BingoCard
{
public:
	BingoCard()
		: winningcard(false)
	{
	};

	std::vector<int> m_cardNumbers;
	std::bitset<5> horLine1;
	std::bitset<5> horLine2;
	std::bitset<5> horLine3;
	std::bitset<5> horLine4;
	std::bitset<5> horLine5;

	std::bitset<5> verLine1;
	std::bitset<5> verLine2;
	std::bitset<5> verLine3;
	std::bitset<5> verLine4;
	std::bitset<5> verLine5;

	bool winningcard;
};

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

	std::vector<int> bingoDraws;
	std::vector<BingoCard> bingoCards;
	int currentCard = -1;

	// Read stream line by line
	for (std::string line; std::getline(source, line);)
	{
		if (bingoDraws.empty())
		{
			std::regex regex("(\\w+)");

			// Hold matches for searching with the above regex
			std::smatch res;

			// Get us the first bag in the line which holds rules for what it contains
			while (std::regex_search(line, res, regex))
			{
				int bingoNumber = std::stoi(res[1]);
				bingoDraws.push_back(bingoNumber);
				line = res.suffix();
			}
		}
		else
		{
			if (line.empty())
			{
				bingoCards.push_back(BingoCard());
				currentCard++;
				continue;
			}

			std::istringstream in(line);
			int bingoCardNumber = 0;

			while (in >> bingoCardNumber)
			{
				bingoCards[currentCard].m_cardNumbers.push_back(bingoCardNumber);
			}
		}
	}

	::ShowWindow(::GetConsoleWindow(), SW_HIDE);

	// Prepare window
	sf::RenderWindow window(sf::VideoMode(1800, 1000), "Toboggan Trajectory");
	window.setFramerateLimit(60);

	sf::Font font;
	if (!font.loadFromFile("DroidSans.ttf"))
	{
	}

	int currentDrawIndex = 0;
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
			int answer = 0;
			int drawPosX = 0;
			int drawPosY = 0;

			int cardNumberPosX = 0;
			int cardNumberPosY = 70;

			int boardOffSetX = 0;
			int boardOffSetY = 70;

			int currentDraw = bingoDraws[currentDrawIndex];
			std::string drawStr;
			drawStr += std::to_string(currentDraw);

			sf::Text drawNumbers(drawStr, font);
			drawNumbers.setPosition(drawPosX, drawPosY);
			drawNumbers.setScale(0.5, 0.5);
			drawPosX += 30;
			if (drawPosX > 1800)
			{
				drawPosX = 0;
				drawPosY += 20;
			}

			window.draw(drawNumbers);

			int lineY = -1;
			for (int i = 1; i < bingoCards.size(); i++)
			{
				BingoCard& card = bingoCards[i];
				lineY++;
				int lineX = -1;

				for (int j = 0; j < (int)card.m_cardNumbers.size(); j++)
				{
					lineX++;
					std::string boardStr = std::to_string(card.m_cardNumbers[j]);

					sf::Text drawNumbers2(boardStr, font);
					drawNumbers2.setPosition(cardNumberPosX, cardNumberPosY);
					drawNumbers2.setScale(0.4, 0.4);

					cardNumberPosX += 20;
					if (lineX == 4)
					{
						cardNumberPosX = boardOffSetX;
						cardNumberPosY += 20;
						lineX = -1;
						boardStr.clear();
					}

					if (card.winningcard == false)
					{
						if (currentDraw == card.m_cardNumbers[j])
						{
							drawNumbers2.setFillColor(sf::Color::Red);
							int vertPos = 0;

							if (j >= 0 && j <= 4)
							{
								card.horLine1.set(j);
								vertPos = j;

							}
							else if (j > 4 && j <= 9)
							{
								card.horLine2.set(j - 5);
								vertPos = j - 5;
							}
							else if (j > 9 && j <= 14)
							{
								card.horLine3.set(j - 10);
								vertPos = j - 10;
							}
							else if (j > 14 && j <= 19)
							{
								card.horLine4.set(j - 15);
								vertPos = j - 15;
							}
							else
							{
								card.horLine5.set(j - 20);
								vertPos = j - 20;
							}

							int pos = j / 5;

							if (vertPos == 0)
							{
								card.verLine1.set(j / 5);
							}
							else if (vertPos == 1)
							{
								card.verLine2.set(j / 5);
							}
							else if (vertPos == 2)
							{
								card.verLine3.set(j / 5);
							}
							else if (vertPos == 3)
							{
								card.verLine4.set(j / 5);
							}
							else
							{
								card.verLine5.set(j / 5);
							}
						}

						if (j >= 0 && j <= 4)
						{
							if (card.horLine1.test(j))
								drawNumbers2.setFillColor(sf::Color::Red);
						}
						else if (j > 4 && j <= 9)
						{
							if (card.horLine2.test(j - 5))
								drawNumbers2.setFillColor(sf::Color::Red);
						}
						else if (j > 9 && j <= 14)
						{
							if (card.horLine3.test(j - 10))
								drawNumbers2.setFillColor(sf::Color::Red);
						}
						else if (j > 14 && j <= 19)
						{
							if (card.horLine4.test(j - 15))
								drawNumbers2.setFillColor(sf::Color::Red);
						}
						else
						{
							if (card.horLine5.test(j - 20))
								drawNumbers2.setFillColor(sf::Color::Red);
						}
					}
					else
					{
						std::bitset<5>	res = card.horLine1 & card.horLine2;
						res = res & card.horLine3;
						res = res & card.horLine4;
						res = res & card.horLine5;

						std::bitset<5>	res2 = card.verLine1 & card.verLine2;
						res2 = res2 & card.verLine3;
						res2 = res2 & card.verLine4;
						res2 = res2 & card.verLine5;

						if (res.any())
						{
							int colComplete = 0;
							for (int i = 0; i < 5; i++)
							{
								if (res.test(i) == 1)
								{
									colComplete = i;
									break;
								}
							}

							if (colComplete == 0)
							{
								if (j == 0 || j == 5 || j == 10 || j == 15 || j == 20)
									drawNumbers2.setFillColor(sf::Color::Green);

							}
							else if (colComplete == 1)
							{
								if (j == 1 || j == 6 || j == 11 || j == 16 || j == 21)
									drawNumbers2.setFillColor(sf::Color::Green);
							}
							else if (colComplete == 2)
							{
								if (j == 2 || j == 7 || j == 12 || j == 17 || j == 22)
									drawNumbers2.setFillColor(sf::Color::Green);
							}
							else if (colComplete == 3)
							{
								if (j == 3 || j == 8 || j == 13 || j == 18 || j == 23)
									drawNumbers2.setFillColor(sf::Color::Green);
							}
							else
							{
								if (j == 4 || j == 9 || j == 14 || j == 19 || j == 24)
									drawNumbers2.setFillColor(sf::Color::Green);
							}
						}

						if (res2.any())
						{
							int rowComplete = 0;
							for (int i = 0; i < 5; i++)
							{
								if (res2.test(i) == 1)
								{
									rowComplete = i;
									break;
								}
							}

							if (rowComplete == 0)
							{
								if (j == 0 || j == 1 || j == 2 || j == 3 || j == 4)
									drawNumbers2.setFillColor(sf::Color::Green);

							}
							else if (rowComplete == 1)
							{
								if (j == 5 || j == 6 || j == 7 || j == 8 || j == 9)
									drawNumbers2.setFillColor(sf::Color::Green);
							}
							else if (rowComplete == 2)
							{
								if (j == 10 || j == 11 || j == 12 || j == 13 || j == 14)
									drawNumbers2.setFillColor(sf::Color::Green);
							}
							else if (rowComplete == 3)
							{
								if (j == 10 || j == 11 || j == 12 || j == 13 || j == 14)
									drawNumbers2.setFillColor(sf::Color::Green);
							}
							else
							{
								if (j == 20 || j == 21 || j == 22 || j == 23 || j == 24)
									drawNumbers2.setFillColor(sf::Color::Green);
							}

						}
					}

					window.draw(drawNumbers2);
				}

				if (currentDrawIndex >= 5)
				{
					std::bitset<5>	res = card.horLine1 & card.horLine2;
					res = res & card.horLine3;
					res = res & card.horLine4;
					res = res & card.horLine5;

					std::bitset<5>	res2 = card.verLine1 & card.verLine2;
					res2 = res2 & card.verLine3;
					res2 = res2 & card.verLine4;
					res2 = res2 & card.verLine5;


					bool win = false;
					if (res.any())
					{
						win = true;
					}
					if (res2.any())
					{
						win = true;
					}

					if (win && card.winningcard == false)
					{
						card.winningcard = true;
						for (int j = 0; j < (int)card.m_cardNumbers.size(); j++)
						{
							int currentNumber = card.m_cardNumbers[j];
							if (j >= 0 && j <= 4)
							{
								if (card.horLine1.test(j) == 0)
									answer += currentNumber;
							}
							else if (j > 4 && j <= 9)
							{
								if (card.horLine2.test(j - 5) == 0)
									answer += currentNumber;
							}
							else if (j > 9 && j <= 14)
							{
								if (card.horLine3.test(j - 10) == 0)
									answer += currentNumber;
							}
							else if (j > 14 && j <= 19)
							{
								if (card.horLine4.test(j - 15) == 0)
									answer += currentNumber;
							}
							else
							{
								if (card.horLine5.test(j - 20) == 0)
									answer += currentNumber;
							}
						}

						answer *= currentDraw;
						printf("Winning Card result: %d\n", answer);
						answer = 0;
					}
				}

				if (lineY == 13)
				{
					lineY = -1;
					boardOffSetY += 110;
					boardOffSetX = -120;
				}

				boardOffSetX += 120;
				cardNumberPosX = boardOffSetX;
				cardNumberPosY = boardOffSetY;


			}

			currentDrawIndex++;
			if (currentDrawIndex == bingoCards.size())
			{
				currentDrawIndex = bingoCards.size() - 1;
			}
		}

		window.display();
		Sleep(100);

	}
}

































//// GiantSquid.cpp : This file contains the 'main' function. Program execution begins and ends there.
////
//
//#include <iostream>
//#include <sstream>
//#include <fstream>
//#include <vector>
//#include <regex>
//#include <bitset>
//
//#include <SFML/Graphics.hpp>
//#include <Windows.h>
//
//class BingoCard
//{
//public:
//	BingoCard() 
//		: winningcard(false)
//	{
//	};
//	
//	std::vector<int> m_cardNumbers;
//	std::bitset<5> horLine1;
//	std::bitset<5> horLine2;
//	std::bitset<5> horLine3;
//	std::bitset<5> horLine4;
//	std::bitset<5> horLine5;
//
//	std::bitset<5> verLine1;
//	std::bitset<5> verLine2;
//	std::bitset<5> verLine3;
//	std::bitset<5> verLine4;
//	std::bitset<5> verLine5;
//
//	bool winningcard;
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
//	// Check if there was a problem opening the file
//	if (!source)
//	{
//		std::cout << "Can't open file!";
//	}
//
//	std::vector<int> bingoDraws;
//	std::vector<BingoCard> bingoCards;
//	int currentCard = -1;
//
//	// Read stream line by line
//	for (std::string line; std::getline(source, line);)
//	{
//		if (bingoDraws.empty())
//		{
//			std::regex regex("(\\w+)");
//
//			// Hold matches for searching with the above regex
//			std::smatch res;
//
//			// Get us the first bag in the line which holds rules for what it contains
//			while (std::regex_search(line, res, regex))
//			{
//				int bingoNumber = std::stoi(res[1]);
//				bingoDraws.push_back(bingoNumber);
//				line = res.suffix();
//			}
//		}
//		else
//		{			
//			if (line.empty())
//			{
//				bingoCards.push_back(BingoCard());
//				currentCard++;
//				continue;
//			}
//
//			std::istringstream in(line);
//			int bingoCardNumber = 0;
//
//			while (in >> bingoCardNumber)
//			{
//				bingoCards[currentCard].m_cardNumbers.push_back(bingoCardNumber);
//			}
//		}
//	}
//
//	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
//
//	// Prepare window
//	sf::RenderWindow window(sf::VideoMode(1500, 700), "Toboggan Trajectory");
//	window.setFramerateLimit(60);
//
//	sf::Font font;
//	if (!font.loadFromFile("DroidSans.ttf"))
//	{
//	}
//
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//		}
//
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
//		{
//		}
//
//		window.clear();
//
//		int answer = 0;
//		int currentPosX = 0;
//		int currentPosY = 0;
//
//
//		int currentPosX2 = 0;
//		int currentPosY2 = 60;
//		for (int i = 0; i < (int)bingoDraws.size(); i++)
//		{
//			int currentDraw = bingoDraws[i];
//			std::string drawStr;
//			drawStr += std::to_string(currentDraw);
//
//			sf::Text drawNumbers(drawStr, font);
//			drawNumbers.setPosition(currentPosX, currentPosY);
//			drawNumbers.setScale(0.4, 0.4);
//			currentPosX+=30;
//			if (currentPosX > 1200) 
//			{
//				currentPosX = 0;
//				currentPosY += 20;
//			}
//
//			//window.draw(drawNumbers);
//
//
//			for (auto& card : bingoCards)
//			{
//				if (card.winningcard == false)
//				{
//					std::string boardStr;
//					for (int j = 0; j < (int)card.m_cardNumbers.size(); j++)
//					{
//						
//						boardStr += std::to_string(card.m_cardNumbers[j]);
//						boardStr += " ";
//
//						sf::Text drawNumbers2(boardStr, font);
//						drawNumbers2.setPosition(currentPosX2, currentPosY2);
//						drawNumbers2.setScale(0.4, 0.4);
//						currentPosX2 += 30;
//
//						if (j % 5 == 0 && j != 0)
//						{
//							currentPosX2 = 0;
//							currentPosY2 += 20;
//							//window.draw(drawNumbers2);
//						}
//
//
//
//						if (currentDraw == card.m_cardNumbers[j])
//						{
//							int vertPos = 0;
//
//							if (j >= 0 && j <= 4)
//							{
//								card.horLine1.set(j);
//								vertPos = j;
//
//							}
//							else if (j > 4 && j <= 9)
//							{
//								card.horLine2.set(j - 5);
//								vertPos = j - 5;
//							}
//							else if (j > 9 && j <= 14)
//							{
//								card.horLine3.set(j - 10);
//								vertPos = j - 10;
//							}
//							else if (j > 14 && j <= 19)
//							{
//								card.horLine4.set(j - 15);
//								vertPos = j - 15;
//							}
//							else
//							{
//								card.horLine5.set(j - 20);
//								vertPos = j - 20;
//							}
//
//							int pos = j / 5;
//
//							if (vertPos == 0)
//							{
//								card.verLine1.set(j / 5);
//							}
//							else if (vertPos == 1)
//							{
//								card.verLine2.set(j / 5);
//							}
//							else if (vertPos == 2)
//							{
//								card.verLine3.set(j / 5);
//							}
//							else if (vertPos == 3)
//							{
//								card.verLine4.set(j / 5);
//							}
//							else
//							{
//								card.verLine5.set(j / 5);
//							}
//						}
//					}
//
//					if (i >= 5)
//					{
//						std::bitset<5>	res = card.horLine1 & card.horLine2;
//						res = res & card.horLine3;
//						res = res & card.horLine4;
//						res = res & card.horLine5;
//
//						std::bitset<5>	res2 = card.verLine1 & card.verLine2;
//						res2 = res2 & card.verLine3;
//						res2 = res2 & card.verLine4;
//						res2 = res2 & card.verLine5;
//
//
//						bool win = false;
//						if (res.any())
//						{
//							int foo;
//							foo = 5;
//							win = true;
//						}
//						if (res2.any())
//						{
//							win = true;
//						}
//
//						if (win)
//						{
//							card.winningcard = true;
//							for (int j = 0; j < (int)card.m_cardNumbers.size(); j++)
//							{
//								int currentNumber = card.m_cardNumbers[j];
//								if (j >= 0 && j <= 4)
//								{
//									if (card.horLine1.test(j) == 0)
//										answer += currentNumber;
//								}
//								else if (j > 4 && j <= 9)
//								{
//									if (card.horLine2.test(j - 5) == 0)
//										answer += currentNumber;
//								}
//								else if (j > 9 && j <= 14)
//								{
//									if (card.horLine3.test(j - 10) == 0)
//										answer += currentNumber;
//								}
//								else if (j > 14 && j <= 19)
//								{
//									if (card.horLine4.test(j - 15) == 0)
//										answer += currentNumber;
//								}
//								else
//								{
//									if (card.horLine5.test(j - 20) == 0)
//										answer += currentNumber;
//								}
//							}
//
//							answer *= currentDraw;
//							printf("Winning Card result: %d\n", answer);
//							answer = 0;
//						}
//					}
//				}
//			}
//		}
//
//		window.display();
//		Sleep(10);
//	}
//}