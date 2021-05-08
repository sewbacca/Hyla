
#pragma once

#include "types.h"

class Position
{
private:
	bitboard bitboardByPiece[PIECE_COUNT] {};
public:
	Color sideToMove = WHITE;
	CastlingRights castlingRights = CR_ALL;
	Square enPassantSquare = NO_SQUARE;
	int halfMoves = 0;
	int rule50 = 0;
public:
	// Complex functions
	void play(Move);
	void undo();

	// Position editing
	
	void place(Square, Piece);
	void move(Square from, Square to);
	Piece remove(Square);

	// Queries

	Piece at(Square) const;
};