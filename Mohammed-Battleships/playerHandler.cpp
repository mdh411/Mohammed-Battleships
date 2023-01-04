#include "adaship.h"

PlayerHandler::PlayerHandler(Board* myBoard, Board* enemyBoard) : GameHandler(myBoard, enemyBoard) {

}


// uses ASCII values
// 97 is the number used internally by C++ to represent 'a'
int PlayerHandler::letterToCoord(char x) {
	if (x >= 97) {
		x -= 32; // -32 will make it a capital letter (e.g., 65 = 'A')
	}

	if (x < 65 || x >(_enemyBoard->getBoardSize() - 1)) {
		return x - 65;
	}
	else {
		return -1;
	}
}

// takes user input and returns coords if valid
std::vector<int> PlayerHandler::getNextAttack() {
	bool valid = false;
	std::vector<int> coords(2, -1);

	while (!valid) {
		std::cout << "Please enter a coordinate pair to hit (A-J)(1-10): " << std::endl;

		std::string input;

		int col, row;
		int bSize = _enemyBoard->getBoardSize();

		// nested if statement for robustness but not ideal for readability
		if (getline(std::cin, input)) { // valid input check - returns false if error

			if (input.size() > 0 && input.size() <= 3) { // input size cannot be greater than 3

				if (isalpha(input[0]) && isdigit(input[1]) && (input.size() <= 2 || isdigit(input[2]))) { // check type for each value of coord

					try {

						std::string num = input.substr(1); // substr starts from pos 1 (which is acc 2nd value)
						row = stoi(num) - 1;

						if (row < bSize && row >= 0) { // if row is within board

							col = letterToCoord(input[0]);

							if (col < bSize && col >= 0) { // if col is within board
								coords[0] = row;
								coords[1] = col;

								if (!_enemyBoard->getTileAtCoords(coords)._hit) { // check not already hit
									return coords; // now safe to return coords
								}
								else {
									std::cout << "Invalid attack, you've already hit that spot!" << std::endl;
								}

							}
							else {
								std::cout << "Invalid attack, make sure the coordinate is in bounds." << std::endl;
							}
						}
						else {
							std::cout << "Invalid attack, make sure the coordinate is in bounds." << std::endl;
						}

					}
					catch (...) {
						std::cout << "Invalid attack, make sure the coordinate has a number." << std::endl;
					}
				}
				else {
					// flexibility to quit at any time - if input has one char && it's q then quit
					if (input.size() == 1 && (input[0] == 'q' || input[0] == 'Q')) {
						throw new std::string("Thanks for playing...Bye.");
					}
					std::cout << "Invalid attack, make sure you use the correct format." << std::endl;
				}
			}
			else {
				std::cout << "Invalid attack, make sure you use only 2 or 3 characters!" << std::endl;
			}
		}
		else {
			std::cout << "Invalid attack, please try again." << std::endl;
		}
	}
}


// attempt at improving this method - slightly buggy so reverted to original
// 
//std::vector<int> PlayerHandler::getNextAttack() {
//    std::vector<int> coords(2, -1);
//
//    while (true) {
//        std::cout << "Please enter a coordinate pair to hit (A-J)(1-10): " << std::endl;
//
//        std::string input;
//        if (!getline(std::cin, input)) {
//            std::cout << "Invalid input, please try again." << std::endl;
//            continue;
//        }
//
//        // Check if player wants to quit
//        if (input.size() == 1 && (input[0] == 'q' || input[0] == 'Q')) {
//            std::cout << "Thanks for playing...Bye." << std::endl;
//            break;
//        }
//
//        // Check for valid input size
//        if (input.size() > 3 || input.size() <= 1) {
//            std::cout << "Invalid attack, make sure you use only 2 or 3 characters!" << std::endl;
//            continue;
//        }
//
//        // Check for valid coordinate format
//        if (!isalpha(input[0]) || !isdigit(input[1]) || (input.size() == 3 && !isdigit(input[2]))) {
//            std::cout << "Invalid attack, make sure you use the correct format." << std::endl;
//            continue;
//        }
//
//        int row, col;
//        try {
//            // Convert row coordinate to integer
//            std::string num = input.substr(1);
//            row = stoi(num) - 1;
//        }
//        catch (const std::exception& e) {
//            std::cout << "Invalid attack, make sure the coordinate has a number." << std::endl;
//            continue;
//        }
//
//        // Convert column coordinate to integer
//        col = letterToCoord(input[0]);
//
//        // Check if coordinates are within board bounds
//        int bSize = _enemyBoard->getBoardSize();
//        if (row < 0 || row >= bSize || col < 0 || col >= bSize) {
//            std::cout << "Invalid attack, make sure the coordinate is in bounds." << std::endl;
//            continue;
//        }
//
//        // Check if tile has already been hit
//        coords[0] = row;
//        coords[1] = col;
//        if (_enemyBoard->getTileAtCoords(coords)._hit) {
//            std::cout << "Invalid attack, you've already hit that spot!" << std::endl;
//            continue;
//        }
//
//        return coords;
//    }
//
//    // Return default value if player wants to quit
//    return coords;
//}