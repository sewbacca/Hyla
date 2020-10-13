/*
	author: Sewbacca
	file: board.cpp
	Implementation for board representation
*/

#include "board.h"


U64 Board::board(Piece piece) const
{
	if (piece == No_Piece) return 0ULL;
	return pieces[piece];
}

Piece Board::at(Field field) const
{
	for(Piece piece { W_Pawn }; piece < PIECE_COUNT; ++piece)
	{
		if(pieces[piece] & field)
		{
			return piece;
		}
	}

	return No_Piece;
}

void Board::place(Piece piece, Field field)
{
	remove(field);
	if (piece != No_Piece)
		pieces[piece] |= field;
}

void Board::remove(Field field)
{
	U64 delpos { ~(to_bitboard(field)) };

	for(U64& bitboard : pieces)
	{
		bitboard &= delpos;
	}
}
