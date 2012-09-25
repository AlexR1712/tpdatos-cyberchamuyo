#ifndef READBUFFER_H_
#define READBUFFER_H_

#include "buffer.h"
#include "record.h"

#include <fstream>
#include <iostream>

#ifndef FILE_BUFFER_SIZE
#define FILE_BUFFER_SIZE 25
#endif /*FILE_BUFFER_SIZE*/

template<class T> class ReadBuffer : public Buffer<T> {
private:
	void load();
public:
	ReadBuffer();

	ReadBuffer(std::string filePath, unsigned int maxSize);

	void initialize(std::string filePath, unsigned int maxSize);

	void finalize();

	T getRecord();

	~ReadBuffer();
};

template<class T> ReadBuffer<T>::ReadBuffer() {
}

template<class T> ReadBuffer<T>::ReadBuffer(std::string filePath, unsigned int maxSize):Buffer<T>(maxSize) {
	this->getFile().open(filePath.c_str(),std::iostream::in | std::iostream::binary);
	this->load();
}

template<class T> void ReadBuffer<T>:: ReadBuffer::load() {
	std::string line;
	char fileBuffer[FILE_BUFFER_SIZE];
	Record* record = new T();

	while ( (this->size() < this->getMaxSize()) && !(this->getFile().eof()) && !(this->getFile().fail())) {
		line = "";
		this->getFile().getline(fileBuffer,FILE_BUFFER_SIZE);
		line += fileBuffer;
		while (this->getFile().gcount() == FILE_BUFFER_SIZE) {
			this->getFile().getline(fileBuffer,FILE_BUFFER_SIZE);
			line += fileBuffer;
		}
		if (line.size() != 0) {
			record->parseString(line);
			this->push(*(static_cast<T*>(record)));
		}
	}
	delete record;
}

template<class T> T ReadBuffer<T>::getRecord() {
	T record;

	record = this->getBuffer().front();
	this->pop();
	if (this->size() == 0)
		this->load();

	return record;
}

template<class T> void ReadBuffer<T>::initialize(std::string filePath, unsigned int maxSize) {
	this->setMaxSize(maxSize);
	this->finalize();
	this->getFile().open(filePath.c_str(),std::iostream::in | std::iostream::binary);
	this->load();
}

template<class T> void ReadBuffer<T>::finalize() {
	while (this->size() > 0) {
		this->pop();
	}
	this->getFile().close();
}

template<class T> ReadBuffer<T>::~ReadBuffer() {
	this->finalize();
}

#endif /* READBUFFER_H_ */
