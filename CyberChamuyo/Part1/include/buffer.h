#ifndef BUFFER_H_
#define BUFFER_H_

#include <string>
#include <fstream>
#include <queue>

#include "record.h"

template<class T> class Buffer {
private:
	std::fstream file;

	unsigned int maxSize;

	std::queue<T> buffer;
protected:
	std::fstream& getFile();

	std::queue<T>& getBuffer();

	const unsigned int getMaxSize() const;

	void setMaxSize(unsigned int maxSize);

	void push(const T& record);

	void pop();
public:
	Buffer(unsigned int maxSize = 0);

	virtual void initialize(std::string filePath, unsigned int maxSize) = 0;

	virtual void finalize() = 0;

	const unsigned int size();

	Record& front();

	bool empty();

	virtual ~Buffer() = 0;
};

template<class T> Buffer<T>::Buffer(unsigned int maxSize){
	this->maxSize = maxSize;
}

template<class T> std::queue<T>& Buffer<T>::getBuffer() {
	return this->buffer;
}

template<class T> std::fstream& Buffer<T>::getFile() {
	return this->file;
}

template<class T> const unsigned int Buffer<T>::getMaxSize() const {
	return this->maxSize;
}

template<class T> void Buffer<T>::setMaxSize(unsigned int maxSize) {
	this->maxSize = maxSize;
}

template<class T> const unsigned int Buffer<T>::size() {
	return this->getBuffer().size();
}

template<class T> void Buffer<T>::push(const T& record) {
	this->getBuffer().push(record);
}

template<class T> void Buffer<T>::pop() {
	this->getBuffer().pop();
}

template<class T> bool Buffer<T>::empty() {
	return (this->size() == 0);
}

template<class T> Record& Buffer<T>::front(){
	return this->getBuffer().front();
}

template<class T> Buffer<T>::~Buffer(){
}

#endif /* BUFFER_H_ */
