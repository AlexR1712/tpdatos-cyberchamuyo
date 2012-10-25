#ifndef STRINGUTILITIES_H_
#define STRINGUTILITIES_H_

#include <string>
#include <vector>

namespace StringUtilities {

void splitString(std::string string, std::vector<std::string>& splittedString, char delimiter);

bool isNumeric(std::string string);

std::string padLeft(std::string string, char padWith, unsigned int padTo);

std::string padRight(std::string string, char padWith, unsigned int padTo);

int StringToInt (const std::string Text );

std::string intToString(int i);

std::string floatToString(float f);

std::string trim(std::string string);

}

#endif /* STRINGUTILITIES_H_ */
