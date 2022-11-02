#include <iostream>
#include "Checker.h"

// Constructor
Checker::Checker(Color c) : Piece(CHECKER, c) {}

/* Determine if this is a valid move based on the rules of a normal piece. */
bool Checker::isValidMove(const Board *board, const std::pair<int, int> &fromCoords, const std::pair<int, int> &toCoords) const
{
	if (board->isDiagonalMove(fromCoords, toCoords))
	{
		if (board->isPathClear(fromCoords, toCoords))
		{
			return true;
		}
	}

	// If we've gotten this far, not a valid move
	return false;

}


// Do I need to check that the final piece is a piece of the opposite color
