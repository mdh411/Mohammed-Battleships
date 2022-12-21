#include "adaShip.h"

void fileParser(std::string fileName) {
	std::vector<std::string> linesOfConfigFile;
	std::ifstream file;

	// open file and add all lines to a vector
	file.open(fileName);
	if (file.is_open())
	{
		std::string line;

		while (getline(file, line)) {
			line.erase(std::remove_if(line.begin(), line.end(), isspace), // remove whitespaces from line
				line.end());
			linesOfConfigFile.push_back(line);
		}
		file.close();
	}
	else {
		std::cerr << "Couldn't open config file for reading.\n"; // if unable to open file output this
	}

	for (int i = 0; i < linesOfConfigFile.size(); i++)
	{
		std::string currentItem;
		char delim = ':'; char delim2 = 'x'; char delim3 = ',';
		std::stringstream singleLine(linesOfConfigFile[i]);
		std::string key, val1, val2;

		std::getline(singleLine, currentItem, delim); // get first part of the line
		key = currentItem; // store it
		if (key == "Board") {
			std::getline(singleLine, currentItem, delim2);
			val1 = currentItem;
			std::getline(singleLine, currentItem, delim2);
			val2 = currentItem;
		}
		else if (key == "Boat") {
			std::getline(singleLine, currentItem, delim3);
			val1 = currentItem;
			std::getline(singleLine, currentItem, delim3);
			val2 = currentItem;
		}

		std::cout << "key: " << key << " val1: " << val1 << " val2: " << val2 << "\n";
	}
}