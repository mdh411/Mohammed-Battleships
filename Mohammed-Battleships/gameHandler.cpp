#include "adaship.h"

// use of abstraction for gameHandler constructor
GameHandler::GameHandler(Board* myBoard, Board* enemyBoard) {
	_myBoard = myBoard;
	_enemyBoard = enemyBoard;
	_nextCoords = *(new std::vector<int>(2, 0));
}