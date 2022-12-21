#pragma once

#include "adaShip.h"

class BoardTile {
	bool empty = true;
	Ship* currentShip;
	bool hit = false;
};