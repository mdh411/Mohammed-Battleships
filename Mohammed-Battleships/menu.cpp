#include "adaship.h"

void menu() {
    std::string prompt =
        "\nPlease enter a number to start your preferred game type: ";
    std::vector<std::string> options = { "\t1. One player v CPU",

                                        "\n\t0. Quit" };
    std::string selection = "-1";

    std::cout << "\nWelcome to Adaship";
    // this is a while loop variant - block will execute once before checking if
    // condition is true block will repeat until condition becomes false.
    do {
        selection = getOptions(options, prompt);
        if (isNumber(selection)) {
            int selectionInt = strToInt(selection, 0);

            switch (selectionInt) {
                // case 1: playerVsCpu();
                // break;

            case 0:
                std::cout << "\nThank you for playing...Bye.";
                break;
            default:
                std::cout << "\n'" << selection
                    << "' is an invalid option - please try again.";
                break;
            }
        }
        else {
            std::cout << "\n'" << selection
                << "' is an invalid option - please try again.";
        }
    } while (selection != "0");
}