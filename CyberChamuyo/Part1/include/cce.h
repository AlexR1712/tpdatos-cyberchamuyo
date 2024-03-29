﻿#ifndef CCE_H_
#define CCE_H_

#include <string>
#include <set>
#include <vector>

#include "outputTexts.h"
#include "IndiceArbol.h"
#include "DispersionEx.h"
#include "fixedLengthRecordSequentialFile.h"
#include "fixedLengthTextRecord.h"
#include "FixedLengthTRecord.h"
#include "fixedLengthRecord.h"
#include "OcurrenceFileRecord.h"
#include "BooleanIndex.h"
#include "SignaturePortionIndex.h"

#ifndef CONFIG_FILE_PATH
#define CONFIG_FILE_PATH "config/cce.properties"
#endif /*CONFIG_FILE_PATH*/

#ifndef T_RECORD_SIZE
#define T_RECORD_SIZE 50
#endif /*T_RECORD_SIZE*/

#ifndef CONFIG_DIRECTORY_PATH
#define CONFIG_DIRECTORY_PATH "config"
#endif /*CONFIG_DIRECTORY_PATH*/

#ifndef BIN_DIRECTORY_PATH
#define BIN_DIRECTORY_PATH "bin"
#endif /*BIN_DIRECTORY_PATH*/

#ifndef OUTPUT_FILES_DIRECTORY_PATH
#define OUTPUT_FILES_DIRECTORY_PATH "outputFiles"
#endif /*OUTPUT_FILES_DIRECTORY_PATH*/

#ifndef STOP_WORDS_FILE_PATH_PROPERTY_NAME
#define STOP_WORDS_FILE_PATH_PROPERTY_NAME "stopWordsFilePath"
#endif /*STOP_WORDS_FILE_PATH_PROPERTY_NAME*/

#ifndef STATUS_FILE_PATH
#define STATUS_FILE_PATH "bin/statisticsManagerStatus"
#endif /*STATUS_FILE_PATH*/

#ifndef RANKINGS_FILE_PATH
#define RANKINGS_FILE_PATH "bin/rankings.bin"
#endif /*RANKINGS_FILE_PATH*/

#ifndef RANKINGS_FILE_PATH_ORDERED
#define RANKINGS_FILE_PATH_ORDERED "bin/rankings_ordered.bin"
#endif /*RANKINGS_FILE_PATH_ORDERED*/

#ifndef DICTIONARY_INDEX_FILE_PATH
#define DICTIONARY_INDEX_FILE_PATH "bin/dic.bin"
#endif /*DICTIONARY_INDEX_FILE_PATH*/

#ifndef NOT_FOUND_WORDS_INDEX_FILE_PATH
#define NOT_FOUND_WORDS_INDEX_FILE_PATH "bin/notf.bin"
#endif /*NOT_FOUND_WORDS_INDEX_FILE_PATH*/

#ifndef MEMORABLE_QUOTES_INDEX_FILE_PATH
#define MEMORABLE_QUOTES_INDEX_FILE_PATH "bin/memquotes.bin"
#endif /*MEMORABLE_QUOTES_INDEX_FILE_PATH*/

#ifndef T_FILE_PATH
#define T_FILE_PATH "bin/tFile.bin"
#endif /*T_FILE_PATH*/

#ifndef	BOOLEAN_INDEX_FILE_NAME
#define BOOLEAN_INDEX_FILE_NAME "bin/invertedLists.bin"
#endif /*BOOLEAN_INDEX_FILE_NAME*/

#ifndef	BITSLICE_INDEX_FILE_NAME
#define BITSLICE_INDEX_FILE_NAME "bin/SignatureFile.bin"
#endif /*BITSLICE_INDEX_FILE_NAME*/

#ifndef OCURRENCE_FILE_PATH
#define OCURRENCE_FILE_PATH "bin/ocurrenceFile.bin"
#endif /*OCURRENCE_FILE_PATH*/

#ifndef OCURRENCE_FILE_PATH_ORDERED
#define OCURRENCE_FILE_PATH_ORDERED "bin/orderedOcurrenceFile.bin"
#endif /*OCURRENCE_FILE_PATH_ORDERED*/

//#ifndef DICTIONARY_RANDOMIZED_ORDERED_FILE_PATH
//#define DICTIONARY_RANDOMIZED_ORDERED_FILE_PATH "outputFiles/dictionary_RANDOMIZED_ORDERED"
//#endif /*DICTIONARY_RANDOMIZED_ORDERED_FILE_PATH*/
//
//#ifndef DICTIONARY_NORMALIZED_FILE_PATH
//#define DICTIONARY_NORMALIZED_FILE_PATH "outputFiles/dictionary_NORMALIZED.txt"
//#endif /*DICTIONARY_NORMALIZED_FILE_PATH*/

#ifndef AUTHOR_QUOTE_SEPARATOR
#define AUTHOR_QUOTE_SEPARATOR '\t'
#endif /*AUTHOR_QUOTE_SEPARATOR*/

#ifndef QUOTES_WORDS_SEPARATOR
#define QUOTES_WORDS_SEPARATOR ' '
#endif /*QUOTES_WORDS_SEPARATOR*/

//Clase para obtener las estadísticas solicitadas en el TP.
class CCE {
private:

//	unsigned int numberOfErasedQuotes;

	//Ubicacion del archivo de diccionario.
	std::string inputDictionaryFilePath;

	//Ubicacion del archivo de frases celebres.
	std::string inputMemorableQuotesFilePath;

	//Ubicacion del archivo de stopWords.
	std::string stopWordsFilePath;

	//Cantidad total de palabras.
	unsigned int numberOfWords;

	//Cantidad total de frases.
	unsigned int numberOfQuotes;

	//Cantidad total de fallas.
	unsigned int numberOfFailures;

	//Flag que indica si se está corriendo el programa por primera vez.
	bool firstRun;

	//Flag que indica si el componente se inicializó correctamente.
	bool successfullInit;

	//Stop words.
	std::set<std::string> stopWords;

	//Indice del diccionario.
	IndiceArbol* dictionary;

	//Indice de las frases celebres.
	Hash::DispersionEx* memorableQuotes;

	//Indice de palabras no encontradas.
	IndiceArbol* notFoundWords;

	FixedLengthRecordSequentialFile<FixedLengthTRecord>* T;

	BooleanIndex* booleanIndex;

	SignaturePortionIndex* sigPortionIndex;

	std::string getInputDictionaryFilePath() const;

	void setInputDictionaryFilePath(std::string dictionaryFilePath);

	std::string getInputMemorableQuotesFilePath() const;

	void setInputMemorableQuotesFilePath(std::string memorableQuotesFilePath);

	std::string getStopWordsFilePath() const;

	void setStopWordsFilePath(std::string stopWordsFilePath);

	unsigned int getNumberOfWords() const;

	void setNumberOfWords(unsigned int numberOfWords);

	unsigned int getNumberOfQuotes() const;

	void setNumberOfQuotes(unsigned int numberOfPhrases);

	unsigned int getNumberOfFailures() const;

	void setNumberOfFailures(unsigned int numberOfFailures);

	std::set<std::string>& getStopWords();

	IndiceArbol* getDictionary();

	Hash::DispersionEx* getMemorableQuotes();

	IndiceArbol* getNotFoundWords();

	BooleanIndex* getBooleanIndex() const;

	FixedLengthRecordSequentialFile<FixedLengthTRecord>* getT() const;

//	bool isFirstRun() const;

//	void setFirstRun(bool firstRun);

	//void setSuccessfullInit(bool successfullInit);

	//Metodo para cargar el estado del modulo desde un archivo.
	void loadStatus();

	//Metodo para cargar las stop words.
	void loadStopWords();

	//Metodo para crear el diccionario.
	void createDictionary();

	//Metodo para cargar las frases celebres.
	void loadMemorableQuotes();

	//Indica si el comando ingresado es valido.
	bool isValidCommand(std::string& command, std::vector<std::string>& commandParams);

	//Imprime por pantalla la cantidad de palabras promedio por frase.
	void printAverageWordsPerPhrase();

	//Imprime por pantalla la cantidad promedio de fallos.
	void printAverageFailures();

	//Imprime por pantalla las palabras no encontradas.
	void printNotFoundWords();

	//Imprime por pantalla el ranking de palabras mas buscadas.
	void printWordRanking(unsigned int rankingSize);

	//Metodo para guardar el estado del modulo en un archivo.
	void saveStatus();

	bool checkDirectoryStructure();

	//Metodo para limpiar las estadisticas.
	void clearStatistics();

	void clearDictionary();

	void clearNotFoundWords();

	void clearMemorableQuotes();

	void clearIndex();

	void clearTFile();

	void clearAll();

	void insertPhrase(std::string phrase);

	void erasePhrase(unsigned int phraseId);

	void index();

	std::vector<std::string> tokenizePhrase(std::string phrase);

	void addPhrase(std::string phrase);

	void search(std::vector<std::string>& terms, std::ostream& os);

	void searchSignature(std::vector<std::string>& terms, std::ostream& os);

	void modify(unsigned int phraseId, std::vector<std::string> modifiedPhrase);

	bool validateDataStructureIntegrity(std::string& filesToLoad);

public:
	//Constructor.
	CCE();

	bool isSuccessfullInit() const;

	//Metodo para procesar el comando recibido.
	void processCommand(std::string& command, std::vector<std::string>& commandParams);

	//Metodo para imprimir la ayuda.
	void printHelp();

	//Destructor.
	~CCE();
};

#endif /* CCE_H_ */
