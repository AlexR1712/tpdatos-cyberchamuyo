#include "textRecord.h"

#include <stdlib.h>
#include <iostream>

#include "stringUtilities.h"

TextRecord::TextRecord() {
}

std::string TextRecord::getData() const {
	return this->data;
}

void TextRecord::setData(std::string data) {
	this->data = data;
}

TextRecord& TextRecord::operator=(const TextRecord& other) {
	this->setData(other.getData());
	return *this;
}

void TextRecord::deserialize(std::string string) {
	this->setData(string);
}

std::string TextRecord::serialize() {
	return this->getData();
}

TextRecord::~TextRecord() {
}
