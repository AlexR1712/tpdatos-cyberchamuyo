#ifndef DICTIONARYRANDOMIZER_H_
#define DICTIONARYRANDOMIZER_H_

#include <string>

#ifndef FILE_BUFFER_SIZE
#define FILE_BUFFER_SIZE 5
#endif /*FILE_BUFFER_SIZE*/

#ifndef OUTPUT_FILE_PATH_TEXT
#define OUTPUT_FILE_PATH_TEXT "dictionary_RANDOMIZED.txt"
#endif /*OUTPUT_FILE_PATH_TEXT*/

#ifndef OUTPUT_FILE_PATH_BINARY
#define OUTPUT_FILE_PATH_BINARY "dictionary_RANDOMIZED"
#endif /*OUTPUT_FILE_PATH_BINARY*/

class DictionayRandomizer {
private:
	void createRandomIds(std::string dictionaryPath);

public:
	DictionayRandomizer();

	void randomizeDictionary(std::string dictionaryPath, bool showId);

	~DictionayRandomizer();
};

#endif /* DICTIONARYRANDOMIZER_H_ */
