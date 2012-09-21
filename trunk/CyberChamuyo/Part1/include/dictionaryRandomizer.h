#ifndef DICTIONARYRANDOMIZER_H_
#define DICTIONARYRANDOMIZER_H_

#include <string>

#ifndef RANDOM_STARTS_AT
#define RANDOM_STARTS_AT 1000
#endif /*RANDOM_STARTS_AT*/

#ifndef REGISTER_SIZE_IN_CHARS
#define REGISTER_SIZE_IN_CHARS 22
#endif /*REGISTER_SIZE_IN_CHARS*/

class DictionayRandomizer {
public:
	DictionayRandomizer();

	void randomizeDictionary(std::string dictionaryPath);

	~DictionayRandomizer();
};

#endif /* DICTIONARYRANDOMIZER_H_ */
