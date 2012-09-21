#ifndef STRINGUTILITIES_H_
#define STRINGUTILITIES_H_

#include <string>
#include <vector>

void splitString(std::string& string, std::vector<std::string>& splittedString, char delimiter);

bool isNumeric(std::string& string);

std::string leftPad(std::string string, char padWith, unsigned int padTo);

std::string intToString(int i);

#endif /* STRINGUTILITIES_H_ */
