#ifndef DICTIONARYNORMALIZER_H_
#define DICTIONARYNORMALIZER_H_

#include <string>

class DictionayNormalizer {
private:
	void normalizeWord(std::string& string);

public:
	DictionayNormalizer();

	void normalizeDictionary(std::string dictionaryPath);

	~DictionayNormalizer();
};


#endif /* DICTIONARYNORMALIZER_H_ */
