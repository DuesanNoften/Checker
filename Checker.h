#ifndef CHECKER_H
#define CHECKER_H

#include "Board.h"
#include "Piece.h"

class Checker : public Piece
{
public:
    Checker(Color c);
	bool isValidMove(const Board *board, const std::pair<int, int> &fromCoords, const std::pair<int, int> &toCoords) const override;
    ~Checker() override = default;
};

#endif
