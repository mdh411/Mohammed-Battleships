#pragma once

const int DEFAULT_BOARDSIZE = 10;
const int DEFAULT_NSHIPS = 5;

// bounds for board size
const int MAX_SIZE = 25; // capped at 25 until I can solve challenge with letters past Z
const int MIN_SIZE = 5;

const std::string openingMessage =
"Welcome to Mohammed's Battleships game!"
"\n\nWhen it is your turn, enter the co-ordinates for your next attack on "
"the enemy fleet."
"\nUse the format (Letter)(Number) - e.g. 'B2'"
"\nH = Hit\tM = Miss"
"\nThe game is won when all of the opponent's fleet is destroyed"
"\nGood Luck!!!\n";

const int menuOptions = 3;
const std::string menuStrings[menuOptions] = { "Player Vs CPU", "Set Board Dimensions", "Quit" };