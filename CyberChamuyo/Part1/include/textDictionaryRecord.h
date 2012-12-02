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

//Clase que representa un registro de diccionario que se almacena de forma de texto.
template<bool withId> class TextDictionaryRecord : public DictionaryRecord {
public:
	//Constructor.
	TextDictionaryRecord();

	//Metodo para hidratar el objeto desde un string.
	void deserialize(std::vector<unsigned char>& recordAsCharVector);

	//Metodo para serializar el objeto a un string.
	void serialize(std::vector<unsigned char>& recordAsCharVector);

	//Destructor.
	virtual ~TextDictionaryRecord();
};

template<bool withId> TextDictionaryRecord<withId>::TextDictionaryRecord():DictionaryRecord(withId) {
}

template<bool withId> void TextDictionaryRecord<withId>::deserialize(std::vector<unsigned char>& recordAsCharVector) {
	std::vector<std::string> recordParams;
	std::string string;

	for (unsigned int i = 0; i < recordAsCharVector.size(); i++) {
		string += recordAsCharVector[i];
	}

	if (this->getIdInFile()) {
		StringUtilities::splitString(string,recordParams,SEPARATOR);
		this->setId(atol(recordParams[0].c_str()));
		this->setWord(recordParams[1]);
	} else {
		this->setWord(string);
	}
}

template<bool withId> void TextDictionaryRecord<withId>::serialize(std::vector<unsigned char>& recordAsCharVector) {
	std::string recordAsString;

	if (this->getIdInFile())
		recordAsString += StringUtilities::padLeft(StringUtilities::intToString(this->getId()),ID_PADDING_CHAR,ID_LENGTH) + SEPARATOR;
	recordAsString += this->getWord();

	recordAsCharVector.clear();
	for (unsigned int i = 0; i < recordAsString.size(); i++) {
		recordAsCharVector.push_back(recordAsString[i]);
	}
}

template<bool withId> TextDictionaryRecord<withId>::~TextDictionaryRecord() {
}

#endif /* TEXTDICTIONARYRECORD_H_ */
