#include "adaship.h"

//constructor
CPUHandler::CPUHandler(Board* myBoard, Board* enemyBoard, int difficulty) : GameHandler(myBoard, enemyBoard) {
    srand(time(nullptr)); //set random seed based on time so always diff
    _difficulty = difficulty;
}

//Returns the current difficulty of the game.
int CPUHandler::getDifficulty() {
    return _difficulty;
}


bool CPUHandler::setDifficulty(int d) {
    if (d >= 1 && d <= 3) {
        _difficulty = d;
        return true;
    }
    else {
        return false;
    }
}

// 1 (easy), 2 (normal aka 50% hard), 3 (hard aka 100% hard)
std::vector<int> CPUHandler::getNextAttack() {
    if (_difficulty == 3) { //hard mode
        return getHardCoords();
    } else if (_difficulty == 2) {
        if (rand() % 2 == 0) { // 50/50 chance of random or hard mode attack
            return getRndCoords();
        }
        else {
            return getHardCoords();
        }
    }
    else if (_difficulty == 1) {
        return getRndCoords();
    }
    else {
        return getRndCoords();
    }
    
}

//gets random coords for attack 
//towards the end will become v ineffcient
std::vector<int> CPUHandler::getRndCoords() {
    std::vector<int> tempCoords(2, 0);
    std::vector<int> finalcoords(2, -1);
    //Get a random starting point.
    int startx = (rand() % (_enemyBoard->getBoardSize()));
    int starty = (rand() % (_enemyBoard->getBoardSize()));

    int bSize = _enemyBoard->getBoardSize();
    bool valid = false;
    for (int i = startx; i < bSize; i++) {
        tempCoords[0] = i;
        for (int j = starty; j < bSize; j++) {
            tempCoords[1] = j;
            if (!(_enemyBoard->getTileAtCoords(tempCoords)._hit)) {
                finalcoords[0] = i;
                finalcoords[1] = j;
                return finalcoords;
            }

            if (j == bSize - 1) {
                j = -1;
            }
            if (j == starty - 1) {
                j = bSize;
            }

        }
        if (i == bSize - 1) {
            i = -1;
        }
        if (i == startx - 1) {
            i = bSize;
        }
    }

    return tempCoords;
}

std::vector<int> CPUHandler::getHardCoords() {
    // Store the board size in a local variable for better performance
    const int bSize = _enemyBoard->getBoardSize();
    std::vector<int> tempCoords(2, 0); //temp coords
    std::vector<std::vector<int>> coordsToCheck;

    // Loop through the board and add all tiles that are adjacent to previously hit tiles
    // to a list of coordinates to check
    for (int i = 0; i < bSize; i++) {
        tempCoords[0] = i;
        for (int j = 0; j < bSize; j++) {
            tempCoords[1] = j;
            // If the CPU has previously hit, not missed and the ship is still not destroyed...
            if (_enemyBoard->getTileAtCoords(tempCoords)._hit && !_enemyBoard->getTileAtCoords(tempCoords)._empty && !_enemyBoard->getShipAtCoords(tempCoords)->isDestroyed()) {
                for (int g = 0; g < 4; g++) {
                    int alty = (g == 0) ? i + 1 : (g == 1) ? i - 1 : i;
                    int altx = (g == 2) ? j + 1 : (g == 3) ? j - 1 : j;
                    if (altx >= 0 && altx < bSize && alty >= 0 && alty < bSize) { //make sure its inbounds
                        std::vector<int> adjacentCoords = { alty, altx };
                        // Only add coordinates that have not been hit
                        if (!_enemyBoard->getTileAtCoords(adjacentCoords)._hit) {
                            coordsToCheck.push_back(adjacentCoords);
                        }
                    }
                }
            }
        }
    }

    // If there are any coordinates to check, return the first one in the list
    if (!coordsToCheck.empty()) {
        return coordsToCheck[0];
    }
    // Otherwise, return a random set of coordinates
    return getRndCoords();
}