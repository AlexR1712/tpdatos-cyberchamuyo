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

class DictionaryNormalizer {
private:
	std::map<std::wstring,std::string> charMap;

	std::map<std::wstring,std::string>& getCharMap();

	void loadCharmap();

	std::string normalizeWord(const std::string string);

public:
	DictionaryNormalizer();

	void normalize(std::string dictionaryPath);

	~DictionaryNormalizer();
};


#endif /* DICTIONARYNORMALIZER_H_ */
