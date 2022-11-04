#include <iostream>
#include "Board.h"
#include "Piece.h"

/* Default constructor */
Piece::Piece(Type t, Color c)
{
	type = t;
	color = c;
	moves = 0;
}

/* Override << operator to print out the type and color of the piece. */
std::ostream &operator<<(std::ostream &out, const Piece &piece)
{
	// This has to use a getter because this is a friend function
	out << " " << piece.colorToChar(piece.getColor()) << piece.typeToChar(piece.getType()) << " ";
	return out;
}

Color Piece::getColor() const
{
	return color;
}

void Piece::setColor(Color color)
{
	Piece::color = color;
}

Type Piece::getType() const
{
	return type;
}

void Piece::setType(Type type)
{
	Piece::type = type;
}

bool Piece::getMoved() const
{
	return moves > 0;
}

void Piece::incrementMoves()
{
	moves++;
}

void Piece::decrementMoves()
{
	moves--;
}

/* Enum converters */
char Piece::typeToChar(Type type) const
{
	switch(type)
	{

        case CHECKER: return 'C';
        case KING: return 'K';
		default: return ' ';
	}
}

char Piece::colorToChar(Color color) const
{
	switch(color)
	{
		case WHITE: return 'W';
		case BLACK: return 'B';
		default: return ' ';
	}
}
