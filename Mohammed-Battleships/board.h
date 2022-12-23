#pragma once

#include "adaShip.h"

// handles the game boards
class Board {
private:
	int _size; // board dimensions
	int _nShips; // number of ships on board - want to customize later on

	// using a 2d vector for board
	std::vector<std::vector<BoardTile>> _board;
	std::vector<Ship*> _ships;

	void addShipToBoard(Ship* s);

public:

	// default board constructor
	Board(int size = DEFAULT_BOARDSIZE, int nShips = DEFAULT_NSHIPS);

	int getBoardSize() const;
	void setBoardSize(int size);

	std::string displayBoard();
	std::string displayHiddenBoard();
	bool hit(std::vector<int> coords);
	bool isFleetDestroyed();
};