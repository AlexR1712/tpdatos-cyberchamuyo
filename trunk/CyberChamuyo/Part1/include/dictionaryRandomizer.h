#ifndef DICTIONARYRANDOMIZER_H_
#define DICTIONARYRANDOMIZER_H_

#include <string>

#include <random>
#include <chrono>


#ifndef RANDOM_RANGE_MIN
#define RANDOM_RANGE_MIN "randomRangeMin"
#endif /*RANDOM_RANGE_MIN*/

#ifndef RANDOM_RANGE_MAX
#define RANDOM_RANGE_MAX "randomRangeMax"
#endif /*RANDOM_RANGE_MAX*/

#ifndef OUTPUT_FILE_PATH_TEXT
#define OUTPUT_FILE_PATH_TEXT "outputFilePathText"
#endif /*OUTPUT_FILE_PATH_TEXT*/

#ifndef OUTPUT_FILE_PATH_BINARY
#define OUTPUT_FILE_PATH_BINARY "outputFilePathBinary"
#endif /*OUTPUT_FILE_PATH_BINARY*/

#ifndef OUTPUT_FILE_PATH_BINARY_ORDERED
#define OUTPUT_FILE_PATH_BINARY_ORDERED "outputFilePathBinaryOrdered"
#endif /*OUTPUT_FILE_PATH_BINARY_ORDERED*/

//Clase cuya función es aleatorizar un diccionario.
class DictionaryRandomizer {
private:
	//generador de números aleatorios.
	std::default_random_engine generator;

	unsigned int randomRangeMin;

	unsigned int randomRangeMax;

	std::string randomizedDictionaryAsTextFilePath;

	std::string randomizedDictionaryAsBinaryFilePath;

	std::string orderedRandomizedDictionaryFilePath;

	std::default_random_engine& getGenerator();

	unsigned int getRandomRangeMin() const;

	unsigned int getRandomRangeMax() const;

	std::string getRandomizedDictionaryAsTextFilePath() const;

	std::string getRandomizedDictionaryAsBinaryFilePath() const;

	//Metodo para crear un archivo de trabajo asignando a cada palabra del diccionario un ID aleatorio.
	void createRandomIds(std::string dictionaryPath);

	//Metodo para generar un ID aleatorio.
	long generateRandomId();

public:
	//Constructor
	DictionaryRandomizer();

	std::string getOrderedRandomizedDictionaryFilePath() const;

	//Metodo para aleatorizar el diccionario ubicado en dictionaryPath.
	void randomizeDictionary(std::string dictionaryPath, bool showId);

	//Destructor
	~DictionaryRandomizer();
};

#endif /* DICTIONARYRANDOMIZER_H_ */
