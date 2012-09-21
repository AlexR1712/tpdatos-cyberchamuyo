#include "record.h"

#include <stdlib.h>
#include <iostream>

#include "stringUtilities.h"

Record::Record() {
	this->id = 0;
}

int Record::getId() const {
	return id;
}

void Record::setId(int id) {
	this->id = id;
}

const std::string& Record::getWord() const {
	return word;
}

void Record::setWord(const std::string& word) {
	this->word = word;
}

void Record::parseString(std::string string) {
	std::vector<std::string> recordParams;

	splitString(string,recordParams,'\t');

	this->setId(atoi(recordParams[0].c_str()));
	this->setWord(recordParams[1]);
}

Record& Record::operator=(const Record& other) {
	this->setId(other.getId());
	this->setWord(other.getWord());
	return *this;
}

bool Record::operator>(const Record& other) {
	if (this->getId() > other.getId())
		return true;
	if ( (this->getId() == other.getId()) && (this->getWord() > other.getWord()) )
		return true;
	return false;
}

bool Record::operator<(const Record& other) {
	if (this->getId() < other.getId())
		return true;
	if ( (this->getId() == other.getId()) && (this->getWord() < other.getWord()) )
		return true;
	return false;
}

std::ostream& operator<<(std::ostream& ostream, Record& record){
	ostream << leftPad(intToString(record.getId()),'0',9) + '\t' + record.getWord().substr(0,12) << std::endl;
	return ostream;
}

Record::~Record() {
}
