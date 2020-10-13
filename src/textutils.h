/*
	author: Sewbacca
	file: textutils.h
	Contains textutils used for uci and debugging
*/

#ifndef TEXTUTILS_H
#define TEXTUTILS_H

#include <string>
#include <istream>

#include "board.h"

void debug_board(std::ostream&, const Board& board);
Board read_fen(std::istream&);
std::string to_fen(const Board&);

#endif // TEXTUTILS_H