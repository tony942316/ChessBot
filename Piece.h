#pragma once

#include <SFML/Graphics.hpp>
#include "Debug.h"

class Piece
{
public:
	Piece();
	Piece(unsigned short rank, unsigned short file, char color);
public:
	unsigned short getRank();
	unsigned short getFile();
	unsigned int getVal();
	char getColor();
	char getSymbol();
	bool isAlive();
	sf::Sprite* getSprite();

	bool getFirstMove();
	bool getInPassing();

	void setFirstMove();
	void confirmFirstMove();
	void setInPassing();
	void negInPassing();

	void setVal(unsigned int value);
	void kill();
	void setSprite(sf::Texture* pTex);
protected:
	unsigned short rank = -1;
	unsigned short file = -1;
	bool alive = true;
	unsigned int value = 0;
	char color = 'X';
	char symbol = 'X';
	sf::Texture* pTex;
	sf::Sprite sprite;
	bool firstMove = true;
	bool inPassing = false;
};

class Pawn : public Piece
{
public:
	Pawn(unsigned short rank, unsigned short file, char color, sf::Texture* pTex);
public:
	bool getFirstMove();

	void setFirstMove();
	void confirmFirstMove();
private:
	bool firstMove = true;
};

class Knight : public Piece
{
public:
	Knight(unsigned short rank, unsigned short file, char color, sf::Texture* pTex);
};

class Bishop : public Piece
{
public:
	Bishop(unsigned short rank, unsigned short file, char color, sf::Texture* pTex);
};

class Rook : public Piece
{
public:
	Rook(unsigned short rank, unsigned short file, char color, sf::Texture* pTex);
};

class Queen : public Piece
{
public:
	Queen(unsigned short rank, unsigned short file, char color, sf::Texture* pTex);
};

class King : public Piece
{
public:
	King(unsigned short rank, unsigned short file, char color, sf::Texture* pTex);
};