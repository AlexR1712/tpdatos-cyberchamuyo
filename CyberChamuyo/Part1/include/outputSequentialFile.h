#ifndef OUTPUTSEQUENTIALFILE_H_
#define OUTPUTSEQUENTIALFILE_H_

#include "sequentialFile.h"

#include <fstream>

#include "record.h"

template<class T> class OutputSequentialFile : public SequentialFile<T> {
protected:
	virtual void flush() = 0;
public:
	OutputSequentialFile();

	void close();

	void putRecord(const T& record);

	virtual ~OutputSequentialFile() = 0;
};

template<class T> OutputSequentialFile<T>::OutputSequentialFile() {
}

template<class T> void OutputSequentialFile<T>::close() {
	this->flush();
	this->getFile().close();
}

template<class T> void OutputSequentialFile<T>::putRecord(const T& record) {
	this->getBuffer().push(record);
	if (this->getBuffer().size() == this->getBufferMaxSize()) {
		this->flush();
	}
}

template<class T> OutputSequentialFile<T>::~OutputSequentialFile() {
}

#endif /* OUTPUTSEQUENTIALFILE_H_ */
