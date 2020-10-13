/*
	author: Sewbacca
	file: board.h
	Contains board definition
*/

#pragma once

#include <array>

#include "defs.h"

class Board
{
public:
	U64 board(Piece) const;
	Piece at(Field) const;

	void place(Piece, Field);
	void remove(Field);

	Color turn { White };
	CastlingSide rights { No_Castling };
	Field enpas { No_Field };
	int hisply { 0 };
	int fiftyply { 0 };
private:
	std::array<U64, PIECE_COUNT> pieces { };
};
