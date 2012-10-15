#include <stdlib.h>
#include "tp1.h"
#include "dictionaryNormalizer.h"
#include "dictionaryRandomizer.h"

int main(int argc, char *argv[]){
	std::string command;
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

	return EXIT_SUCCESS;
}
