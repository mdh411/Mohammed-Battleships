#pragma once

#include "adaship.h"

// handles the game boards
class Board {
private:
	int _size;   // board dimensions
	int _nShips; // number of ships on board - want to customize later on

	// using a 2d vector for board
	std::vector<std::vector<BoardTile>> _board;
	std::vector<Ship*> _ships;

	bool validatePos(Ship* s); // checks if ship would be valid on the current board
	int letterToCoord(char x);    // gets a coord from a letter input
	void addShipToBoard(Ship* s); // adds ship to board and vector of ships

public:
	// default board constructor
	Board(int size = DEFAULT_BOARDSIZE, int nShips = DEFAULT_NSHIPS);
	void randomPopulate(); // randomly populates board with ships

	int getBoardSize() const;
	void setBoardSize(int size);

	std::string displayBoard();
	std::string displayHiddenBoard(); // displays board but hides ships for gameplay purposes
	bool isFleetDestroyed(); // check if all ships on a board are destroyed

	bool hit(std::vector<int> coords);              // hits a coord on the board
	Ship* getShipAtCoords(std::vector<int> coords); // gets the ship at a coord
	BoardTile getTileAtCoords(std::vector<int> coords); // similar to above but returns tile
};