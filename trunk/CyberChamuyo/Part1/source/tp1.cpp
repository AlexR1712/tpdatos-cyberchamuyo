#include "../include/tp1.h"

#include <stdlib.h>
#include <iostream>

#include "../include/stringUtilities.h"
#include "../include/statisticsManager.h"
#include "../include/fixedLengthRecordSequentialFile.h"
#include "../include/fixedLengthTextRecord.h"
#include "../include/InvertedList.h"

int main(int argc, char *argv[]){
	std::string userInput;
	std::string command;
	std::vector<std::string>* commandParams = new std::vector<std::string>;
	StatisticsManager statisticsManager;

	//cargaDiccionario inputFiles/dictionary2.txt
	//cargaFrases inputFiles/frases-celebres.txt
	//cargaIndices
	//busquedaBooleano perro

	if
	(statisticsManager.isSuccessfullInit()) {
		statisticsManager.printHelp();
		do {
			std::cout << "Ingrese un comando: " << std::endl;
			userInput = "";
			std::getline(std::cin,userInput);
			command = parseCommand(userInput,commandParams);
			if (command != USER_COMMAND_EXIT) {
				statisticsManager.processCommand(command,*commandParams);
			}
		} while (command != USER_COMMAND_EXIT);

		return EXIT_SUCCESS;
	} else {
		std::cout << "Error en inicialización. Saliendo del programa..." << std::endl;
		return EXIT_FAILURE;
	}
}

std::string parseCommand(std::string userInput, std::vector<std::string>* commandParams) {
	std::string command = "";
	unsigned int from = 0;
	unsigned int to = 0;

	to = userInput.find(' ',from);
	command = userInput.substr(from,to);

	commandParams->clear();
	while (to != userInput.npos && to < userInput.length()) {
		from = to + 1;
		if (userInput[from] == '"') {
			from++;
			to = userInput.find('"',from);
			commandParams->push_back(userInput.substr(from,(to-from)));
			to++;
		} else {
			to = userInput.find(' ',from);
			commandParams->push_back(userInput.substr(from,(to-from)));
		}
	}

	return command;
}
