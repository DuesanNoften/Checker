#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "board.h"

class Game
{
public:
	// Start game
	void run();
	void testRun();

	// Movement
	bool move(std::pair<int,int> fromCoords, std::pair<int,int> toCoords);
    bool winCondition(Color defendingColor);
    bool tie(Color defendingColor);
    Color getTurn(int moveNumber) const;
	// Utilities
	void printBoard();
	std::string printColor(Color color);

private:
	Board board;
};

#endif
