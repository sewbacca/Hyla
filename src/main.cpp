/*
	author: Sewbacca
	file: main.cpp
	Main entry point for Hyla
*/

#include <iostream>
#include "board.h"
#include "textutils.h"

int main(int argc, char const *argv[])
{
	while(true)
	{
		Board board { read_fen(std::cin) };
		debug_board(std::cout, board);
	}
}
