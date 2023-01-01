#pragma once

const int DEFAULT_BOARDSIZE = 10;
const int DEFAULT_NSHIPS = 5;

// bounds for board size
const int MAX_SIZE = 80;
const int MIN_SIZE = 5;

const std::string openingMessage =
"Welcome to Mohammed's Battleships game!"
"\n\nWhen it is your turn, enter the co-ordinates for your next attack on "
"the enemy fleet."
"\nUse the format (Letter)(Number) - e.g. 'B2'"
"\nH = Hit\tM = Miss"
"\nThe game is won when all of the opponent's fleet is destroyed"
"\nGood Luck!!!\n";

const int menuOptions = 2;
const std::string menuStrings[menuOptions] = { "Player Vs CPU", "Quit" };