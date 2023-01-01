#include "adaship.h"

int main() {
	//fileParser("adaShipConfig.ini");

	try {
		Game* battleShips = new Game(); //initiates a new game
		battleShips->contGame(); // keeps game running till end
	}
	catch (std::string const* e) {
		std::cout << *e << std::endl; // catch errors and display them
		return 1;
	}

	return 0;
}