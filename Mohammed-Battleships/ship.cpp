#include "adaship.h"

// ship constructor
Ship::Ship(std::string name, int len, bool vertical, std::vector<int> coords) {
    _shipName = name;
    _length = len;
    _vertical = vertical;
    _coords = coords;
}

// destroys the ship
void Ship::destroy() {
    _destroyed = true;
}

// logs a hit on the ship && whether it destroyed ship
void Ship::hit() {
    _hits += 1;
    if (_hits >= _length) {
        _destroyed = true;
    }
}

// get name of ship
std::string Ship::getName() {
    return _shipName;
}

// return whether ship is destroyed or not
bool Ship::isDestroyed() {
    return _destroyed;
}

// return whether ship is vertical or not
bool Ship::isVertical() {
    return _vertical;
}

// get number of hits ship has taken
int Ship::getHits() {
    return _hits;
}

// gets leading coord for ship
std::vector<int> Ship::getCoords() {
    return _coords;
}

// gets ship's length
int Ship::getLength() {
    return _length;
}

//gets column ship is on (as an int)
int Ship::getCol() {
    return _coords[1];
}

//gets row ship is on (as an int)
int Ship::getRow() {
    return _coords[0];
}