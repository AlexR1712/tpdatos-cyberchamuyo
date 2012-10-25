#include <string>
#include <ostream>
#include <stdlib.h>
#include "dictionaryRecord.h"
#include "stringUtilities.h"

#ifndef TEXTDICTIONARYRECORD_H_
#define TEXTDICTIONARYRECORD_H_

#ifndef ID_LENGTH
#define ID_LENGTH 9
#endif /*ID_LENGTH*/

#ifndef ID_PADDING_CHAR
#define ID_PADDING_CHAR '0'
#endif /*ID_PADDING_CHAR*/

#ifndef SEPARATOR
#define SEPARATOR '\t'
#endif /*SEPARATOR*/

template<bool withId> class TextDictionaryRecord : public DictionaryRecord {
public:
	TextDictionaryRecord();

	void deserialize(std::string string);

	std::string serialize();

	virtual ~TextDictionaryRecord();
};

template<bool withId> TextDictionaryRecord<withId>::TextDictionaryRecord():DictionaryRecord(withId) {
}

template<bool withId> void TextDictionaryRecord<withId>::deserialize(std::string string) {
	std::vector<std::string> recordParams;

	if (this->getIdInFile()) {
		StringUtilities::splitString(string,recordParams,SEPARATOR);
		this->setId(atol(recordParams[0].c_str()));
		this->setWord(recordParams[1]);
	} else {
		this->setWord(string);
	}
}

template<bool withId> std::string TextDictionaryRecord<withId>::serialize() {
	std::string recordAsString;

	if (this->getIdInFile())
		recordAsString += StringUtilities::padLeft(StringUtilities::intToString(this->getId()),ID_PADDING_CHAR,ID_LENGTH) + SEPARATOR;
	recordAsString += this->getWord();

	return recordAsString;
}

template<bool withId> TextDictionaryRecord<withId>::~TextDictionaryRecord() {
}

#endif /* TEXTDICTIONARYRECORD_H_ */
