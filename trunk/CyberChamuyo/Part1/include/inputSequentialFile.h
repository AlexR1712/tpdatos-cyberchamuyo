#ifndef INPUTSEQUENTIALFILE_H_
#define INPUTSEQUENTIALFILE_H_

#include "sequentialFile.h"

#include <fstream>

#include "record.h"

template<class T> class InputSequentialFile : public SequentialFile<T> {
protected:
	virtual void load() = 0;
public:
	InputSequentialFile();

	void close();

	T& peek();

	T getRecord();

	virtual ~InputSequentialFile() = 0;
};

template<class T> InputSequentialFile<T>::InputSequentialFile() {
}

template<class T> void InputSequentialFile<T>::close() {
	while (this->getBuffer().size() > 0) {
		this->getBuffer().pop();
	}
	this->getFile().close();
}

template<class T> T& InputSequentialFile<T>::peek() {
	return this->getBuffer().front();
}

template<class T> T InputSequentialFile<T>::getRecord() {
	T record;

	record = this->getBuffer().front();
	this->getBuffer().pop();
	if (this->getBuffer().size() == 0)
		this->load();

	return record;
}

template<class T> InputSequentialFile<T>::~InputSequentialFile() {
}

#endif /* INPUTSEQUENTIALFILE_H_ */
