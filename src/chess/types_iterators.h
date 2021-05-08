
#pragma once

#include "utils/enum_iterator.h"

#include "types.h"

struct Pieces
{
	typedef EnumIterator<Piece> iterator;

	iterator begin() { return iterator(WP); }
	iterator end() { return iterator(NO_PIECE); }
};
