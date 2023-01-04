#include "adaship.h"

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
		if (compare(key, "BOARD")) {
			std::getline(singleLine, currentItem, delim2);
			val1 = currentItem;
			std::getline(singleLine, currentItem, delim2);
			val2 = currentItem;
		}
		else if (compare(key, "SHIP")) {
			std::getline(singleLine, currentItem, delim3);
			val1 = currentItem;
			std::getline(singleLine, currentItem, delim3);
			val2 = currentItem;
		}

		std::cout << "key: " << key << " val1: " << val1 << " val2: " << val2 << "\n";
	}
}



// FILE PARSER ATTEMPT #1 (DEPRECATED but kept because it is an interesting bit of code)

//void parseFromFile(const char* filePath)
//{
//	// first param = file pointer pointer. Needs address to pointer where we are storing pointer
//	// double pointer - address of variable which is a pointer
//	FILE* file = NULL;
//	fopen_s(&file, filePath, "rb"); // 'rb' opens file to read in binary mode (windows specific)
//	if (file)
//	{
//		// Open file for reading
//		size_t fileSize = 0; // size_t = unsigned int as big as architecture of app
//		fseek(file, 0, SEEK_END); //  moves file pos indicator to end with offset 0
//		fileSize = ftell(file);
//		rewind(file); // moves file pos indicator to start
//
//		// had to do static cast for c++
//		char* fileContent = static_cast<char*>(malloc(fileSize + 1)); // allocate one byte more to have space for null term
//		if (fileContent)
//		{
//			if (fread(fileContent, fileSize, 1, file) == 1) // to validate it works - returns how many counts were possible. max is 1 as set in param. if it fails will be 0.
//			{
//				// read success
//				fileContent[fileSize] = '\0';
//				fileParser(fileContent);
//
//			}
//			free(fileContent);
//		}
//		fclose(file);
//	}
//}
//
//void fileParser(const char* iniData)
//{
//	// working buffer
//	char buffer[256]; // to save section name // buffer will have 256 characters
//	*buffer = '\0'; // first char will be null terminator - basically empty string. *buffer at this point is an uninitialized pointer
//
//	// Current values
//	char currentSection[256];
//	*currentSection = '\0';
//	char currentKey[256];
//	char currentValue[256];
//
//	// 0 - Ready for Ini Data
//	// 1 - Comment started
//	// 2 - Section name started
//	// 3 - Key started
//	// 4 - key finished
//	// 5 - ready for value
//	// 6 - value started
//	// 7 - invalid data
//
//	int32_t state = 0;
//	// starts at address of first character, as long as deref of current add not null term - increment add to next character
//	for (const char* c = iniData; *c; c++)
//	{
//		switch (state)
//		{
//			// Waiting for ini data
//		case 0:
//			switch (*c)
//			{
//			case ';': // Start comment
//				state = 1;
//				break;
//			case '[': // Start section name
//				state = 2;
//				break;
//			case ' ': // valid spacings
//			case '\t':
//			case '\n':
//				break;
//			default: // State key
//				appendBuffer(buffer, *c);
//				state = 3;
//			}
//			break;
//
//			// Reading comment
//		case 1:
//			if (*c == '\n') state = 0; // End comment
//			break;
//
//			// Section name stated
//		case 2:
//			switch (*c)
//			{
//			case ']': // End section name
//				strcpy_s(currentSection, 256, buffer);
//				*buffer = '\0';
//				state = 0;
//				break;
//			case '\n': // Invalid section name (discard)
//				*buffer = '\0';
//				state = 0;
//				break;
//			default:
//				appendBuffer(buffer, *c);
//				break;
//			}
//			break;
//
//			// Key started
//		case 3:
//			switch (*c)
//			{
//			case ' ': // End key
//			case '\t':
//				strcpy_s(currentKey, 256, buffer);
//				*buffer = '\0';
//				state = 4;
//				break;
//			case '\n': // Invalid kvp
//				state = 0;
//				break;
//			default:
//				appendBuffer(buffer, *c);
//				break;
//			}
//			break;
//
//			// End of key
//		case 4:
//			switch (*c)
//			{
//			case '=':  // Ready for value
//				state = 5;
//				break;
//			case '\n':  // Invalid kvp
//				state = 0;
//				break;
//			case ' ':
//			case '\t':
//				state = 7;
//				break;
//			}
//			break;
//
//			// Ready for value
//		case 5:
//			switch (*c)
//			{
//			case '\n': // Invalid kvp
//				state = 0;
//				break;
//			case ' ': // Begin value
//			case '\t':
//				appendBuffer(buffer, *c);
//				state = 6;
//				break;
//			}
//			break;
//
//			// Start of value
//		case 6:
//			switch (*c)
//			{
//			case '\n': // end of value
//				stripeBuffer(buffer);
//				strcpy_s(currentValue, 256, buffer);
//				*buffer = '\0';
//				state = 0;
//
//				// Report out
//				printf("Property: %s:%s\n", currentKey, currentValue);
//				break;
//			case '\t': // replace tab with spaces
//				strcat_s(buffer, 256, "    ");;
//				break;
//			default:
//				appendBuffer(buffer, *c);
//				break;
//
//			}
//
//			// Invalid value
//		case 7:
//			if (*c == '\n') state = 0;
//			break;
//		}
//	}
//}
//
//// every time we read something valid - we write to buffer
//// *cursor - dereferences cursor
//// 1. cursor assigned to buffer
//// 2. move forward till we find null terminator
//
//void appendBuffer(char* buffer, char c)
//{
//	if (!iscntrl(c))
//	{
//		char str[2] = { c, '\0' };
//		strcat_s(buffer, 256, str); // safe vsn of strcat - size defined (256)
//	}
//}
//
//// remove whitespace from end of buffer
//// char *c is pointer to last char of str
//// 1. get length of current str
//// 2. minus 1 to get last - first index is 0 so last is len - 1
//// 3. extract that as a char
//void stripeBuffer(char* buffer)
//{
//	char* c = &buffer[strlen(buffer) - 1];
//	if (*c == ' ' || *c == '\t')
//	{
//		*c = '\0';
//		stripeBuffer(buffer); // recursion - calling func in func
//	}
//}