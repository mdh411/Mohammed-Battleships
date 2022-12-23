#include "adaship.h"

int main() {
	//menu();
	//fileParser("adaShipConfig.ini");
	Board* newBoard = new Board(10);
	std::cout << newBoard->displayBoard();
}