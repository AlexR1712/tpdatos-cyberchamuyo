#include "../include/logRecord.h"

#include <iostream>

#include "../include/stringUtilities.h"

LogRecord::LogRecord() {
}

LogRecord::LogRecord(std::string title, std::string itemName) {
	this->title = title;
	this->itemName = itemName;
}

std::string LogRecord::getTitle() const {
	return this->title;
}

void LogRecord::setTitle(std::string title) {
	this->title = title;
}

std::string LogRecord::getItemName() const {
	return this->itemName;
}

void LogRecord::setItemName(std::string itemName) {
	this->itemName = itemName;
}

std::vector<unsigned int>& LogRecord::getLogItems() {
	return this->logItems;
}

void LogRecord::serialize(std::vector<unsigned char>& recordAsCharVector) {
	std::string recordAsString = this->getTitle() + ": " + '\n';

	if (this->getLogItems().size() == 0) {
		recordAsString += " -" + '\n';
	} else {
		for (unsigned int i = 0; i < this->getLogItems().size(); i++) {
			recordAsString += this->getItemName() + " " + StringUtilities::intToString(i + 1) + " - " + StringUtilities::intToString(this->getLogItems()[i]) + '\n';
		}
	}

	recordAsCharVector.clear();
	for (unsigned int i = 0; i < recordAsString.size(); i++) {
		recordAsCharVector.push_back(recordAsString[i]);
	}
}

void LogRecord::deserialize(std::vector<unsigned char>& recordAsCharVector) {
}

LogRecord& LogRecord::operator=(LogRecord& other) {
	this->setTitle(other.getTitle());
	this->setItemName(other.getItemName());
	this->getLogItems().assign(other.getLogItems().begin(),other.getLogItems().end());
	return *this;
}


LogRecord::~LogRecord() {
}
