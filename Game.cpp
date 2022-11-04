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
        if (board.movePiece(from, to))
        {
            currentMove++;
            toMove = getTurn(currentMove);
        }
        else
        {
           std::cout<<"Error Invalid move.\n";
        }
    }
}

void Game::guiRun()
{
    return;
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
 * - Each player have just one piece
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

// Change guiTurn between White/Black
void Game::switchGuiTurn()
{
    if (guiTurn == WHITE)
    {
        guiTurn = BLACK;
    }
    else {
        guiTurn = WHITE;
    }
}

// Clear move1 and move2 strings
void Game::resetMoves()
{
    move1 = "";
    move2 = "";
}

void Game::getInput(QString input)
{
    qDebug() << "Game saw that " << input << "was clicked, and will now respond.";

    // If this is the first click, store it in move1
    if (move1 == "")
    {
        move1 = input.toStdString();
    }
    // If this is the second click, store it in move2
    else
    {
        move2 = input.toStdString();

        // We can now pass the move to the Game
        std::pair<int, int> from = board.algebraicToInt(move1); 	// convert substring to pair
        std::pair<int, int> to = board.algebraicToInt(move2);		// convert substring to pair

        // Verify that a piece was selected
        if (board.getPiece(from) == nullptr)
        {
            qDebug() << "No piece selected.";
            sendResponse("Invalid Move");
            resetMoves();
            return;
        }

        if (board.getPiece(from)->getColor() != guiTurn)
        {
            std::cout << "Error: It's " << printColor(guiTurn) << "'s turn." << '\n';
            qDebug() << "Game.cpp: Error: Not your turn.";
            emit sendResponse("Invalid Move");
            resetMoves();
            return;
        }

        // Attempt to move piece
        else if (board.movePiece(from, to))
        {
            switchGuiTurn();
            // Send QString response containing the two spaces of the valid move
            QString sendStr = "";
            QString part1 = QString::fromStdString(move1);
            QString part2 = QString::fromStdString(move2);
            sendStr += part1;
            sendStr += part2;
            sendResponse(sendStr);
        }
        else
        {
            std::cout << "Error: Invalid move.\n";
            qDebug() << "Error: Invalid move.";
            sendResponse("Invalid Move");
        }
        if(tie(guiTurn))
        {
            sendResponse("Tie");
        }
        resetMoves();
    }

}
