#include "adaship.h"

// constructor
CPUHandler::CPUHandler(Board* myBoard, Board* enemyBoard)
    : GameHandler(myBoard, enemyBoard) {
    srand(time(nullptr)); // set random seed based on time so always diff
}

std::vector<int> CPUHandler::getNextAttack() {
    return getRndCoords(); // not smart CPU yet just guesses randomly
}

// gets random coords for attack
// towards the end will become v ineffcient
std::vector<int> CPUHandler::getRndCoords() {
    std::vector<int> tempCoords(2, 0);

    bool valid = false;
    while (!valid) {
        tempCoords[0] = rand() % _enemyBoard->getBoardSize() - 1;
        tempCoords[1] = rand() % _enemyBoard->getBoardSize() - 1;

        if (!_enemyBoard->getTileAtCoords(tempCoords)._hit) {
            valid = true;
        }
    }

    return tempCoords;
}