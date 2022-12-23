#include "adaship.h"

Board::Board(int size, int nShips) : _ships(0) {
	_size = size;
	_nShips = nShips;

	if (size > MAX_SIZE) {
		throw new std::string("Board size is too large. Valid board sizes are from " + std::to_string(MIN_SIZE) + " to " + std::to_string(MAX_SIZE) + ".");
	}
	else if (size < MIN_SIZE) {
		throw new std::string("Board size is too small. Valid board sizes are from " + std::to_string(MIN_SIZE) + " to " + std::to_string(MAX_SIZE) + ".");
	}

	//add board tiles to board by row and col
	for (int i = 0; i < size; i++) {
		std::vector<BoardTile> currentTileVector;
		_board.push_back(currentTileVector);
		for (int j = 0; j < size; j++) {
			BoardTile currentTile;
			_board[i].push_back(currentTile);
		}
	}
}

int Board::getBoardSize() const {
	return _size;
}

std::string Board::displayBoard() {

	std::string boardStr;
	std::string boardStr2;

	boardStr += "  |";
	boardStr2 += "====";
	for (int i = 0; i < _size; i++) {

		boardStr += " ";
		boardStr += i + 'A';
		boardStr += " |";
		boardStr2 += "====";
	}
	boardStr += "\n";
	boardStr += (boardStr2 + "\n");

	for (int i = 0; i < _board.size(); i++) {

		boardStr += (i >= 9) ? (std::to_string(i + 1) + "| ") : (std::to_string(i + 1) + " | ");


		for (int j = 0; j < _board[0].size(); j++) {
			if (!_board[i][j]._empty && !_board[i][j]._hit) {
				boardStr += _board[i][j]._currentShip->getName().at(0);
				boardStr += _board[i][j]._currentShip->getName().at(1);
				boardStr += "  ";
			}
			else if (_board[i][j]._hit && _board[i][j]._empty) {
				boardStr += "M   ";
			}
			else if (!_board[i][j]._hit) {
				boardStr += "~   ";
			}
			else {
				boardStr += "H   ";
			}
		}
		boardStr += "\n";
	}

	boardStr += (boardStr2 + "\n");

	return boardStr;

}

std::string Board::displayHiddenBoard() {
	std::string BoardStr;
	std::string boardStr2;

	BoardStr += "  |";
	boardStr2 += "====";

	for (int i = 0; i < _size; i++) {

		BoardStr += " ";
		BoardStr += i + 'A';
		BoardStr += " |";
		boardStr2 += "====";
	}
	BoardStr += "\n";


	BoardStr += (boardStr2 + "\n");
	for (int i = 0; i < _board.size(); i++) {
		BoardStr += (i >= 9) ? (std::to_string(i + 1) + "| ") : (std::to_string(i + 1) + " | ");
		for (int j = 0; j < _board[0].size(); j++) {
			if (!_board[i][j]._hit) {
				BoardStr += "~   ";
			}
			else if (_board[i][j]._hit && _board[i][j]._empty) {
				BoardStr += "M   ";
			}
			else {
				BoardStr += "H   ";
			}
		}
		BoardStr += "\n";
	}
	BoardStr += (boardStr2 + "\n");

	return BoardStr;
}

void Board::addShipToBoard(Ship* s) {
	_ships.push_back(s);

	for (int i = 0; i < s->getLength(); i++) {
		if (s->isVertical()) {
			_board[s->getRow()][s->getCol() + i]._empty = false;
			_board[s->getRow()][s->getCol() + i]._currentShip = s;
		}
		else {
			_board[s->getRow() + i][s->getCol()]._empty = false;
			_board[s->getRow() + i][s->getCol()]._currentShip = s;
		}
	}
}