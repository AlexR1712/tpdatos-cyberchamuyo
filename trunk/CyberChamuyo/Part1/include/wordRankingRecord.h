#ifndef WORDRANKINGRECORD_H_
#define WORDRANKINGRECORD_H_

#include "record.h"

#include <string>

class WordRankingRecord : public Record {
private:
	unsigned long int numberOfSearches;

	std::string word;

public:
	WordRankingRecord();

	unsigned long int getNumberOfSearches() const;

	void setNumberOfSearches(unsigned long int numberOfSearches);

	std::string getWord() const;

	void setWord(std::string word);

	void deserialize(std::vector<unsigned char>& recordAsCharVector);

	WordRankingRecord& operator=(const WordRankingRecord& other);

	bool operator>(const WordRankingRecord& other);

	bool operator<(const WordRankingRecord& other);

	void serialize(std::vector<unsigned char>& recordAsCharVector);

	~WordRankingRecord();
};

#endif /* WORDRANKINGRECORD_H_ */
