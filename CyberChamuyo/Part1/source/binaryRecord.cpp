#include "binaryRecord.h"

#include <stdlib.h>
#include <iostream>

#include "stringUtilities.h"

BinaryRecord::BinaryRecord(bool idVisible):Record(idVisible) {
}

void BinaryRecord::parseString(std::string string) {
	std::vector<std::string> recordParams;

	splitString(string,recordParams,DEFAULT_SEPARATOR);
	if (recordParams.size() == 1)
		this->setWord(trim(recordParams[0]));
	else {
		this->setId(atol(recordParams[0].c_str()));
		this->setWord(trim(recordParams[1]));
	}
	this->setSizeInChar(SIZE_IN_CHAR);
}

std::string BinaryRecord::serialize() {
	std::string recordAsString;

	if (this->isIdVisible())
		recordAsString += intToString(this->getId()) + DEFAULT_SEPARATOR;
	recordAsString += this->getWord();

	return recordAsString.substr(0,this->getSizeInChar());
}

BinaryRecord::~BinaryRecord() {
}
