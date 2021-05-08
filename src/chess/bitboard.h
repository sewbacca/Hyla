
#pragma once

#include <cassert>
#include <iterator>

#include "types.h"

constexpr bitboard square_bb(Square square) { return 1ULL << square; }

constexpr bitboard& operator |= (bitboard& container, Square square) { return container |= square_bb(square); }
constexpr bitboard& operator &= (bitboard& container, Square square) { return container &= square_bb(square); }
constexpr bitboard& operator ^= (bitboard& container, Square square) { return container ^= square_bb(square); }

constexpr bitboard operator | (bitboard board, Square square) { return board | square_bb(square); }
constexpr bitboard operator & (bitboard board, Square square) { return board & square_bb(square); }
constexpr bitboard operator ^ (bitboard board, Square square) { return board ^ square_bb(square); }

constexpr Square lsb(bitboard board);
constexpr void destroy_lsb(bitboard& board);

class BitSquares
{
private:
	bitboard board;
public:
	class iterator : std::iterator<std::input_iterator_tag, Square>
	{
	private:
		bitboard board;
	public:
		explicit iterator(bitboard board) : board { board } { }

		iterator& operator++() { destroy_lsb(board); return *this; }
		iterator operator++(int) { iterator copy = *this; ++(*this); return copy; }
		bool operator==(iterator other) { return board == other.board; }
		bool operator!=(iterator other) { return !(*this == other); }
		Square operator*() const { return lsb(board); }
	};

	BitSquares(bitboard board) : board { board } { };
	iterator begin() const { return iterator(board); }
	iterator end() const { return iterator(0ULL); }
};

// Constexpr implementations

constexpr void destroy_lsb(bitboard& board)
{
	// Example:
	// 11000 & (11000 - 1) = 11000 & 10111 = 10000
	board &= board - 1;
}

#if defined(__GNUC__)  // GCC, Clang, ICC

constexpr Square lsb(bitboard board)
{
	assert(board);
	return Square(__builtin_ctzll(board));
}

#else
#error "Compiler not supported."
#endif
