
#pragma once

#include "types.h"

constexpr Square make_square(File, Row);

// Constexpr implementations

constexpr Square make_square(File file, Row row)
{
	return Square(row * BOARD_DIAMETER + file);
}
