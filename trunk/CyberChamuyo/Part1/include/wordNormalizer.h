#ifndef WORDNORMALIZER_H_
#define WORDNORMALIZER_H_

#ifndef CHAR_MAP_FILE_PATH_PROPERTY_NAME
#define CHAR_MAP_FILE_PATH_PROPERTY_NAME "charMapFilePath"
#endif /*CHAR_MAP_FILE_PATH_PROPERTY_NAME*/

#include <string>
#include <unordered_map>

//Clase cuya función es normalizar un diccionario.
class WordNormalizer {
private:
	//Path del archivo que contiene el mapa de caracteres utilizado para normalizar palabras.
	std::string charMapFilePath;

	//Mapa de caracteres especiales a normalizar.
	std::unordered_map<char,char> charMap;

	std::string getCharMapFilePath() const;

	std::unordered_map<char,char>& getCharMap();

	//Metodo para cargar el mapa de caracteres especiales a normalizar desde un archivo.
	void loadCharmap();

public:
	//Constructor
	WordNormalizer();

	//Metodo para normalizar una palabra.
	std::string normalizeWord(const std::string string);

	//Destructor
	~WordNormalizer();
};


#endif /* WORDNORMALIZER_H_ */
