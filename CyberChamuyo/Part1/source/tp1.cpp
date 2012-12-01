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
	std::vector<std::string> commandParams;
	StatisticsManager statisticsManager;

	if (statisticsManager.isSuccessfullInit()) {
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
	} else {
		std::cout << "Error en inicialización. Saliendo del programa..." << std::endl;
		return EXIT_FAILURE;
	}
}

std::string parseCommand(std::string userInput, std::vector<std::string>& commandParams) {
	std::string command = "";

	StringUtilities::splitString(userInput,commandParams,USER_COMMAND_SEPARATOR);
	command = commandParams[0];
	commandParams.erase(commandParams.begin());

	return command;

}
