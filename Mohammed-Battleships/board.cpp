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


//randomly populate board - this is for mvp but hoping to get this from file in next iteration
void Board::randomPopulate() {
	srand(time(nullptr)); //set seed

	const int maxCount = 700000; // to prevent infinite loops
	int count = 1;
	int lengths[5] = { 5, 4, 3, 3, 2 };
	std::string names[5] = { "Carrier", "Battleship", "Destroyer", "Submarine", "Patrol Boat" };

	for (int i = 0; i < _nShips; i++) {
		bool valid = false;
		while (!valid) {
			bool tVertical = rand() % 2 == 0; //set a random orientation
			int tRow; //temp row
			int tCol; //temp col
			std::vector<int> tcoord(2, 0); //temp coords

			//assign trow and and tcol, so it doesn't go off board
			if (tVertical) {
				tRow = rand() % (_size);
				tCol = rand() % ((_size)-lengths[i % 5] + 1);
			}
			else {
				tCol = rand() % (_size);
				tRow = rand() % ((_size)-lengths[i % 5] + 1);
			}

			//assign
			tcoord[0] = tRow;
			tcoord[1] = tCol;

			//create temp object
			Ship* tempShip = new Ship(names[i % 5], lengths[i % 5], tVertical, tcoord);

			//check if valid?
			if (validatePos(tempShip)) {
				valid = true;
				addShipToBoard(tempShip);
			}
			//otherwise repeat.

			//safety catch
			count++;
			if (count > maxCount) {
				throw new std::string("Error - Random Fill Took Too Long To Complete, Please Try Again");
			}
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
	boardStr2 += "____";
	for (int i = 0; i < _size; i++) {

		boardStr += " ";
		boardStr += i + 'A';
		boardStr += " |";
		boardStr2 += "____";
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
	boardStr2 += "____";

	for (int i = 0; i < _size; i++) {

		BoardStr += " ";
		BoardStr += i + 'A';
		BoardStr += " |";
		boardStr2 += "____";
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

bool Board::hit(std::vector<int> coords) {

	//check if coords are inbounds
	if (coords[0] >= 0 && coords[0] < _size && coords[1] >= 0 && coords[1] < _size) {
		_board[coords[0]][coords[1]]._hit = true;

		//check if coords hit a ship
		if (!_board[coords[0]][coords[1]]._empty && _board[coords[0]][coords[1]]._currentShip != nullptr) {
			_board[coords[0]][coords[1]]._currentShip->hit();
		}
		return true;
	}
	else {
		return false;
	}
}

int Board::letterToCoord(char x) {
	//make lowercase if upper
	if (x >= 97) {
		x -= 32;
	}

	//validity check (0-10), must modify this with size
	if (x < 65 || x >(_size - 1)) {
		return x - 65;
	}
	else {
		return -1;
	}
}

bool Board::validatePos(Ship* s) {
	bool tempAlign = s->isVertical();
	int currentX = s->getCol();
	int currentY = s->getRow();
	int currentLen = s->getLength();
	Ship tempShip = *s;

	bool valid = true;

	//check OoB first
	if (tempAlign) {
		if (currentX + currentLen > _size)
			valid = false;
	}
	else {
		if (currentY + currentLen > _size)
			valid = false;
	}

	//Validate part 2 (collision)
	bool valid2 = true;

	//check collision against all other ship
	for (int j = 0; j < _ships.size(); j++) {

		Ship* other = _ships[j]; //the other ship being checked for

		//if parallel
		if (other->isVertical() == tempAlign) {
			if (tempShip.isVertical()) { //horizontal
				if (currentY == other->getRow()) {  //on the same row
					if (currentX <= other->getCol() + other->getLength() - 1 &&
						currentX + currentLen - 1 >= other->getCol()) { //and overlaping
						valid2 = false; //that means they are colliding
					}
				}
			}
			else { //vertical
				if (currentX == other->getCol()) {  //on the same column
					if (currentY <= other->getRow() + other->getLength() - 1 && currentY + currentLen - 1 >= other->getRow()) {
						valid2 = false; //then they are colliding
					}
				}
			}
		}
		else { //if not parallel

			//dumb check- checks every position for conflict.
			//invalidates on first occasion. This is O(n^2) function
			//is in need of a rewrite for efficiency, but works for now.
			for (int ii = 0; ii < currentLen; ii++) {
				for (int jj = 0; jj < other->getLength(); jj++) {
					if (tempShip.isVertical()) {
						if (currentX + ii == other->getCol() && currentY == other->getRow() + jj) {
							valid2 = false;
						}
					}
					else {
						if (currentX == other->getCol() + jj && currentY + ii == other->getRow()) {
							valid2 = false;
						}
					}
				}
			}
		}
	}

	//if one or the other is not valid, then return false,
	//as they are conflicting.
	if (!valid || !valid2) {
		return false;
	}
	else {
		return true;
	}
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

bool Board::isFleetDestroyed() {
	for (int i = 0; i < _ships.size(); i++) {
		if (!_ships[i]->isDestroyed()) {
			return false;
		}
	}
	return true;
}

Ship* Board::getShipAtCoords(std::vector<int> coords) {
	//check if coords are inbounds
	if (coords[0] >= 0 && coords[0] < _size && coords[1] >= 0 && coords[1] < _size) {
		if (!_board[coords[0]][coords[1]]._empty && _board[coords[0]][coords[1]]._currentShip != nullptr) {
			return _board[coords[0]][coords[1]]._currentShip;
		}
		else {
			return nullptr;
		}
	}
	else {
		std::cout << "These Coordinates are out of bounds, please try again.";
	}
}

BoardTile Board::getTileAtCoords(std::vector<int> coords) {
	//check if coords are inbounds
	if (coords[0] >= 0 && coords[0] < _size && coords[1] >= 0 && coords[1] < _size) {
		return _board[coords[0]][coords[1]];
	}
	else {
		std::cout << "These Coordinates are out of bounds, please try again.";
	}
}