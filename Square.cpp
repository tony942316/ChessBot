#include "Square.h"

#include <iostream>

Square::Square()
{
}

Square::Square(unsigned short rank, unsigned short file)
{
	this->rank = rank;
	if (this->rank > 7 || this->rank < 0)
	{
		throw "Rank out of bounds";
	}

	this->file = file;
	if (this->file > 7 || this->file < 0)
	{
		throw "File out of bounds";
	}

	if (this->file % 2 == 1)
	{
		fileOdd = true;
	}

	updateColor();
	if (this->color == 'B')
	{
		//sprite.setTextureRect(sf::IntRect(1, 67, 31, 31));
	}
	else
	{
		//sprite.setTextureRect(sf::IntRect(34, 67, 31, 31));
	}

	//sprite.setScale(sf::Vector2f(3.0f, 3.0f));
	//sprite.setPosition(sf::Vector2f(300.f, 300.f));
	//sprite.setPosition(sf::Vector2f(32 * this->file, 32 * this->rank));
}

Square::Square(Square& s)
{
	rank = s.rank;
	file = s.file;
	color = s.color;
	fileOdd = s.fileOdd;
}

unsigned short Square::getRank()
{
	return rank;
}

unsigned short Square::getFile()
{
	return file;
}

char Square::getColor()
{
	return color;
}

bool Square::hasPiece()
{
	return ownPiece;
}

Piece* Square::getPiece()
{
	return piece;
}

sf::Sprite* Square::getSprite()
{
	return &sprite;
}

void Square::setPos(unsigned short rank, unsigned short file)
{
	this->rank = rank;
	this->file = file;
}

void Square::setRank(unsigned short rank)
{
	this->rank = rank;
}

void Square::setFile(unsigned short file)
{
	this->file = file;
}

void Square::setPiece(Piece* piece)
{
	this->piece = piece;
	ownPiece = true;
}

void Square::removePiece()
{
	this->piece = nullptr;
	ownPiece = false;
}

void Square::setSprite(sf::Texture* pTex)
{
	this->pTex = pTex;
	sprite.setTexture(*pTex);
	if (this->color == 'B')
	{
		sprite.setTextureRect(sf::IntRect(1, 67, 32, 32));
	}
	else
	{
		sprite.setTextureRect(sf::IntRect(34, 67, 32, 32));
	}

	float scaler = 2.0f;

	sprite.setScale(sf::Vector2f(scaler, scaler));
	sprite.setPosition(sf::Vector2f(992 - (file * 32 * scaler), 642 - (rank * 32 * scaler)));
}

bool Square::isSelected()
{
	return selected;
}

void Square::select()
{
	selected = true;
}

void Square::deselect()
{
	selected = false;
}

void Square::updateColor()
{
	if (fileOdd && (rank % 2 == 0))
	{
		color = 'B';
	}
	else if (!fileOdd && (rank % 2 == 1))
	{
		color = 'B';
	}
	else
	{
		color = 'W';
	}
}