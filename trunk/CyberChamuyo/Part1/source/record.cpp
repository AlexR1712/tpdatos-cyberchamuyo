#include "record.h"

#include <stdlib.h>
#include <iostream>

#include "stringUtilities.h"

Record::Record(bool idVisible) {
	this->id = 0;
	this->idVisible = idVisible;
	this->sizeInChar = 0;
}

unsigned long int Record::getId() const {
	return id;
}

void Record::setId(unsigned long int id) {
	this->id = id;
}

const std::string& Record::getWord() const {
	return this->word;
}

void Record::setWord(const std::string& word) {
	this->word = word;
}

bool Record::isIdVisible() const {
    return idVisible;
}

void Record::setIdVisible(bool isIdVisible) {
	this->idVisible = isIdVisible;
}

unsigned short int Record::getSizeInChar() const {
	return this->sizeInChar;
}

void Record::setSizeInChar(unsigned short int sizeInChar) {
	this->sizeInChar = sizeInChar;
}

Record& Record::operator=(const Record& other) {
	this->setId(other.getId());
	this->setWord(other.getWord());
	this->setIdVisible(other.isIdVisible());
	this->setSizeInChar(other.getSizeInChar());
	return *this;
}

bool Record::operator>(const Record& other) {
	if (this->getId() > other.getId())
		return true;
	if ( (this->getId() == other.getId()) && (this->getWord().compare(other.getWord()) > 0) )
		return true;
	return false;
}

bool Record::operator<(const Record& other) {
	if (this->getId() < other.getId())
		return true;
	if ( (this->getId() == other.getId()) && (this->getWord().compare(other.getWord()) < 0) )
		return true;
	return false;
}

Record::~Record() {
}
