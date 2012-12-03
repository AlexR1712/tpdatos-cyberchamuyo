#include "../include/textRecord.h"

#include "../include/stringUtilities.h"

TextRecord::TextRecord() {
	this->setRecordSize(0);
}

std::string TextRecord::getData() const {
	return this->data;
}

void TextRecord::setData(std::string data) {
	this->data = data;
	this->setRecordSize(data.size());
}

TextRecord& TextRecord::operator=(const TextRecord& other) {
	this->setRecordSize(other.getRecordSize());
	this->setData(other.getData());
	return *this;
}

void TextRecord::deserialize(std::vector<unsigned char>& recordAsCharVector) {
	std::string recordAsString;

	for (unsigned int i = 0; i < recordAsCharVector.size(); i++) {
		recordAsString += recordAsCharVector[i];
	}
	this->setData(recordAsString);
	this->setRecordSize(recordAsCharVector.size());
}

void TextRecord::serialize(std::vector<unsigned char>& recordAsCharVector) {
	std::string recordAsString = this->getData();

	recordAsCharVector.clear();
	for (unsigned int i = 0; i < this->getRecordSize(); i++) {
		recordAsCharVector.push_back(recordAsString[i]);
	}
//	recordAsCharVector.push_back('\n');
}

TextRecord::~TextRecord() {
}
