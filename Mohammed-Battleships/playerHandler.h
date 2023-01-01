#pragma once
#include "adaship.h"

class PlayerHandler : public GameHandler {
private:
	int letterToCoord(char x);

public:
	PlayerHandler(Board* myBoard, Board* enemyBoard); // constructor
	virtual std::vector<int> getNextAttack() final; // get the next set of coords
};