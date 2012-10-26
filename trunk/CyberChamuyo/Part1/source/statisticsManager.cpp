#include "../include/statisticsManager.h"

#include <iostream>

#include "../include/textInputSequentialFile.h"
#include "../include/textOutputSequentialFile.h"
#include "../include/binaryInputSequentialFile.h"
#include "../include/binaryDictionaryRecord.h"
#include "../include/textRecord.h"
#include "../include/externalSorter.h"
#include "../include/dictionaryNormalizer.h"
#include "../include/dictionaryRandomizer.h"
#include "../include/stringUtilities.h"

StatisticsManager::StatisticsManager() {
	this->loadStatus();
	this->loadStopWords();
	this->createDictionary(false);
	this->getDictionary().createIndex("outputFiles/dictionary_RANDOMIZED_ORDERED");
	//this->getMemorableQuotes().createIndex(this->getMemorableQuotesFilePath());
	if (this->getNumberOfWords() == 0)
		this->loadMemorableQuotes(true);
}

std::string StatisticsManager::getDictionaryFilePath() const {
	return dictionaryFilePath;
}

void StatisticsManager::setDictionaryFilePath(std::string dictionaryFilePath) {
	this->dictionaryFilePath = dictionaryFilePath;
}

std::string StatisticsManager::getMemorableQuotesFilePath() const {
	return memorableQuotesFilePath;
}

void StatisticsManager::setMemorableQuotesFilePath(std::string memorableQuotesFilePath) {
	this->memorableQuotesFilePath = memorableQuotesFilePath;
}

unsigned int StatisticsManager::getNumberOfWords() const {
	return this->numberOfWords;
}

void StatisticsManager::setNumberOfWords(unsigned int numberOfWords) {
	this->numberOfWords = numberOfWords;
}

unsigned int StatisticsManager::getNumberOfQuotes() const {
	return this->numberOfQuotes;
}

void StatisticsManager::setNumberOfQuotes(unsigned int numberOfQuotes) {
	this->numberOfQuotes = numberOfQuotes;
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

IndiceArbol& StatisticsManager::getDictionary() {
	return this->dictionary;
}

//ObjetoDeLucas& StatisticsManager::getMemorableQuotes() {
//	return this->memorableQuotes;
//}

IndiceArbol& StatisticsManager::getNotFoundWords() {
	return this->notFoundWords;
}

void StatisticsManager::loadStatus() {
	TextInputSequentialFile<TextRecord> statusFile(STATUS_FILE_PATH,FILES_BUFFER_SIZE);

	this->setDictionaryFilePath(statusFile.getRecord().getData());
	this->setMemorableQuotesFilePath(statusFile.getRecord().getData());
	this->setNumberOfWords(StringUtilities::StringToInt(statusFile.getRecord().getData()));
	this->setNumberOfQuotes(StringUtilities::StringToInt(statusFile.getRecord().getData()));
	this->setNumberOfFailures(StringUtilities::StringToInt(statusFile.getRecord().getData()));

}

void StatisticsManager::loadStopWords() {
	TextInputSequentialFile<TextRecord> stopWordsFile(STOP_WORDS_FILE_PATH,FILES_BUFFER_SIZE);
	TextRecord stopWord;

	while (!stopWordsFile.endOfFile()) {
		stopWord = stopWordsFile.getRecord();
		this->getStopWords().insert(stopWord.getData());
	}
}

void StatisticsManager::createDictionary(bool force) {
	BinaryInputSequentialFile<BinaryDictionaryRecord<true> > dictionaryFile("outputFiles/dictionary_RANDOMIZED_ORDERED");
	if (dictionaryFile.fail() || force) {
		DictionaryNormalizer dictionaryNormalizer;
		DictionayRandomizer dictionayRandomizer;

		dictionaryNormalizer.normalize(this->getDictionaryFilePath());
		dictionayRandomizer.randomizeDictionary("outputFiles/dictionary_NORMALIZED.txt",false);
	}
}

void StatisticsManager::loadMemorableQuotes(bool insertInHash) {
	TextInputSequentialFile<TextRecord> memorableQuotesFile(this->getMemorableQuotesFilePath(),FILES_BUFFER_SIZE);
	std::string phrase;
	std::vector<std::string> phraseWords;
	unsigned int totalQuotes = 0;
	unsigned int totalWords = 0;
	unsigned int totalFailures = 0;
	ExternalSorter externalSorter(FILES_BUFFER_SIZE,true);

	while (!memorableQuotesFile.endOfFile()) {
		phrase = memorableQuotesFile.getRecord().getData();
		//separo el autor de la frase
		StringUtilities::splitString(phrase,phraseWords,AUTHOR_QUOTE_SEPARATOR);
		//separo la frase en palabras
		StringUtilities::splitString(phraseWords[phraseWords.size() - 1],phraseWords,QUOTES_WORDS_SEPARATOR);
		totalQuotes++;
		for (unsigned int i = 0; i < phraseWords.size(); i++) {
			//chequeo que no sea stopWord.
			if(this->getStopWords().find(phraseWords[i]) != this->getStopWords().end()) {
				totalWords++;
				//si no est� en el �ndice de fallos ni en el diccionario, se inserta en el �ndice de fallos y se
				//contabiliza.
				if (this->getNotFoundWords().find(phraseWords[i])) {
					totalFailures++;
				} else {
					if (!this->getDictionary().find(phraseWords[i])) {
						this->getNotFoundWords().insert(phraseWords[i]);
						totalFailures++;
					}
				}
			}
		}
		if (insertInHash) {
			//this->getMemorableQuotes().insert(phrase);
		}
	}

	//Se guardan las estad�sticas.
	this->setNumberOfWords(totalWords);
	this->setNumberOfQuotes(totalQuotes);
	this->setNumberOfFailures(totalFailures);

	//Se genera el ranking de palabras.
	this->getDictionary().exportar(RANKINGS_FILE_PATH);
	externalSorter.sort(RANKINGS_FILE_PATH,RANKINGS_FILE_PATH_ORDERED,true);
}

void StatisticsManager::clearStatistics() {
	this->setNumberOfWords(0);
	this->setNumberOfQuotes(0);
	this->setNumberOfFailures(0);
}

void StatisticsManager::printAverageWordsPerPhrase() {
	std::cout << TEXT_AVG_WORDS_PER_QUOTE
			  << StringUtilities::floatToString(this->getNumberOfWords() / this->getNumberOfQuotes())
			  << std::endl;
}

void StatisticsManager::printAverageFailures() {
	std::cout << TEXT_AVG_FAILURES
			  << StringUtilities::floatToString(this->getNumberOfFailures() / this->getNumberOfWords())
			  << std::endl;
}

void StatisticsManager::printNotFoundWords() {
	BinaryDictionaryRecord<true> record;

	std::cout << TEXT_NOT_FOUND_WORDS << std::endl;
	while (getDictionary().hasNext()) {
		record = this->getDictionary().next();
		std::cout << record.getWord() << std::endl;
	}
}

void StatisticsManager::printWordRanking(unsigned int rankingSize) {
	BinaryInputSequentialFile<BinaryDictionaryRecord<true> > wordRankingFile(RANKINGS_FILE_PATH_ORDERED,FILES_BUFFER_SIZE);
	BinaryDictionaryRecord<true> record;

	if (rankingSize > 0) {
		std::cout << TEXT_MOST_SEARCHED_WORDS_TITLE(StringUtilities::intToString(rankingSize)) << std::endl;
		for (unsigned int i = 0; ( (i < rankingSize) && (!wordRankingFile.endOfFile()) ); i++) {
			record = wordRankingFile.getRecord();
			std::cout << TEXT_MOST_SEARCHED_WORDS_ITEM(StringUtilities::intToString(i + 1),record.getWord(),StringUtilities::intToString(record.getId())) << std::endl;
		}
	} else {
		std::cout << ERROR_TEXT_INVALID_RANKING_SIZE << std::endl;
	}
}

bool StatisticsManager::isValidCommand(std::string& command, std::vector<std::string>& commandParams) {
	if ( ((command != COMMAND_PRINT_AVG_WORDS_PER_QUOTE) &&
		  (command != COMMAND_PRINT_AVG_FAILURES) &&
		  (command != COMMAND_PRINT_NOT_FOUND_WORDS) &&
		  (command != COMMAND_PRINT_WORD_RANKING) &&
		  (command != COMMAND_LOAD_DICTIONARY) &&
		  (command != COMMAND_LOAD_MEMORABLE_QUOTES) &&
		  (command != COMMAND_PRINT_HELP)) ||
		 (((command == COMMAND_PRINT_WORD_RANKING) ||
		   (command == COMMAND_LOAD_DICTIONARY) ||
		   (command == COMMAND_LOAD_MEMORABLE_QUOTES)) &&
		  (commandParams.size() != 1))  ) {
		return false;
	}

	return true;
}

void StatisticsManager::saveStatus() {
	TextOutputSequentialFile<TextRecord> statusFile(STATUS_FILE_PATH,FILES_BUFFER_SIZE);
	TextRecord statusRecord;

	statusRecord.setData(this->getDictionaryFilePath());
	statusFile.putRecord(statusRecord);
	statusRecord.setData(this->getMemorableQuotesFilePath());
	statusFile.putRecord(statusRecord);
	statusRecord.setData(StringUtilities::intToString(this->getNumberOfWords()));
	statusFile.putRecord(statusRecord);
	statusRecord.setData(StringUtilities::intToString(this->getNumberOfQuotes()));
	statusFile.putRecord(statusRecord);
	statusRecord.setData(StringUtilities::intToString(this->getNumberOfFailures()));
	statusFile.putRecord(statusRecord);
}

void StatisticsManager::printHelp() {
	std::cout 	<< std::endl
				<< HELP_TITLE << std::endl
				<< HELP_TEXT_AVG_WORDS_PER_QUOTE << std::endl
				<< std::endl
				<< HELP_TEXT_AVG_FAILURES << std::endl
				<< std::endl
				<< HELP_TEXT_NOT_FOUND_WORDS << std::endl
				<< std::endl
				<< HELP_TEXT_WORD_RANKING << std::endl
				<< std::endl
				<< HELP_TEXT_LOAD_DICTIONARY << std::endl
				<< std::endl
				<< HELP_TEXT_LOAD_MEMORABLE_QUOTES << std::endl
				<< std::endl
				<< HELP_TEXT_CALLHELP << std::endl
				<< std::endl
				<< HELP_TEXT_EXIT <<std::endl
				<< std::endl;
}

void StatisticsManager::processCommand(std::string& command, std::vector<std::string>& commandParams) {
	if (this->isValidCommand(command,commandParams)) {
		if (command == COMMAND_PRINT_AVG_WORDS_PER_QUOTE) {
			this->printAverageWordsPerPhrase();
		}

		if (command == COMMAND_PRINT_AVG_FAILURES) {
			this->printAverageFailures();
		}

		if (command == COMMAND_PRINT_NOT_FOUND_WORDS) {
			this->printNotFoundWords();
		}

		if (command == COMMAND_PRINT_WORD_RANKING) {
			if (commandParams.size() == 1) {
				this->printWordRanking(StringUtilities::StringToInt(commandParams[0]));
			}
		}

		if (command == COMMAND_LOAD_DICTIONARY) {
			this->getDictionary().clear();
			this->clearStatistics();
			this->setDictionaryFilePath(commandParams[0]);
			this->createDictionary(true);
			this->getDictionary().createIndex("outputFiles/dictionary_RANDOMIZED_ORDERED");
			this->loadMemorableQuotes(false);
		}

		if (command == COMMAND_LOAD_MEMORABLE_QUOTES) {
			//this->getMemorableQuotes().clear();
			clearStatistics();
			this->setMemorableQuotesFilePath(commandParams[0]);
			this->loadMemorableQuotes(true);
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
