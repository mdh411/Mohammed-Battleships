#pragma once

#include "adaShip.h"

class Board {
private:
	int size;

	std::vector<std::vector<BoardTile>> board;
	std::vector<Ship*> ships;

public:
	Board(int size);

	static const int MAX_SIZE = 80;
	static const int MIN_SIZE = 5;
};