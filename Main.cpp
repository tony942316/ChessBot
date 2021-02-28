#include <iostream>

#include "Board.h"

const int windowWidth = 16 * 100;
const int windowHeight = 9 * 100;

unsigned short xTranslation(float x);
unsigned short yTranslation(float y);

int main()
{
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "My window");
	sf::Texture white;
	sf::Texture black;
	sf::Texture circle;
	sf::Sprite sprite;
	sf::Sprite sCircle;

	int pastClick[] = { -1, -1 };
	int currentClick[] = { -1, -1 };
	Square* curSquare = nullptr;
	bool selecting = false;
	bool whiteTurn = true;
	if (!white.loadFromFile("Textures/WhitePieces.png"))
	{
		throw "Texture Error";
	}

	if (!black.loadFromFile("Textures/BlackPieces.png"))
	{
		throw "Texture Error";
	}

	if (!circle.loadFromFile("Textures/SelectCircle.png"))
	{
		throw "Texture Error";
	}

	ChessBoard chessBoard(&black, &white);
	sCircle.setTexture(circle);
	sCircle.setTextureRect(sf::IntRect(67, 1, 31, 31));
	sCircle.setColor(sf::Color::Transparent);
	sCircle.setScale(2.0f, 2.0f);

	sprite.setTexture(white);
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					std::cout << "the right button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;
				}

				else if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;
					std::cout << "(" << yTranslation(event.mouseButton.y) << ", " << xTranslation(event.mouseButton.x) << ")" << std::endl;
					pastClick[0] = currentClick[0];
					pastClick[1] = currentClick[1];
					currentClick[0] = yTranslation(event.mouseButton.y);
					currentClick[1] = xTranslation(event.mouseButton.x);
					if (selecting)
					{
						if (currentClick[0] >= 0 && currentClick[0] < 8 && currentClick[1] >= 0 && currentClick[1] < 8)
						{
							Square* curSquare = chessBoard.getSquare(currentClick[0], currentClick[1]);
							if (chessBoard.getSquare(pastClick[0], pastClick[1])->hasPiece())
							{
								if ((chessBoard.getSquare(pastClick[0], pastClick[1])->getPiece()->getColor() == 'W' && whiteTurn) || (chessBoard.getSquare(pastClick[0], pastClick[1])->getPiece()->getColor() == 'B' && !whiteTurn))
								{
									if (!(chessBoard.movePiece(pastClick[0], pastClick[1], currentClick[0], currentClick[1])))
									{
										std::cout << "Invalid Move" << std::endl;
									}
									else
									{
										whiteTurn = !whiteTurn;
										if (curSquare->getPiece()->getSymbol() == 'K')
										{
											if (abs(currentClick[1] - pastClick[1]) == 2)
											{
												Square* rookSquare = nullptr;
												if (pastClick[1] > currentClick[1])
												{
													rookSquare = chessBoard.getSquare(curSquare->getRank(), 2);
												}
												else if (pastClick[1] < currentClick[1])
												{
													rookSquare = chessBoard.getSquare(curSquare->getRank(), 4);
												}
												rookSquare->getPiece()->getSprite()->setPosition(sf::Vector2f(992 - (rookSquare->getFile() * 32 * 2.0f), 642 - (rookSquare->getRank() * 32 * 2.0f)));
											}
										}
										chessBoard.getSquare(currentClick[0], currentClick[1])->getPiece()->getSprite()->setPosition(sf::Vector2f(992 - (currentClick[1] * 32 * 2.0f), 642 - (currentClick[0] * 32 * 2.0f)));
									}
								}

							}

						}
						selecting = false;
						sCircle.setColor(sf::Color::Transparent);
						chessBoard.printTrace();
					}
					else if (currentClick[0] >= 0 && currentClick[0] < 8 && currentClick[1] >= 0 && currentClick[1] < 8)
					{
						curSquare = chessBoard.getSquare(currentClick[0], currentClick[1]);
						sCircle.setPosition(544 + (7 - currentClick[1]) * 64, 194 + (7 - currentClick[0]) * 64);
						if (whiteTurn)
						{
							sCircle.setColor(sf::Color::Red);
						}
						else
						{
							sCircle.setColor(sf::Color::Blue);
						}
						selecting = true;
					}
				}
			}
		}

		window.clear(sf::Color::Green);

		for (unsigned short i = 0; i < 8; i++)
		{
			for (unsigned short j = 0; j < 8; j++)
			{
				window.draw(*chessBoard.getSquare(i, j)->getSprite());
			}
		}

		for (unsigned short i = 0; i < 16; i++)
		{
			if (chessBoard.getWhitePieces()[i]->isAlive())
			{
				window.draw(*chessBoard.getWhitePieces()[i]->getSprite());
			}
			if (chessBoard.getBlackPieces()[i]->isAlive())
			{
				window.draw(*chessBoard.getBlackPieces()[i]->getSprite());
			}
		}

		window.draw(sCircle);

		window.display();
	}

	std::cout << "DONE!!!" << std::endl;
	return 0;
}

unsigned short xTranslation(float x)
{
	return 8 - ceil(((x - 544) / 64));
}

unsigned short yTranslation(float y)
{
	return 8 - ceil(((y - 194) / 64));
}