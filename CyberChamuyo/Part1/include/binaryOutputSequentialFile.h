#ifndef BINARYOUTPUTSEQUENTIALFILE_H_
#define BINARYOUTPUTSEQUENTIALFILE_H_

#include "outputSequentialFile.h"

#include <fstream>

#include "record.h"

template<class T> class BinaryOutputSequentialFile : public OutputSequentialFile<T> {
private:
	void flush();
public:
	BinaryOutputSequentialFile();

	BinaryOutputSequentialFile(std::string filePath, unsigned int bufferMaxSize = 1);

	void open(std::string filePath, unsigned int bufferMaxSize = 1);

	~BinaryOutputSequentialFile();
};

template<class T> BinaryOutputSequentialFile<T>::BinaryOutputSequentialFile() {
}

template<class T> BinaryOutputSequentialFile<T>::BinaryOutputSequentialFile(std::string filePath, unsigned int bufferMaxSize) {
	this->open(filePath,bufferMaxSize);
}

template<class T> void BinaryOutputSequentialFile<T>::flush() {
	Record* record = new T();
	unsigned int recordSize;
	std::string recordAsString;

	while (this->getBuffer().size() > 0) {
		recordAsString = this->getBuffer().front().serialize();
		recordSize = recordAsString.size();
		this->getFile().write(reinterpret_cast<const char*>(&recordSize),sizeof(unsigned int));
		this->getFile().write(recordAsString.c_str(),recordSize);
		this->getBuffer().pop();
	}

	delete record;
}

template<class T> void BinaryOutputSequentialFile<T>::open(std::string filePath, unsigned int bufferMaxSize) {
	if (bufferMaxSize < 1)
		bufferMaxSize = 1;
	this->setBufferMaxSize(bufferMaxSize);

	if (this->getFile().is_open())
		this->close();
	this->getFile().open(filePath.c_str(),std::iostream::out | std::iostream::binary);
}

template<class T> BinaryOutputSequentialFile<T>::~BinaryOutputSequentialFile() {
	this->close();
}

#endif /* BINARYOUTPUTSEQUENTIALFILE_H_ */
