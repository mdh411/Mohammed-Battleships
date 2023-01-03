#include "adaship.h"

// game constructor
Game::Game(int size, int nShips) {
    // instantiates boards
    _playerBoard = new Board(size);
    _enemyBoard = new Board(size);

    // instantiates player handler and cpu handler
    _player = new PlayerHandler(_playerBoard, _enemyBoard);
    _enemy = new CPUHandler(_playerBoard, _enemyBoard);

    _size = size;
    _nShips = nShips;
}

// intro to game - welcome + basic outline
std::string Game::intro() { return openingMessage; }

// displays menu options to user
std::string Game::menu() {
    std::string menuStr;

    menuStr += "\nPlease enter a number to start your preferred game type:\n";
    for (int i = 0; i < menuOptions; i++) {
        menuStr += (std::to_string(i + 1) + ": " + menuStrings[i] + "\n");
    }

    return menuStr;
}

// sets up game - currently not very useful as there is only one real option
// (playerVScpu)
bool Game::setupGame() {
    if (!_isSetUp) {

        std::cout << intro() << std::endl;
        bool inputDone = false;
        while (!inputDone) {
            std::cout << menu() << std::endl;
            int option = getValidInput(menuOptions);
            switch (option) {
            case 1: // player vs CPU
                inputDone = true;
                std::cout << "Game starting..." << std::endl;
                break;
            case 2: {
                std::cout << "Enter a valid board size (" << MIN_SIZE << "-" << MAX_SIZE << "):\n";
                _size = getValidInput(MAX_SIZE, MIN_SIZE);

                // Instantiate boards
                _playerBoard = new Board(_size, _nShips);
                _enemyBoard = new Board(_size, _nShips);

                // Instantiate player handlers
                _player = new PlayerHandler(_playerBoard, _enemyBoard);
                _enemy = new CPUHandler(_playerBoard, _enemyBoard);
                std::cout << "Successfully set grid to " << _size << "x" << _size << ".\n\n";
                break;
            }
               
            case 3:
                throw new std::string("Thank you for playing...Bye.");
                break;
            default:
                throw new std::string("Unexpected - Quitting game...Bye.");
                break;
            }
        }

        // populate board randomly for now
        _playerBoard->randomPopulate();
        _enemyBoard->randomPopulate();

        std::cout << "*** *********************** START *********************** ***"
            << std::endl
            << std::endl;
        std::cout << displayGameBoards()
            << std::endl; // display personal and enemy boards

        _isSetUp = true; // switch to true as setup should only run once

        return true;
    }
    return false;
}

// handles main game mechanics:
// register hits/destroyed ships, display hit results, detect win & show final
// boards
void Game::runTurn() {
    // check game still in progress
    if (!_isFinished) {
        _nTurn++; // increment turn count

        // declare bools to be used for logging attack results
        bool p1DestroyedShip = false, p2DestroyedShip = false, p1Hit = false,
            p2Hit = false;

        std::vector<int> p1Coords;
        try {
            p1Coords = (_player->getNextAttack());
        }
        catch (...) {
            std::cout << displayFinalBoards() << std::endl;
            throw new std::string("User has quit, exiting...");
        }
        std::vector<int> p2coords(_enemy->getNextAttack());

        // Hit corresponding boards
        _enemyBoard->hit(p1Coords);
        Ship* p1Target = _enemyBoard->getShipAtCoords(p1Coords);

        // check if not nullptr
        if (p1Target) {
            // set context switches
            if (p1Target->isDestroyed()) {
                p1DestroyedShip = true;
            }
            else {
                p1Hit = true;
            }
        }

        // Player 2

        _playerBoard->hit(p2coords);
        Ship* p2Target = _playerBoard->getShipAtCoords(p2coords);

        // check if not nullptr
        if (p2Target) {
            // set context switches
            if (p2Target->isDestroyed()) {
                p2DestroyedShip = true;
            }
            else {
                p2Hit = true;
            }
        }

        // show turn
        std::string turnStr = std::to_string(_nTurn);
        if (_nTurn < 10)
            turnStr += " ";
        std::cout << "*** *********************** Turn " << turnStr
            << "*********************** ***" << std::endl
            << std::endl;
        std::cout << std::endl << displayGameBoards() << std::endl;

        // show result of attack
        if (p1DestroyedShip) {
            std::cout << "You sunk a " << p2Target->getName() << "!" << std::endl;
        }
        else if (p1Hit) {
            std::cout
                << "You hit an enemy ship!"
                << std::endl; // dont display ship name as it can give away size.
        }

        char column = p2coords[1] + 'A';
        std::cout << "The CPU guessed ";
        std::cout << column;
        std::cout << p2coords[0] + 1 << "." << std::endl;

        if (p2DestroyedShip) {
            std::cout << "The CPU sunk your " << p2Target->getName() << "!"
                << std::endl;
        }
        else if (p2Hit) {
            std::cout << "The CPU hit your " << p2Target->getName() << "!"
                << std::endl;
        }

        // check for winner
        if (_playerBoard->isFleetDestroyed() && _enemyBoard->isFleetDestroyed()) {
            _isFinished = true;
            std::cout << std::endl << "So tight! It's a tie!" << std::endl;
        }
        else if (_playerBoard->isFleetDestroyed()) {
            _isFinished = true;
            std::cout << std::endl << "CPU Wins!" << std::endl;
        }
        else if (_enemyBoard->isFleetDestroyed()) {
            _isFinished = true;
            std::cout << std::endl << "You win!" << std::endl;
        }

        // display full boards on game end
        if (_isFinished) {
            std::cout << displayFinalBoards() << std::endl;
            std::cout << "Great Game!" << std::endl;
        }

    }
    else {
        throw new std::string("Game has already finished. Please construct a new "
            "game class to replay.");
    }
}

// runs the game
bool Game::runGame() {
    if (!_isSetUp) {
        setupGame();
    }
    if (!_isFinished) {
        runTurn();
    }
    else {
        return false;
    }
    return true;
}

// keeps game running till finished
bool Game::contGame() {
    if (_isFinished)
        return false;
    while (!_isFinished) {
        this->runGame();
    }
    return true;
}

// returns -1 if quit, gets a valid integer input min-max inclusive from input
int Game::getValidInput(int max, int min) {
    std::string input;
    while (true) {
        try {
            std::getline(std::cin, input);
            if (input[0] == 'q' || input[0] == 'Q') {
                return -1;
            }
            bool valid = true;
            if (!stoi(input) || stoi(input) > max || stoi(input) < min) {
                throw 1000;
            }
            else {
                std::cout << std::endl;
                return stoi(input);
            }
        }
        catch (...) {
            std::cout << "Invalid input, please try again: " << std::endl;
        }
    }
}

// displays boards - hides enemy board
std::string Game::displayGameBoards() {
    std::stringstream current;
    current << "\n=== Enemy's Board: ===\n" << std::endl;
    current << _enemyBoard->displayHiddenBoard() << std::endl;
    current << "=== Your Board: ===\n" << std::endl;
    current << _playerBoard->displayBoard() << std::endl;
    return current.str();
}

// displays everything on both boards
std::string Game::displayFinalBoards() {
    std::stringstream current;
    current << std::endl << "-- Full Boards --" << std::endl << std::endl;
    current << "-CPU's Board:-" << std::endl;
    current << _enemyBoard->displayHiddenBoard() << std::endl;
    current << "-Your Board:-" << std::endl;
    current << _playerBoard->displayBoard() << std::endl;
    return current.str();
}