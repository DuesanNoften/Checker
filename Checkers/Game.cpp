#include <vector>
#include <string>
#include <sstream>
#include "Game.h"

/* Basic implementation of checkers. */
void Game::run()
{
	// Set up turn-based game
	std::string input;
	int currentMove = 1;
	Color toMove = getTurn(currentMove);

	// Print instructions
    std::cout << "Welcome to Checkers game. Enter moves as space-separated strings (e.g. e2 e4) or exit to quit." << '\n';

	// Repeat until game is finished
	while (true)
	{

		// Print board
		printBoard();

		// Get first input
		std::cout << printColor(toMove) << "'s turn. Enter move: ";
		std::getline(std::cin, input);

		// Handle non-move commands
		if (input == "exit")
		{
			break;
		}
		else if (input == "moves")
		{
			board.printMoves();
			continue;
		}
		else if (input == "revert")
		{
			if (currentMove > 1)
			{
				board.revertLastMove();
				currentMove--;
				toMove = getTurn(currentMove);
			}
			else
			{
				std::cout << "Can't revert - already at beginning of game." << '\n';
			}
			continue;
		}
		else if (input == "captures")
		{
			board.printCapturedPieces();
			continue;
		}

		// Convert input to a move
		std::string buf;					// for parsing input
		std::stringstream ss(input);       	// insert the string into a stream
		std::vector<std::string> tokens; 	// create vector to hold substrings
		while (ss >> buf)
		{
			tokens.push_back(buf);
		}
		std::pair<int, int> from = board.algebraicToInt(tokens[0]); 	// convert substring to pair
		std::pair<int, int> to = board.algebraicToInt(tokens[1]);		// convert substring to pair

		// Verify that the correct player is moving
		if (board.getPiece(from)->getColor() != toMove)
		{
			std::cout << "Error: It's " << printColor(toMove) << "'s turn." << '\n';
			continue;
		}


		// Attempt move piece
				currentMove++;
				toMove = getTurn(currentMove);
        }
}

/* For trying out different chess play configurations. */
void Game::testRun()
{
	std::cout << "Starting board for move testing\n";
	board.printBoardAlgebraicAxes();

    std::cout << "Testing checker moving forward\n";
	board.movePiece(std::make_pair(0, 2), std::make_pair(1, 1));
	board.printBoardAlgebraicAxes();

    std::cout << "Testing checker capturing\n";
	board.movePiece(std::make_pair(1, 1), std::make_pair(3, 3));
	board.printBoardAlgebraicAxes();

    std::cout << "Testing checker moving into friendly piece (should fail)\n";
	board.movePiece(std::make_pair(3, 3), std::make_pair(1, 5));
	board.printBoardAlgebraicAxes();


}


// Returns true if a team has run out of pieces
bool Game::winCondition(Color defendingColor)
{
		return false;	
}

/* Returns true if a player is in stalemate. The conditions of stalemate are:
 * - No legal moves
 * - Each player have just one piece for two turns
*/
bool Game::tie(Color defendingColor)
{

	// No other options for defendingColor, so return true for isStalemate
    return false;
}

/* Pass a move from the Game to the Board. */
bool Game::move(std::pair<int, int> fromCoords, std::pair<int, int> toCoords)
{
	return board.movePiece(fromCoords, toCoords);
}

/* Print the Board. */
void Game::printBoard()
{
	board.printBoardAlgebraicAxes();
}

/* Determine whose turn it is based on the number of moves in the current game. */
Color Game::getTurn(int moveNumber) const
{
	if (moveNumber % 2 == 1)
	{
		return WHITE;
	}
	else
	{
		return BLACK;
	}
}

/* Print the string representation of a Color enum. */
std::string Game::printColor(Color color)
{
	if (color == WHITE)
	{
		return "White";
	}
	else
	{
		return "Black";
	}
}
