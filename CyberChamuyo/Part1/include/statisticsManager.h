#ifndef STATISTICSMANAGER_H_
#define STATISTICSMANAGER_H_

#include <string>
#include <set>
#include <vector>

#include "outputTexts.h"

#ifndef STATUS_FILE_PATH
#define STATUS_FILE_PATH "config//statisticsManager//statisticsManagerStatus"
#endif /*STATUS_FILE_PATH*/

#ifndef STOP_WORDS_FILE_PATH
#define STOP_WORDS_FILE_PATH "inputFiles//stop-words.txt"
#endif /*STOP_WORDS_FILE_PATH*/

#ifndef RANKINGS_FILE_PATH
#define RANKINGS_FILE_PATH "outputFiles//rankings"
#endif /*RANKINGS_FILE_PATH*/

#ifndef RANKINGS_FILE_PATH_ORDERED
#define RANKINGS_FILE_PATH_ORDERED "outputFiles//rankings_ordered"
#endif /*RANKINGS_FILE_PATH_ORDERED*/

#ifndef FILES_BUFFER_SIZE
#define FILES_BUFFER_SIZE 10
#endif /*FILES_BUFFER_SIZE*/

#ifndef AUTHOR_QUOTE_SEPARATOR
#define AUTHOR_QUOTE_SEPARATOR '\t'
#endif /*AUTHOR_QUOTE_SEPARATOR*/

#ifndef QUOTES_WORDS_SEPARATOR
#define QUOTES_WORDS_SEPARATOR ' '
#endif /*QUOTES_WORDS_SEPARATOR*/

class StatisticsManager {
private:
	std::string dictionaryFilePath;

	std::string memorableQuotesFilePath;

	unsigned int numberOfWords;

	unsigned int numberOfQuotes;

	unsigned int numberOfFailures;

	//Es un set porque la búsqueda es generalmente mas rápida que la búsqueda binaria en un vector.
	//TODO Mariano. Corregir la configuración del proyecto para usar unordered_set que debería ser aun mas rápido.
	std::set<std::string> stopWords;

	//A falta de mejores nombres por ahora
	//ObjetoDeSeba dictionary;

	//A falta de mejores nombres por ahora
	//ObjetoDeLucas memorableQuotes;

	//ObjetoDeSeba notFoundWords;

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

	//ObjetoDeSeba& getDictionary();

	//ObjetoDeLucas& getMemorableQuotes();

	//ObjetoDeSeba& getNotFoundWords();

	void loadStatus();

	void loadStopWords();

	void createDictionary(bool force);

	void loadMemorableQuotes(bool insertInHash);

	void clearStatistics();

	bool isValidCommand(std::string& command, std::vector<std::string>& commandParams);

	void printAverageWordsPerPhrase();

	void printAverageFailures();

	void printNotFoundWords();

	void printWordRanking(unsigned int rankingSize);

	void saveStatus();

public:
	StatisticsManager();

	void processCommand(std::string& command, std::vector<std::string>& commandParams);

	void printHelp();

	~StatisticsManager();
};

#endif /* STATISTICSMANAGER_H_ */
