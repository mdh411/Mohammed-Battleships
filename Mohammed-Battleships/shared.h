#pragma once

#include "adaShip.h"

std::string getOptions(std::vector<std::string> options, std::string question);
bool isNumber(std::string str);
int strToInt(std::string str, int initVal);
static std::string& ltrim(std::string& s);
static std::string& rtrim(std::string& s);