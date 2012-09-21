#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include "tp1.h"
#include "dictionaryNormalizer.h"
#include "dictionaryRandomizer.h"
#include "externalSorter.h"

int main(int argc, char *argv[]){
	std::string command;

	DictionayNormalizer dictionayNormalizer;
	dictionayNormalizer.normalizeDictionary("dictionary.txt");

	DictionayRandomizer dictionayRandomizer;
	dictionayRandomizer.randomizeDictionary("dictionary_NORMALIZED.txt");

	ExternalSorter externalSorter;
	externalSorter.sort("dictionary_RANDOMIZED.txt");

	std::cout << "Ingresa una tecla para continuar" << std::endl;
	std::getline(std::cin,command);

	return EXIT_SUCCESS;
}

void externalHeapSort(){
	std::ifstream inputFile;
	inputFile.open("randomizedBinary",std::fstream::in);
	std::ofstream outputFile;
	outputFile.open("orderedFile");
	std::vector<unsigned int> sortBuffer;
	unsigned int sortBufferIndex = 0;
	unsigned int heapSize = 0;
	std::string line;
	std::vector<std::string> registerParams;
	unsigned int parentIndex = 0;

	unsigned int aux;
	bool swaped = true;

	while (std::getline(inputFile,line) && !(line.empty())) {
		std::cout << "Procesando linea: " << line << std::endl;
		sortBuffer.push_back(atoi(registerParams[0].c_str()));
		heapSize++;
		sortBufferIndex = sortBuffer.size();

		parentIndex = sortBufferIndex / 2;
		while ( (parentIndex != 0) && (swaped) ) {
			if (sortBuffer[parentIndex - 1] > sortBuffer[sortBufferIndex - 1]) {
				aux = sortBuffer[parentIndex - 1];
				sortBuffer[parentIndex - 1] = sortBuffer[sortBufferIndex - 1];
				sortBuffer[sortBufferIndex - 1] = aux;
				sortBufferIndex = parentIndex;
				parentIndex = sortBufferIndex / 2;
			} else {
				swaped = false;
			}
		}

		//meter en el heap
		//outputFile <<   << std::endl;
	}

}
