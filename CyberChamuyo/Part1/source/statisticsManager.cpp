#include "statisticsManager.h"

#include <iostream>

#include "textInputSequentialFile.h"
#include "textDictionaryRecord.h"
#include "binaryDictionaryRecord.h"
#include "stringUtilities.h"
#include "externalSorter.h"


StatisticsManager::StatisticsManager() {
	this->loadStopWords();
	this->initializeIndexes();
}


//ObjetoDeSeba& StatisticsManager::getDictionary() {
//	return this->dictionary;
//}

//ObjetoDeLucas& StatisticsManager::getPhrases() {
//	return this->phrases;
//}

//ObjetoDeSeba& StatisticsManager::getNotFoundWords() {
//	return this->notFoundWords;
//}

std::set<std::string>& StatisticsManager::getStopWords() {
	return this->stopWords;
}

float StatisticsManager::getAverageWordsPerPhrase() const {
	return this->averageWordsPerPhrase;
}

void StatisticsManager::setAverageWordsPerPhrase(float averageWordsPerPhrase) {
	this->averageWordsPerPhrase = averageFailures;
}

float StatisticsManager::getAverageFailures() const {
	return this->averageFailures;
}

void StatisticsManager::setAverageFailures(float averageFailures) {
	this->averageFailures = averageWordsPerPhrase;
}



void StatisticsManager::loadStopWords() {
	//TODO Mariano. Crear un objeto registro de texto puro para estos casos usarlo donde corresponda.
	TextInputSequentialFile<TextDictionaryRecord<false> > stopWordsFile("stop-words.txt",10);
	TextDictionaryRecord<false> stopWord;

	while (!stopWordsFile.endOfFile()) {
		stopWord = stopWordsFile.getRecord();
		this->getStopWords().insert(stopWord.getWord());
	}
}

void StatisticsManager::initializeIndexes(std::string dictionaryFilePath) {
	//this->getDictionary().createIndex(dictionaryFilePath);
	this->createPhrases();
}

//ver de ponerle un nombre mejor
void StatisticsManager::createPhrases(std::string phrasesFilePath) {
	TextInputSequentialFile<TextDictionaryRecord<false> > phrasesFile(phrasesFilePath,10);
	std::string phrase;
	std::vector<std::string> phraseWords;
	unsigned int totalPhrases = 0;
	unsigned int totalWords = 0;
	unsigned int totalFailures = 0;
	ExternalSorter externalSorter(10,true);

	while (!phrasesFile.endOfFile()) {
		phrase = phrasesFile.getRecord().getWord();
		splitString(phrase,phraseWords,' ');
		totalPhrases++;
		for (unsigned int i = 0; i < phraseWords.size(); i++) {
			//chequeo que no sea stopWord.
			if(this->getStopWords().find(phraseWords[i]) != this->getStopWords().end()) {
				totalWords++;
				//si no está en el índice de fallos ni en el diccionario, se inserta en el índice de fallos y se
				//contabiliza.
				//if (!this->getNotFoundWords().find(phraseWords[i])) {
				//	if (!this->getDictionary().find(phraseWords[i])) {
				//		this->getNotFoundWords().insert(phraseWords[i]);
				//		totalFailures++;
				//	}
				//} else {
				//	totalFailures++;
				//}
			}
		}
		//this->getPhrases().insert(phrase);
	}

	//Se guardan las tasas pedidas.
	//TODO Chequear si son realmente las tasas pedidas.
	this->setAverageWordsPerPhrase(totalWords / totalPhrases);
	this->setAverageFailures(totalFailures / totalWords);

	//Se genera el ranking de palabras.
	//this->getDictionary().export("dictionary-export");
	//TODO ver que onda con el archivo de particiones. Dado que se Maxi dijo que se debe poder decirle si se
	//quiere que deje o no la carpeta de particiones, ahora crea una carpeta de particiones nueva cada vez.
	//Se podrían discutir posibilidades
	externalSorter.sort("dictionary-export",true);
}

void StatisticsManager::printAverageWordsPerPhrase() {
	//TODO Mariano. Usar constante para el texto.
	std::cout << "Cantidad de terminos promedio por frase: " << floatToString(this->getAverageWordsPerPhrase()) << std::endl;
}

void StatisticsManager::printAverageFailures() {
	//TODO Mariano. Usar constante para el texto.
	std::cout << "Tasa de fallos de terminos: " << floatToString(this->getAverageFailures()) << std::endl;
}

void StatisticsManager::printNotFoundWords() {
	//Acá hay que ver que funcionalidad expone "ObjetoDeSeba". No le veo sentido persistirlo en un archivo
	//secuencial para luego imprimirlo. Si se puede sería conveniente de la siguiente forma:
	BinaryDictionaryRecord<true> record;

	std::cout << "Terminos no encontrados: " << std::endl;
	//while (objetoDeSeba tenga siguiente) {
	//	registro = this->getDictionary().next();
		std::cout << record.getWord() << std::endl;
	//}
}

void StatisticsManager::printWordRanking(unsigned int rankingSize) {
	BinaryInputSequentialFile<BinaryDictionaryRecord<true> > wordRankingFile("dictionary-export",10);
	BinaryDictionaryRecord<true> record;

	std::cout << "Ranking de las " << intToString(rankingSize) << " palabras mas buscadas: " << std::endl;
	for (unsigned int i = 0; ( (i < rankingSize) && (!wordRankingFile.endOfFile()) ); i++) {
		record = wordRankingFile.getRecord();
		std::cout << intToString(i + 1) << ") " << record.getWord() << " - " << intToString(record.getId()) << " veces." << std::endl;
	}
}

void StatisticsManager::printHelp() {
	std::cout 	<< std::endl
				<< HELP_TITLE << std::endl
				<< HELP_TEXT_AVG_WORDS_PER_PHRASE << std::endl
				<< std::endl
				<< HELP_TEXT_AVG_FAILURES << std::endl
				<< std::endl
				<< HELP_TEXT_NOT_FOUND_WORDS << std::endl
				<< std::endl
				<< HELP_TEXT_WORD_RANKING << std::endl
				<<std::endl
				<< HELP_TEXT_LOAD_DICTIONARY << std::endl
				<< std::endl
				<< HELP_TEXT_LOAD_PHRASES << std::endl
				<< std::endl
				<< HELP_TEXT_CALLHELP << std::endl
				<< std::endl
				<< HELP_TEXT_EXIT <<std::endl
				<< std::endl;
}

bool StatisticsManager::isValidCommand(std::string& command, std::vector<std::string>& commandParams) {
	//TODO Mariano.
	return true;
}

void StatisticsManager::processCommand(std::string& command, std::vector<std::string>& commandParams) {
	if (this->isValidCommand(command,commandParams)) {
		if (command == COMMAND_PRINT_AVG_WORDS_PER_PHRASE) {
			this->printAverageWordsPerPhrase();
		}

		if (command == COMMAND_PRINT_AVG_FAILURES) {
			this->printAverageFailures();
		}

		if (command == COMMAND_PRINT_NOT_FOUND_WORDS) {
			this->printNotFoundWords();
		}

		if (command == COMMAND_PRINT_WORD_RANKING) {
			//TODO Mariano. cambiar el atoi por su equivalente de C++
			this->printWordRanking(atoi(commandParams[1].c_str()));
		}

		if (command == COMMAND_LOAD_DICTIONARY) {
			this->initializeIndexes(commandParams[1].c_str());
		}

		if (command == COMMAND_LOAD_PHRASES) {
			this->createPhrases(commandParams[1].c_str());
		}

		if (command == COMMAND_PRINT_HELP) {
			this->printHelp();
		}
	} else {
		std::cout << ERROR_TEXT_INVALID_COMMAND << command << std::endl;
	}
}

StatisticsManager::~StatisticsManager() {
}
