#ifndef STATISTICSMANAGER_H_
#define STATISTICSMANAGER_H_

#include <string>
#include <set>
#include <vector>

#include "outputTexts.h"
#include "IndiceArbol.h"
#include "DispersionEx.h"

#ifndef OUTPUT_DIRECTORY_PATH
#define OUTPUT_DIRECTORY_PATH "outputFiles"
#endif

#ifndef INPUT_DIRECTORY_PATH
#define INPUT_DIRECTORY_PATH "inputFiles"
#endif

#ifndef CONFIG_DIRECTORY_PATH
#define CONFIG_DIRECTORY_PATH "config"
#endif

#ifndef STATUS_FILE_PATH
#define STATUS_FILE_PATH "config/statisticsManager/statisticsManagerStatus"
#endif /*STATUS_FILE_PATH*/

#ifndef STOP_WORDS_FILE_PATH
#define STOP_WORDS_FILE_PATH "inputFiles/stop-words.txt"
#endif /*STOP_WORDS_FILE_PATH*/

#ifndef RANKINGS_FILE_PATH
#define RANKINGS_FILE_PATH "outputFiles/rankings"
#endif /*RANKINGS_FILE_PATH*/

#ifndef RANKINGS_FILE_PATH_ORDERED
#define RANKINGS_FILE_PATH_ORDERED "outputFiles/rankings_ordered"
#endif /*RANKINGS_FILE_PATH_ORDERED*/

#ifndef DICTIONARY_RANDOMIZED_ORDERED_FILE_PATH
#define DICTIONARY_RANDOMIZED_ORDERED_FILE_PATH "outputFiles/dictionary_RANDOMIZED_ORDERED"
#endif /*DICTIONARY_RANDOMIZED_ORDERED_FILE_PATH*/

#ifndef DICTIONARY_NORMALIZED_FILE_PATH
#define DICTIONARY_NORMALIZED_FILE_PATH "outputFiles/dictionary_NORMALIZED.txt"
#endif /*DICTIONARY_NORMALIZED_FILE_PATH*/

#ifndef DICTIONARY_NAME
#define DICTIONARY_NAME "dic.bin"
#endif /*DICTIONARY_NAME*/

#ifndef NOTFOUND_NAME
#define NOTFOUND_NAME "notf.bin"
#endif /*NOTFOUND_NAME*/

#ifndef MEMORABLE_QUOTES_NAME
#define MEMORABLE_QUOTES_NAME "memquotes.bin"
#endif /*MEMORABLE_QUOTES_NAME*/

#ifndef FILES_BUFFER_SIZE
#define FILES_BUFFER_SIZE 10
#endif /*FILES_BUFFER_SIZE*/

#ifndef AUTHOR_QUOTE_SEPARATOR
#define AUTHOR_QUOTE_SEPARATOR '\t'
#endif /*AUTHOR_QUOTE_SEPARATOR*/

#ifndef QUOTES_WORDS_SEPARATOR
#define QUOTES_WORDS_SEPARATOR ' '
#endif /*QUOTES_WORDS_SEPARATOR*/

//Clase para obtener las estadísticas solicitadas en el TP.
class StatisticsManager {
private:
	//Ubicacion del archivo de diccionario.
	std::string dictionaryFilePath;

	//Ubicacion del archivo de frases celebres.
	std::string memorableQuotesFilePath;

	//Cantidad total de palabras.
	unsigned int numberOfWords;

	//Cantidad total de frases.
	unsigned int numberOfQuotes;

	//Cantidad total de fallas.
	unsigned int numberOfFailures;

	//Stop words.
	std::set<std::string> stopWords;

	//Indice del diccionario.
	IndiceArbol* dictionary;

	//Indice de las frases celebres.
	Hash::DispersionEx* memorableQuotes;

	//Indice de palabras no encontradas.
	IndiceArbol* notFoundWords;

	std::string getDictionaryFilePath() const;

	void setDictionaryFilePath(std::string dictionaryFilePath);

	std::string getMemorableQuotesFilePath() const;

	void setMemorableQuotesFilePath(std::string memorableQuotesFilePath);

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

	//Metodo para cargar el estado del modulo desde un archivo.
	void loadStatus();

	//Metodo para cargar las stop words.
	void loadStopWords();

	//Metodo para crear el diccionario.
	void createDictionary(bool force);

	//Metodo para cargar las frases celebres.
	void loadMemorableQuotes(bool insertInHash);

	//Metodo para limpiar las estadisticas.
	void clearStatistics();

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

	void checkDirectoryStructure();
public:
	//Constructor.
	StatisticsManager();

	//Metodo para procesar el comando recibido.
	void processCommand(std::string& command, std::vector<std::string>& commandParams);

	//Metodo para imprimir la ayuda.
	void printHelp();

	//Destructor.
	~StatisticsManager();
};

#endif /* STATISTICSMANAGER_H_ */
