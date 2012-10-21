#include <string>
#include <ostream>
#include "dictionaryRecord.h"

#ifndef BINARYDICTIONARYRECORD_H_
#define BINARYDICTIONARYRECORD_H_

template<bool withId> class BinaryDictionaryRecord : public DictionaryRecord {
public:
	BinaryDictionaryRecord();

	void deserialize(std::string string);

	std::string serialize();

	virtual ~BinaryDictionaryRecord();
};

template<bool withId> BinaryDictionaryRecord<withId>::BinaryDictionaryRecord():DictionaryRecord(withId) {
}

template<bool withId> void BinaryDictionaryRecord<withId>::deserialize(std::string string) {
	std::vector<std::string> recordParams;

	if (this->getIdInFile()) {
		this->setId(*(reinterpret_cast<const unsigned long int*>((string.substr(0,sizeof(unsigned long int))).c_str())));
		this->setWord(string.substr(sizeof(unsigned long int)));
	} else {
		this->setWord(string);
	}

}

template<bool withId> std::string BinaryDictionaryRecord<withId>::serialize() {
	std::string recordAsString;
	const char* idAsCharArray;
	unsigned long int id;

	if (this->getIdInFile()) {
		id = this->getId();
		idAsCharArray = reinterpret_cast<const char*>(&id);
		recordAsString.append(idAsCharArray,sizeof(unsigned long int));
	}
	recordAsString += this->getWord();

	return recordAsString;
}

template<bool withId> BinaryDictionaryRecord<withId>::~BinaryDictionaryRecord() {
}

#endif /* BINARYGRECORD_H_ */
