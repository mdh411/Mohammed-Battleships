#pragma once
#include "adaship.h"

class CPUHandler : public GameHandler {
public:
    CPUHandler(Board* myBoard, Board* enemyBoard); // Constructor
    virtual std::vector<int> getNextAttack()
        final; // final specifier ensures it's not overriden by derived class
    std::vector<int> getRndCoords();
};