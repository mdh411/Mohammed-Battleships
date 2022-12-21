#pragma once

#include "adaship.h"

class Ship {
private:
	std::string shipName;
	int length;
	bool vertical;
	std::vector<int> coords;
	int hits = 0;
	bool destroyed = false;

public:
	Ship();

	std::string getName();
	bool isDestroyed();
	bool isVertical();
	int getHits();
	std::vector<int> getCoords();
	int getLength();
};