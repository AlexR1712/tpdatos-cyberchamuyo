#include "tp1.h"

#include <stdlib.h>
#include <iostream>

#include "dictionaryNormalizer.h"
#include "dictionaryRandomizer.h"
#include "stringUtilities.h"
#include "statisticsManager.h"

int main(int argc, char *argv[]){
	std::string userInput;
	std::string command;
	std::vector<std::string> commandParams;
	StatisticsManager statisticsManager;
	bool showId = false;

	if (argc == 2) {
		command = argv[1];
		if (command == "true")
			showId = true;
	}

	DictionaryNormalizer dictionaryNormalizer;
	dictionaryNormalizer.normalize("dictionary.txt");

	DictionayRandomizer dictionayRandomizer;
	dictionayRandomizer.randomizeDictionary("dictionary_NORMALIZED.txt",showId);

	statisticsManager.printHelp();
	do {
		std::cout << "Ingrese un comando: " << std::endl;
		userInput = "";
		std::getline(std::cin,userInput);
		command = parseCommand(userInput,commandParams);
		if (command != USER_COMMAND_EXIT) {
			statisticsManager.processCommand(command,commandParams);
		}
		commandParams.clear();
	} while (command != USER_COMMAND_EXIT);

	return EXIT_SUCCESS;
}

std::string parseCommand(std::string& userInput, std::vector<std::string>& commandParams) {
	std::string command = "";

	splitString(userInput,commandParams,USER_COMMAND_SEPARATOR);
	command = commandParams[0];
	commandParams.erase(commandParams.begin());

	return command;
}
