#ifndef DICTIONARYNORMALIZER_H_
#define DICTIONARYNORMALIZER_H_

#ifndef N
#define N 5
#endif /*N*/

#include <string>

class DictionayNormalizer {
private:
	std::string normalizeWord(const std::string& string) const;

public:
	DictionayNormalizer();

	void normalizeDictionary(std::string dictionaryPath);

	~DictionayNormalizer();
};


#endif /* DICTIONARYNORMALIZER_H_ */
