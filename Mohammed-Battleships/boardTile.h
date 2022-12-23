#pragma once

#include "adaShip.h"

class Ship;

class BoardTile {
public:
	bool _empty = true;
	Ship* _currentShip;
	bool _hit = false;
};