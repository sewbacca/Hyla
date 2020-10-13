
#include "defs.h"

std::tuple <PieceType, Color> seperate(Piece piece)
{
	if(piece == No_Piece) return { No_PieceType, No_Color };

	Color color { piece <= W_King ? White : Black };
	PieceType type { static_cast<PieceType>(color == White ?  piece : piece - B_Pawn) };
	return { type, color };
}

Piece combine(PieceType type, Color color)
{
	if(type == No_PieceType) return No_Piece;
	return static_cast<Piece>((color == White ? W_Pawn : B_Pawn) + type);
}

Field select_field(int x, int y)
{
	return static_cast<Field>(x + y * 8);
}

std::tuple <int, int> point(Field field)
{
	if(field == No_Field)
		return { -1, -1 };

	return { field % 8, field / 8};
}

U64 to_bitboard(Field field)
{
	return 1ULL << field;
}

U64 operator | (U64 bitboard, Field field)
{
	return bitboard | to_bitboard(field);
}

U64& operator |= (U64& bitboard, Field field)
{
	return bitboard |= to_bitboard(field);
}

U64 operator & (U64 bitboard, Field field)
{
	return bitboard & to_bitboard(field);
}

U64& operator &= (U64& bitboard, Field field)
{
	return bitboard &= to_bitboard(field);
}

Piece& operator++(Piece& piece)
{
	return piece = static_cast<Piece>(piece + 1);
}

Field& operator++(Field& field)
{
	return field = static_cast<Field>(field + 1);
}

CastlingSide& operator |= (CastlingSide& orig, CastlingSide append)
{
	return orig = static_cast<CastlingSide>(orig | append);
}