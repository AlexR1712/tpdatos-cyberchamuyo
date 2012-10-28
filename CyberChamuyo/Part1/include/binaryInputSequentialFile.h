#ifndef BINARYINPUTSEQUENTIALFILE_H_
#define BINARYINPUTSEQUENTIALFILE_H_

#include "inputSequentialFile.h"

#include <fstream>

#include "record.h"

template<class T> class BinaryInputSequentialFile : public InputSequentialFile<T> {
private:
	void load();
public:
	BinaryInputSequentialFile();

	BinaryInputSequentialFile(std::string filePath, unsigned int bufferMaxSize = 1);

	void open(std::string filePath, unsigned int bufferMaxSize = 1);

	~BinaryInputSequentialFile();
};

template<class T> BinaryInputSequentialFile<T>::BinaryInputSequentialFile() {
}

template<class T> BinaryInputSequentialFile<T>::BinaryInputSequentialFile(std::string filePath, unsigned int bufferMaxSize) {
	this->open(filePath,bufferMaxSize);
}

template<class T> void BinaryInputSequentialFile<T>::load() {
	std::string recordAsString;
	unsigned int recordSize;
	char* recordAsCharArray;
	Record* record = new T();

	while ( (this->getFile().good()) && (this->getBuffer().size() < this->getBufferMaxSize()) ) {
		recordAsString = "";
		this->getFile().read(reinterpret_cast<char*>(&recordSize),sizeof(unsigned int));
		if (this->getFile().good()) {
			recordAsCharArray = new char[recordSize];
			this->getFile().read(recordAsCharArray,recordSize);
			recordAsString.append(recordAsCharArray,recordSize);
			delete[] recordAsCharArray;

			if (recordAsString.size() != 0) {
				record->deserialize(recordAsString);
				this->getBuffer().push(*(static_cast<T*>(record)));
			}
		}
	}
	delete record;
}

template<class T> void BinaryInputSequentialFile<T>::open(std::string filePath, unsigned int bufferMaxSize) {
	if (bufferMaxSize < 1)
		bufferMaxSize = 1;
	this->setBufferMaxSize(bufferMaxSize);

	if (this->getFile().is_open())
		this->close();
	this->getFile().open(filePath.c_str(),std::iostream::in | std::iostream::binary);
	this->load();
}

template<class T> BinaryInputSequentialFile<T>::~BinaryInputSequentialFile() {
	this->close();
}

#endif /* BINARYINPUTSEQUENTIALFILE_H_ */
