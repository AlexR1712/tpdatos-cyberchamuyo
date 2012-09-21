#include "writeBuffer.h"

#include <fstream>

WriteBuffer::WriteBuffer(unsigned int maxSize):Buffer(maxSize) {
}

WriteBuffer::WriteBuffer(std::string filePath, unsigned int maxSize):Buffer(maxSize) {
	this->getFile().open(filePath.c_str(),std::iostream::out | std::iostream::binary);
}

void WriteBuffer::putRecord(const Record& record) {
	this->push(record);
	if (this->size() == this->getMaxSize()) {
		this->flush();
	}
}

void WriteBuffer::flush() {
	while (this->size() > 0) {
		this->getFile() << this->getBuffer().front();
		this->pop();
	}
}

void WriteBuffer::initialize(std::string filePath) {
	this->finalize();
	this->getFile().open(filePath.c_str(),std::iostream::out | std::iostream::binary);
}

void WriteBuffer::finalize() {
	this->flush();
	this->getFile().close();
}

WriteBuffer::~WriteBuffer() {
	this->finalize();
}
