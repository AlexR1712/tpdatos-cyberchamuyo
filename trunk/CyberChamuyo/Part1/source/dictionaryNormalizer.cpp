#include "dictionaryNormalizer.h"

#include <fstream>
#include <iostream>
#include <string>

DictionayNormalizer::DictionayNormalizer() {
}

void DictionayNormalizer::normalizeDictionary(std::string dictionaryPath) {
	std::ifstream inputFile;
	std::ofstream normalizedFile;

	inputFile.open(dictionaryPath.c_str(),std::fstream::in);
	normalizedFile.open("dictionary_NORMALIZED.txt");
	std::string line;

	while (std::getline(inputFile,line) && !(line.empty())) {
		std::cout << "Procesando linea: " << line << std::endl;
		normalizeWord(line);
		normalizedFile << line << std::endl;
	}

	inputFile.close();
	normalizedFile.close();
}

void DictionayNormalizer::normalizeWord(std::string& string) {
	char c;
	for (unsigned int i = 0; i < string.length(); ++i) {
		c = string[i];
		if ( (c == '�') || (c == '�') )
			c = 'a';
		if ( (c == '�') || (c == '�') )
			c = 'e';
		if ( (c == '�') || (c == '�') )
			c = 'i';
		if ( (c == '�') || (c == '�') )
			c = 'o';
		if ( (c == '�') || (c == '�') || (c == '�') || (c == '�') )
			c = 'u';
		if (c >= 'A' && c <= 'Z')
			c = c + 32;
		string[i] = c;
	};
}

DictionayNormalizer::~DictionayNormalizer() {
}
