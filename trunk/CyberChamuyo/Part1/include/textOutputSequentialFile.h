#ifndef TEXTOUTPUTSEQUENTIALFILE_H_
#define TEXTOUTPUTSEQUENTIALFILE_H_

#include "outputSequentialFile.h"

#include <fstream>

#include "record.h"

template<class T> class TextOutputSequentialFile : public OutputSequentialFile<T> {
private:
	void flush();
public:
	TextOutputSequentialFile();

	TextOutputSequentialFile(std::string filePath, unsigned int bufferMaxSize = 1);

	void open(std::string filePath, unsigned int bufferMaxSize = 1);

	~TextOutputSequentialFile();
};

template<class T> TextOutputSequentialFile<T>::TextOutputSequentialFile() {
}

template<class T> TextOutputSequentialFile<T>::TextOutputSequentialFile(std::string filePath, unsigned int bufferMaxSize) {
	this->open(filePath,bufferMaxSize);
}

template<class T> void TextOutputSequentialFile<T>::flush() {
	while (this->getBuffer().size() > 0) {
		this->getFile() << this->getBuffer().front().serialize() << std::endl;
		this->getBuffer().pop();
	}
}

template<class T> void TextOutputSequentialFile<T>::open(std::string filePath, unsigned int bufferMaxSize) {
	if (bufferMaxSize < 1)
		bufferMaxSize = 1;
	this->setBufferMaxSize(bufferMaxSize);

	if (this->getFile().is_open())
		this->close();
	this->getFile().open(filePath.c_str(),std::iostream::out);
}


template<class T> TextOutputSequentialFile<T>::~TextOutputSequentialFile() {
	this->close();
}

#endif /* TEXTOUTPUTSEQUENTIALFILE_H_ */
