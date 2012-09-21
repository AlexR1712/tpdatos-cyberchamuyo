#include "readBuffer.h"

#include <fstream>

#include <iostream>

ReadBuffer::ReadBuffer(unsigned int maxSize):Buffer(maxSize) {
}

ReadBuffer::ReadBuffer(std::string filePath, unsigned int maxSize):Buffer(maxSize) {
	this->getFile().open(filePath.c_str(),std::iostream::in);
	this->load();
}

void ReadBuffer::load() {
	std::string line;
	Record record;

	while ( (this->size() < this->getMaxSize()) && std::getline(this->getFile(),line) && !(line.empty()) ) {
		std::cout << "cargando en readBuffer la linea: " << line << std::endl;
		record.parseString(line);
		this->push(record);
	}
}

Record ReadBuffer::getRecord() {
	Record record;

	record = this->getBuffer().front();
	this->pop();
	if (this->size() == 0)
		this->load();

	return record;
}

void ReadBuffer::initialize(std::string filePath) {
	this->finalize();
	this->getFile().open(filePath.c_str(),std::iostream::in);
	this->load();
}

void ReadBuffer::finalize() {
	while (this->size() > 0) {
		this->pop();
	}
	this->getFile().close();
}

ReadBuffer::~ReadBuffer() {
	this->finalize();
}
