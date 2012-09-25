#ifndef DICTIONARYRANDOMIZER_H_
#define DICTIONARYRANDOMIZER_H_

#include <string>

#ifndef N
#define N 5
#endif /*N*/

class DictionayRandomizer {
public:
	DictionayRandomizer();

	void randomizeDictionary(std::string dictionaryPath, bool showId);

	~DictionayRandomizer();
};

#endif /* DICTIONARYRANDOMIZER_H_ */
