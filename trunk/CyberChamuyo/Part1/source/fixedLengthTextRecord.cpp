#include "../include/fixedLengthTextRecord.h"

#include <stdlib.h>
#include <iostream>

#include "../include/stringUtilities.h"

FixedLengthTextRecord::FixedLengthTextRecord(unsigned int recordSize) : FixedLengthRecord(recordSize) {
}

std::string FixedLengthTextRecord::getData() const {
	return this->data;
}

void FixedLengthTextRecord::setData(std::string data) {
	this->data = data;
}

FixedLengthTextRecord& FixedLengthTextRecord::operator=(const FixedLengthTextRecord& other) {
	this->setRecordSize(other.getRecordSize());
	this->setData(other.getData());
	return *this;
}

void FixedLengthTextRecord::deserialize(std::vector<unsigned char>& recordAsCharVector) {
	std::string dataAsString;
	unsigned int size;

	size = recordAsCharVector[0];
	for (unsigned int i = 1; i <= size; i++) {
		dataAsString += recordAsCharVector[i];
	}

	this->setData(dataAsString);
}

void FixedLengthTextRecord::serialize(std::vector<unsigned char>& recordAsCharVector) {
	std::string dataAsString = this->getData();

	recordAsCharVector.clear();
	dataAsString = dataAsString.substr(0,this->getRecordSize() - 1);

	recordAsCharVector.push_back(this->getData().size());
	for (unsigned int i = 0; i < dataAsString.size(); i++) {
		recordAsCharVector.push_back(dataAsString[i]);
	}
}

FixedLengthTextRecord::~FixedLengthTextRecord() {
}
