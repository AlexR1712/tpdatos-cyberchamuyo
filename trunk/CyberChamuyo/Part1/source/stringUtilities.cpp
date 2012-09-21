#include <sstream>
#include "stringUtilities.h"

void splitString(std::string& string, std::vector<std::string>& splittedString, char delimiter) {
	unsigned int from = 0;
	unsigned int to = 0;

	while (to != string.npos) {
		to = string.find(delimiter,from);
		splittedString.push_back(string.substr(from,(to-from)));
		from = to + 1;
	}
}

bool isNumeric(std::string& string) {
	if (string == "") {
		return false;
	} else {
		for (unsigned int i = 0; i < string.size(); i++) {
			if (!isdigit(string[i])) {
				return false;
			}
		}
	}
	return true;
}

std::string leftPad(std::string string, char padWith, unsigned int padTo) {
	std::string paddedString = "";

	if (padTo >= string.size()) {
		for (unsigned int i = 0; i < (padTo - string.size()); i++) {
			paddedString += padWith;
		}
	}

	paddedString += string;

	return paddedString;
}

std::string intToString(int i) {
	std::stringstream stringstream;
	stringstream << i;
	return stringstream.str();
}
