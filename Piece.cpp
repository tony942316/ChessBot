#include "Piece.h"

#include <cmath>

Piece::Piece()
{

}

Piece::Piece(unsigned short rank, unsigned short file, char color)
{
	this->rank = rank;
	this->file = file;
	this->color = color;
}

unsigned int Piece::getVal()
{
	return value;
}

unsigned short Piece::getRank()
{
	return rank;
}

unsigned short Piece::getFile()
{
	return file;
}

char Piece::getColor()
{
	return color;
}

char Piece::getSymbol()
{
	return symbol;
}

bool Piece::isAlive()
{
	return alive;
}

sf::Sprite* Piece::getSprite()
{
	return &sprite;
}

bool Piece::getFirstMove()
{
	return firstMove;
}

bool Piece::getInPassing()
{
	return inPassing;
}

void Piece::setFirstMove()
{
	firstMove = true;
}

void Piece::confirmFirstMove()
{
	firstMove = false;
}

void Piece::setInPassing()
{
	inPassing = true;
}

void Piece::negInPassing()
{
	inPassing = false;
}

void Piece::setVal(unsigned int value)
{
	this->value = value;
}

void Piece::kill()
{
	alive = false;
}

void Piece::setSprite(sf::Texture* pTex)
{

}

Pawn::Pawn(unsigned short rank, unsigned short file, char color, sf::Texture* pTex)
{
	this->rank = rank;
	this->file = file;
	this->color = color;
	this->symbol = 'P';
	this->value = 1;
	this->firstMove = true;
	sprite.setTexture(*pTex);
	sprite.setTextureRect(sf::IntRect(1, 1, 32, 32));
	float scaler = 2.0f;
	sprite.setScale(sf::Vector2f(scaler, scaler));
	sprite.setPosition(sf::Vector2f(992 - (file * 32 * scaler), 642 - (rank * 32 * scaler)));
}

bool Pawn::getFirstMove()
{
	return firstMove;
}

void Pawn::setFirstMove()
{
	this->firstMove = true;
}

void Pawn::confirmFirstMove()
{
	firstMove = false;
}

Knight::Knight(unsigned short rank, unsigned short file, char color, sf::Texture* pTex)
{
	this->rank = rank;
	this->file = file;
	this->color = color;
	this->value = 3;
	this->symbol = 'N';
	sprite.setTexture(*pTex);
	sprite.setTextureRect(sf::IntRect(67, 1, 32, 32));
	float scaler = 2.0f;
	sprite.setScale(sf::Vector2f(scaler, scaler));
	sprite.setPosition(sf::Vector2f(992 - (file * 32 * scaler), 642 - (rank * 32 * scaler)));
}

Bishop::Bishop(unsigned short rank, unsigned short file, char color, sf::Texture* pTex)
{
	this->rank = rank;
	this->file = file;
	this->color = color;
	this->value = 3;
	this->symbol = 'B';
	sprite.setTexture(*pTex);
	sprite.setTextureRect(sf::IntRect(1, 34, 32, 32));
	float scaler = 2.0f;
	sprite.setScale(sf::Vector2f(scaler, scaler));
	sprite.setPosition(sf::Vector2f(992 - (file * 32 * scaler), 642 - (rank * 32 * scaler)));
}

Rook::Rook(unsigned short rank, unsigned short file, char color, sf::Texture* pTex)
{
	this->rank = rank;
	this->file = file;
	this->color = color;
	this->value = 4;
	this->symbol = 'R';
	sprite.setTexture(*pTex);
	sprite.setTextureRect(sf::IntRect(34, 1, 32, 32));
	float scaler = 2.0f;
	sprite.setScale(sf::Vector2f(scaler, scaler));
	sprite.setPosition(sf::Vector2f(992 - (file * 32 * scaler), 642 - (rank * 32 * scaler)));
}

Queen::Queen(unsigned short rank, unsigned short file, char color, sf::Texture* pTex)
{
	this->rank = rank;
	this->file = file;
	this->color = color;
	this->value = 5;
	this->symbol = 'Q';
	sprite.setTexture(*pTex);
	sprite.setTextureRect(sf::IntRect(34, 34, 32, 32));
	float scaler = 2.0f;
	sprite.setScale(sf::Vector2f(scaler, scaler));
	sprite.setPosition(sf::Vector2f(992 - (file * 32 * scaler), 642 - (rank * 32 * scaler)));
}

King::King(unsigned short rank, unsigned short file, char color, sf::Texture* pTex)
{
	this->rank = rank;
	this->file = file;
	this->color = color;
	this->value = 100;
	this->symbol = 'K';
	sprite.setTexture(*pTex);
	sprite.setTextureRect(sf::IntRect(67, 34, 32, 32));
	float scaler = 2.0f;
	sprite.setScale(sf::Vector2f(scaler, scaler));
	sprite.setPosition(sf::Vector2f(992 - (file * 32 * scaler), 642 - (rank * 32 * scaler)));
}