#pragma once

#include "Square.h"

class ChessBoard
{
public:
	ChessBoard(sf::Texture* black, sf::Texture* white);

public:
	Square* getSquare(unsigned short rank, unsigned short file);
	Piece* getPiece(unsigned short rank, unsigned short file);
	Piece** getWhitePieces();
	Piece** getBlackPieces();
	sf::Sprite getSprite();

	bool clearPath(Square* start, Square* end);
	bool validPawnMove(Square* pos, Square* dest);
	bool validRookMove(Square* start, Square* end);
	bool validKnightMove(Square* start, Square* end);
	bool validBishopMove(Square* start, Square* end);
	bool validQueenMove(Square* start, Square* end);
	bool validKingMove(Square* start, Square* end);
	bool validMove(Square* start, Square* end, char type);
	bool movePiece(unsigned short rank1, unsigned short file1, unsigned short rank2, unsigned short file2);
	std::vector<Piece*> attacked(Square* square);
	bool validSquare(unsigned short rank, unsigned short file);
	bool movPiece(unsigned short rank1, unsigned short file1, unsigned short rank2, unsigned short file2);
	bool wouldCauseCheck(Square* start, Square* dest);
	std::vector<Piece*> inCheck(Square* kingSquare);
	std::vector<Piece*> threats(Square* square, char color);
	std::vector<Piece*> checkFile(Square* file);
	std::vector<Piece*> checkRank(Square* rank);
	std::vector<Piece*> checkDiag(Square* diag);
	std::vector<Piece*> checkL(Square* l);
	void printTrace();
	void printBoard();

private:
	Square tiles[8][8] = {};
	Square* pTiles[8][8] = {};
	Square* pWhiteKingSquare;
	Square* pBlackKingSquare;
	Piece whitePieces[16] = {};
	Piece* pWhitePieces[16] = {};
	Piece blackPieces[16] = {};
	Piece* pBlackPieces[16] = {};
	sf::Texture* black;
	sf::Texture* white;
	sf::Sprite sprite;
	buggy squash;
};