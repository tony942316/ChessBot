#include "Board.h"

#include <iostream>

ChessBoard::ChessBoard(sf::Texture* black, sf::Texture* white)
{
	this->black = black;
	this->white = white;
	for (unsigned short i = 0; i < 8; i++)
	{
		for (unsigned short j = 0; j < 8; j++)
		{
			tiles[i][j] = Square(i, j);
			pTiles[i][j] = &tiles[i][j];
			pTiles[i][j]->setSprite(this->white);
		}
	}

	for (unsigned short i = 0; i < 7; i++)
	{
		whitePieces[i] = Pawn(1, i, 'W', white);
		pWhitePieces[i] = &whitePieces[i];
		pTiles[1][i]->setPiece(pWhitePieces[i]);
		blackPieces[i] = Pawn(6, i, 'B', black);
		pBlackPieces[i] = &blackPieces[i];
		pTiles[6][i]->setPiece(pBlackPieces[i]);
	}

	whitePieces[7] = Pawn(1, 7, 'W', white);
	pWhitePieces[7] = &whitePieces[7];
	pTiles[1][7]->setPiece(pWhitePieces[7]);
	blackPieces[7] = Pawn(6, 7, 'B', black);
	pBlackPieces[7] = &blackPieces[7];
	pTiles[6][7]->setPiece(pBlackPieces[7]);

	((Pawn*)pTiles[6][7]->getPiece())->setFirstMove();

	whitePieces[8] = Rook(0, 0, 'W', white);
	whitePieces[9] = Rook(0, 7, 'W', white);
	whitePieces[10] = Knight(0, 1, 'W', white);
	whitePieces[11] = Knight(0, 6, 'W', white);
	whitePieces[12] = Bishop(0, 2, 'W', white);
	whitePieces[13] = Bishop(0, 5, 'W', white);
	whitePieces[14] = King(0, 3, 'W', white);
	whitePieces[15] = Queen(0, 4, 'W', white);

	pWhiteKingSquare = pTiles[0][3];

	for (unsigned short i = 8; i < 16; i++)
	{
		pWhitePieces[i] = &whitePieces[i];
		pTiles[pWhitePieces[i]->getRank()][pWhitePieces[i]->getFile()]->setPiece(pWhitePieces[i]);
	}

	blackPieces[8] = Rook(7, 0, 'B', black);
	blackPieces[9] = Rook(7, 7, 'B', black);
	blackPieces[10] = Knight(7, 1, 'B', black);
	blackPieces[11] = Knight(7, 6, 'B', black);
	blackPieces[12] = Bishop(7, 2, 'B', black);
	blackPieces[13] = Bishop(7, 5, 'B', black);
	blackPieces[14] = King(7, 3, 'B', black);
	blackPieces[15] = Queen(7, 4, 'B', black);

	pBlackKingSquare = pTiles[7][3];

	for (unsigned short i = 8; i < 16; i++)
	{
		pBlackPieces[i] = &blackPieces[i];
		pTiles[pBlackPieces[i]->getRank()][pBlackPieces[i]->getFile()]->setPiece(pBlackPieces[i]);
	}
}

Square* ChessBoard::getSquare(unsigned short rank, unsigned short file)
{
	return pTiles[rank][file];
}

Piece* ChessBoard::getPiece(unsigned short rank, unsigned short file)
{
	if (getSquare(rank, file)->hasPiece())
	{
		return getSquare(rank, file)->getPiece();
	}
	else
	{
		return nullptr;
	}
}

Piece** ChessBoard::getWhitePieces()
{
	return pWhitePieces;
}

Piece** ChessBoard::getBlackPieces()
{
	return pBlackPieces;
}

sf::Sprite ChessBoard::getSprite()
{
	return sprite;
}

bool ChessBoard::clearPath(Square* start, Square* end)
{
	if (!(start->hasPiece()))
	{
		return false;
	}
	else if (end->hasPiece())
	{
		if (end->getPiece()->getColor() == start->getPiece()->getColor())
		{
			return false;
		}
	}

	if (start->getFile() == end->getFile())
	{
		if (start->getRank() < end->getRank())
		{
			for (unsigned short i = start->getRank() + 1; i < end->getRank(); i++)
			{
				if (pTiles[i][start->getFile()]->hasPiece())
				{
					return false;
				}
			}
			return true;
		}
		else
		{
			for (unsigned short i = end->getRank() + 1; i < start->getRank(); i++)
			{
				if (pTiles[i][start->getFile()]->hasPiece())
				{
					return false;
				}
			}
			return true;
		}
	}
	else if (start->getRank() == end->getRank())
	{
		if (start->getFile() < end->getFile())
		{
			for (unsigned short i = start->getFile() + 1; i < end->getFile(); i++)
			{
				if (pTiles[start->getRank()][i]->hasPiece())
				{
					return false;
				}
			}
			return true;
		}
		else
		{
			for (unsigned short i = start->getFile() - 1; i > end->getFile(); i--)
			{
				if (pTiles[start->getRank()][i]->hasPiece())
				{
					return false;
				}
			}
			return true;
		}
	}
	else if (abs(end->getRank() - start->getRank()) == abs(end->getFile() - start->getFile()))
	{
		if (end->getRank() > start->getRank() && end->getFile() > start->getFile())
		{
			unsigned short i = start->getRank() + 1;
			unsigned short j = start->getFile() + 1;
			while (i < end->getRank() && j < end->getFile())
			{
				if (pTiles[i][j]->hasPiece())
				{
					return false;
				}
				i++;
				j++;
			}
			return true;
		}
		else if (end->getRank() > start->getRank() && start->getFile() > end->getFile())
		{
			unsigned short i = start->getRank() + 1;
			unsigned short j = start->getFile() - 1;
			while (i < end->getRank() && j > end->getFile())
			{
				if (pTiles[i][j]->hasPiece())
				{
					return false;
				}
				i++;
				j--;
			}
			return true;
		}
		else if (start->getRank() > end->getRank() && end->getFile() > start->getFile())
		{
			unsigned short i = start->getRank() - 1;
			unsigned short j = start->getFile() + 1;
			while (i > end->getRank() && j < end->getFile())
			{
				if (pTiles[i][j]->hasPiece())
				{
					return false;
				}
				i--;
				j++;
			}
			return true;
		}
		else if (start->getRank() > end->getRank() && start->getFile() > end->getFile())
		{
			unsigned short i = start->getRank() - 1;
			unsigned short j = start->getFile() - 1;
			while (i > end->getRank() && j > end->getFile())
			{
				if (pTiles[i][j]->hasPiece())
				{
					return false;
				}
				i--;
				j--;
			}
			return true;
		}
	}
	else
	{
		return false;
	}
}

bool ChessBoard::validPawnMove(Square* pos, Square* dest)
{
	Piece* pawn = pos->getPiece();
	if (pawn->getColor() == 'W')
	{
		if (pawn->getFirstMove())
		{
			squash.addTrace("Pawn First Move");
		}
		if (dest->getRank() == pos->getRank() + 1 && dest->getFile() == pos->getFile() && !(dest->hasPiece()))
		{
			return true;
		}
		else if (dest->getRank() == pos->getRank() + 2 && dest->getFile() == pos->getFile() && !(dest->hasPiece()) && clearPath(pos, dest) && pawn->getFirstMove())
		{
			pawn->setInPassing();
			return true;
		}
		else if (pos->getRank() == 4 && dest->getRank() == pos->getRank() + 1 && (dest->getFile() == pos->getFile() + 1 || dest->getFile() == pos->getFile() - 1) && !dest->hasPiece())
		{
			if (pTiles[4][dest->getFile()]->hasPiece())
			{
				Piece* somePiece = pTiles[4][dest->getFile()]->getPiece();
				if (somePiece->getSymbol() == 'P' && somePiece->getColor() == 'B' && somePiece->getInPassing())
				{
					return true;
				}
			}
		}
		else if (dest->getRank() == pos->getRank() + 1 && (dest->getFile() == pos->getFile() + 1 || dest->getFile() == pos->getFile() - 1) && dest->hasPiece())
		{
			if (dest->getPiece()->getColor() == 'B')
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			squash.addTrace("Invalid Pawn Move");
			return false;
		}
	}
	else
	{
		if (dest->getRank() == pos->getRank() - 1 && dest->getFile() == pos->getFile() && !(dest->hasPiece()))
		{
			return true;
		}
		else if (dest->getRank() == pos->getRank() - 2 && dest->getFile() == pos->getFile() && !(dest->hasPiece()) && clearPath(pos, dest) && pawn->getFirstMove())
		{
			pawn->setInPassing();
			return true;
		}
		else if (pos->getRank() == 3 && dest->getRank() == pos->getRank() - 1 && (dest->getFile() == pos->getFile() + 1 || dest->getFile() == pos->getFile() - 1) && !dest->hasPiece())
		{
			if (pTiles[3][dest->getFile()]->hasPiece())
			{
				Piece* somePiece = pTiles[3][dest->getFile()]->getPiece();
				if (somePiece->getSymbol() == 'P' && somePiece->getColor() == 'W' && somePiece->getInPassing())
				{
					return true;
				}
			}
		}
		else if (dest->getRank() == pos->getRank() - 1 && (dest->getFile() == pos->getFile() + 1 || dest->getFile() == pos->getFile() - 1) && dest->hasPiece())
		{
			if (dest->getPiece()->getColor() == 'W')
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
}

bool ChessBoard::validRookMove(Square* start, Square* end)
{
	if (((start->getRank() == end->getRank()) || (start->getFile() == end->getFile())) && clearPath(start, end))
	{
		if (!(end->hasPiece()))
		{
			return true;
		}
		else if (start->getPiece()->getColor() != end->getPiece()->getColor())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool ChessBoard::validKnightMove(Square* start, Square* end)
{
	if ((abs(end->getRank() - start->getRank()) == 2 && abs(end->getFile() - start->getFile()) == 1) || (abs(end->getRank() - start->getRank()) == 1 && abs(end->getFile() - start->getFile()) == 2))
	{
		if (!(end->hasPiece()))
		{
			return true;
		}
		else if (start->getPiece()->getColor() != end->getPiece()->getColor())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool ChessBoard::validBishopMove(Square* start, Square* end)
{
	if ((abs(end->getRank() - start->getRank()) == abs(end->getFile() - start->getFile())) && clearPath(start, end))
	{
		if (!(end->hasPiece()))
		{
			return true;
		}
		else if (start->getPiece()->getColor() != end->getPiece()->getColor())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool ChessBoard::validQueenMove(Square* start, Square* end)
{
	if (validRookMove(start, end) || validBishopMove(start, end))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ChessBoard::validKingMove(Square* start, Square* end)
{
	Piece* king = start->getPiece();
	Piece* lRook = nullptr;
	Piece* rRook = nullptr;
	if (king->getColor() == 'W')
	{
		lRook = pWhitePieces[9];
		rRook = pWhitePieces[8];
	}
	else
	{
		lRook = pBlackPieces[9];
		rRook = pBlackPieces[8];
	}

	if (!validSquare(end->getRank(), end->getFile()))
	{
		squash.addTrace("Invalid Square");
		return false;
	}

	std::vector<Piece*> offenders(attacked(end));
	if (!offenders.empty())
	{
		for (Piece* offender : offenders)
		{
			if (offender->getColor() != start->getPiece()->getColor())
			{
				squash.addTrace("Would be check");
				return false;
			}
		}

	}

	if (end->hasPiece())
	{
		if (end->getPiece()->getColor() == start->getPiece()->getColor())
		{
			squash.addTrace("Same Color Piece");
			return false;
		}
	}

	if (end->getRank() == start->getRank() && end->getFile() == start->getFile() - 2)
	{
		if (king->getFirstMove() && rRook->getFirstMove())
		{
			if (!pTiles[start->getRank()][start->getFile() - 1]->hasPiece() && !pTiles[start->getRank()][start->getFile() - 2]->hasPiece())
			{
				std::vector<Piece*> offenders;
				for (unsigned short i = 0; i < 3; i++)
				{
					offenders = attacked(pTiles[start->getRank()][start->getFile() - i]);
					for (Piece* offender : offenders)
					{
						if (offender->getColor() != king->getColor())
						{
							squash.addTrace("Can't castle through check");
							return false;
						}
					}
				}
				
				return true;
			}
		}

	}
	else if (end->getRank() == start->getRank() && end->getFile() == start->getFile() + 2)
	{
		if (king->getFirstMove() && lRook->getFirstMove())
		{
			if (!pTiles[start->getRank()][start->getFile() + 1]->hasPiece() && !pTiles[start->getRank()][start->getFile() + 2]->hasPiece() && !pTiles[start->getRank()][start->getFile() + 3]->hasPiece())
			{
				std::vector<Piece*> offenders;
				for (unsigned short i = 0; i < 4; i++)
				{
					offenders = attacked(pTiles[start->getRank()][start->getFile() + i]);
					for (Piece* offender : offenders)
					{
						if (offender->getColor() != king->getColor())
						{
							squash.addTrace("Can't castle through check");
							return false;
						}
					}
				}

				return true;
			}
		}
	}

	if (abs(end->getRank() - start->getRank()) > 1 || abs(end->getFile() - start->getFile()) > 1)
	{
		squash.addTrace("Out of Range");
		return false;
	}

	return true;
}

bool ChessBoard::validMove(Square* start, Square* end, char type)
{
	if (type == 'P')
	{
		return validPawnMove(start, end);
	}
	else if (type == 'R')
	{
		return validRookMove(start, end);
	}
	else if (type == 'N')
	{
		return validKnightMove(start, end);
	}
	else if (type == 'B')
	{
		return validBishopMove(start, end);
	}
	else if (type == 'Q')
	{
		return validQueenMove(start, end);
	}
	else if (type == 'K')
	{
		return validKingMove(start, end);
	}
	else
	{
		return false;
	}
}

bool ChessBoard::movePiece(unsigned short rank1, unsigned short file1, unsigned short rank2, unsigned short file2)
{
	Square* fromSquare = getSquare(rank1, file1);
	Square* toSquare = getSquare(rank2, file2);
	if (fromSquare->hasPiece())
	{
		squash.addTrace("HasPiece");
		Piece* currentPiece = fromSquare->getPiece();
		if (currentPiece->getColor() == 'W' && currentPiece->getSymbol() != 'K')
		{
			fromSquare->removePiece();
			std::vector<Piece*> offenders(attacked(pWhiteKingSquare));
			if (!offenders.empty())
			{
				std::vector<Piece*> threats;
				for (Piece* offender : offenders)
				{
					if (offender->getColor() != 'W')
					{
						threats.push_back(offender);
					}
				}

				if (threats.size() > 1)
				{
					squash.addTrace("Would cause check White");
					fromSquare->setPiece(currentPiece);
					return false;
				}
				else if (threats.size() == 1)
				{
					if (toSquare->hasPiece())
					{
						if (toSquare->getPiece() != threats.front())
						{
							squash.addTrace("Would cause check2 White");
							fromSquare->setPiece(currentPiece);
							return false;
						}
					}
					else if (!toSquare->hasPiece())
					{
						fromSquare->setPiece(currentPiece);
						if (validMove(fromSquare, toSquare, currentPiece->getSymbol()))
						{
							fromSquare->removePiece();
							toSquare->setPiece(currentPiece);
							std::vector<Piece*> offenders2(attacked(pWhiteKingSquare));
							for (Piece* offender : offenders2)
							{
								if (offender->getColor() != 'W')
								{
									toSquare->removePiece();
									fromSquare->setPiece(currentPiece);
									squash.addTrace("Would cause check3 White");
									return false;
								}
							}
							toSquare->removePiece();
							fromSquare->setPiece(currentPiece);
						}
					}
				}
			}
			fromSquare->setPiece(currentPiece);
		}
		else if (currentPiece->getColor() == 'B' && currentPiece->getSymbol() != 'K')
		{
			fromSquare->removePiece();
			std::vector<Piece*> offenders(attacked(pBlackKingSquare));
			if (!offenders.empty())
			{
				std::vector<Piece*> threats;
				for (Piece* offender : offenders)
				{
					if (offender->getColor() != 'B')
					{
						threats.push_back(offender);
					}
				}

				if (threats.size() > 1)
				{
					squash.addTrace("Would cause check Black");
					fromSquare->setPiece(currentPiece);
					return false;
				}
				else if (threats.size() == 1)
				{
					if (toSquare->hasPiece())
					{
						if (toSquare->getPiece() != threats.front())
						{
							squash.addTrace("Would cause check2 Black");
							fromSquare->setPiece(currentPiece);
							return false;
						}
					}
					else if (!toSquare->hasPiece())
					{
						fromSquare->setPiece(currentPiece);
						if (validMove(fromSquare, toSquare, currentPiece->getSymbol()))
						{
							fromSquare->removePiece();
							toSquare->setPiece(currentPiece);
							std::vector<Piece*> offenders2(attacked(pBlackKingSquare));
							for (Piece* offender : offenders2)
							{
								if (offender->getColor() != 'B')
								{
									toSquare->removePiece();
									fromSquare->setPiece(currentPiece);
									squash.addTrace("Would cause check3 Black");
									return false;
								}
							}
							toSquare->removePiece();
							fromSquare->setPiece(currentPiece);
						}
					}
				}
			}
			fromSquare->setPiece(currentPiece);
		}

		if (currentPiece->getSymbol() != 'N' && clearPath(fromSquare, toSquare))
		{
			if (currentPiece->getSymbol() == 'P')
			{
				if (validPawnMove(fromSquare, toSquare))
				{
					Piece* pawn = currentPiece;
					if (pawn->getFirstMove())
					{
						pawn->confirmFirstMove();
					}

					if (toSquare->getRank() == 7 && pawn->getColor() == 'W')
					{
						*currentPiece = Queen(currentPiece->getRank(), currentPiece->getFile(), 'W', white);
					}
					else if (toSquare->getRank() == 0 && pawn->getColor() == 'B')
					{
						*currentPiece = Queen(currentPiece->getRank(), currentPiece->getFile(), 'B', black);
					}
					
					if (!toSquare->hasPiece() && toSquare->getFile() != fromSquare->getFile())
					{
						Square* passingSquare = pTiles[fromSquare->getRank()][toSquare->getFile()];
						Piece* deadPiece = passingSquare->getPiece();
						deadPiece->kill();
						fromSquare->removePiece();
						passingSquare->removePiece();
						toSquare->setPiece(currentPiece);

						return true;
					}
					else if (toSquare->hasPiece())
					{
						Piece* deadPiece = toSquare->getPiece();
						deadPiece->kill();
						fromSquare->removePiece();
						toSquare->removePiece();
						toSquare->setPiece(currentPiece);
						
						return true;
					}
					else
					{
						fromSquare->removePiece();
						toSquare->setPiece(currentPiece);
						return true;
					}
				}
				else
				{
					squash.addTrace("Invalid Pawn Move");
					return false;
				}
			}
			else if (currentPiece->getSymbol() == 'R')
			{
				if (validRookMove(fromSquare, toSquare))
				{
					if (toSquare->hasPiece())
					{
						Piece* deadPiece = toSquare->getPiece();
						deadPiece->kill();
						fromSquare->removePiece();
						toSquare->removePiece();
						toSquare->setPiece(currentPiece);
						currentPiece->confirmFirstMove();

						return true;
					}
					else
					{
						fromSquare->removePiece();
						toSquare->setPiece(currentPiece);
						currentPiece->confirmFirstMove();
						return true;
					}
				}
				else
				{
					squash.addTrace("Invalid Rook Move");
					return false;
				}
			}
			else if (currentPiece->getSymbol() == 'B')
			{
				if (validBishopMove(fromSquare, toSquare))
				{
					if (toSquare->hasPiece())
					{
						Piece* deadPiece = toSquare->getPiece();
						deadPiece->kill();
						fromSquare->removePiece();
						toSquare->removePiece();
						toSquare->setPiece(currentPiece);

						return true;
					}
					else
					{
						fromSquare->removePiece();
						toSquare->setPiece(currentPiece);
						return true;
					}
				}
				else
				{
					squash.addTrace("Invalid Bishop Move");
					return false;
				}
			}
			else if (currentPiece->getSymbol() == 'Q')
			{
				if (validQueenMove(fromSquare, toSquare))
				{
					if (toSquare->hasPiece())
					{
						Piece* deadPiece = toSquare->getPiece();
						deadPiece->kill();
						fromSquare->removePiece();
						toSquare->removePiece();
						toSquare->setPiece(currentPiece);

						return true;
					}
					else
					{
						fromSquare->removePiece();
						toSquare->setPiece(currentPiece);
						return true;
					}
				}
				else
				{
					squash.addTrace("Invalid Queen Move");
					return false;
				}
			}
			else
			{
				if (validKingMove(fromSquare, toSquare))
				{
					if (abs(toSquare->getFile() - fromSquare->getFile()) == 2)
					{
						Square* rookSquare = nullptr;
						Square* targetSquare = nullptr;
						fromSquare->removePiece();
						toSquare->setPiece(currentPiece);
						if (toSquare->getFile() > fromSquare->getFile())
						{
							rookSquare = pTiles[fromSquare->getRank()][7];
							targetSquare = pTiles[fromSquare->getRank()][fromSquare->getFile() + 1];
						}
						else
						{
							rookSquare = pTiles[fromSquare->getRank()][0];
							targetSquare = pTiles[fromSquare->getRank()][fromSquare->getFile() - 1];
						}
						Piece* rook = rookSquare->getPiece();
						rookSquare->removePiece();
						targetSquare->setPiece(rook);
						currentPiece->confirmFirstMove();
						rook->confirmFirstMove();
						return true;
					}
					else if (toSquare->hasPiece())
					{
						Piece* deadPiece = toSquare->getPiece();
						deadPiece->kill();
						fromSquare->removePiece();
						toSquare->removePiece();
						toSquare->setPiece(currentPiece);
						if (currentPiece->getColor() == 'W')
						{
							pWhiteKingSquare = toSquare;
						}
						else
						{
							pBlackKingSquare = toSquare;
						}
						
						currentPiece->confirmFirstMove();
						return true;
					}
					else
					{
						fromSquare->removePiece();
						toSquare->setPiece(currentPiece);
						if (currentPiece->getColor() == 'W')
						{
							pWhiteKingSquare = toSquare;
						}
						else
						{
							pBlackKingSquare = toSquare;
						}
						currentPiece->confirmFirstMove();
						return true;
					}
				}
				else
				{
					squash.addTrace("Invalid King Move");
					return false;
				}
			}
		}
		else if (currentPiece->getSymbol() == 'N')
		{
			if (validKnightMove(fromSquare, toSquare))
			{
				if (toSquare->hasPiece())
				{
					Piece* deadPiece = toSquare->getPiece();
					deadPiece->kill();
					fromSquare->removePiece();
					toSquare->removePiece();
					toSquare->setPiece(currentPiece);

					return true;
				}
				else
				{
					fromSquare->removePiece();
					toSquare->setPiece(currentPiece);
					return true;
				}
			}
			else
			{
				squash.addTrace("Invalid Knight Move");
				return false;
			}
		}
		else
		{
			squash.addTrace("Invalid Piece");
			return false;
		}
	}
	else
	{
		squash.addTrace("No Piece in Square");
		return false;
	}
}

std::vector<Piece*> ChessBoard::attacked(Square* square)
{
	std::vector<Piece*> offenders;

	for (short i = 1; i > -2; i--)
	{
		for (short j = 1; j > -2; j--)
		{
			if (j == 0 && i == 0)
			{
				continue;
			}
			else if (!validSquare(square->getRank() + i, square->getFile() + j))
			{
				continue;
			}
			else
			{
				if (pTiles[square->getRank() + i][square->getFile() + j]->hasPiece())
				{
					Piece* offender = pTiles[square->getRank() + i][square->getFile() + j]->getPiece();
					if (offender->getSymbol() == 'K')
					{
						offenders.push_back(offender);
					}
				}
			}
		}
	}

	for (unsigned short i = square->getRank() + 1; i < 8; i++)
	{
		if (pTiles[i][square->getFile()]->hasPiece())
		{
			Piece* offender = pTiles[i][square->getFile()]->getPiece();
			if (offender->getSymbol() == 'R' || offender->getSymbol() == 'Q')
			{
				squash.addTrace("Attacker T");
				offenders.push_back(offender);
				break;
			}
			else if (offender->getSymbol() != 'K')
			{
				break;
			}
		}
	}

	for (short i = square->getRank() - 1; i >= 0; i--)
	{
		if (pTiles[i][square->getFile()]->hasPiece())
		{
			Piece* offender = pTiles[i][square->getFile()]->getPiece();
			if (offender->getSymbol() == 'R' || offender->getSymbol() == 'Q')
			{
				squash.addTrace("Attacker B");
				offenders.push_back(offender);
				break;
			}
			else if (offender->getSymbol() != 'K')
			{
				break;
			}
		}
	}
	
	for (unsigned short i = square->getFile() + 1; i < 8; i++)
	{
		if (pTiles[square->getRank()][i]->hasPiece())
		{
			Piece* offender = pTiles[square->getRank()][i]->getPiece();
			if (offender->getSymbol() == 'R' || offender->getSymbol() == 'Q')
			{
				squash.addTrace("Attacker L");
				offenders.push_back(offender);
				break;
			}
			else if (offender->getSymbol() != 'K')
			{
				break;
			}
		}
	}
	
	for (short i = square->getFile() - 1; i >= 0; i--)
	{
		if (pTiles[square->getRank()][i]->hasPiece())
		{
			Piece* offender = pTiles[square->getRank()][i]->getPiece();
			if (offender->getSymbol() == 'R' || offender->getSymbol() == 'Q')
			{
				squash.addTrace("Attacker R");
				offenders.push_back(offender);
				break;
			}
			else if (offender->getSymbol() != 'K')
			{
				break;
			}
		}
	}
	
	short file = square->getFile() + 1;
	short rank = square->getRank() + 1;
	while (file < 8 && rank < 8)
	{
		if (pTiles[rank][file]->hasPiece())
		{
			Piece* offender = pTiles[rank][file]->getPiece();
			if (offender->getSymbol() == 'B' || offender->getSymbol() == 'Q')
			{
				squash.addTrace("Attacker TL");
				offenders.push_back(offender);
				break;
			}
			else if (offender->getSymbol() != 'K')
			{
				break;
			}
		}
	file++;
	rank++;
	}

	file = square->getFile() + 1;
	rank = square->getRank() - 1;
	while (file < 8 && rank >= 0)
	{
		if (pTiles[rank][file]->hasPiece())
		{
			Piece* offender = pTiles[rank][file]->getPiece();
			if (offender->getSymbol() == 'B' || offender->getSymbol() == 'Q')
			{
				squash.addTrace("Attacker BL");
				offenders.push_back(offender);
				break;
			}
			else if (offender->getSymbol() != 'K')
			{
				break;
			}
		}
		file++;
		rank--;
	}

	file = square->getFile() - 1;
	rank = square->getRank() + 1;
	while (file >= 0 && rank < 8)
	{
		if (pTiles[rank][file]->hasPiece())
		{
			Piece* offender = pTiles[rank][file]->getPiece();
			if (offender->getSymbol() == 'B' || offender->getSymbol() == 'Q')
			{
				squash.addTrace("Attacker TR");
				offenders.push_back(offender);
				break;
			}
			else if (offender->getSymbol() != 'K')
			{
				break;
			}
		}
		file--;
		rank++;
	}

	file = square->getFile() - 1;
	rank = square->getRank() - 1;
	while (file >= 0 && rank >= 0)
	{
		if (pTiles[rank][file]->hasPiece())
		{
			Piece* offender = pTiles[rank][file]->getPiece();
			if (offender->getSymbol() == 'B' || offender->getSymbol() == 'Q')
			{
				squash.addTrace("Attacker BR");
				offenders.push_back(offender);
				break;
			}
			else if (offender->getSymbol() != 'K')
			{
				break;
			}
		}
		file--;
		rank--;
	}

	file = square->getFile();
	rank = square->getRank();
	short rankAndFileOps[16] = {  1,  2,
								 -1,  2,
								  2,  1,
								  2, -1,
								  1, -2,
								 -1, -2,
								 -2,  1,
								 -2, -1  };
	short i = 0;
	short tempRank = 0;
	short tempFile = 0;
	while (i < 16)
	{
		tempRank = rank + rankAndFileOps[i];
		tempFile = file + rankAndFileOps[i + 1];
		if (tempRank >= 0 && tempRank < 8 && tempFile >= 0 && tempRank < 8)
		{
			if (pTiles[tempRank][tempFile]->hasPiece())
			{
				Piece* offender = pTiles[tempRank][tempFile]->getPiece();
				if (offender->getSymbol() == 'N')
				{
					squash.addTrace("N Attacker");
					offenders.push_back(offender);
				}
			}
		}
		i += 2;
	}

	if (square->getRank() + 1 < 8)
	{
		if (square->getFile() + 1 < 8)
		{
			if (pTiles[square->getRank() + 1][square->getFile() + 1]->hasPiece())
			{
				Piece* offender = pTiles[square->getRank() + 1][square->getFile() + 1]->getPiece();
				if (offender->getColor() == 'B')
				{
					if (offender->getSymbol() == 'P')
					{
						squash.addTrace("P Attacker TL");
						offenders.push_back(offender);
					}
				}
			}
		}

		if (square->getFile() - 1 >= 0)
		{
			if (pTiles[square->getRank() + 1][square->getFile() - 1]->hasPiece())
			{
				std::cout << "Do you see the TR black Pawn?" << std::endl;
				Piece* offender = pTiles[square->getRank() + 1][square->getFile() - 1]->getPiece();
				if (offender->getColor() == 'B')
				{
					if (offender->getSymbol() == 'P')
					{
						squash.addTrace("P Attacker TR");
						offenders.push_back(offender);
					}
				}
			}
		}
	}

	if (square->getRank() - 1 >= 0)
	{
		if (square->getFile() + 1 < 8)
		{
			if (pTiles[square->getRank() - 1][square->getFile() + 1]->hasPiece())
			{
				Piece* offender = pTiles[square->getRank() - 1][square->getFile() + 1]->getPiece();
				if (offender->getColor() == 'W')
				{
					if (offender->getSymbol() == 'P')
					{
						squash.addTrace(offender->getSymbol() + " Attacker BL");
						offenders.push_back(offender);
					}
				}
			}
		}

		if (square->getFile() - 1 >= 0)
		{
			if (pTiles[square->getRank() - 1][square->getFile() - 1]->hasPiece())
			{
				Piece* offender = pTiles[square->getRank() - 1][square->getFile() - 1]->getPiece();
				if (offender->getColor() == 'W')
				{
					if (offender->getSymbol() == 'P')
					{
						squash.addTrace(offender->getSymbol() + " Attacker BR");
						offenders.push_back(offender);
					}
				}
			}
		}
	}

	return offenders;
}

bool ChessBoard::validSquare(unsigned short rank, unsigned short file)
{
	if (rank >= 0 && rank < 8 && file >= 0 && file < 8)
	{
		//squash.addTrace("validSquare: True");
		return true;
	}
	else
	{
		//squash.addTrace("validSquare: False");
		return false;
	}
}

bool ChessBoard::wouldCauseCheck(Square* start, Square* dest)
{
	Piece* piece = start->getPiece();
	Piece* target = nullptr;
	Square* kingSquare;
	if (piece->getColor() == 'W')
	{
		kingSquare = pWhiteKingSquare;
	}
	else
	{
		kingSquare = pBlackKingSquare;
	}

	if (dest->hasPiece())
	{
		target = dest->getPiece();
	}

	start->removePiece();
	if (target != nullptr)
	{
		dest->removePiece();
	}
	dest->setPiece(piece);
	std::vector<Piece*> threats = inCheck(kingSquare);
	dest->removePiece();
	start->setPiece(piece);
	if (target != nullptr)
	{
		dest->setPiece(target);
	}

	if (threats.size() == 0)
	{
		squash.addTrace("wouldCauseCheck: False");
		return false;
	}
	else
	{
		squash.addTrace("wouldCauseCheck: True");
		return true;
	}
}

std::vector<Piece*> ChessBoard::inCheck(Square* kingSquare)
{
	std::vector<Piece*> attackers = threats(kingSquare, kingSquare->getPiece()->getColor());
	return attackers;
}

std::vector<Piece*> ChessBoard::threats(Square* square, char color)
{
	std::vector<Piece*> threats;
	threats.reserve(16);
	std::vector<Piece*> temp;
	temp = checkFile(square);
	for (Piece* p : temp)
	{
		if (p->getColor() == color)
		{
			threats.push_back(p);
		}
	}
	temp = checkRank(square);
	for (Piece* p : temp)
	{
		if (p->getColor() == color)
		{
			threats.push_back(p);
		}
	}
	temp = checkDiag(square);
	for (Piece* p : temp)
	{
		if (p->getColor() == color)
		{
			threats.push_back(p);
		}
	}
	temp = checkL(square);
	for (Piece* p : temp)
	{
		if (p->getColor() == color)
		{
			threats.push_back(p);
		}
	}

	return threats;
}

std::vector<Piece*> ChessBoard::checkFile(Square* file)
{
	std::vector<Piece*> offenders;

	for (int i = file->getRank() + 1; i < 8; i++)
	{
		if (pTiles[i][file->getFile()]->hasPiece())
		{
			Piece* piece = pTiles[i][file->getFile()]->getPiece();
			if (i == file->getRank() + 1 && piece->getSymbol() == 'K')
			{
				squash.addTrace("checkFile: Top King");
				offenders.push_back(piece);
			}
			else if (piece->getSymbol() == 'R' || piece->getSymbol() == 'Q')
			{
				squash.addTrace("checkFile: Top Q/R");
				offenders.push_back(piece);
			}
			break;
		}
	}

	for (int i = file->getRank() - 1; i >= 0; i--)
	{
		if (pTiles[i][file->getFile()]->hasPiece())
		{
			Piece* piece = pTiles[i][file->getFile()]->getPiece();
			if (i == file->getRank() - 1 && piece->getSymbol() == 'K')
			{
				squash.addTrace("checkFile: Bottom King");
				offenders.push_back(piece);
			}
			else if (piece->getSymbol() == 'R' || piece->getSymbol() == 'Q')
			{
				squash.addTrace("checkFile: Bottom Q/R");
				offenders.push_back(piece);
			}
			break;
		}
	}

	return offenders;
}

std::vector<Piece*> ChessBoard::checkRank(Square* rank)
{
	std::vector<Piece*> offenders;

	for (int i = rank->getFile() + 1; i < 8; i++)
	{
		if (pTiles[rank->getRank()][i]->hasPiece())
		{
			Piece* piece = pTiles[rank->getRank()][i]->getPiece();
			if (i == rank->getRank() + 1 && piece->getSymbol() == 'K')
			{
				squash.addTrace("checkRank: Left King");
				offenders.push_back(piece);
			}
			else if (piece->getSymbol() == 'R' || piece->getSymbol() == 'Q')
			{
				squash.addTrace("checkRank: Left Q/R");
				offenders.push_back(piece);
			}
			break;
		}
	}

	for (int i = rank->getFile() - 1; i >= 0; i--)
	{
		if (pTiles[rank->getRank()][i]->hasPiece())
		{
			Piece* piece = pTiles[rank->getRank()][i]->getPiece();
			if (i == rank->getRank() - 1 && piece->getSymbol() == 'K')
			{
				squash.addTrace("checkRank: Right King");
				offenders.push_back(piece);
			}
			else if (piece->getSymbol() == 'R' || piece->getSymbol() == 'Q')
			{
				squash.addTrace("chekcRank: Right Q/R");
				offenders.push_back(piece);
			}
			break;
		}
	}

	return offenders;
}

std::vector<Piece*> ChessBoard::checkDiag(Square* diag)
{
	std::vector<Piece*> offenders;

	int i = diag->getRank() + 1;
	int j = diag->getFile() + 1;
	while (i < 8 && j < 8)
	{
		if (pTiles[i][j]->hasPiece())
		{
			Piece* piece = pTiles[i][j]->getPiece();
			if (i == diag->getRank() + 1 && j == diag->getFile() + 1 && (piece->getSymbol() == 'K' || (piece->getSymbol() == 'P' && piece->getColor() == 'B')))
			{
				squash.addTrace("checkDiag: TL K/P");
				offenders.push_back(piece);
			}
			else if (piece->getSymbol() == 'B' || piece->getSymbol() == 'Q')
			{
				squash.addTrace("checkDiag: TL Q/B");
				offenders.push_back(piece);
			}
			break;
		}
		i++;
		j++;
	}

	i = diag->getRank() + 1;
	j = diag->getFile() - 1;

	while (i < 8 && j >= 0)
	{
		if (pTiles[i][j]->hasPiece())
		{
			Piece* piece = pTiles[i][j]->getPiece();
			if (i == diag->getRank() + 1 && j == diag->getFile() - 1 && (piece->getSymbol() == 'K' || (piece->getSymbol() == 'P' && piece->getColor() == 'B')))
			{
				squash.addTrace("checkDiag: TR K/P");
				offenders.push_back(piece);
			}
			else if (piece->getSymbol() == 'B' || piece->getSymbol() == 'Q')
			{
				squash.addTrace("checkDiag: TR Q/B");
				offenders.push_back(piece);
			}
			break;
		}
		i++;
		j--;
	}

	i = diag->getRank() - 1;
	j = diag->getFile() + 1;

	while (i >= 0 && j < 8)
	{
		if (pTiles[i][j]->hasPiece())
		{
			Piece* piece = pTiles[i][j]->getPiece();
			if (i == diag->getRank() - 1 && j == diag->getFile() + 1 && (piece->getSymbol() == 'K' || (piece->getSymbol() == 'P' && piece->getColor() == 'W')))
			{
				squash.addTrace("checkDiag: BL K/P");
				offenders.push_back(piece);
			}
			else if (piece->getSymbol() == 'B' || piece->getSymbol() == 'Q')
			{
				squash.addTrace("checkDiag: BL Q/B");
				offenders.push_back(piece);
			}
			break;
		}
		i--;
		j++;
	}

	i = diag->getRank() - 1;
	j = diag->getFile() - 1;

	while (i >= 0 && j >= 0)
	{
		if (pTiles[i][j]->hasPiece())
		{
			Piece* piece = pTiles[i][j]->getPiece();
			if (i == diag->getRank() - 1 && j == diag->getFile() - 1 && (piece->getSymbol() == 'K' || (piece->getSymbol() == 'P' && piece->getColor() == 'W')))
			{
				squash.addTrace("checkDiag: BR K/P");
				offenders.push_back(piece);
			}
			else if (piece->getSymbol() == 'B' || piece->getSymbol() == 'Q')
			{
				squash.addTrace("checkDiag: BR Q/B");
				offenders.push_back(piece);
			}
			break;
		}
		i--;
		j--;
	}

	return offenders;
}

std::vector<Piece*> ChessBoard::checkL(Square* l)
{
	std::vector<Piece*> offenders;

	short rankAndFileOps[16] = { 1,  2,
								-1,  2,
								 2,  1,
								 2, -1,
								 1, -2,
								-1, -2,
								-2,  1,
								-2, -1 };

	unsigned int i = 0;
	unsigned int curRank = -1;
	unsigned int curFile = -1;
	while (i < 16)
	{
		curRank = l->getRank() + rankAndFileOps[i];
		curFile = l->getFile() + rankAndFileOps[i + 1];
		if (validSquare(curRank, curFile))
		{
			if (pTiles[curRank][curFile]->hasPiece())
			{
				Piece* offender = pTiles[curRank][curFile]->getPiece();
				if (offender->getSymbol() == 'N')
				{
					squash.addTrace("checkL: N");
					offenders.push_back(offender);
				}
			}
			i += 2;
		}
	}

	return offenders;
}

void ChessBoard::printTrace()
{
	squash.printTrace();
}

void ChessBoard::printBoard()
{
	for (short i = 7; i >= 0; i--)
	{
		for (short j = 7; j >= 0; j--)
		{
			if (pTiles[i][j]->hasPiece())
			{
				std::cout << pTiles[i][j]->getPiece()->getSymbol();
			}
			else
			{
				std::cout << '-';
			}
		}
		std::cout << std::endl;
	}
}