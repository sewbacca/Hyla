
#pragma once

#include "types.h"

class Position
{
private:
public:
	Color sideToMove = WHITE;
	CastlingRights rights = CR_ALL;
	Square enPassantSquare = NO_SQUARE;
	int halfMoves = 0;
	int rule50 = 0;
public:
	void play(Move);
	void undo();
	void place(Square, Piece);
};