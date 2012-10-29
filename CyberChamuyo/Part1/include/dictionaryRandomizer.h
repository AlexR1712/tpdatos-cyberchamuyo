#ifndef DICTIONARYRANDOMIZER_H_
#define DICTIONARYRANDOMIZER_H_

#include <string>

#include <random>
#include <chrono>


#ifndef RANDOM_RANGE_MIN
#define RANDOM_RANGE_MIN 1
#endif /*RANDOM_RANGE_MIN*/

#ifndef RANDOM_RANGE_MAX
#define RANDOM_RANGE_MAX 999999999
#endif /*RANDOM_RANGE_MAX*/

#ifndef FILE_BUFFER_SIZE
#define FILE_BUFFER_SIZE 5
#endif /*FILE_BUFFER_SIZE*/

#ifndef OUTPUT_FILE_PATH_TEXT
#define OUTPUT_FILE_PATH_TEXT "outputFiles/dictionary_RANDOMIZED.txt"
#endif /*OUTPUT_FILE_PATH_TEXT*/

#ifndef OUTPUT_FILE_PATH_BINARY
#define OUTPUT_FILE_PATH_BINARY "outputFiles/dictionary_RANDOMIZED"
#endif /*OUTPUT_FILE_PATH_BINARY*/

#ifndef OUTPUT_FILE_PATH_BINARY_ORDERED
#define OUTPUT_FILE_PATH_BINARY_ORDERED "outputFiles/dictionary_RANDOMIZED_ORDERED"
#endif /*OUTPUT_FILE_PATH_BINARY_ORDERED*/

//Clase cuya función es aleatorizar un diccionario.
class DictionayRandomizer {
private:
	//generador de números aleatorios.
	std::default_random_engine generator;

	std::default_random_engine& getGenerator();

	//Metodo para crear un archivo de trabajo asignando a cada palabra del diccionario un ID aleatorio.
	void createRandomIds(std::string dictionaryPath);

	//Metodo para generar un ID aleatorio.
	long generateRandomId();

public:
	//Constructor
	DictionayRandomizer();

	//Metodo para aleatorizar el diccionario ubicado en dictionaryPath.
	void randomizeDictionary(std::string dictionaryPath, bool showId);

	//Destructor
	~DictionayRandomizer();
};

#endif /* DICTIONARYRANDOMIZER_H_ */
