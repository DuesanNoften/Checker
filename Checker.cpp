#include <iostream>
#include "Checker.h"

// Constructor
Checker::Checker(Color c) : Piece(CHECKER, c) {}

/* Determine if this is a valid move based on the rules of a normal piece. */
bool Checker::isValidMove(const Board *board, const std::pair<int, int> &fromCoords, const std::pair<int, int> &toCoords) const
{
	if (board->isDiagonalMove(fromCoords, toCoords))
	{
        if (board->getMoveLength(fromCoords, toCoords)==1)
		{
			return true;
		}
        else if(board->getMoveLength(fromCoords,toCoords)==2)
        {
            if(board->isPathClear(fromCoords,toCoords)==false){
                return true;
            }
        }
	}
	return false;
}


