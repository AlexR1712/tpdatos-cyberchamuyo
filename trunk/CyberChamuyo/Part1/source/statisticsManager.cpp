#include "../include/statisticsManager.h"
#include "../include/propertiesLoader.h"
#include "../include/binaryDictionaryRecord.h"
#include "../include/textRecord.h"
#include "../include/externalSorter.h"
#include "../include/wordNormalizer.h"
#include "../include/dictionaryNormalizer.h"
#include "../include/dictionaryRandomizer.h"
#include "../include/stringUtilities.h"
#include "../include/DispersionEx.h"
#include "../include/fileUtilities.h"
#include "../include/outputTexts.h"
#include "../include/FixedLengthTRecord.h"
#include "../include/fixedLengthRecordSequentialFile.h"
#include "../include/textFile.h"
#include "../include/wordRankingRecord.h"
#include <time.h>

std::list<unsigned int> lAnd(std::vector<std::list<unsigned int> > searchResultLists) {
	int unsigned max = 100000000;
	for(unsigned int i = 0; i < searchResultLists.size(); ++i) {
		searchResultLists[i].push_back(max);
	}
	std::list<unsigned int>::iterator current_it = searchResultLists[0].begin();
	std::list<unsigned int> current_list = searchResultLists[0];
	std::list<unsigned int>::iterator next_it;
	std::list<unsigned int> totalRes;
	for(unsigned int i = 1; i < searchResultLists.size(); ++i) {
		std::list<unsigned int> res;
		next_it = searchResultLists[i].begin();
		std::list<unsigned int> next_list = searchResultLists[i];
		while(*current_it != max && *next_it != max) {
			if(*current_it == *next_it) {
				res.push_back(*current_it);
				current_it++;
				next_it++;
			} else {
				if(*current_it > *next_it)
					++next_it;
				else {
					++current_it;
				}
			}
		}
		current_list = res;
		current_it = current_list.begin();
		totalRes = res;
	}
	return totalRes;
}


StatisticsManager::StatisticsManager() {
	if (this->checkDirectoryStructure()) {
		PropertiesLoader propertiesLoader(CONFIG_FILE_PATH);

		this->successfullInit = true;
		this->stopWordsFilePath = propertiesLoader.getPropertyValue(STOP_WORDS_FILE_PATH_PROPERTY_NAME);
		this->dictionary = new IndiceArbol(DICTIONARY_INDEX_FILE_PATH);
		this->notFoundWords = new IndiceArbol(NOT_FOUND_WORDS_INDEX_FILE_PATH);
		this->memorableQuotes = new Hash::DispersionEx(MEMORABLE_QUOTES_INDEX_FILE_PATH);
		this->T = new FixedLengthRecordSequentialFile<FixedLengthTRecord>(T_RECORD_SIZE);
		this->booleanIndex = new BooleanIndex();
		//this->numberOfErasedQuotes = 0;
		this->numberOfFailures = 0;
		this->numberOfQuotes = 0;
		this->numberOfWords = 0;
		this->sigPortionIndex = new SignaturePortionIndex;
		this->loadStatus();
		this->loadStopWords();
	} else {
		successfullInit = false;
	}
}

std::string StatisticsManager::getInputDictionaryFilePath() const {
	return this->inputDictionaryFilePath;
}

void StatisticsManager::setInputDictionaryFilePath(std::string inputDictionaryFilePath) {
	this->inputDictionaryFilePath = inputDictionaryFilePath;
}

std::string StatisticsManager::getInputMemorableQuotesFilePath() const {
	return this->inputMemorableQuotesFilePath;
}

void StatisticsManager::setInputMemorableQuotesFilePath(std::string inputMemorableQuotesFilePath) {
	this->inputMemorableQuotesFilePath = inputMemorableQuotesFilePath;
}

std::string StatisticsManager::getStopWordsFilePath() const {
	return this->stopWordsFilePath;
}

void StatisticsManager::setStopWordsFilePath(std::string stopWordsFilePath) {
	this->stopWordsFilePath = stopWordsFilePath;
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

IndiceArbol* StatisticsManager::getDictionary() {
	return this->dictionary;
}

Hash::DispersionEx* StatisticsManager::getMemorableQuotes() {
	return this->memorableQuotes;
}

IndiceArbol* StatisticsManager::getNotFoundWords() {
	return this->notFoundWords;
}

//bool StatisticsManager::isFirstRun() const {
//	return this->firstRun;
//}
//
//void StatisticsManager::setFirstRun(bool firstRun) {
//	this->firstRun = firstRun;
//}

bool StatisticsManager::isSuccessfullInit() const	{
    return this->successfullInit;
}

BooleanIndex* StatisticsManager::getBooleanIndex() const {
	return this->booleanIndex;
}

FixedLengthRecordSequentialFile<FixedLengthTRecord>* StatisticsManager::getT() const {
	return this->T;
}

//void StatisticsManager::setSuccessfullInit(bool successfullInit) {
//    this->successfullInit = successfullInit;
//}

void StatisticsManager::loadStatus() {
	TextFile<TextRecord> statusFile;
	std::string errorMessage;

	statusFile.open(STATUS_FILE_PATH);
	if (statusFile.isFileExists()) {
		this->setInputDictionaryFilePath(statusFile.getNextRecord().getData());
		this->setInputMemorableQuotesFilePath(statusFile.getNextRecord().getData());

		if ( (this->getInputDictionaryFilePath() != "") && (this->getDictionary()->isEmpty()) )
			errorMessage = errorMessage + ERROR_FILE_NOT_FOUND + DICTIONARY_INDEX_FILE_PATH + "\n";

		if ( (this->getInputMemorableQuotesFilePath() != "") && (this->getMemorableQuotes()->isEmpty()) )
			errorMessage = errorMessage + ERROR_FILE_NOT_FOUND + MEMORABLE_QUOTES_INDEX_FILE_PATH + "\n";

		if ( (this->getInputMemorableQuotesFilePath() != "") && (this->getNotFoundWords()->isEmpty()) )
			errorMessage = errorMessage + ERROR_FILE_NOT_FOUND + NOT_FOUND_WORDS_INDEX_FILE_PATH + "\n";

		if (errorMessage == "") {
			this->setNumberOfWords(StringUtilities::stringToInt(statusFile.getNextRecord().getData()));
			this->setNumberOfQuotes(StringUtilities::stringToInt(statusFile.getNextRecord().getData()));
			this->setNumberOfFailures(StringUtilities::stringToInt(statusFile.getNextRecord().getData()));
			this->getT()->open(T_FILE_PATH);
//			this->setFirstRun(false);
		} else {
//			this->setFirstRun(true);
			this->setInputDictionaryFilePath("");
			this->setInputMemorableQuotesFilePath("");
			this->getT()->open(T_FILE_PATH,true);
			std::cout << ERROR_STATUS_RETRIEVAL_FAILURE << std::endl
					  << errorMessage << std::endl;
		}
	}
//	else
//		this->setFirstRun(true);
}

void StatisticsManager::loadStopWords() {
	TextFile<TextRecord> stopWordsFile;

	stopWordsFile.open(this->getStopWordsFilePath());
	if (stopWordsFile.isFileExists()) {
		while (!stopWordsFile.endOfFile()) {
			this->getStopWords().insert(stopWordsFile.getNextRecord().getData());
		}
	} else {
		std::cout << ERROR_FILE_NOT_FOUND << this->getStopWordsFilePath() << std::endl;
	}
}

void StatisticsManager::createDictionary() {
	VariableLengthRecordSequentialFile<TextRecord> inputDictionaryFile;

	inputDictionaryFile.open(this->getInputDictionaryFilePath());
	if (inputDictionaryFile.isFileExists()) {
		DictionaryNormalizer dictionaryNormalizer;
		DictionaryRandomizer dictionaryRandomizer;

		inputDictionaryFile.close();
		dictionaryNormalizer.normalize(this->getInputDictionaryFilePath());
		dictionaryRandomizer.randomizeDictionary(dictionaryNormalizer.getOutputFilePath(),false);

		if(this->getDictionary()->isEmpty()) {
			T->open(T_FILE_PATH,true);
			this->getDictionary()->createIndex(dictionaryRandomizer.getOrderedRandomizedDictionaryFilePath(), T);
			T->close();
		}
	} else {
		std::cout << ERROR_FILE_NOT_FOUND << this->getInputDictionaryFilePath() << std::endl;
	}
}

void StatisticsManager::loadMemorableQuotes() {
	TextFile<TextRecord> memorableQuotesFile;
	std::string phrase;
	WordNormalizer normalizer;
	std::vector<std::string> phraseWords;
	unsigned int totalQuotes = 0;
	unsigned int totalWords = 0;
	unsigned int totalFailures = 0;
	ExternalSorter<VariableLengthRecordSequentialFile<WordRankingRecord>,WordRankingRecord > externalSorter(10,true);

	memorableQuotesFile.open(this->getInputMemorableQuotesFilePath());
	if (memorableQuotesFile.isFileExists()) {
		////////////////// TEMPORAL /////////////////////
		this->getT()->open(T_FILE_PATH);
		VariableLengthRecordSequentialFile<OcurrenceFileRecord> ocurrenceFile;
		//ocurrenceFilePath = OCURRENCE_FILE_PATH;
		ocurrenceFile.open(OCURRENCE_FILE_PATH,true);
		///////////
		this->getDictionary()->rewind();
		while (!memorableQuotesFile.endOfFile()) {
			//std::vector<std::string> terminosYaInsertados;
			phrase = memorableQuotesFile.getNextRecord().getData();
			//separo el autor de la frase
			StringUtilities::splitString(phrase,phraseWords,AUTHOR_QUOTE_SEPARATOR);
			//separo la frase en palabras
			StringUtilities::splitString(phraseWords[phraseWords.size() - 1],phraseWords,QUOTES_WORDS_SEPARATOR);
			totalQuotes++;
			for (unsigned int i = 0; i < phraseWords.size(); i++) {
				//chequeo que no sea stopWord.
//				bool enc = false;
				unsigned int termId = 1;
				phraseWords[i] = normalizer.normalizeWord(phraseWords[i]);
				if( (this->getStopWords().find(phraseWords[i]) == this->getStopWords().end()) && (phraseWords[i].size() > 0) ) {
					totalWords++;
					if (this->getNotFoundWords()->find(phraseWords[i])) {
						totalFailures++;
					}
					if (!this->getDictionary()->find(phraseWords[i])) {
						termId = this->getT()->getLastRecordPosition() + 1;
						this->getNotFoundWords()->insert(phraseWords[i]);
						totalFailures++;
						this->getDictionary()->insert(termId,phraseWords[i], 0);
						FixedLengthTRecord tRecord(T_RECORD_SIZE);
						tRecord.setTerm(phraseWords[i]);
						tRecord.setId(termId);
						this->getT()->putRecord(tRecord);
					} else {
						RegistroArbol reg;
						reg = this->getDictionary()->textSearch(phraseWords[i]);
						termId = reg.getTermId();
					}
//					for(unsigned int j = 0; j < terminosYaInsertados.size(); ++j) {
//						if(phraseWords[i] == terminosYaInsertados[j])
//							enc = true;
//					}
				///////////////////// TEMPORAL ////////////////
//					if(!enc) {
//						terminosYaInsertados.push_back(phraseWords[i]);
						OcurrenceFileRecord ocurrenceRecord;
						ocurrenceRecord.setTermId(termId);
						ocurrenceRecord.setDocId(totalQuotes);
						ocurrenceFile.putRecord(ocurrenceRecord);
						///////////////////////////////////////////////
//					}
				}
			}

			this->getMemorableQuotes()->insert(phrase);
		}

		//Se guardan las estadísticas.
		this->setNumberOfWords(totalWords);
		this->setNumberOfQuotes(totalQuotes);
		this->setNumberOfFailures(totalFailures);
		T->close();
		ocurrenceFile.close();
		//Se genera el ranking de palabras.
		this->getDictionary()->exportar(RANKINGS_FILE_PATH);
		externalSorter.sort(RANKINGS_FILE_PATH,RANKINGS_FILE_PATH_ORDERED,true);
	} else {
		std::cout << ERROR_FILE_NOT_FOUND << this->getInputMemorableQuotesFilePath() << std::endl;
	}
}

void StatisticsManager::clearStatistics() {
	this->setNumberOfWords(0);
	this->setNumberOfQuotes(0);
	this->setNumberOfFailures(0);
}

void StatisticsManager::printAverageWordsPerPhrase() {
	float result;

	if (this->getNumberOfQuotes() != 0)
		result = static_cast<float>(this->getNumberOfWords()) / this->getNumberOfQuotes();
	else
		result = this->getNumberOfWords();

	std::cout << TEXT_AVG_WORDS_PER_QUOTE
			  << StringUtilities::floatToString(result)
			  << std::endl;
}

void StatisticsManager::printAverageFailures() {
	float result;

	if (this->getNumberOfWords() != 0)
		result = static_cast<float>(this->getNumberOfFailures()) / this->getNumberOfWords();
	else
		result = this->getNumberOfFailures();

	std::cout << TEXT_AVG_FAILURES
			  << StringUtilities::floatToString(result)
			  << std::endl;
}

void StatisticsManager::printNotFoundWords() {
	BinaryDictionaryRecord<true> record;

	std::cout << TEXT_NOT_FOUND_WORDS << std::endl;
	if (!this->getNotFoundWords()->isEmpty()) {
		this->getNotFoundWords()->rewind();
		while (getNotFoundWords()->hasNext()) {
			record = this->getNotFoundWords()->next();
			std::cout << record.getWord() << std::endl;
		}
	} else
		std::cout << TEXT_NO_NOT_FOUND_WORDS << std::endl;
}

void StatisticsManager::printWordRanking(unsigned int rankingSize) {
	VariableLengthRecordSequentialFile<WordRankingRecord> wordRankingFile;
	WordRankingRecord record;
	unsigned int i = 0;

	if (rankingSize > 0) {
		wordRankingFile.open(RANKINGS_FILE_PATH_ORDERED);
		if (wordRankingFile.isFileExists()) {
			std::cout << TEXT_MOST_SEARCHED_WORDS_TITLE(StringUtilities::intToString(rankingSize)) << std::endl;
			while(!wordRankingFile.endOfFile() && i < rankingSize) {
				i++;
				record = wordRankingFile.getNextRecord();
				std::cout << TEXT_MOST_SEARCHED_WORDS_ITEM(StringUtilities::intToString(i),record.getWord(),StringUtilities::intToString(record.getNumberOfSearches())) << std::endl;
			}
		} else {
			std::cout << ERROR_RETRIEVING_WORD_RANKING << std::endl;
		}
	} else {
		std::cout << ERROR_TEXT_INVALID_RANKING_SIZE << std::endl;
	}
}


void StatisticsManager::index() {
	ExternalSorter<VariableLengthRecordSequentialFile<OcurrenceFileRecord>,OcurrenceFileRecord> sorter(5,false);
	VariableLengthRecordSequentialFile<OcurrenceFileRecord> ocurrenceFileOrdered;
	OcurrenceFileRecord ocurrenceRecord;
	unsigned int idTermino = 0;
	unsigned int idListaInvertida = 0;

	//sorter.sort(OCURRENCE_FILE_PATH,OCURRENCE_FILE_PATH_ORDERED,false);
	//ocurrenceFileOrdered.open(OCURRENCE_FILE_PATH_ORDERED);

	//asumo que el ID de la lista invertida es incremental.
	if (ocurrenceFileOrdered.isFileExists()) {
		while(!ocurrenceFileOrdered.endOfFile()) {
			ocurrenceRecord = ocurrenceFileOrdered.getNextRecord();
			if (idTermino != ocurrenceRecord.getTermId()) {
				idTermino = ocurrenceRecord.getTermId();
				//idListaInvertida = cosaQueHaceListasInvertidas.create(idTermino);
				this->getDictionary()->insert(ocurrenceRecord.getTermId(),this->getT()->getRecord(ocurrenceRecord.getTermId()).getTerm(),idListaInvertida);
				//cosaQueHacePorcionesDeFirmas.create(idTermino);
			}
			//cosaQueHaceListasInvertidas.add(idListaInvertida,idTermino,ocurrenceRecord.getDocId());
			//cosaQueHacePorcionesDeFirmas.add(idTermino,ocurrenceRecord.getDocId());
		}
	} else {
		//TODO este error debe estar en el open del archivo.
		std::cout << ERROR_FILE_NOT_FOUND << std::endl;
	}

}

void StatisticsManager::erasePhrase(unsigned int idPhrase) {
	WordNormalizer wordNormalizer;
	std::vector<std::string> phraseWords;
	std::string phrase;

	this->getMemorableQuotes()->getFrase(idPhrase,phrase);
	//StringUtilities::splitString(phrase,phraseWords,AUTHOR_QUOTE_SEPARATOR);
	StringUtilities::splitString(phrase,phraseWords,QUOTES_WORDS_SEPARATOR);
	unsigned int size = phraseWords.size();
	for (unsigned int i = 0; i < size; i++) {
		phraseWords[i] = wordNormalizer.normalizeWord(phraseWords[i]);
		if ( (this->getStopWords().find(phraseWords[i]) == this->getStopWords().end()) /* && !(this->getNotFoundWords()->find(phraseWords[i]))*/ ) {
			if (/*booleanIndex->creado()*/true)
				this->getBooleanIndex()->eraseTermInDoc(phraseWords[i], idPhrase, this->getDictionary());
			this->setNumberOfWords(this->getNumberOfWords() - 1);
		}
	}
	this->setNumberOfQuotes(this->getNumberOfQuotes() - 1);
	this->getMemorableQuotes()->borrarRegistro(idPhrase);
//	this->numberOfErasedQuotes++;
}

void StatisticsManager::addPhrase(std::string phrase) {
	WordNormalizer wordNormalizer;
	std::vector<std::string> phraseWords;
	unsigned int listId = 0;

	StringUtilities::splitString(phrase,phraseWords,QUOTES_WORDS_SEPARATOR);
	this->setNumberOfQuotes(this->getNumberOfQuotes() + 1);
	this->getT()->open(T_FILE_PATH, false);
	for (unsigned int i = 0; i < phraseWords.size(); i++) {
		phraseWords[i] = wordNormalizer.normalizeWord(phraseWords[i]);
		if( (this->getStopWords().find(phraseWords[i]) == this->getStopWords().end()) && (phraseWords[i].size() > 0) ) {
			this->setNumberOfWords(this->getNumberOfWords() + 1);
			if (this->getNotFoundWords()->find(phraseWords[i]))
				this->setNumberOfFailures(this->getNumberOfFailures() + 1);
			unsigned int termId = 0;
//			unsigned int docId = this->getNumberOfQuotes() + this->numberOfErasedQuotes;
//			this->getMemorableQuotes()->getLastId();
			if (!this->getDictionary()->find(phraseWords[i])) {
				termId = this->getT()->getLastRecordPosition() + 1;
				///////// Especifico indice Booleano //////////
				if (this->getBooleanIndex()->isLoaded()) {
					//listId = this->booleanIndex->addTerm(phraseWords[i],this->getNumberOfQuotes() + this->numberOfErasedQuotes);
					listId = this->getBooleanIndex()->addTerm(phraseWords[i],this->getMemorableQuotes()->getLastId() + 1);
					///////////////////////////////////////////////
				}
				this->getDictionary()->insert(termId, phraseWords[i], listId);
				//cosaQueHacePorcionesDeFirmas.add(idTermino,ocurrenceRecord.getDocId());
				FixedLengthTRecord tRecord(T_RECORD_SIZE);
				tRecord.setTerm(phraseWords[i]);
				tRecord.setId(termId);
				this->getT()->putRecord(tRecord);
			} else {
				if (this->getBooleanIndex()->isLoaded())
					//this->booleanIndex->addDocToTerm(phraseWords[i],this->getNumberOfQuotes() + this->numberOfErasedQuotes,this->getDictionary());
					this->getBooleanIndex()->addDocToTerm(phraseWords[i],this->getMemorableQuotes()->getLastId() + 1,this->getDictionary());
			}
		}
	}

	for (unsigned int i = 0; i < 2; i++) {
		phrase = AUTHOR_QUOTE_SEPARATOR + phrase;
	}
	this->getMemorableQuotes()->insert(phrase);
}

bool StatisticsManager::isValidCommand(std::string& command, std::vector<std::string>& commandParams) {
	if ( ((command != COMMAND_PRINT_AVG_WORDS_PER_QUOTE) &&
		  (command != COMMAND_PRINT_AVG_FAILURES) &&
		  (command != COMMAND_PRINT_NOT_FOUND_WORDS) &&
		  (command != COMMAND_PRINT_WORD_RANKING) &&
		  (command != COMMAND_LOAD_DICTIONARY) &&
		  (command != COMMAND_LOAD_INDEXES) &&
		  (command != COMMAND_LOAD_MEMORABLE_QUOTES) &&
		  (command != COMMAND_BOOLEAN_SEARCH) &&
		  (command != COMMAND_SIGNATURE_SEARCH) &&
		  (command != COMMAND_INDEX_BY_BOOLEAN) &&
		  (command != COMMAND_INDEX_BY_SIGNATURE) &&
		  (command != COMMAND_ADD_PHRASE) &&
		  (command != COMMAND_MODIFY_PHRASE) &&
		  (command != COMMAND_ERASE_PHRASE) &&
		  (command != COMMAND_PRINT_HELP)) ||
		 (((command == COMMAND_PRINT_WORD_RANKING) ||
		   (command == COMMAND_LOAD_DICTIONARY) ||
		   (command == COMMAND_ERASE_PHRASE) ||
		   (command == COMMAND_ADD_PHRASE) ||
		   (command == COMMAND_BOOLEAN_SEARCH) ||
		   (command == COMMAND_LOAD_MEMORABLE_QUOTES)) &&
		  (commandParams.size() != 1)) ||
		 ((command == COMMAND_MODIFY_PHRASE) &&
		   (commandParams.size() != 2))  ) {
		return false;
		//	TODO agregar condicion para que COMMAND_BOOLEAN_SEARCH requiera 1 o mas params
		//	y COMMAND_MODIFY_PHRASE requiera 2 o mas parametros
	}

	return true;
}

void StatisticsManager::saveStatus() {
	TextFile<TextRecord> statusFile;
	TextRecord statusRecord;

	statusFile.open(STATUS_FILE_PATH,true);
	statusRecord.setData(this->getInputDictionaryFilePath());
	statusFile.putRecord(statusRecord);
	statusRecord.setData(this->getInputMemorableQuotesFilePath());
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
				<< HELP_TEXT_SIGNATURE_SEARCH << std::endl
				<< std::endl
				<< HELP_TEXT_INDEX_BY_BOOLEAN << std::endl
				<< std::endl
				<< HELP_TEXT_INDEX_BY_SIGNATURE << std::endl
				<< std::endl
				<< HELP_TEXT_CALLHELP << std::endl
				<< std::endl
				<< HELP_TEXT_EXIT <<std::endl
				<< std::endl
				<< HELP_TEXT_DICTIONARY_FILE_PATH << ((this->getInputDictionaryFilePath() != "") ? this->getInputDictionaryFilePath() : "-")
				<< std::endl
				<< HELP_TEXT_MEMORABLE_QUOTES_FILE_PATH << ((this->getInputMemorableQuotesFilePath() != "") ? this->getInputMemorableQuotesFilePath() : "-")
				<< std::endl;
}

bool StatisticsManager::validateDataStructureIntegrity(std::string& filesToLoad) {
	filesToLoad = "";
	if (this->getInputDictionaryFilePath() == "") {
		filesToLoad += TEXT_DICTIONARY;
	}

	if (this->getInputMemorableQuotesFilePath() == "") {
		if (filesToLoad != "")
			filesToLoad += ", ";
		filesToLoad += TEXT_MEMORABLE_QUOTES;
	}

	return (filesToLoad == "");
}

void StatisticsManager::processCommand(std::string& command, std::vector<std::string>& commandParams) {
	if (this->isValidCommand(command,commandParams)) {
		if (command == COMMAND_PRINT_AVG_WORDS_PER_QUOTE) {
			this->printAverageWordsPerPhrase();
			//this->dictionary->exportar("/home/lucasj/workspace/TpDatos2012/outputFiles/out.txt");

		}

		if (command == COMMAND_PRINT_AVG_FAILURES) {
			this->printAverageFailures();
		}

		if (command == COMMAND_PRINT_NOT_FOUND_WORDS) {
			this->printNotFoundWords();
		}

		if (command == COMMAND_PRINT_WORD_RANKING) {
			if (commandParams.size() == 1) {
				this->printWordRanking(StringUtilities::stringToInt(commandParams[0]));
			}
		}

		if (command == COMMAND_LOAD_DICTIONARY) {
			this->clearDictionary();
			this->clearStatistics();
			this->clearNotFoundWords();
			this->clearMemorableQuotes();
//			this->clearIndex();
			this->setInputDictionaryFilePath(commandParams[0]);
			this->createDictionary();
//			delete dictionary;
//			dictionary = new IndiceArbol(DICTIONARY_INDEX_FILE_PATH);
//			this->getDictionary()->createIndex(DICTIONARY_RANDOMIZED_ORDERED_FILE_PATH);
//			this->getMemorableQuotes()->clear();
//			delete memorableQuotes;
//			memorableQuotes = new Hash::DispersionEx(MEMORABLE_QUOTES_INDEX_FILE_PATH);
//			this->getNotFoundWords()->clear();
//			delete notFoundWords;
//			notFoundWords = new IndiceArbol(NOT_FOUND_WORDS_INDEX_FILE_PATH);
//			if (this->getInputMemorableQuotesFilePath() != "") {
//				this->clearNotFoundWords();
//				this->loadMemorableQuotes(false);
//			}
		}

		if (command == COMMAND_LOAD_MEMORABLE_QUOTES) {
//			this->getMemorableQuotes()->clear();
			std::string filesToLoad;

			this->setInputMemorableQuotesFilePath(commandParams[0]);
			if (validateDataStructureIntegrity(filesToLoad)) {
				this->clearNotFoundWords();
				this->clearMemorableQuotes();
				this->clearStatistics();

				//this->clearDictionary();
				//this->createDictionary();
				this->getDictionary()->clearLists();

				this->loadMemorableQuotes();
			} else {
				std::cout << ERROR_COMMAND_PREREQUISITES << filesToLoad << std::endl;
			}
//			delete memorableQuotes;
//			memorableQuotes = new Hash::DispersionEx(MEMORABLE_QUOTES_NAME);
//			this->getNotFoundWords()->clear();
//			delete notFoundWords;
//			notFoundWords = new IndiceArbol(NOTFOUND_NAME);
			this->loadMemorableQuotes();
		}

		if (command == COMMAND_LOAD_INDEXES) {
			std::string filesToLoad;

			if (validateDataStructureIntegrity(filesToLoad)) {
				ExternalSorter<VariableLengthRecordSequentialFile<OcurrenceFileRecord>,OcurrenceFileRecord> sorter(5,false);
				sorter.sort(OCURRENCE_FILE_PATH,OCURRENCE_FILE_PATH_ORDERED,true);

				getT()->open(T_FILE_PATH,false);
				this->sigPortionIndex->load(this->getT(),OCURRENCE_FILE_PATH_ORDERED,this->getDictionary());
				this->getBooleanIndex()->load(this->getT(),OCURRENCE_FILE_PATH_ORDERED,this->getDictionary());

				getT()->close();
			} else {
				std::cout << ERROR_COMMAND_PREREQUISITES << filesToLoad << std::endl;
			}
		}

			if (command == COMMAND_ADD_PHRASE) {
			std::string filesToLoad;

			if (validateDataStructureIntegrity(filesToLoad)) {
				std::string phrase;
				for(unsigned int i = 0; i < commandParams.size(); ++i) {
					phrase.append(commandParams[i]);
					phrase.push_back(' ');
				}

				this->addPhrase(phrase);
			} else {
				std::cout << ERROR_COMMAND_PREREQUISITES << filesToLoad << std::endl;
			}
		}

		if (command == COMMAND_MODIFY_PHRASE) {
			std::string filesToLoad;

			if (validateDataStructureIntegrity(filesToLoad)) {
				//TODO ver de agregar la frase en el hash y solo indexarla si el indica está creado
				std::vector<std::string> phraseTerms;
				for(unsigned int i = 1; i < commandParams.size(); ++i)
					phraseTerms.push_back(commandParams[i]);
				this->modify(StringUtilities::stringToInt(commandParams[0]), phraseTerms);
			} else {
				std::cout << ERROR_COMMAND_PREREQUISITES << filesToLoad << std::endl;
			}
		}

		if (command == COMMAND_ERASE_PHRASE) {
			std::string filesToLoad;

			if (validateDataStructureIntegrity(filesToLoad)) {
				//TODO ver de agregar la frase en el hash y solo indexarla si el indica está creado
				erasePhrase(StringUtilities::stringToInt(commandParams[0]));
			} else {
				std::cout << ERROR_COMMAND_PREREQUISITES << filesToLoad << std::endl;
			}
		}

		if (command == COMMAND_BOOLEAN_SEARCH) {
			if (this->getBooleanIndex()->isLoaded())
				search(commandParams, std::cout);
			else
				std::cout << ERROR_COMMAND_SEARCH_PREREQUISITES << std::endl;
		}

		if (command == COMMAND_SIGNATURE_SEARCH) {
			searchSignature(commandParams, std::cout);
			/*if (this->getBooleanIndex()->isLoaded())
				search(commandParams, std::cout);
			else
				std::cout << ERROR_COMMAND_SEARCH_PREREQUISITES << std::endl;*/
		}

		if (command == COMMAND_PRINT_HELP) {
			this->printHelp();
		}

	} else {
		std::cout << ERROR_TEXT_INVALID_COMMAND << command << std::endl;
	}
}

std::vector<std::string> getNotMatchingTerms(std::vector<std::string>&  array, std::vector<std::string>& toMatchTerms) {
	std::vector<std::string> ret;
	for(unsigned int i = 0; i < array.size(); ++i) {
		bool isPresent = false;
		for(unsigned int j = 0; (j < toMatchTerms.size()) && !isPresent; ++j) {
			if(array[i] == toMatchTerms[j])
				isPresent = true;
		}
		if(!isPresent)
			ret.push_back(array[i]);
	}
	return ret;
}

std::string termsToString(std::vector<std::string> terms) {
	std::string ret;
	int i = 0;
	for(; i < (terms.size() - 1); ++i) {
		ret.append(terms[i]);
		ret.push_back(' ');
	}
	ret.append(terms[i]);
	return ret;
}

void StatisticsManager::modify(unsigned int phraseId, std::vector<std::string> newPhraseTerms) {
	std::string oldPhrase;
	WordNormalizer wordNormalizer;
	this->getMemorableQuotes()->getFrase(phraseId, oldPhrase);
	std::vector<std::string> oldPhraseTerms;
	std::vector<std::string> termsToAdd;
	std::vector<std::string> termsToRemove;
	unsigned int list_id = 0;

	T->open(T_FILE_PATH, false);
	StringUtilities::splitString(oldPhrase, oldPhraseTerms,QUOTES_WORDS_SEPARATOR);
	for(unsigned int i = 0; i < oldPhraseTerms.size(); ++i) {
		oldPhraseTerms[i] = wordNormalizer.normalizeWord(oldPhraseTerms[i]);
		StringUtilities::quitarPuntuacion(oldPhraseTerms[i]);
	}
	for(unsigned int i = 0; i < newPhraseTerms.size(); ++i) {
		newPhraseTerms[i] = wordNormalizer.normalizeWord(newPhraseTerms[i]);
		StringUtilities::quitarPuntuacion(newPhraseTerms[i]);
	}
	termsToAdd = getNotMatchingTerms(newPhraseTerms, oldPhraseTerms);
	termsToRemove = getNotMatchingTerms(oldPhraseTerms, newPhraseTerms);
	for(unsigned int i = 0; i < termsToAdd.size(); ++i) {
		if(this->getStopWords().find(termsToAdd[i]) == this->getStopWords().end()) {
			RegistroArbol reg = this->getDictionary()->textSearch(termsToAdd[i]);
			if(reg.getListId() == 0) {
				unsigned int termId = this->getT()->getLastRecordPosition() + 1;
				FixedLengthTRecord tRecord(T_RECORD_SIZE);
				tRecord.setTerm(termsToAdd[i]);
				this->getT()->putRecord(tRecord);
				if (this->getBooleanIndex()->isLoaded()) {
					list_id = this->getBooleanIndex()->addTerm(termsToAdd[i], phraseId);
				}
				this->getDictionary()->insert(termId, termsToAdd[i], list_id);
			} else
				if (this->getBooleanIndex()->isLoaded()) {
					this->getBooleanIndex()->addDocToTerm(termsToAdd[i], phraseId, this->getDictionary());
				}
		}
	}
	if (this->getBooleanIndex()->isLoaded()) {
		for(unsigned int i = 0; i < termsToRemove.size(); ++i) {
			if(this->getStopWords().find(termsToRemove[i]) == this->getStopWords().end())
				this->getBooleanIndex()->eraseTermInDoc(termsToRemove[i], phraseId, this->getDictionary());
		}
	}
	getT()->close();
//	std::string author = "lala";	//TODO	deshardcodear luego
	std::string phrase_str = termsToString(newPhraseTerms);
	this->getMemorableQuotes()->modificar(phrase_str,""/*author*/,phraseId);
}

void StatisticsManager::search(std::vector<std::string>& commandParams, std::ostream& os) {
	double clock_start = clock();
	std::string word;
	std::list<unsigned int> res;
	std::vector<std::list<unsigned int> > res_lists;
	os << SEARCH_TERM_LIST_MSG << ' ';
	for(unsigned int i = 0; i < commandParams.size(); ++i) {
		word = commandParams[i];
		os << word;
		res_lists.push_back(this->getBooleanIndex()->search(word, this->getDictionary()));
	}
	os << std::endl;
	if(res_lists.size() > 1)
		res = lAnd(res_lists);
	else
		res = res_lists[0];
	std::list<unsigned int>::iterator it;
	float clock_end = clock();
	os << EXECUTION_TIME_MSG << ((clock_end - clock_start) * 1000) /(float)CLOCKS_PER_SEC << std::endl;
	if(*(res_lists[0].begin()) != 0) {
		for(it = res.begin(); it != res.end(); ++it) {
			std::string frase;
			this->getMemorableQuotes()->getFrase(*it, frase);
			os << *it << ' ' << frase << std::endl;
		}
	} else {
		os << TEXT_NO_RESULTS_FOR_SEARCH << std::endl;
	}
}

void StatisticsManager::searchSignature(std::vector<std::string>& commandParams, std::ostream& os) {
	double clock_start = clock();
	std::string word;
	std::list<unsigned int> res;
	std::vector<std::list<unsigned int> > res_lists;
	os << SEARCH_TERM_LIST_MSG << ' ';
	for(int i = 0; i < commandParams.size(); ++i) {
		word = commandParams[i];
		os << word;
		res_lists.push_back(this->sigPortionIndex->search(word, this->getDictionary()));
	}
	os << std::endl;
	if(res_lists.size() > 1)
		res = lAnd(res_lists);
	else
		res = res_lists[0];
	std::list<unsigned int>::iterator it;
	double clock_end = clock();
	os << EXECUTION_TIME_MSG << (clock_end - clock_start)/(double)CLOCKS_PER_SEC << std::endl;
	if(*(res_lists[0].begin()) != 0) {
		for(it = res.begin(); it != res.end(); ++it) {
			std::string frase;
			this->getMemorableQuotes()->getFrase(*it, frase);

			os << *it << ' ' << frase << std::endl;
		}
	} else {
		os << "No hubo coincidencias para esta busqueda" << std::endl;
	}
}


bool StatisticsManager::checkDirectoryStructure() {
	if(!FileUtilities::directoryExists(CONFIG_DIRECTORY_PATH)) {
		std::cout << ERROR_CONFIG_DIRECTORY_NOT_FOUND << std::endl;
		return false;
	} else {
		if(!FileUtilities::directoryExists(BIN_DIRECTORY_PATH))
			FileUtilities::createFolder(BIN_DIRECTORY_PATH);

		if(!FileUtilities::directoryExists(OUTPUT_FILES_DIRECTORY_PATH))
			FileUtilities::createFolder(OUTPUT_FILES_DIRECTORY_PATH);

		return true;
	}
//
//	if(!FileUtilities::directoryExists(INPUT_DIRECTORY_PATH)) {
//		std::cout << INEXISTANT_INPUT_DIRECTORY_ERROR << std::endl;
//		throw(1);
//	}
//	if(!FileUtilities::directoryExists(CONFIG_DIRECTORY_PATH)) {
//		std::cout << INEXISTANT_CONFIG_DIRECTORY_INEXISTANT_ERROR << std::endl;
//		throw(1);
//	}
//	if(FileUtilities::directoryExists(OUTPUT_DIRECTORY_PATH))
//		FileUtilities::createFolder(OUTPUT_DIRECTORY_PATH);
//	ifstream status_file(STATUS_FILE_PATH);
//	if(!status_file.good()) {
//		std::cout << INEXISTANT_OR_BAD_STATUS_FILE_ERROR << std::endl;
//		throw(1);
//	}
//	ifstream stop_words_file(STOP_WORDS_FILE_PATH);
//	if(!stop_words_file.good()) {
//		std::cout << INEXISTANT_OR_BAD_STOP_WORDS_FILE_ERROR << std::endl;
//		throw(1);
//	}
////	ifstream char_map_file(CHAR_MAP_FILE_PATH);
////	if(!char_map_file.good()) {
////		std::cout << INEXISTANT_OR_BAD_CHAR_MAP_FILE_ERROR << std::endl;
////		throw(1);
////	}
//	ifstream dictionary_file(this->getDictionaryFilePath());
//	if(!dictionary_file.good()) {
//		std::cout << INEXISTANT_OR_BAD_DICTIONARY_FILE_ERROR << std::endl;
//		throw(1);
//	}
//	ifstream mem_quotes_file(this->getMemorableQuotesFilePath());
//	if(!mem_quotes_file.good()) {
//		std::cout << INEXISTANT_OR_BAD_MEMORABLE_QUOTES_FILE_ERROR << std::endl;
//		throw(1);
//	}
}

void StatisticsManager::clearDictionary() {
	delete this->getDictionary();
	this->dictionary = new IndiceArbol(DICTIONARY_INDEX_FILE_PATH);
}

void StatisticsManager::clearNotFoundWords() {
	delete this->getNotFoundWords();
	this->notFoundWords = new IndiceArbol(NOT_FOUND_WORDS_INDEX_FILE_PATH);
}

void StatisticsManager::clearMemorableQuotes() {
	delete this->getMemorableQuotes();
	this->memorableQuotes = new Hash::DispersionEx(MEMORABLE_QUOTES_INDEX_FILE_PATH);
}

std::vector<std::string> StatisticsManager::tokenizePhrase(std::string phrase) {
	std::vector<std::string> phraseWords;
	std::vector<std::string> ret;
	WordNormalizer normalizer;
	StringUtilities::splitString(phrase,phraseWords,AUTHOR_QUOTE_SEPARATOR);
	StringUtilities::splitString(phraseWords[phraseWords.size() - 1],phraseWords,QUOTES_WORDS_SEPARATOR);
	for(unsigned int i = 0; i < phraseWords.size(); ++i) {
		StringUtilities::sacarR(phraseWords[i]);
		normalizer.normalizeWord(phraseWords[i]);
		StringUtilities::quitarPuntuacion(phraseWords[i]);
		if(this->getStopWords().find(phraseWords[i]) == this->getStopWords().end())
			ret.push_back(phraseWords[i]);
	}
	return ret;
}

StatisticsManager::~StatisticsManager() {
	this->saveStatus();
	delete this->getNotFoundWords();
	delete this->getDictionary();
	delete this->getMemorableQuotes();
}
