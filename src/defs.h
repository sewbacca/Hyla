/*
	author: Sewbacca
	file: defs.h
	Contains a lot of often used definitions
*/

#pragma once

#include <tuple>
#include <cinttypes>

typedef uint64_t U64;
typedef uint8_t U8;

constexpr int PIECE_TYPE_COUNT { 6 };
constexpr int PIECE_COUNT { 12 };
constexpr int FIELD_COUNT { 64 };
constexpr int SIDE_LENGTH { 8 };

enum PieceType : U8
{
	Pawn = 0,
	Knight,
	Bishop,
	Rook,
	Queen,
	King,
	No_PieceType = 6
};

enum Piece : U8
{
	W_Pawn = 0,
	W_Knight,
	W_Bishop,
	W_Rook,
	W_Queen,
	W_King,
	B_Pawn = 6,
	B_Knight,
	B_Bishop,
	B_Rook,
	B_Queen,
	B_King = 11,
	No_Piece = 12
};

enum Color : U8
{
	White = 0,
	Black,
	No_Color
};

enum Field : U8
{
	A1, B1, C1, D1, E1, F1, G1, H1,
	A2, B2, C2, D2, E2, F2, G2, H2,
	A3, B3, C3, D3, E3, F3, G3, H3,
	A4, B4, C4, D4, E4, F4, G4, H4,
	A5, B5, C5, D5, E5, F5, G5, H5,
	A6, B6, C6, D6, E6, F6, G6, H6,
	A7, B7, C7, D7, E7, F7, G7, H7,
	A8, B8, C8, D8, E8, F8, G8, H8,
	No_Field
};

enum CastlingSide : U8
{
	No_Castling   = 0,
	W_KingSide    = 0b1000,
	W_QueenSide   = 0b0100,
	B_KingSide    = 0b0010,
	B_QueenSide   = 0b0001,
};

// Piece analysis

std::tuple <PieceType, Color> seperate(Piece);
Piece combine(PieceType, Color);
Field select_field(int x, int y);
std::tuple <int, int> point(Field);

// Bitboard helper

U64 to_bitboard(Field);

U64 operator | (U64 bitboard, Field);
U64& operator |= (U64& bitboard, Field);

U64 operator & (U64 bitboard, Field);
U64& operator &= (U64& bitboard, Field);

// Make enums iterable

Piece& operator++(Piece&);
Field& operator++(Field&);

// Combinate rights

CastlingSide& operator |= (CastlingSide&, CastlingSide);