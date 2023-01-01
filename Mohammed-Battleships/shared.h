#pragma once

#include "adaship.h"

// std::string getOptions(std::vector<std::string> options, std::string
// question);
bool isNumber(std::string str);
int strToInt(std::string str, int initVal);
static std::string& ltrim(std::string& s);
static std::string& rtrim(std::string& s);
bool compare_pred(unsigned char a, unsigned char b);
bool compare(std::string const& a, std::string const& b);