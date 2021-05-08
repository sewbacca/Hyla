
#include "position.h"
#include "types_iterators.h"


void Position::play(Move)
{

}

void Position::undo()
{

}

void Position::place(Square position, Piece piece)
{
	bitboardByPiece[piece] |= position;
}

Piece Position::remove(Square square)
{
	for(Piece piece : Pieces())
	{
		if(bitboardByPiece[piece] & square)
		{
			bitboardByPiece[piece] ^= square;
			return piece;
		}
	}

	return NO_PIECE;
}

void Position::move(Square from, Square to)
{
	place(to, remove(from));
}

Piece Position::at(Square square) const
{
	for(Piece piece : Pieces())
	{
		if(bitboardByPiece[piece] & square)
			return piece;
	}

	return NO_PIECE;
}
