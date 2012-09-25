#ifndef WRITEBUFFER_H_
#define WRITEBUFFER_H_

#include <fstream>

#include "buffer.h"

template<class T> class WriteBuffer : public Buffer<T> {
private:
	void flush();
public:
	WriteBuffer();

	WriteBuffer(std::string filePath, unsigned int maxSize);

	void initialize(std::string filePath, unsigned int maxSize);

	void finalize();

	void putRecord(const T& record);

	~WriteBuffer();
};

template<class T> WriteBuffer<T>::WriteBuffer() {
}

template<class T> WriteBuffer<T>::WriteBuffer(std::string filePath, unsigned int maxSize):Buffer<T>(maxSize) {
	this->getFile().open(filePath.c_str(),std::iostream::out | std::iostream::binary);
}

template<class T> void WriteBuffer<T>::putRecord(const T& record) {
	this->push(record);
	if (this->size() == this->getMaxSize()) {
		this->flush();
	}
}

template<class T> void WriteBuffer<T>::flush() {
	Record* record = new T();

	while (this->size() > 0) {
		*record = this->getBuffer().front();
		this->getFile() << record->serialize() << std::endl;
		this->pop();
	}

	delete record;
}

template<class T> void WriteBuffer<T>::initialize(std::string filePath, unsigned int maxSize) {
	this->setMaxSize(maxSize);
	this->finalize();
	this->getFile().open(filePath.c_str(),std::iostream::out | std::iostream::binary);
}

template<class T> void WriteBuffer<T>::finalize() {
	this->flush();
	this->getFile().close();
}

template<class T> WriteBuffer<T>::~WriteBuffer() {
	this->finalize();
}

#endif /* WRITEBUFFER_H_ */
