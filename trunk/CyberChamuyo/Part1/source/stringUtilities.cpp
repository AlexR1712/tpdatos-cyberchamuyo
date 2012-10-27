#include <sstream>
#include "../include/stringUtilities.h"

namespace StringUtilities {

void sacarR(std::string& s) {
	if(s.find('\r') != std::string::npos)
		s.erase(s.find('\r'));
}

void splitString(std::string string, std::vector<std::string>& splittedString, char delimiter) {
	unsigned int from = 0;
	unsigned int to = 0;

	while (to != string.npos) {
		to = string.find(delimiter,from);
		splittedString.push_back(string.substr(from,(to-from)));
		from = to + 1;
	}
}

bool isNumeric(std::string string) {
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

std::string padLeft(std::string string, char padWith, unsigned int padTo) {
	std::string paddedString = "";

	if (padTo >= string.size()) {
		for (unsigned int i = 0; i < (padTo - string.size()); i++) {
			paddedString += padWith;
		}
	}

	paddedString += string;

	return paddedString;
}

std::string padRight(std::string string, char padWith, unsigned int padTo) {
	std::string paddedString = string;

	if (padTo >= string.size()) {
		for (unsigned int i = 0; i < (padTo - string.size()); i++) {
			paddedString += padWith;
		}
	}

	return paddedString;
}

int StringToInt (const std::string Text ) {
	int result;
	std::stringstream stringstream(Text);
	return stringstream >> result ? result : 0;
}

std::string intToString(int i) {
	std::stringstream stringstream;
	stringstream << i;
	return stringstream.str();
}

std::string floatToString(float f) {
	std::stringstream stringstream;
	stringstream << f;
	return stringstream.str();
}

std::wstring stringToWstring(std::string string) {
	std::wstring wString;

	std::copy(string.begin(),string.end(),std::back_inserter(wString));
	return wString;
}

std::string trim(std::string string) {
	unsigned int from = 0;
	unsigned int to = string.size();
	bool finished = false;

	for (unsigned int i = 0; (i < string.size()) && !finished; i++) {
		if (string[i] == ' ')
			from++;
		else
			finished = true;
	}

	finished = false;
	for (unsigned int i = string.size() - 1; (i >= 0) && !finished; i--) {
		if (string[i] == ' ')
			to--;
		else
			finished = true;
	}

	return string.substr(from,to);
}

}
