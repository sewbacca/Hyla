
#include <stdexcept>
#include <sstream>

#include "textutils.h"

// Helper

static char to_char(Piece piece)
{
	char c { ' ' };
	auto [type, color] = seperate(piece);
	switch (type)
	{
		case Pawn:   c = 'P'; break;
		case Knight: c = 'N'; break;
		case Bishop: c = 'B'; break;
		case Rook:   c = 'R'; break;
		case Queen:  c = 'Q'; break;
		case King:   c = 'K'; break;
		case No_PieceType: break;
	}

	if (color == Black)
		c = tolower(c);
	return c;
}

static Piece from_char(char piece)
{
	PieceType type { No_PieceType };
	Color color { White };
	switch (toupper(piece))
	{
	case 'P': type = Pawn;   break;
	case 'N': type = Knight; break;
	case 'B': type = Bishop; break;
	case 'R': type = Rook;   break;
	case 'Q': type = Queen;  break;
	case 'K': type = King;   break;
	default: throw std::runtime_error("Invalid char");
	}

	if(islower(piece))
		color = Black;

	return combine(type, color);
}

static std::string str_rights(CastlingSide rights)
{
	std::stringstream stream { };

	if(rights & W_KingSide) stream << 'K';
	if(rights & W_QueenSide) stream << 'Q';
	if(rights & B_KingSide) stream << 'k';
	if(rights & B_QueenSide) stream << 'q';
	if(rights == No_Castling) stream << '-';

	return stream.str();
}

static std::string str_field(Field field)
{
	std::stringstream stream { };
	if (field == No_Field)
	{
		stream << '-';
	}
	else
	{
		auto [x, y] = point(field);
		stream << char { 'a' + x };
		stream << char { '1' + y };
	}
	return stream.str();
}

static Field parse_field(std::string field)
{
	Field result { No_Field };
	if(field.size() == 2)
	{
		result = select_field(field[1] - '1', field[0] - 'a');

		if (result < A1 || result > H8)
			return No_Field;
	}
	return result;
}

// Implementation

void debug_board(std::ostream& stream, const Board& board)
{
	for(int y { SIDE_LENGTH - 1 }; y >= 0; --y)
	{
		for(int x { 0 }; x < SIDE_LENGTH; ++x)
		{
			stream << to_char( board.at( select_field(x, y) ) );
		}
		stream << std::endl;
	}

	stream << "Turn: " << (board.turn == White ? "w" : "b") << std::endl;
	stream << "Rights: " << str_rights(board.rights) << std::endl;
	stream << "En passent: " << str_field(board.enpas) << std::endl;
 	stream << "Fifty ply: " << board.fiftyply << std::endl;
	stream << "Clock: " << board.hisply << std::endl;
	stream << "Fen: " << to_fen(board) << std::endl;
}

std::string to_fen(const Board& board)
{
	std::stringstream stream { };

	for(int y { SIDE_LENGTH - 1 }; y >= 0; --y)
	{
		int empty { 0 };
		for(int x { 0 }; x < SIDE_LENGTH; ++x)
		{
			Piece piece { board.at( select_field(x, y) ) };

			if (piece == No_Piece) empty++;
			else
			{
				if (empty > 0) stream << empty;
				empty = 0;

				stream << to_char(piece);
			}
		}
		if(empty > 0) stream << empty;
		if (y != 0) stream << '/';
	}
	stream << ' ';

	stream << (board.turn == White ? "w" : "b") << ' ';
	stream << str_rights(board.rights) << ' ';
	stream << str_field(board.enpas) << ' ';
	stream << board.fiftyply << ' ';
	stream << board.hisply / 2 + 1;

	return stream.str();
}

Board read_fen(std::istream& stream)
{
	Board board { };

	std::string str_board { };
	std::string turn { };
	std::string rights { };
	std::string enpas { };
	int fiftyply { };
	int fullmoves { };

	int x { 0 }, y { SIDE_LENGTH - 1 };

	// Read data

	stream >> std::skipws;

	stream >> str_board;
	stream >> turn;
	stream >> rights;
	stream >> enpas;
	stream >> fiftyply;
	stream >> fullmoves;

	// Parse data

	{ // Parse board
		for(char c : str_board)
		{
			if(isdigit(c))
			{
				x += c - '0';
			}
			else if(c == '/')
			{
				x = 0;
				--y;
			}
			else if(isalpha(c))
			{
				board.place(from_char(c), select_field(x, y));
				++x;
			}
			else
				throw std::runtime_error("Invalid fen");
		}
	}

	{ // Parse Color
		if (turn == "w")
			board.turn = White;
		else if(turn == "b")
			board.turn = Black;
		else
			throw std::runtime_error("Invalid fen");
	}

	{ // Parse castling rights
		if (rights == "-")
			board.rights = No_Castling;
		else
			for(char right : rights)
			{
				switch (right)
				{
				case 'K': board.rights |= W_KingSide; break;
				case 'Q': board.rights |= W_QueenSide; break;
				case 'k': board.rights |= B_KingSide; break;
				case 'q': board.rights |= B_QueenSide; break;
				default:
					throw std::runtime_error("Invalid fen");
				}
			}
	}

	{ // Parse simple stuff
		board.enpas = parse_field(enpas);
		board.fiftyply = fiftyply;
		board.hisply = (fullmoves - 1) * 2 + (board.turn == White ? 0 : 1);
	}

	return board;
}
