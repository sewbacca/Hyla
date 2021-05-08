
#pragma once

#include <cstdint>

#include "utils/enum_operators.h"

// Typedefs

typedef uint64_t bitboard;

// Constants

constexpr char STARTPOS[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

constexpr int PIECE_COUNT = 12;
constexpr int PIECE_TYPE_COUNT = 6;
constexpr int SQUARE_COUNT = 64;
constexpr int BOARD_DIAMETER = 8;
constexpr int MAX_MOVES = 512;
constexpr int MAX_HISTORY = 2048;

// Enums

enum Square
{
	A1, B1, C1, D1, E1, F1, G1, H1,
	A2, B2, C2, D2, E2, F2, G2, H2,
	A3, B3, C3, D3, E3, F3, G3, H3,
	A4, B4, C4, D4, E4, F4, G4, H4,
	A5, B5, C5, D5, E5, F5, G5, H5,
	A6, B6, C6, D6, E6, F6, G6, H6,
	A7, B7, C7, D7, E7, F7, G7, H7,
	A8, B8, C8, D8, E8, F8, G8, H8,

	NO_SQUARE,
};

enum File
{
	FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H,

	NO_FILE
};

enum Row
{
	ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8,

	NO_ROW
};

enum Direction
{
	NORTH = 8,
	SOUTH = -8,
	EAST = 1,
	WEST = -1,
	NORTH_WEST = NORTH + WEST,
	NORTH_EAST = NORTH + EAST,
	SOUTH_WEST = SOUTH + WEST,
	SOUTH_EAST = SOUTH + EAST,
};

enum PieceType
{
	PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING,
	
	NO_PIECE_TYPE
};

enum Color
{
	WHITE, BLACK
};

enum Piece
{
	WP, WN, WB, WR, WQ, WK,
	BP, BN, BB, BR, BQ, BK,
	NO_PIECE,
};

enum CastlingRights
{
	CR_W_OO  = 0b1000,
	CR_W_OOO = 0b0100,
	CR_B_OO  = 0b0010,
	CR_B_OOO = 0b0001,

	CR_OO    = CR_W_OO | CR_B_OO,
	CR_OOO   = CR_W_OOO | CR_B_OOO,
	CR_WHITE = CR_W_OO | CR_W_OOO,
	CR_BLACK = CR_B_OO | CR_B_OOO,
	CR_ALL   = CR_W_OO | CR_W_OOO | CR_B_OO | CR_B_OOO,
};

// Classes

class Move { };

class MoveList
{
private:
	Move moves[MAX_MOVES];
	Move* position = moves;
public:
	Move* begin() { return moves; }
	Move* end()   { return position; }
	void push_back(Move move) { *position++ = move; }
};

// Operators

ENABLE_BITWISE_OPERATORS(CastlingRights)

ENABLE_CREMENT_OPERATORS(Square)
ENABLE_BASIC_OPERATORS(Square)

ENABLE_BASIC_OPERATORS(File)
ENABLE_CREMENT_OPERATORS(File)

ENABLE_BASIC_OPERATORS(Row)
ENABLE_CREMENT_OPERATORS(Row)
