#include "stringRecord.h"

#include <stdlib.h>
#include <iostream>

#include "stringUtilities.h"

StringRecord::StringRecord(bool idVisible):Record(idVisible) {
}

void StringRecord::parseString(std::string string) {
	std::vector<std::string> recordParams;

	splitString(string,recordParams,DEFAULT_SEPARATOR);
	if (recordParams.size() == 1) {
		this->setWord(recordParams[0]);
		this->setSizeInChar(recordParams[0].size());
	} else {
		this->setId(atol(recordParams[0].c_str()));
		this->setWord(recordParams[1]);
		this->setSizeInChar(ID_AS_STRING_LENGTH + 1/*separator*/ + recordParams[1].size());
	}

}

std::string StringRecord::serialize() {
	std::string recordAsString;

	if (this->isIdVisible())
		recordAsString += leftPad(intToString(this->getId()),ID_PADDING_CHAR,ID_AS_STRING_LENGTH) + DEFAULT_SEPARATOR;
	recordAsString += this->getWord();

	return recordAsString;
}

StringRecord::~StringRecord() {
}
