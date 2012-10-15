#ifndef TEXTINPUTSEQUENTIALFILE_H_
#define TEXTINPUTSEQUENTIALFILE_H_

#include "inputSequentialFile.h"

#include <fstream>

#include "record.h"

template<class T> class TextInputSequentialFile : public InputSequentialFile<T> {
private:
	void load();
public:
	TextInputSequentialFile();

	TextInputSequentialFile(std::string filePath, unsigned int bufferMaxSize = 1);

	void open(std::string filePath, unsigned int bufferMaxSize);

	~TextInputSequentialFile();
};

template<class T> TextInputSequentialFile<T>::TextInputSequentialFile() {
}

template<class T> TextInputSequentialFile<T>::TextInputSequentialFile(std::string filePath, unsigned int bufferMaxSize) {
	this->open(filePath,bufferMaxSize);
}

template<class T> void TextInputSequentialFile<T>::load() {
	std::string recordAsString;
	Record* record = new T();

	while ( (this->getFile().good()) && (this->getBuffer().size() < this->getBufferMaxSize()) ) {
		recordAsString = "";
		std::getline(this->getFile(),recordAsString);

		if (recordAsString.size() != 0) {
			record->deserialize(recordAsString);
			this->getBuffer().push(*(static_cast<T*>(record)));
		}

	}
	delete record;
}

template<class T> void TextInputSequentialFile<T>::open(std::string filePath, unsigned int bufferMaxSize) {
	if (bufferMaxSize < 1)
		bufferMaxSize = 1;
	this->setBufferMaxSize(bufferMaxSize);

	if (this->getFile().is_open())
		this->close();
	this->getFile().open(filePath.c_str(),std::iostream::in);
	this->load();
}

template<class T> TextInputSequentialFile<T>::~TextInputSequentialFile() {
	this->close();
}

#endif /* TEXTINPUTSEQUENTIALFILE_H_ */
