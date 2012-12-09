#include "../include/cce.h"
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
#include <ctime>
#include <chrono>

CCE::CCE() {
	if (this->checkDirectoryStructure()) {
		PropertiesLoader propertiesLoader(CONFIG_FILE_PATH);

		this->successfullInit = true;
		this->stopWordsFilePath = propertiesLoader.getPropertyValue(STOP_WORDS_FILE_PATH_PROPERTY_NAME);
		this->dictionary = new IndiceArbol(DICTIONARY_INDEX_FILE_PATH);
		this->notFoundWords = new IndiceArbol(NOT_FOUND_WORDS_INDEX_FILE_PATH);
		this->memorableQuotes = new Hash::DispersionEx(MEMORABLE_QUOTES_INDEX_FILE_PATH);
		this->T = new FixedLengthRecordSequentialFile<FixedLengthTRecord>(T_RECORD_SIZE);
		this->booleanIndex = new BooleanIndex(BOOLEAN_INDEX_FILE_NAME);
		this->numberOfFailures = 0;
		this->numberOfQuotes = 0;
		this->numberOfWords = 0;
		this->sigPortionIndex = new SignaturePortionIndex(BITSLICE_INDEX_FILE_NAME);
		this->loadStatus();
		this->loadStopWords();
	} else {
		successfullInit = false;
	}
}

std::string CCE::getInputDictionaryFilePath() const {
	return this->inputDictionaryFilePath;
}

void CCE::setInputDictionaryFilePath(std::string inputDictionaryFilePath) {
	this->inputDictionaryFilePath = inputDictionaryFilePath;
}

std::string CCE::getInputMemorableQuotesFilePath() const {
	return this->inputMemorableQuotesFilePath;
}

void CCE::setInputMemorableQuotesFilePath(std::string inputMemorableQuotesFilePath) {
	this->inputMemorableQuotesFilePath = inputMemorableQuotesFilePath;
}

std::string CCE::getStopWordsFilePath() const {
	return this->stopWordsFilePath;
}

void CCE::setStopWordsFilePath(std::string stopWordsFilePath) {
	this->stopWordsFilePath = stopWordsFilePath;
}

unsigned int CCE::getNumberOfWords() const {
	return this->numberOfWords;
}

void CCE::setNumberOfWords(unsigned int numberOfWords) {
	this->numberOfWords = numberOfWords;
}

unsigned int CCE::getNumberOfQuotes() const {
	return this->numberOfQuotes;
}

void CCE::setNumberOfQuotes(unsigned int numberOfQuotes) {
	this->numberOfQuotes = numberOfQuotes;
}

unsigned int CCE::getNumberOfFailures() const {
	return this->numberOfFailures;
}

void CCE::setNumberOfFailures(unsigned int numberOfFailures) {
	this->numberOfFailures = numberOfFailures;
}

std::set<std::string>& CCE::getStopWords() {
	return this->stopWords;
}

IndiceArbol* CCE::getDictionary() {
	return this->dictionary;
}

Hash::DispersionEx* CCE::getMemorableQuotes() {
	return this->memorableQuotes;
}

IndiceArbol* CCE::getNotFoundWords() {
	return this->notFoundWords;
}

bool CCE::isSuccessfullInit() const	{
    return this->successfullInit;
}

BooleanIndex* CCE::getBooleanIndex() const {
	return this->booleanIndex;
}

FixedLengthRecordSequentialFile<FixedLengthTRecord>* CCE::getT() const {
	return this->T;
}

void CCE::loadStatus() {
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
		} else {
			this->clearAll();
			std::cout << ERROR_STATUS_RETRIEVAL_FAILURE << std::endl
					  << errorMessage << std::endl;
		}
	} else {
		this->clearAll();
	}
}

void CCE::loadStopWords() {
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

void CCE::createDictionary() {
	VariableLengthRecordSequentialFile<TextRecord> inputDictionaryFile;

	inputDictionaryFile.open(this->getInputDictionaryFilePath());
	if (inputDictionaryFile.isFileExists()) {
		DictionaryNormalizer dictionaryNormalizer;
		DictionaryRandomizer dictionaryRandomizer;

		inputDictionaryFile.close();
		dictionaryNormalizer.normalize(this->getInputDictionaryFilePath());
		dictionaryRandomizer.randomizeDictionary(dictionaryNormalizer.getOutputFilePath(),false);

		if(this->getDictionary()->isEmpty()) {
			this->getT()->open(T_FILE_PATH,true);
			this->getDictionary()->createIndex(dictionaryRandomizer.getOrderedRandomizedDictionaryFilePath(), T);
			this->getT()->close();
		}
	} else {
		std::cout << ERROR_FILE_NOT_FOUND << this->getInputDictionaryFilePath() << std::endl;
	}
}

void CCE::loadMemorableQuotes() {
	TextFile<TextRecord> memorableQuotesFile;
	std::string phrase;
	WordNormalizer normalizer;
	std::vector<std::string> phraseWords;
	unsigned int totalQuotes = 0;
	unsigned int totalWords = 0;
	unsigned int totalFailures = 0;
	unsigned int termId = 0;
	ExternalSorter<VariableLengthRecordSequentialFile<WordRankingRecord>,WordRankingRecord > externalSorter(10,true);

	memorableQuotesFile.open(this->getInputMemorableQuotesFilePath());
	if (memorableQuotesFile.isFileExists()) {
		this->getT()->open(T_FILE_PATH);
		VariableLengthRecordSequentialFile<OcurrenceFileRecord> ocurrenceFile;
		ocurrenceFile.open(OCURRENCE_FILE_PATH,true);
		this->getDictionary()->rewind();
		while (!memorableQuotesFile.endOfFile()) {
			phrase = memorableQuotesFile.getNextRecord().getData();
			StringUtilities::splitString(phrase,phraseWords,AUTHOR_QUOTE_SEPARATOR);
			StringUtilities::splitString(phraseWords[phraseWords.size() - 1],phraseWords,QUOTES_WORDS_SEPARATOR);
			totalQuotes++;
			for (unsigned int i = 0; i < phraseWords.size(); i++) {
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
						this->getDictionary()->insert(termId,phraseWords[i],0);
						FixedLengthTRecord tRecord(T_RECORD_SIZE);
						tRecord.setTerm(phraseWords[i]);
						tRecord.setId(termId);
						this->getT()->putRecord(tRecord);
					} else {
						RegistroArbol reg;
						reg = this->getDictionary()->textSearch(phraseWords[i]);
						termId = reg.getTermId();
					}
					OcurrenceFileRecord ocurrenceRecord;
					ocurrenceRecord.setTermId(termId);
					ocurrenceRecord.setDocId(totalQuotes);
					ocurrenceFile.putRecord(ocurrenceRecord);
				}
			}

			this->getMemorableQuotes()->insert(phrase);
		}

		this->setNumberOfWords(totalWords);
		this->setNumberOfQuotes(totalQuotes);
		this->setNumberOfFailures(totalFailures);
		this->getT()->close();
		ocurrenceFile.close();

		this->getDictionary()->exportar(RANKINGS_FILE_PATH);
		externalSorter.sort(RANKINGS_FILE_PATH,RANKINGS_FILE_PATH_ORDERED,true);
	} else {
		std::cout << ERROR_FILE_NOT_FOUND << this->getInputMemorableQuotesFilePath() << std::endl;
	}
}

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

void CCE::printAverageWordsPerPhrase() {
	float result;

	if (this->getNumberOfQuotes() != 0)
		result = static_cast<float>(this->getNumberOfWords()) / this->getNumberOfQuotes();
	else
		result = this->getNumberOfWords();

	std::cout << TEXT_AVG_WORDS_PER_QUOTE
			  << StringUtilities::floatToString(result)
			  << std::endl;
}

void CCE::printAverageFailures() {
	float result;

	if (this->getNumberOfWords() != 0)
		result = static_cast<float>(this->getNumberOfFailures()) / this->getNumberOfWords();
	else
		result = this->getNumberOfFailures();

	std::cout << TEXT_AVG_FAILURES
			  << StringUtilities::floatToString(result)
			  << std::endl;
}

void CCE::printNotFoundWords() {
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

void CCE::printWordRanking(unsigned int rankingSize) {
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

void CCE::erasePhrase(unsigned int idPhrase) {
	WordNormalizer wordNormalizer;
	std::vector<std::string> phraseWords;
	std::string phrase;

	if (this->getMemorableQuotes()->getFrase(idPhrase,phrase)) {
		StringUtilities::splitString(phrase,phraseWords,QUOTES_WORDS_SEPARATOR);
		unsigned int size = phraseWords.size();
		for (unsigned int i = 0; i < size; i++) {
			phraseWords[i] = wordNormalizer.normalizeWord(phraseWords[i]);
			if (this->getStopWords().find(phraseWords[i]) == this->getStopWords().end()) {
				if (this->getBooleanIndex()->isLoaded()) {
					this->getBooleanIndex()->eraseTermInDoc(phraseWords[i], idPhrase, this->getDictionary());
					this->sigPortionIndex->eraseTermInDoc(phraseWords[i], idPhrase, this->getDictionary());
				}
			this->setNumberOfWords(this->getNumberOfWords() - 1);
			}
		}
		this->setNumberOfQuotes(this->getNumberOfQuotes() - 1);
		this->getMemorableQuotes()->borrarRegistro(idPhrase);
	} else {
		std::cout << "frase con encontrada" << std::endl;
	}
}

void CCE::addPhrase(std::string phrase) {
	WordNormalizer wordNormalizer;
	std::vector<std::string> phraseWords;
	unsigned int listId = 0;
	unsigned int termId = 0;

	StringUtilities::splitString(phrase,phraseWords,QUOTES_WORDS_SEPARATOR);
	this->setNumberOfQuotes(this->getNumberOfQuotes() + 1);
	this->getT()->open(T_FILE_PATH);
	for (unsigned int i = 0; i < phraseWords.size(); i++) {
		phraseWords[i] = wordNormalizer.normalizeWord(phraseWords[i]);
		if ( (this->getStopWords().find(phraseWords[i]) == this->getStopWords().end()) && (phraseWords[i].size() > 0) ) {
			this->setNumberOfWords(this->getNumberOfWords() + 1);
			unsigned int docId = this->getMemorableQuotes()->getLastId() + 1;		
			if (!this->getDictionary()->find(phraseWords[i])) {
				this->setNumberOfFailures(this->getNumberOfFailures() + 1);
				termId = this->getT()->getLastRecordPosition() + 1;
				if (this->getBooleanIndex()->isLoaded()) {
					listId = this->getBooleanIndex()->addTerm(phraseWords[i], this->getMemorableQuotes()->getLastId() + 1);
					this->sigPortionIndex->addTerm(termId, docId);
				}
				this->getDictionary()->insert(termId, phraseWords[i], listId);
				FixedLengthTRecord tRecord(T_RECORD_SIZE);
				tRecord.setTerm(phraseWords[i]);
				tRecord.setId(termId);
				this->getT()->putRecord(tRecord);
			} else {
				if (this->getBooleanIndex()->isLoaded()) {
					this->getBooleanIndex()->addDocToTerm(phraseWords[i],docId,this->getDictionary());
					this->sigPortionIndex->addDocToTerm(phraseWords[i],docId,this->getDictionary());
				}
			}
		}
	}

	for (unsigned int i = 0; i < 2; i++) {
		phrase = AUTHOR_QUOTE_SEPARATOR + phrase;
	}

	this->getMemorableQuotes()->insert(phrase);
}

bool CCE::isValidCommand(std::string& command, std::vector<std::string>& commandParams) {
	//TODO cambiar a un mapa de command params size
	if ( ((command != COMMAND_PRINT_AVG_WORDS_PER_QUOTE) &&
		  (command != COMMAND_PRINT_AVG_FAILURES) &&
		  (command != COMMAND_PRINT_NOT_FOUND_WORDS) &&
		  (command != COMMAND_PRINT_WORD_RANKING) &&
		  (command != COMMAND_LOAD_DICTIONARY) &&
		  (command != COMMAND_LOAD_INDEXES) &&
		  (command != COMMAND_LOAD_MEMORABLE_QUOTES) &&
		  (command != COMMAND_SEARCH) &&
//		  (command != COMMAND_SIGNATURE_SEARCH) &&
		  (command != COMMAND_LOAD_INDEXES) &&
//		  (command != COMMAND_INDEX_BY_SIGNATURE) &&
		  (command != COMMAND_ADD_PHRASE) &&
		  (command != COMMAND_MODIFY_PHRASE) &&
		  (command != COMMAND_ERASE_PHRASE) &&
		  (command != COMMAND_PRINT_HELP)) ||
		 (((command == COMMAND_PRINT_WORD_RANKING) ||
		   (command == COMMAND_LOAD_DICTIONARY) ||
		   (command == COMMAND_ERASE_PHRASE) ||
		   (command == COMMAND_ADD_PHRASE) ||
		   (command == COMMAND_SEARCH) ||
		   (command == COMMAND_LOAD_MEMORABLE_QUOTES)) &&
		  (commandParams.size() != 1)) ||
		 ((command == COMMAND_MODIFY_PHRASE) &&
		   (commandParams.size() != 2))  ) {
		return false;
	}

	return true;
}

void CCE::saveStatus() {
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

void CCE::printHelp() {
	std::cout 	<< std::endl
				<< HELP_TITLE << std::endl
				<< HELP_TEXT_LOAD_DICTIONARY << std::endl
				<< std::endl
				<< HELP_TEXT_LOAD_MEMORABLE_QUOTES << std::endl
				<< std::endl
				<< HELP_TEXT_AVG_WORDS_PER_QUOTE << std::endl
				<< std::endl
				<< HELP_TEXT_AVG_FAILURES << std::endl
				<< std::endl
				<< HELP_TEXT_NOT_FOUND_WORDS << std::endl
				<< std::endl
				<< HELP_TEXT_WORD_RANKING << std::endl
				<< std::endl
				<< HELP_TEXT_LOAD_INDEX << std::endl
				<< std::endl
				<< HELP_TEXT_SEARCH << std::endl
				<< std::endl
				<< HELP_TEXT_ADD_PHRASE << std::endl
				<< std::endl
				<< HELP_TEXT_MODIFY_PHRASE << std::endl
				<< std::endl
				<< HELP_TEXT_ERASE_PHRASE << std::endl
				<< std::endl
				<< HELP_TEXT_EXIT <<std::endl
				<< std::endl
				<< HELP_TEXT_DICTIONARY_FILE_PATH << ((this->getInputDictionaryFilePath() != "") ? this->getInputDictionaryFilePath() : "-")
				<< std::endl
				<< HELP_TEXT_MEMORABLE_QUOTES_FILE_PATH << ((this->getInputMemorableQuotesFilePath() != "") ? this->getInputMemorableQuotesFilePath() : "-")
				<< std::endl;
}

bool CCE::validateDataStructureIntegrity(std::string& filesToLoad) {
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

void CCE::processCommand(std::string& command, std::vector<std::string>& commandParams) {
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
			this->printWordRanking(StringUtilities::stringToInt(commandParams[0]));
		}

		if (command == COMMAND_LOAD_DICTIONARY) {
			this->clearAll();
			this->setInputDictionaryFilePath(commandParams[0]);
			this->createDictionary();
		}

		if (command == COMMAND_LOAD_MEMORABLE_QUOTES) {

			if (this->getInputDictionaryFilePath() != "") {
				if (this->getInputMemorableQuotesFilePath() != "") {
					this->clearNotFoundWords();
					this->clearMemorableQuotes();
					this->clearStatistics();
					this->getDictionary()->clearLists();
					this->clearIndex();
				}
				this->setInputMemorableQuotesFilePath(commandParams[0]);
				this->loadMemorableQuotes();
			} else {
				std::cout << ERROR_COMMAND_PREREQUISITES << TEXT_DICTIONARY << std::endl;
			}
		}

		if (command == COMMAND_LOAD_INDEXES) {
			std::string filesToLoad;

			if (validateDataStructureIntegrity(filesToLoad)) {
				ExternalSorter<VariableLengthRecordSequentialFile<OcurrenceFileRecord>,OcurrenceFileRecord> sorter(5,false);
				sorter.sort(OCURRENCE_FILE_PATH,OCURRENCE_FILE_PATH_ORDERED,true);

				this->getT()->open(T_FILE_PATH);
				this->sigPortionIndex->load(this->getT(),OCURRENCE_FILE_PATH_ORDERED,this->getDictionary());
				std::ofstream arch ("archSig.txt");
				arch << *(this->sigPortionIndex);
				this->getBooleanIndex()->load(this->getT(),OCURRENCE_FILE_PATH_ORDERED,this->getDictionary());
				std::ofstream arch2 ("archInv.txt");
				arch2 << *(this->booleanIndex);
				this->getT()->close();
			} else {
				std::cout << ERROR_COMMAND_PREREQUISITES << filesToLoad << std::endl;
			}
		}

		if (command == COMMAND_ADD_PHRASE) {
			std::string filesToLoad;

			if (validateDataStructureIntegrity(filesToLoad)) {
				std::string phrase;
				this->addPhrase(commandParams[0]);
			} else {
				std::cout << ERROR_COMMAND_PREREQUISITES << filesToLoad << std::endl;
			}
		}

		if (command == COMMAND_MODIFY_PHRASE) {
			std::string filesToLoad;

			if (validateDataStructureIntegrity(filesToLoad)) {
				if (StringUtilities::isNumeric(commandParams[0])) {
					std::vector<std::string> newPhraseTerms;

					StringUtilities::splitString(commandParams[1],newPhraseTerms,' ');
						this->modify(StringUtilities::stringToInt(commandParams[0]),newPhraseTerms);
				} else {
					std::cout << "El id de la frase a modificar debe ser numerico y mayor a cero." << filesToLoad << std::endl;
				}
			} else {
				std::cout << ERROR_COMMAND_PREREQUISITES << filesToLoad << std::endl;
			}
		}

		if (command == COMMAND_ERASE_PHRASE) {
			std::string filesToLoad;

			if (validateDataStructureIntegrity(filesToLoad)) {
				erasePhrase(StringUtilities::stringToInt(commandParams[0]));
			} else {
				std::cout << ERROR_COMMAND_PREREQUISITES << filesToLoad << std::endl;
			}
		}

		if (command == COMMAND_SEARCH) {
			std::chrono::time_point<std::chrono::high_resolution_clock> searchPreparationsStart;
			std::chrono::time_point<std::chrono::high_resolution_clock> searchPreparationsEnd;
			std::chrono::time_point<std::chrono::high_resolution_clock> booleansearchStart;
			std::chrono::time_point<std::chrono::high_resolution_clock> booleansearchEnd;
			std::chrono::time_point<std::chrono::high_resolution_clock> signatureSearchStart;
			std::chrono::time_point<std::chrono::high_resolution_clock> signatureSearchEnd;
			unsigned long int preparationsTimeInMicroseconds;
			unsigned long int booleanSearchTimeInMicroseconds;
			unsigned long int signatureSearchTimeInMicroseconds;
			unsigned long int searchTimeDifferenceInMicroseconds;
			std::ofstream searchLog;

			searchLog.open("outputFiles/searchLog.log",std::ios_base::out | std::iostream::app);

			if (this->getBooleanIndex()->isLoaded()) {
				WordNormalizer normalizer;
				std::vector<std::string> wordsToSearch;
				std::string word;

				searchPreparationsStart = std::chrono::high_resolution_clock::now();
				StringUtilities::splitString(commandParams[0],commandParams,' ');
				for (unsigned int i = 0; i < commandParams.size(); ++i) {
					word = normalizer.normalizeWord(commandParams[i]);
					if (this->getStopWords().find(word) == this->getStopWords().end())
						wordsToSearch.push_back(word);
				}

				searchPreparationsEnd = std::chrono::high_resolution_clock::now();
				preparationsTimeInMicroseconds = std::chrono::duration_cast<std::chrono::microseconds> (searchPreparationsEnd-searchPreparationsStart).count();
				if (!wordsToSearch.empty()) {
					searchLog << "-----------------Inicio busqueda-----------------" << std::endl << std::endl;

					booleansearchStart = std::chrono::high_resolution_clock::now();
					searchLog << "	Busqueda booleana:" << std::endl << std::endl;
					this->search(wordsToSearch,searchLog);
					booleansearchEnd = std::chrono::high_resolution_clock::now();
					booleanSearchTimeInMicroseconds = std::chrono::duration_cast<std::chrono::microseconds> (booleansearchEnd-booleansearchStart).count() + preparationsTimeInMicroseconds;
					searchLog << std::endl << EXECUTION_TIME_MSG << StringUtilities::intToString(booleanSearchTimeInMicroseconds) << " Microsegundos." << std::endl << std::endl;

					signatureSearchStart = std::chrono::high_resolution_clock::now();
					searchLog << "	Busqueda por indice de porciones de firmas:" << std::endl << std::endl;
					this->searchSignature(wordsToSearch,searchLog);
					signatureSearchEnd = std::chrono::high_resolution_clock::now();
					signatureSearchTimeInMicroseconds = std::chrono::duration_cast<std::chrono::microseconds> (signatureSearchEnd-signatureSearchStart).count() + preparationsTimeInMicroseconds;
					searchLog << std::endl << EXECUTION_TIME_MSG << StringUtilities::intToString(signatureSearchTimeInMicroseconds) << " Microsegundos." << std::endl << std::endl;

					searchLog << "La búsqueda ";
					if (booleanSearchTimeInMicroseconds < signatureSearchTimeInMicroseconds) {
						searchTimeDifferenceInMicroseconds = signatureSearchTimeInMicroseconds - booleanSearchTimeInMicroseconds;
						searchLog << "por indice booleano";
					} else {
						searchTimeDifferenceInMicroseconds = booleanSearchTimeInMicroseconds - signatureSearchTimeInMicroseconds;
						searchLog << "por indice de firmas";
					}
					searchLog << " fue mas rapida por " << StringUtilities::intToString(searchTimeDifferenceInMicroseconds) << " microsegundos." << std::endl << std::endl;

					searchLog << "-----------------Fin busqueda-----------------" << std::endl << std::endl;

					std::cout << "Busqueda realizada. Ver log en \"outputFiles/searchLog.log\" para mas detalles" << std::endl;
				} else
					std::cout << "No hay términos relevantes para realizar la búsqueda." << std::endl;

				searchLog.close();
			} else
				std::cout << ERROR_COMMAND_SEARCH_PREREQUISITES << std::endl;
		}
//
//		if (command == COMMAND_SIGNATURE_SEARCH) {
//			searchSignature(commandParams, std::cout);
//			/*if (this->getBooleanIndex()->isLoaded())
//				search(commandParams, std::cout);
//			else
//				std::cout << ERROR_COMMAND_SEARCH_PREREQUISITES << std::endl;*/
//		}

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

void CCE::modify(unsigned int phraseId, std::vector<std::string> newPhraseTerms) {
	std::string oldPhrase;
	WordNormalizer wordNormalizer;
	this->getMemorableQuotes()->getFrase(phraseId, oldPhrase);
	std::vector<std::string> oldPhraseTerms;
	std::vector<std::string> termsToAdd;
	std::vector<std::string> termsToRemove;
	unsigned int list_id = 0;
	std::string phrase_str = termsToString(newPhraseTerms);

	this->getT()->open(T_FILE_PATH);
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
					this->sigPortionIndex->addTerm(termId, phraseId);
				}
				this->getDictionary()->insert(termId, termsToAdd[i], list_id);
			} else {
				if (this->getBooleanIndex()->isLoaded()) {
					this->getBooleanIndex()->addDocToTerm(termsToAdd[i], phraseId, this->getDictionary());
					this->sigPortionIndex->addDocToTerm(termsToAdd[i], phraseId, this->getDictionary());
				}
			}
		}
	}
	if (this->getBooleanIndex()->isLoaded()) {
		for(unsigned int i = 0; i < termsToRemove.size(); ++i) {
			if(this->getStopWords().find(termsToRemove[i]) == this->getStopWords().end()) {
				this->getBooleanIndex()->eraseTermInDoc(termsToRemove[i], phraseId, this->getDictionary());
				this->sigPortionIndex->eraseTermInDoc(termsToRemove[i], phraseId, this->getDictionary());
			}
		}
	}
	getT()->close();
	this->getMemorableQuotes()->modificar(phrase_str,"",phraseId);
}

void CCE::search(std::vector<std::string>& wordsToSearch, std::ostream& os) {
	std::string word;
	std::list<unsigned int> res;
	std::vector<std::list<unsigned int> > res_lists;
	os << SEARCH_TERM_LIST_MSG << std::endl << "\t\t";
	for(unsigned int i = 0; i < wordsToSearch.size(); ++i) {
		word = wordsToSearch[i];
		os << word << " ";
		res_lists.push_back(this->getBooleanIndex()->search(word, this->getDictionary()));
	}
	os << std::endl << std::endl;
	if(res_lists.size() > 1)
		res = lAnd(res_lists);
	else
		res = res_lists[0];
	std::list<unsigned int>::iterator it;
	if(*(res_lists[0].begin()) != 0) {
		os << "		Frases encontradas:" << std::endl;
		for(it = res.begin(); it != res.end(); ++it) {
			std::string frase;
			this->getMemorableQuotes()->getFrase(*it, frase);
			os << "\t\t" << *it << " - " << frase << std::endl;
		}
	} else {
		os << TEXT_NO_RESULTS_FOR_SEARCH << std::endl;
	}
}

void CCE::searchSignature(std::vector<std::string>& commandParams, std::ostream& os) {
	std::string word;
	std::list<unsigned int> res;
	std::vector<std::list<unsigned int> > res_lists;
	os << SEARCH_TERM_LIST_MSG << std::endl << "\t\t";
	for(unsigned int i = 0; i < commandParams.size(); ++i) {
		word = commandParams[i];
		os << word << " ";
		res_lists.push_back(this->sigPortionIndex->search(word, this->getDictionary()));
	}
	os << std::endl << std::endl;
	if(res_lists.size() > 1)
		res = lAnd(res_lists);
	else
		res = res_lists[0];
	std::list<unsigned int>::iterator it;
	if(*(res_lists[0].begin()) != 0) {
		os << "		Frases encontradas:" << std::endl;
		for(it = res.begin(); it != res.end(); ++it) {
			std::string frase;
			this->getMemorableQuotes()->getFrase(*it, frase);
			os << "\t\t" << *it << " - " << frase << std::endl;
		}
	} else {
		os << TEXT_NO_RESULTS_FOR_SEARCH << std::endl;
	}
}


bool CCE::checkDirectoryStructure() {
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
}

void CCE::clearDictionary() {
	delete this->getDictionary();
	FileUtilities::deleteFile(DICTIONARY_INDEX_FILE_PATH);
	this->dictionary = new IndiceArbol(DICTIONARY_INDEX_FILE_PATH);
}

void CCE::clearNotFoundWords() {
	delete this->getNotFoundWords();
	FileUtilities::deleteFile(NOT_FOUND_WORDS_INDEX_FILE_PATH);
	this->notFoundWords = new IndiceArbol(NOT_FOUND_WORDS_INDEX_FILE_PATH);
}

void CCE::clearMemorableQuotes() {
	delete this->getMemorableQuotes();
	FileUtilities::deleteFile(MEMORABLE_QUOTES_INDEX_FILE_PATH);
	this->memorableQuotes = new Hash::DispersionEx(MEMORABLE_QUOTES_INDEX_FILE_PATH);
}

void CCE::clearIndex() {
	delete this->getBooleanIndex();
	delete this->sigPortionIndex;
	FileUtilities::deleteFile(BOOLEAN_INDEX_FILE_NAME);
	FileUtilities::deleteFile(BITSLICE_INDEX_FILE_NAME);
	this->booleanIndex = new BooleanIndex(BOOLEAN_INDEX_FILE_NAME);
	this->sigPortionIndex = new SignaturePortionIndex(BITSLICE_INDEX_FILE_NAME);
}

void CCE::clearTFile() {
	this->getT()->open(T_FILE_PATH,true);
}

void CCE::clearStatistics() {
	this->setNumberOfWords(0);
	this->setNumberOfQuotes(0);
	this->setNumberOfFailures(0);
}

void CCE::clearAll() {
	this->setInputDictionaryFilePath("");
	this->setInputMemorableQuotesFilePath("");
	this->clearStatistics();
	this->clearDictionary();
	this->clearMemorableQuotes();
	this->clearNotFoundWords();
	this->clearTFile();
	this->clearIndex();
}

std::vector<std::string> CCE::tokenizePhrase(std::string phrase) {
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

CCE::~CCE() {
	this->saveStatus();
	delete this->getNotFoundWords();
	delete this->getDictionary();
	delete this->getMemorableQuotes();
	delete this->getBooleanIndex();
	delete this->getT();
	delete this->sigPortionIndex;
}
