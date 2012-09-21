#include "buffer.h"

Buffer::Buffer(unsigned int maxSize){
	this->maxSize = maxSize;
}

std::queue<Record>& Buffer::getBuffer() {
	return this->buffer;
}

std::fstream& Buffer::getFile() {
	return this->file;
}

const unsigned int Buffer::size() {
	return this->getBuffer().size();
}

const unsigned int Buffer::getMaxSize() const {
	return this->maxSize;
}

void Buffer::push(const Record& record) {
	this->getBuffer().push(record);
}

void Buffer::pop() {
	this->getBuffer().pop();
}

bool Buffer::empty() {
	return (this->size() == 0);
}

Record& Buffer::front(){
	return this->getBuffer().front();
}

Buffer::~Buffer(){
}
