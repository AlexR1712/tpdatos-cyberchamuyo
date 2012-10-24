#ifndef SEQUENTIALFILE_H_
#define SEQUENTIALFILE_H_

#include <fstream>
#include <queue>

template<class T> class SequentialFile {
private:
	std::fstream file;

	std::queue<T> buffer;

	unsigned int bufferMaxSize;

protected:
	std::fstream& getFile();

	std::queue<T>& getBuffer();

	const unsigned int getBufferMaxSize() const;

	void setBufferMaxSize(unsigned int bufferMaxSize);

	const bool isBufferEmpty();

public:
	SequentialFile();

	virtual void open(std::string filePath, unsigned int maxSize) = 0;

	virtual void close() = 0;

	const bool endOfFile();

	const bool fail();

	virtual ~SequentialFile() = 0;
};

template<class T> SequentialFile<T>::SequentialFile(){
}

template<class T> std::queue<T>& SequentialFile<T>::getBuffer() {
	return this->buffer;
}

template<class T> std::fstream& SequentialFile<T>::getFile() {
	return this->file;
}

template<class T> const unsigned int SequentialFile<T>::getBufferMaxSize() const {
	return this->bufferMaxSize;
}

template<class T> void SequentialFile<T>::setBufferMaxSize(unsigned int bufferMaxSize) {
	this->bufferMaxSize = bufferMaxSize;
}

template<class T> const bool SequentialFile<T>::endOfFile() {
	return this->getBuffer().empty();
}

template<class T> const bool SequentialFile<T>::fail() {
	return this->getFile().fail();
}

template<class T> SequentialFile<T>::~SequentialFile(){
}

#endif /* SEQUENTIALFILE_H_ */
