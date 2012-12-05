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


StatisticsManager::StatisticsManager() {
	if (this->checkDirectoryStructure()) {
		PropertiesLoader propertiesLoader("config/statisticsManager.properties");

		this->successfullInit = true;
		this->stopWordsFilePath = propertiesLoader.getPropertyValue(STOP_WORDS_FILE_PATH_PROPERTY_NAME);
		this->dictionary = new IndiceArbol(DICTIONARY_INDEX_FILE_PATH);
		this->notFoundWords = new IndiceArbol(NOT_FOUND_WORDS_INDEX_FILE_PATH);
		this->memorableQuotes = new Hash::DispersionEx(MEMORABLE_QUOTES_INDEX_FILE_PATH);
		this->T = new FixedLengthRecordSequentialFile<FixedLengthTRecord>(20);
		this->numberOfFailures = 0;
		this->numberOfQuotes = 0;
		this->numberOfWords = 0;
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

bool StatisticsManager::isFirstRun() const {
	return this->firstRun;
}

void StatisticsManager::setFirstRun(bool firstRun) {
	this->firstRun = firstRun;
}

bool StatisticsManager::isSuccessfullInit() const	{
    return this->successfullInit;
}

void StatisticsManager::setSuccessfullInit(bool successfullInit) {
    this->successfullInit = successfullInit;
}

void StatisticsManager::loadStatus() {
	TextFile<TextRecord> statusFile;
	std::string errorMessage;

	statusFile.open(STATUS_FILE_PATH);
	if (statusFile.isFileExists()) {
		this->setInputDictionaryFilePath(statusFile.getNextRecord().getData());
		this->setInputMemorableQuotesFilePath(statusFile.getNextRecord().getData());

		if ( (this->getInputDictionaryFilePath() != "") && (this->getDictionary()->isEmpty()) )
			errorMessage = errorMessage + "No se pudo recuperar el archivo ubicado en " + DICTIONARY_INDEX_FILE_PATH + "\"\n";

		if ( (this->getInputMemorableQuotesFilePath() != "") && (this->getMemorableQuotes()->isEmpty()) )
			errorMessage = errorMessage + "No se pudo recuperar el archivo ubicado en \"" + MEMORABLE_QUOTES_INDEX_FILE_PATH + "\"\n";

		if ( (this->getInputMemorableQuotesFilePath() != "") && (this->getNotFoundWords()->isEmpty()) )
			errorMessage = errorMessage + "No se pudo recuperar el archivo ubicado en " + NOT_FOUND_WORDS_INDEX_FILE_PATH + "\"\n";

		if (errorMessage == "") {
			this->setNumberOfWords(StringUtilities::stringToInt(statusFile.getNextRecord().getData()));
			this->setNumberOfQuotes(StringUtilities::stringToInt(statusFile.getNextRecord().getData()));
			this->setNumberOfFailures(StringUtilities::stringToInt(statusFile.getNextRecord().getData()));
			this->setFirstRun(false);
		} else {
			this->setFirstRun(true);
			this->setInputDictionaryFilePath("");
			this->setInputMemorableQuotesFilePath("");
			std::cout << "No se pudo recuperar el estado guardado del programa debido a los siguientes errores: " << std::endl
					  << errorMessage << std::endl;
		}
	} else
		this->setFirstRun(true);
}

void StatisticsManager::loadStopWords() {
	TextFile<TextRecord> stopWordsFile;

	stopWordsFile.open(this->getStopWordsFilePath());
	if (stopWordsFile.isFileExists()) {
		while (!stopWordsFile.endOfFile()) {
			this->getStopWords().insert(stopWordsFile.getNextRecord().getData());
		}
	} else {
		std::cout << "WARNING: Archivo de stop words no encontrado." << std::endl;
	}
}

void StatisticsManager::createDictionary(bool force) {
	VariableLengthRecordSequentialFile<TextRecord> inputDictionaryFile;

	inputDictionaryFile.open(this->getInputDictionaryFilePath());
	if (inputDictionaryFile.isFileExists()) {
		DictionaryNormalizer dictionaryNormalizer;
		DictionaryRandomizer dictionaryRandomizer;

		inputDictionaryFile.close();
		dictionaryNormalizer.normalize(this->getInputDictionaryFilePath());
		dictionaryRandomizer.randomizeDictionary(dictionaryNormalizer.getOutputFilePath(),false);

		if(this->getDictionary()->isEmpty())
			this->getDictionary()->createIndex(dictionaryRandomizer.getOrderedRandomizedDictionaryFilePath());
	} else {
		std::cout << "Archivo inexistente" << std::endl;
	}
}

void StatisticsManager::loadMemorableQuotes(bool insertInHash) {
	TextFile<TextRecord> memorableQuotesFile;
	std::string phrase;
	WordNormalizer normalizer;
	std::vector<std::string> phraseWords;
	unsigned int totalQuotes = 0;
	unsigned int totalWords = 0;
	unsigned int totalFailures = 0;
	unsigned int idTermino = 0;
	ExternalSorter<VariableLengthRecordSequentialFile<WordRankingRecord>,WordRankingRecord > externalSorter(10,true);

	memorableQuotesFile.open(this->getInputMemorableQuotesFilePath());
	if (memorableQuotesFile.isFileExists()) {
		//////////////////77 TEMPORAL /////////////////////
		T->open("tFile.bin",true);
		VariableLengthRecordSequentialFile<OcurrenceFileRecord> ocurrenceFile;
		//TODO quitar esta variable, es un path interno de un archivo temporal, puede estar harcodeada en una constante.
		ocurrenceFilePath = OCURRENCE_FILE_PATH;
		ocurrenceFile.open(OCURRENCE_FILE_PATH,true);
		///////////
		this->getDictionary()->rewind();
		while (!memorableQuotesFile.endOfFile()) {
			phrase = memorableQuotesFile.getNextRecord().getData();
			//separo el autor de la frase
			StringUtilities::splitString(phrase,phraseWords,AUTHOR_QUOTE_SEPARATOR);
			//separo la frase en palabras
			StringUtilities::splitString(phraseWords[phraseWords.size() - 1],phraseWords,QUOTES_WORDS_SEPARATOR);
			totalQuotes++;


			std::cout << StringUtilities::intToString(totalQuotes) << std::endl;
			if (totalQuotes == 129)
				std::cout << "...IT'S GONNA BLOW!" << std::endl;

			for (unsigned int i = 0; i < phraseWords.size(); i++) {
				//chequeo que no sea stopWord.
				//StringUtilities::sacarR(phraseWords[i]);
				phraseWords[i] = normalizer.normalizeWord(phraseWords[i]);
				std::cout << phraseWords[i] << std::endl;
				//StringUtilities::quitarPuntuacion(phraseWords[i]);
				if(this->getStopWords().find(phraseWords[i]) == this->getStopWords().end()) {
					totalWords++;
					//si no está en el índice de fallos ni en el diccionario, se inserta en el índice de fallos y se
					//contabiliza.
					if (this->getNotFoundWords()->find(phraseWords[i])) {
						totalFailures++;
					} else {
						if (!this->getDictionary()->find(phraseWords[i])) {
							this->getNotFoundWords()->insert(phraseWords[i]);
							totalFailures++;
						} else {
							idTermino++;
							///////////////////// TEMPORAL ////////////////
							FixedLengthTRecord tRecord(20);
							tRecord.setTerm(phraseWords[i]);
							tRecord.setId(idTermino);
							T->putRecord(tRecord);
							OcurrenceFileRecord ocurrenceRecord;
							ocurrenceRecord.setTermId(idTermino);
							ocurrenceRecord.setDocId(totalQuotes);
							ocurrenceFile.putRecord(ocurrenceRecord);
							///////////////////////////////////////////////
						}
					}
				}
			}

			if (insertInHash) {
				this->getMemorableQuotes()->insert(phrase);
			}
		}

		//Se guardan las estadísticas.
		this->setNumberOfWords(totalWords);
		this->setNumberOfQuotes(totalQuotes);
		this->setNumberOfFailures(totalFailures);
		T->close();

		//Se genera el ranking de palabras.
		this->getDictionary()->exportar(RANKINGS_FILE_PATH);
		externalSorter.sort(RANKINGS_FILE_PATH,RANKINGS_FILE_PATH_ORDERED,true);
	} else {
		std::cout << "Archivo inexistente" << std::endl;
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
		std::cout << "No hay palabras no encontradas." << std::endl;
}

void StatisticsManager::printWordRanking(unsigned int rankingSize) {
	VariableLengthRecordSequentialFile<WordRankingRecord> wordRankingFile;
	WordRankingRecord record;
	unsigned int i = 0;

	if (rankingSize > 0) {
		wordRankingFile.open(RANKINGS_FILE_PATH_ORDERED);
		if (wordRankingFile.isFileExists()) {
			std::cout << TEXT_MOST_SEARCHED_WORDS_TITLE(StringUtilities::intToString(rankingSize)) << std::endl;
			while(!wordRankingFile.endOfFile()) {
				i++;
				record = wordRankingFile.getNextRecord();
				std::cout << TEXT_MOST_SEARCHED_WORDS_ITEM(StringUtilities::intToString(i + 1),record.getWord(),StringUtilities::intToString(record.getNumberOfSearches())) << std::endl;
			}
		} else {
			std::cout << "Error al intentar reportar el ranking de palabras" << std::endl;
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

	sorter.sort(OCURRENCE_FILE_PATH,OCURRENCE_FILE_PATH_ORDERED,false);
	ocurrenceFileOrdered.open(OCURRENCE_FILE_PATH_ORDERED);

	//asumo que el ID de la lista invertida es incremental.
	if (ocurrenceFileOrdered.isFileExists()) {
		while(!ocurrenceFileOrdered.endOfFile()) {
			ocurrenceRecord = ocurrenceFileOrdered.getNextRecord();
			if (idTermino != ocurrenceRecord.getTermId()) {
				idTermino = ocurrenceRecord.getTermId();
				//idListaInvertida = cosaQueHaceListasInvertidas.create(idTermino);
				this->getDictionary()->insert(ocurrenceRecord.getTermId(),this->T->getRecord(ocurrenceRecord.getTermId()).getTerm(),idListaInvertida);
				//cosaQueHacePorcionesDeFirmas.create(idTermino);
			}
			//cosaQueHaceListasInvertidas.add(idListaInvertida,idTermino,ocurrenceRecord.getDocId());
			//cosaQueHacePorcionesDeFirmas.add(idTermino,ocurrenceRecord.getDocId());
		}
	} else {
		//TODO este error debe estar en el open del archivo.
		std::cout << "Error al intentar abrir el archivo" << std::endl;
	}

}

void StatisticsManager::erasePhrase(unsigned int idPhrase) {
	WordNormalizer wordNormalizer;
	std::vector<std::string> phraseWords;
	std::string phrase;

	this->getMemorableQuotes()->getFrase(idPhrase,phrase);
	StringUtilities::splitString(phrase,phraseWords,QUOTES_WORDS_SEPARATOR);

	for (unsigned int i = 0; i < phraseWords[i].size(); i++) {
		phraseWords[i] = wordNormalizer.normalizeWord(phraseWords[i]);
		if ( (this->getStopWords().find(phraseWords[i]) != this->getStopWords().end()) && !(this->getNotFoundWords()->find(phraseWords[i])) ) {
			//habria que tener un find que devuelva el id de la frase y el id de la lista invertida en un objeto o similar.
			this->getDictionary()->find(phraseWords[i]);
			//cosaQueHaceListasInvertidas.delete(idListaInvertida,idTermino,docId);
			//cosaQueHacePorcionesDeFirmas.delete(idTermino,ocurrenceRecord.getDocId());
			//this->getDictionary()->erase(phraseWords[i]);
			this->setNumberOfWords(this->getNumberOfWords() - 1);
		}
	}
	this->setNumberOfQuotes(this->getNumberOfQuotes() - 1);
}

void StatisticsManager::addPhrase(std::string phrase) {
	WordNormalizer wordNormalizer;
	std::vector<std::string> phraseWords;

	StringUtilities::splitString(phrase,phraseWords,QUOTES_WORDS_SEPARATOR);

	for (unsigned int i = 0; i < phraseWords.size(); i++) {
		phraseWords[i] = wordNormalizer.normalizeWord(phraseWords[i]);
		if(this->getStopWords().find(phraseWords[i]) == this->getStopWords().end()) {
			this->setNumberOfWords(this->getNumberOfWords() + 1);
			if (this->getNotFoundWords()->find(phraseWords[i])) {
				//this->getNotFoundWords()->erase(phraseWords[i]));
			}
			if (!this->getDictionary()->find(phraseWords[i])) {
				this->setNumberOfFailures(this->getNumberOfFailures() + 1);
				this->getDictionary()->insert(phraseWords[i]);
				//cosaQueHaceListasInvertidas.add(idListaInvertida,idTermino,docId);
				//cosaQueHacePorcionesDeFirmas.add(idTermino,ocurrenceRecord.getDocId());
				///////////////////// TEMPORAL ////////////////
				FixedLengthTRecord tRecord(20);
				tRecord.setTerm(phraseWords[i]);
				//se necesita tener el ultimo id de termino
				//tRecord.setId(T->getLastRecordPosition() + 1);
				T->putRecord(tRecord);
				///////////////////////////////////////////////
			}
		}
	}

	this->getMemorableQuotes()->insert(phrase);
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
				<< HELP_TEXT_CALLHELP << std::endl
				<< std::endl
				<< HELP_TEXT_EXIT <<std::endl
				<< std::endl
				<< "Archivo de diccionario cargado: " << this->getInputDictionaryFilePath()
				<< std::endl
				<< "Archivo de frases célebres cargado: " << this->getInputMemorableQuotesFilePath()
				<< std::endl;
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
//			this->getDictionary()->clear();
			this->clearDictionary();
			this->clearStatistics();
			this->setInputDictionaryFilePath(commandParams[0]);
			this->createDictionary(true);
//			delete dictionary;
//			dictionary = new IndiceArbol(DICTIONARY_INDEX_FILE_PATH);
//			this->getDictionary()->createIndex(DICTIONARY_RANDOMIZED_ORDERED_FILE_PATH);
//			this->getMemorableQuotes()->clear();
//			delete memorableQuotes;
//			memorableQuotes = new Hash::DispersionEx(MEMORABLE_QUOTES_INDEX_FILE_PATH);
//			this->getNotFoundWords()->clear();
//			delete notFoundWords;
//			notFoundWords = new IndiceArbol(NOT_FOUND_WORDS_INDEX_FILE_PATH);
			if (this->getInputMemorableQuotesFilePath() != "") {
				this->clearNotFoundWords();
				this->loadMemorableQuotes(false);
			}
		}

		if (command == COMMAND_LOAD_MEMORABLE_QUOTES) {
//			this->getMemorableQuotes()->clear();
			this->clearNotFoundWords();
			this->clearMemorableQuotes();
			this->clearStatistics();
			this->setInputMemorableQuotesFilePath(commandParams[0]);
//			delete memorableQuotes;
//			memorableQuotes = new Hash::DispersionEx(MEMORABLE_QUOTES_NAME);
//			this->getNotFoundWords()->clear();
//			delete notFoundWords;
//			notFoundWords = new IndiceArbol(NOTFOUND_NAME);
			this->loadMemorableQuotes(true);
		}

		if (command == COMMAND_PRINT_HELP) {
			this->printHelp();
		}
	} else {
		std::cout << ERROR_TEXT_INVALID_COMMAND << command << std::endl;
	}
}

bool StatisticsManager::checkDirectoryStructure() {
	if(!FileUtilities::directoryExists(CONFIG_DIRECTORY_PATH)) {
		std::cout << INEXISTANT_CONFIG_DIRECTORY_INEXISTANT_ERROR << std::endl;
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

void StatisticsManager::insertPhrase(std::string phrase) {
/*	unsigned int phraseId = (this->getMemorableQuotes())->insert(phrase);
	std::vector<std::string> terms = tokenizePhrase(phrase);
	Phrase normalizedPhrase(terms, phraseId);
	BooleanIndex indice;
	TermMap	mapaDeTerminos;
	indice.insertPhrase(normalizedPhrase);
	mapaDeTerminos.insertPhrase(normalizedPhrase);
*/
}


StatisticsManager::~StatisticsManager() {
	this->saveStatus();
	delete this->getNotFoundWords();
	delete this->getDictionary();
	delete this->getMemorableQuotes();
}
