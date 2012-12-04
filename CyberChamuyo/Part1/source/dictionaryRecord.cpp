#include "../include/dictionaryRecord.h"

#include <stdlib.h>
#include <iostream>

#include "../include/stringUtilities.h"

DictionaryRecord::DictionaryRecord(bool withId) {
	this->id = 0;
	this->idInFile = withId;
	this->setRecordSize(sizeof(unsigned long int));
}

unsigned long int DictionaryRecord::getId() const {
	return this->id;
}

void DictionaryRecord::setId(unsigned long int id) {
	this->id = id;
}

const std::string DictionaryRecord::getWord() const {
	return this->word;
}

void DictionaryRecord::setWord(const std::string word) {
	this->word = word;
	this->setRecordSize(sizeof(unsigned long int) + word.size());
}

bool DictionaryRecord::getIdInFile() const {
	return this->idInFile;
}

void DictionaryRecord::setIdInFile(bool withId) {
	this->idInFile = withId;
}

DictionaryRecord& DictionaryRecord::operator=(const DictionaryRecord& other) {
	this->setRecordSize(other.getRecordSize());
	this->setId(other.getId());
	this->setWord(other.getWord());
	return *this;
}

bool DictionaryRecord::operator>(const DictionaryRecord& other) {
	if (this->getId() > other.getId())
		return true;
	if ( (this->getId() == other.getId()) && (this->getWord().compare(other.getWord()) > 0) )
		return true;
	return false;
}

bool DictionaryRecord::operator<(const DictionaryRecord& other) {
	if (this->getId() < other.getId())
		return true;
	if ( (this->getId() == other.getId()) && (this->getWord().compare(other.getWord()) < 0) )
		return true;
	return false;
}

DictionaryRecord::~DictionaryRecord() {
}
