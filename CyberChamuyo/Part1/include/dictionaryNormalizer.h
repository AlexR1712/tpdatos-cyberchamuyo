#ifndef DICTIONARYNORMALIZER_H_
#define DICTIONARYNORMALIZER_H_

#ifndef FILE_BUFFER_SIZE
#define FILE_BUFFER_SIZE 10
#endif /*FILE_BUFFER_SIZE*/

#ifndef CHAR_MAP_FILE_PATH
#define CHAR_MAP_FILE_PATH "config/dictionaryRandomizer/charMap"
#endif /*CHAR_MAP_FILE_PATH*/

#ifndef OUTPUT_FILE_PATH
#define OUTPUT_FILE_PATH "outputFiles/dictionary_NORMALIZED.txt"
#endif /*OUTPUT_FILE_PATH*/

#include <string>
#include <map>

//Clase cuya función es normalizar un diccionario.
class DictionaryNormalizer {
private:
	//Mapa de caracteres especiales a normalizar.
	std::map<std::wstring,char> charMap;

	std::map<std::wstring,char>& getCharMap();

	//Metodo para cargar el mapa de caracteres especiales a normalizar desde un archivo.
	void loadCharmap();

public:
	//Constructor
	DictionaryNormalizer();

	//Metodo para normalizar el diccionario en la ubicacion indicada por diccionaryPath.
	void normalize(std::string dictionaryPath);

	//Metodo para normalizar una palabra.
	std::string normalizeWord(const std::string string);

	//Destructor
	~DictionaryNormalizer();
};


#endif /* DICTIONARYNORMALIZER_H_ */
