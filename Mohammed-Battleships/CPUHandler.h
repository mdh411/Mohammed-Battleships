#pragma once
#include "adaship.h"

class CPUHandler : public GameHandler {
private: 
    int _difficulty = 1;
public:
    CPUHandler(Board* myBoard, Board* enemyBoard, int difficulty); // Constructor
    virtual std::vector<int> getNextAttack()
        final; // final specifier ensures it's not overriden by derived class
    std::vector<int> getRndCoords();
    std::vector<int> getHardCoords();

    int getDifficulty();
    bool setDifficulty(int d);

};