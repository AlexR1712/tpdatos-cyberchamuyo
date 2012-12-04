#include "../include/wordRankingRecord.h"

#include <cstring>

WordRankingRecord::WordRankingRecord() {

}

void WordRankingRecord::serialize(std::vector<unsigned char>& recordAsCharVector) {
	unsigned char numberOfSearchesAsCharArray[sizeof(unsigned long int)];
	unsigned long int numberOfSearches;
	std::string word;

	recordAsCharVector.clear();
	numberOfSearches = this->getNumberOfSearches();
	memcpy(numberOfSearchesAsCharArray,reinterpret_cast<const unsigned char*>(&numberOfSearches),sizeof(unsigned long int));
	for (unsigned int i = 0; i < sizeof(unsigned long int); i++) {
		recordAsCharVector.push_back(numberOfSearchesAsCharArray[i]);
	}

	word = this->getWord();
	for (unsigned int i = 0; i < word.size(); i++) {
		recordAsCharVector.push_back(word[i]);
	}
}

void WordRankingRecord::deserialize(std::vector<unsigned char>& recordAsCharVector) {
	unsigned char numberOfSearchesAsCharArray[sizeof(unsigned long int)];
	std::string word;

	this->setRecordSize(recordAsCharVector.size());

	for (unsigned int i = 0; i < sizeof(unsigned long int); i++) {
		numberOfSearchesAsCharArray[i] = recordAsCharVector[i];
	}
	this->setNumberOfSearches(*(reinterpret_cast<const unsigned long int*>(numberOfSearchesAsCharArray)));

	for (unsigned int i = sizeof(unsigned long int); i < recordAsCharVector.size(); i++) {
		word += recordAsCharVector[i];
	}
	this->setWord(word);
}

unsigned long int WordRankingRecord::getNumberOfSearches() const {
	return this->numberOfSearches;
}

void WordRankingRecord::setNumberOfSearches(unsigned long int numberOfSearches) {
	this->numberOfSearches = numberOfSearches;
}

std::string WordRankingRecord::getWord() const {
	return this->word;
}

void WordRankingRecord::setWord(std::string word) {
	this->word = word;
}

WordRankingRecord& WordRankingRecord::operator=(const WordRankingRecord& other) {
	this->setRecordSize(other.getRecordSize());
	this->setNumberOfSearches(other.getNumberOfSearches());
	this->setWord(other.getWord());
	return *this;
}

bool WordRankingRecord::operator>(const WordRankingRecord& other) {
	if (this->getNumberOfSearches() < other.getNumberOfSearches())
		return true;
	if ( (this->getNumberOfSearches() == other.getNumberOfSearches()) && (this->getWord().compare(other.getWord()) > 0) )
		return true;
	return false;
}

bool WordRankingRecord::operator<(const WordRankingRecord& other) {
	if (this->getNumberOfSearches() > other.getNumberOfSearches())
		return true;
	if ( (this->getNumberOfSearches() == other.getNumberOfSearches()) && (this->getWord().compare(other.getWord()) > 0) )
		return true;
	return false;
}

WordRankingRecord::~WordRankingRecord() {
}
