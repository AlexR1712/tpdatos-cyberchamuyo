#include "statisticsManager.h"

#include <iostream>

#include "textInputSequentialFile.h"
#include "textDictionaryRecord.h"
#include "binaryDictionaryRecord.h"
#include "stringUtilities.h"
#include "externalSorter.h"


StatisticsManager::StatisticsManager() {
	this->loadStatus();
	this->loadStopWords();
	//this->getDictionary().createIndex(this->getDictionaryFilePath());
	//this->getPhrases().createIndex(this->getPhrasesFilePath());
	if (this->getNumberOfWords() == 0)
		this->loadPhrases(true);
}

std::string StatisticsManager::getDictionaryFilePath() const {
	return dictionaryFilePath;
}

void StatisticsManager::setDictionaryFilePath(std::string dictionaryFilePath) {
	this->dictionaryFilePath = dictionaryFilePath;
}

std::string StatisticsManager::getPhrasesFilePath() const {
	return phrasesFilePath;
}

void StatisticsManager::setPhrasesFilePath(std::string phrasesFilePath) {
	this->phrasesFilePath = phrasesFilePath;
}

unsigned int StatisticsManager::getNumberOfWords() const {
	return this->numberOfWords;
}

void StatisticsManager::setNumberOfWords(unsigned int numberOfWords) {
	this->numberOfWords = numberOfWords;
}

unsigned int StatisticsManager::getNumberOfPhrases() const {
	return this->numberOfPhrases;
}

void StatisticsManager::setNumberOfPhrases(unsigned int numberOfPhrases) {
	this->numberOfPhrases = numberOfPhrases;
}

unsigned int StatisticsManager::getNumberOfFailures() const {
	return this->numberOfFailures;
}

void StatisticsManager::setNumberOfFailures(unsigned int numberOfFailures) {
	this->numberOfFailures = numberOfFailures;
}

std::set<std::string>& StatisticsManager::getStopWords() {
	return this->stopWords;
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

void StatisticsManager::loadStatus() {
	TextInputSequentialFile<TextDictionaryRecord<false> > statusFile("statisticsManager.properties",10);

	this->setDictionaryFilePath(statusFile.getRecord().getWord());
	this->setPhrasesFilePath(statusFile.getRecord().getWord());
	this->setNumberOfWords(atoi(statusFile.getRecord().getWord().c_str()));
	this->setNumberOfPhrases(atoi(statusFile.getRecord().getWord().c_str()));
	this->setNumberOfFailures(atoi(statusFile.getRecord().getWord().c_str()));
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

void StatisticsManager::loadPhrases(bool insertInHash) {
	TextInputSequentialFile<TextDictionaryRecord<false> > phrasesFile(this->getPhrasesFilePath(),10);
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
		if (insertInHash) {
			//this->getPhrases().insert(phrase);
		}
	}

	//Se guardan las estadísticas.
	this->setNumberOfWords(totalWords);
	this->setNumberOfPhrases(totalPhrases);
	this->setNumberOfFailures(totalFailures);

	//Se genera el ranking de palabras.
	//this->getDictionary().export("dictionary-export");
	externalSorter.sort("dictionary-export",true);
}

void StatisticsManager::clearStatistics() {
	this->setNumberOfWords(0);
	this->setNumberOfPhrases(0);
	this->setNumberOfFailures(0);
}

void StatisticsManager::printAverageWordsPerPhrase() {
	//TODO Mariano. Usar constante para el texto.
	std::cout << "Cantidad de terminos promedio por frase: "
			  << floatToString(this->getNumberOfWords() / this->getNumberOfPhrases())
			  << std::endl;
}

void StatisticsManager::printAverageFailures() {
	//TODO Mariano. Usar constante para el texto.
	std::cout << "Tasa de fallos de terminos: "
			  << floatToString(this->getNumberOfFailures() / this->getNumberOfWords())
			  << std::endl;
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

bool StatisticsManager::isValidCommand(std::string& command, std::vector<std::string>& commandParams) {
	//TODO Mariano.
	return true;
}

void StatisticsManager::saveStatus() {
	TextOutputSequentialFile<TextDictionaryRecord<false> > statusFile("statisticsManager.properties",10);
	TextDictionaryRecord<false> statusRecord;

	statusRecord.setWord(this->getDictionaryFilePath());
	statusFile.putRecord(statusRecord);
	statusRecord.setWord(this->getPhrasesFilePath());
	statusFile.putRecord(statusRecord);
	statusRecord.setWord(intToString(this->getNumberOfWords()));
	statusFile.putRecord(statusRecord);
	statusRecord.setWord(intToString(this->getNumberOfPhrases()));
	statusFile.putRecord(statusRecord);
	statusRecord.setWord(intToString(this->getNumberOfFailures()));
	statusFile.putRecord(statusRecord);
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
			//this->getDictionary().clear();
			this->clearStatistics();
			this->setDictionaryFilePath(commandParams[1]);
			//this->getDictionary().createIndex(this->getDictionaryFilePath());
			this->loadPhrases(false);
		}

		if (command == COMMAND_LOAD_PHRASES) {
			//this->getPhrases().clear();
			clearStatistics();
			this->setPhrasesFilePath(commandParams[1]);
			//this->getPhrases().createIndex(this->getPhrasesFilePath());
			this->loadPhrases(true);
		}

		if (command == COMMAND_PRINT_HELP) {
			this->printHelp();
		}
	} else {
		std::cout << ERROR_TEXT_INVALID_COMMAND << command << std::endl;
	}
}

StatisticsManager::~StatisticsManager() {
	this->saveStatus();
}
