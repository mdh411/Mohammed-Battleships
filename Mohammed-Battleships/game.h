#pragma once
#include "adaShip.h"
class GameHandler;

class Game {
private:
	Board* _playerBoard;
	Board* _enemyBoard;

	GameHandler* _player;
	GameHandler* _enemy;

	void runTurn();

	int _difficulty = 0;
	int _nTurn = 0;
	int _size = DEFAULT_BOARDSIZE;
	int _nShips = DEFAULT_NSHIPS;
	bool _isSetUp = false;
	bool _isRunning = false;
	bool _isFinished = false;

public:
	Game(int size = DEFAULT_BOARDSIZE, int nShips = DEFAULT_NSHIPS);
	std::string intro();
	std::string menu();
	std::string displayGameBoards();
	std::string displayFinalBoards();

	int getValidInput(int max, int min = 1);

	bool setupGame();
	bool runGame();
	bool contGame();
};