#pragma once

#include "Piece.h"

class Square
{
public:
	Square();
	Square(unsigned short rank, unsigned short file);
	Square(Square& s);

public:
	void operator= (const Square& s)
	{
		rank = s.rank;
		file = s.file;
		color = s.color;
		fileOdd = s.fileOdd;
	}

public:
	unsigned short getRank();
	unsigned short getFile();
	char getColor();
	bool hasPiece();
	Piece* getPiece();
	sf::Sprite* getSprite();
	bool isSelected();

	void setPos(unsigned short rank, unsigned short file);
	void setRank(unsigned short rank);
	void setFile(unsigned short file);
	void setPiece(Piece* piece);
	void removePiece();
	void setSprite(sf::Texture* pTex);
	void select();
	void deselect();

	void updateColor();

private:
	unsigned short rank = 0;
	unsigned short file = 0;
	char color = 'X';
	bool fileOdd = false;
	bool ownPiece = false;
	Piece* piece = nullptr;
	sf::Texture* pTex;
	sf::Sprite sprite;
	bool selected = false;
};