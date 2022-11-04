#include "king.h"

// Constructor
King::King(Color k) : Piece(KING, k){}


bool King::isValidMove(const Board *board, const std::pair<int, int> &fromCoords, const std::pair<int, int> &toCoords) const
{
    if (board->isDiagonalMove(fromCoords, toCoords))
    {
        if (board->isPathClear(fromCoords,toCoords))
        {
            return true;
        }
    }
    return false;
}
