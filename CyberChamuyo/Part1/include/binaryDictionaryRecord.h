#ifndef BINARYDICTIONARYRECORD_H_
#define BINARYDICTIONARYRECORD_H_

#include "dictionaryRecord.h"

#include <string>
#include <ostream>
#include <cstring>


//Clase que representa un registro de diccionario que se almacena de forma binaria.
template<bool withId> class BinaryDictionaryRecord : public DictionaryRecord {
public:
	//Constructor.
	BinaryDictionaryRecord();

	//Metodo para hidratar el objeto desde un string.
	void deserialize(std::vector<unsigned char>& recordAsCharVector);

	//Metodo para serializar el objeto a un string.
	void serialize(std::vector<unsigned char>& recordAsCharVector);

	//Destructor.
	virtual ~BinaryDictionaryRecord();
};

template<bool withId> BinaryDictionaryRecord<withId>::BinaryDictionaryRecord():DictionaryRecord(withId) {
}

template<bool withId> void BinaryDictionaryRecord<withId>::deserialize(std::vector<unsigned char>& recordAsCharVector) {
	std::string idAsString;
	std::string word;

	this->setRecordSize(recordAsCharVector.size());

	if (this->getIdInFile()) {
		for (unsigned int i = 0; i < sizeof(unsigned long int); i++) {
			idAsString += recordAsCharVector[i];
		}
		this->setId(*(reinterpret_cast<const unsigned long int*>(idAsString.c_str())));
	}

	for (unsigned int i = sizeof(unsigned long int); i < recordAsCharVector.size(); i++) {
		word += recordAsCharVector[i];
	}
	this->setWord(word);
}

template<bool withId> void BinaryDictionaryRecord<withId>::serialize(std::vector<unsigned char>& recordAsCharVector) {
	unsigned char idAsCharArray[sizeof(unsigned long int)];
//	int int_size = sizeof(int);
//	memcpy(buffer, reinterpret_cast<const unsigned char*>(&j), sizeof(int));

	unsigned long int id;
	std::string word;

	recordAsCharVector.clear();
	if (this->getIdInFile()) {
		id = this->getId();
		memcpy(idAsCharArray,reinterpret_cast<const unsigned char*>(&id),sizeof(unsigned long int));
		for (unsigned int i = 0; i < sizeof(unsigned long int); i++) {
			recordAsCharVector.push_back(idAsCharArray[i]);
		}
	}

	word = this->getWord();
	for (unsigned int i = 0; i < word.size(); i++) {
		recordAsCharVector.push_back(word[i]);
	}
}

template<bool withId> BinaryDictionaryRecord<withId>::~BinaryDictionaryRecord() {
}

#endif /* BINARYGRECORD_H_ */
