#include "adaship.h"

// gets user input after displaying some options and a prompt - did it differently in the end
//std::string getOptions(std::vector<std::string> options, std::string question)
//{
//    std::string response = "";
//
//    std::cout << "\n\n";
//    if (!options.empty())
//    {
//        copy(options.begin(), options.end(),
//            std::ostream_iterator<std::string>(std::cout, "\n"));
//    }
//
//    std::cout << question;
//    getline(std::cin >> std::ws, response);
//    return response;
//}

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

// trim leading white-spaces
static std::string& ltrim(std::string& s) {
    size_t startpos = s.find_first_not_of(" \t\r\n\v\f");
    if (std::string::npos != startpos)
    {
        s = s.substr(startpos);
    }
    return s;
}

// trim trailing white-spaces
static std::string& rtrim(std::string& s) {
    size_t endpos = s.find_last_not_of(" \t\r\n\v\f");
    if (std::string::npos != endpos)
    {
        s = s.substr(0, endpos + 1);
    }
    return s;
}

// predicate function for case insensitive string comparison
bool compare_pred(unsigned char a, unsigned char b) {
    return std::tolower(a) == std::tolower(b);
}

// main compare function
bool compare(std::string const& a, std::string const& b) {
    if (a.length() == b.length()) {
        return std::equal(b.begin(), b.end(),
            a.begin(), compare_pred);
    }
    else {
        return false;
    }
}