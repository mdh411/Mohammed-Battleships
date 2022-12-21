#include "adaship.h"

// gets user input after displaying some options and a prompt
std::string getOptions(std::vector<std::string> options, std::string question)
{
    std::string response = "";

    std::cout << "\n\n";
    if (!options.empty())
    {
        copy(options.begin(), options.end(),
            std::ostream_iterator<std::string>(std::cout, "\n"));
    }

    std::cout << question;
    getline(std::cin >> std::ws, response);
    return response;
}

// takes a string param and uses istring stream to check if its a number
bool isNumber(std::string str) {
    float number;
    std::istringstream value(str);
    value >> number;
    return !value.fail() && value.eof();
}

int strToInt(std::string str, int initVal) {
    return isNumber(str) ? stoi(str) : initVal;
}