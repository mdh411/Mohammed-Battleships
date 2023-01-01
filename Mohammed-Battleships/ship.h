#pragma once

#include "adaship.h"

class Ship {
private:
	std::string _shipName;

	int _length;

	bool _vertical;

	std::vector<int> _coords;

	int _hits = 0;

	bool _destroyed = false;

public:
	Ship(std::string name, int len, bool vertical, std::vector<int> coords);

	void destroy();
	void hit();

	std::string getName();
	bool isDestroyed();
	bool isVertical();
	int getHits();
	std::vector<int> getCoords();
	int getLength();
	int getCol();
	int getRow();
};