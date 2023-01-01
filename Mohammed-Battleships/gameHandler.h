#pragma once
#include "adaship.h"

class GameHandler {
protected:
	std::vector<int> _nextCoords;
	Board* _myBoard;
	Board* _enemyBoard;
public:
	GameHandler(Board* myBoard, Board* enemyBoard);

	// virtual func allows overriding of method by PlayerHandler and CPUHandler
	virtual std::vector<int> getNextAttack() = 0;
};