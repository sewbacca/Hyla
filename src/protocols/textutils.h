
#pragma once

#include <istream>
#include <ostream>
#include <string>
#include <sstream>

#include "chess.h"
#include "textutils.h"

std::ostream& operator<<(std::ostream& stream, const Position& position);

Position read_fen(std::istream&);
Position read_fen(std::string fen);
Move read_move(std::istream&, const Position&);

// Inline implementations

inline Position read_fen(std::string fen)
{
	std::stringstream stream(fen);
	return read_fen(stream);
}
