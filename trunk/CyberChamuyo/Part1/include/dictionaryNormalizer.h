#ifndef DICTIONARYNORMALIZER_H_
#define DICTIONARYNORMALIZER_H_

#ifndef FILE_BUFFER_SIZE
#define FILE_BUFFER_SIZE 10
#endif /*FILE_BUFFER_SIZE*/

#ifndef OUTPUT_FILE_PATH
#define OUTPUT_FILE_PATH "dictionary_NORMALIZED.txt"
#endif /*OUTPUT_FILE_PATH*/

#include <string>

class DictionaryNormalizer {
private:
	std::string normalizeWord(const std::string& string) const;

public:
	DictionaryNormalizer();

	void normalize(std::string dictionaryPath);

	~DictionaryNormalizer();
};


#endif /* DICTIONARYNORMALIZER_H_ */
