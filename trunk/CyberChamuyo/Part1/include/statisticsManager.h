#ifndef STATISTICSMANAGER_H_
#define STATISTICSMANAGER_H_

#include <string>
#include <set>
#include <vector>

#ifndef COMMAND_PRINT_AVG_WORDS_PER_PHRASE
#define COMMAND_PRINT_AVG_WORDS_PER_PHRASE "palabrasPromedio"
#endif /*COMMAND_PRINT_AVG_WORDS_PER_PHRASE*/

#ifndef COMMAND_PRINT_AVG_FAILURES
#define COMMAND_PRINT_AVG_FAILURES "fallosPromedio"
#endif /*COMMAND_PRINT_AVG_FAILURES*/

#ifndef COMMAND_PRINT_NOT_FOUND_WORDS
#define COMMAND_PRINT_NOT_FOUND_WORDS "palabrasNoEncontradas"
#endif /*COMMAND_PRINT_NOT_FOUND_WORDS*/

#ifndef COMMAND_PRINT_WORD_RANKING
#define COMMAND_PRINT_WORD_RANKING "palabrasMasBuscadas"
#endif /*COMMAND_PRINT_WORD_RANKING*/

#ifndef COMMAND_LOAD_DICTIONARY
#define COMMAND_LOAD_DICTIONARY "cargaDiccionario"
#endif /*COMMAND_LOAD_DICTIONARY*/

#ifndef COMMAND_LOAD_PHRASES
#define COMMAND_LOAD_PHRASES "cargaFrases"
#endif /*COMMAND_LOAD_PHRASES*/

#ifndef COMMAND_PRINT_HELP
#define COMMAND_PRINT_HELP "ayuda"
#endif /*COMMAND_PRINT_HELP*/

#ifndef ERROR_TEXT_INVALID_COMMAND
#define ERROR_TEXT_INVALID_COMMAND "Comando invalido"
#endif /*ERROR_TEXT_INVALID_COMMAND*/

#ifndef HELP_TITLE
#define HELP_TITLE "Ayuda:"
#endif /*HELP_TITLE*/

#ifndef HELP_TEXT_AVG_WORDS_PER_PHRASE
#define HELP_TEXT_AVG_WORDS_PER_PHRASE "	palabrasPromedio: Muestra la cantidad de palabras promedio por frase."
#endif /*HELP_TEXT_AVG_WORDS_PER_PHRASE*/

#ifndef HELP_TEXT_AVG_FAILURES
#define HELP_TEXT_AVG_FAILURES "	fallosPromedio: Muestra la cantidad de fallos promedio."
#endif /*HELP_TEXT_AVG_FAILURES*/

#ifndef HELP_TEXT_NOT_FOUND_WORDS
#define HELP_TEXT_NOT_FOUND_WORDS "	palabrasNoEncontradas: Muestra el listado de palabras no encontradas."
#endif /*HELP_TEXT_NOT_FOUND_WORDS*/

#ifndef HELP_TEXT_WORD_RANKING
#define HELP_TEXT_WORD_RANKING "	palabrasMasBuscadas N: Muestra el ranking de las N palabras mas buscadas."
#endif /*HELP_TEXT_WORD_RANKING*/

#ifndef HELP_TEXT_LOAD_DICTIONARY
#define HELP_TEXT_LOAD_DICTIONARY "	cargaDiccionario path: Cargar un nuevo diccionario ubicado en la ruta espedificada."
#endif /*HELP_TEXT_LOAD_DICTIONARY*/

#ifndef HELP_TEXT_LOAD_PHRASES
#define HELP_TEXT_LOAD_PHRASES "	cargaFrases path: Cargar un nuevo archivo de frases ubicado en la ruta especificada."
#endif /*HELP_TEXT_LOAD_PHRASES*/

#ifndef HELP_TEXT_CALLHELP
#define HELP_TEXT_CALLHELP "	ayuda: reimprimir esta ayuda."
#endif /*HELP_TEXT_CALLHELP*/

#ifndef HELP_TEXT_EXIT
#define HELP_TEXT_EXIT "	salir: abandonar la aplicación."
#endif /*HELP_TEXT_EXIT*/


class StatisticsManager {
private:
	//A falta de mejores nombres por ahora
	//ObjetoDeSeba dictionary;

	//A falta de mejores nombres por ahora
	//ObjetoDeLucas phrases;

	//TODO definir si se usa este objeto o el hashing.
	//ObjetoDeSeba notFoundWords;

	//Es un set porque la búsqueda es generalmente mas rápida que la búsqueda binaria en un vector.
	//TODO Mariano. Corregir la configuración del proyecto para usar unordered_set que debería ser aun mas rápido.
	std::set<std::string> stopWords;

	float averageWordsPerPhrase;

	float averageFailures;

	std::set<std::string>& getStopWords();

	//ObjetoDeSeba& getDictionary();

	//ObjetoDeLucas& getPhrases();

	//ObjetoDeSeba& notFoundWords;

	float getAverageWordsPerPhrase() const;

	void setAverageWordsPerPhrase(float averageWordsPerPhrase);

	float getAverageFailures() const;

	void setAverageFailures(float averageFailures);

	void loadStopWords();

	void initializeIndexes(std::string dictionaryFilePath = "dictionary.txt");

	bool isValidCommand(std::string& command, std::vector<std::string>& commandParams);

	//ver de ponerle un nombre mejor
	void createPhrases(std::string phrasesFilePath = "frases-celebres.txt");

	void printAverageWordsPerPhrase();

	void printAverageFailures();

	void printNotFoundWords();

	void printWordRanking(unsigned int rankingSize);

public:
	StatisticsManager();

	void processCommand(std::string& command, std::vector<std::string>& commandParams);

	void printHelp();

	~StatisticsManager();
};

#endif /* STATISTICSMANAGER_H_ */
