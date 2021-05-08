
#include "chess.h"
#include "textutils.h"

using namespace std;

std::ostream& operator<<(std::ostream& stream, const Position& position)
{
	static const char REPRESENTATIONS [] { 'P', 'N', 'B', 'R', 'Q', 'K', 'p', 'n', 'b', 'r', 'q', 'k', ' ' };
	for(Row row = ROW_8; row >= ROW_1; row--)
	{
		for(File file = FILE_A; file <= FILE_H; file++)
		{
			Piece piece = position.at(make_square(file, row));
			stream << REPRESENTATIONS[piece];
			stream << ' ';
		}
		stream << endl;
	}

	return stream;
}

Square read_square(std::istream&)
{
	throw runtime_error("Not implemented");
}

Position read_fen(std::istream& stream)
{
	Position result;
	File file = FILE_A;
	Row row = ROW_8;

	while(!isspace(stream.peek()) && stream)
	{
		char ch;
		stream >> ch;
		Piece piece;

		switch(ch)
		{
			case '1' ... '8':
				file += ch;
				continue;
			case '/':
				file = FILE_A;
				row -= 1;
				continue;
			case 'P': piece = WP; break;
			case 'N': piece = WN; break;
			case 'B': piece = WB; break;
			case 'R': piece = WR; break;
			case 'Q': piece = WQ; break;
			case 'K': piece = WK; break;
			case 'p': piece = BP; break;
			case 'n': piece = BN; break;
			case 'b': piece = BB; break;
			case 'r': piece = BR; break;
			case 'q': piece = BQ; break;
			case 'k': piece = BK; break;
			default: throw runtime_error(string("Unknown char ") + ch + " in fen");
		}

		result.place(make_square(file, row), piece);
		++file;
	}

	char color;

	stream >> color;
	result.sideToMove = color == 'w' ? WHITE : BLACK;
	
	string castleRights;
	stream >> castleRights;

	for(char right : castleRights)
	{
		switch(right)
		{
			case 'k': result.castlingRights |= CR_B_OO; break;
			case 'K': result.castlingRights |= CR_W_OO; break;
			case 'q': result.castlingRights |= CR_B_OOO; break;
			case 'Q': result.castlingRights |= CR_W_OOO; break;
		}
	}

	result.enPassantSquare = read_square(stream);
	stream >> result.rule50;

	int halfMoveClock;
	stream >> halfMoveClock;
	halfMoveClock = 2 * (halfMoveClock - 1) + (result.sideToMove == BLACK);

	return result;
}

Move read_move(std::istream&, const Position&)
{
	throw runtime_error("Not implemented");
}
