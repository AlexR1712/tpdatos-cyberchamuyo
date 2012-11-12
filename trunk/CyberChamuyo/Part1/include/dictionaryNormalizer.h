#ifndef DICTIONARYNORMALIZER_H_
#define DICTIONARYNORMALIZER_H_

#ifndef OUTPUT_FILE_PATH_PROPERTY_NAME
#define OUTPUT_FILE_PATH_PROPERTY_NAME "outputFilePath"
#endif /*OUTPUT_FILE_PATH_PROPERTY_NAME*/

#include <string>

//Clase cuya función es normalizar un diccionario.
class DictionaryNormalizer {
private:
	//Path del del archivo de salida.
	std::string outputFilePath;

	std::string getOutputFilePath() const;

public:
	//Constructor
	DictionaryNormalizer();

	//Metodo para normalizar el diccionario en la ubicacion indicada por diccionaryPath.
	void normalize(std::string dictionaryPath);

	//Destructor
	~DictionaryNormalizer();
};


#endif /* DICTIONARYNORMALIZER_H_ */
