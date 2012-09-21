#include "dictionaryRandomizer.h"

#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>

#include "stringUtilities.h"

DictionayRandomizer::DictionayRandomizer() {
}

void DictionayRandomizer::randomizeDictionary(std::string dictionaryPath) {
	std::ifstream inputFile;
	std::ofstream randomizedBinary;
	std::ofstream randomizedText;
	std::string line;
	std::string randomizedLine;
	int random;

	inputFile.open(dictionaryPath.c_str(),std::fstream::in);
	randomizedBinary.open("dictionary_RANDOMIZED",std::fstream::out | std::fstream::binary);
	randomizedText.open("dictionary_RANDOMIZED.txt",std::fstream::out);

	srand((unsigned)time(NULL));

	while (std::getline(inputFile,line) && !(line.empty())) {
		std::cout << "Procesando linea: " << line << std::endl;
		random = rand() + RANDOM_STARTS_AT;
		randomizedLine = leftPad(intToString(random),'0',9) + '\t' + line;
		randomizedText << randomizedLine  << std::endl;
		randomizedLine = randomizedLine.substr(0,REGISTER_SIZE_IN_CHARS);
		randomizedBinary << randomizedLine << std::endl;
	}

	inputFile.close();
	randomizedBinary.close();
	randomizedText.close();
}

DictionayRandomizer::~DictionayRandomizer() {
}
