#include "adaship.h"

//constructor
CPUHandler::CPUHandler(Board* myBoard, Board* enemyBoard) : GameHandler(myBoard, enemyBoard) {
    srand(time(nullptr)); //set random seed based on time so always diff
}

std::vector<int> CPUHandler::getNextAttack() {
    return getRndCoords(); //not smart CPU yet just guesses randomly
}

//gets random coords for attack 
//towards the end will become v ineffcient
std::vector<int> CPUHandler::getRndCoords() {
    std::vector<int> tempCoords(2, 0);
    std::vector<int> finalcoords(2, -1);
    //Get a random starting point.
    int startx = (rand() % (_enemyBoard->getBoardSize()));
    int starty = (rand() % (_enemyBoard->getBoardSize()));

    int gSize = _enemyBoard->getBoardSize();
    bool valid = false;
    for (int i = startx; i < gSize; i++) {
        tempCoords[0] = i;
        for (int j = starty; j < gSize; j++) {
            tempCoords[1] = j;
            if (!(_enemyBoard->getTileAtCoords(tempCoords)._hit)) {
                finalcoords[0] = i;
                finalcoords[1] = j;
                return finalcoords;
            }

            if (j == gSize - 1) {
                j = -1;
            }
            if (j == starty - 1) {
                j = gSize;
            }

        }
        if (i == gSize - 1) {
            i = -1;
        }
        if (i == startx - 1) {
            i = gSize;
        }
    }

    return tempCoords;
}