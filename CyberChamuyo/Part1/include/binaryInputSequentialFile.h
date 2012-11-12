#ifndef BINARYINPUTSEQUENTIALFILE_H_
#define BINARYINPUTSEQUENTIALFILE_H_

#include "inputSequentialFile.h"

#include <fstream>

#include "record.h"

//Clase que representa un archivo secuencial para lectura de registro binarios.
template<class T> class BinaryInputSequentialFile : public InputSequentialFile<T> {
private:
	//Metodo para cargar en el buffer del archivo los proximos registros del archivo
	void load();
public:
	//Constructor.
	BinaryInputSequentialFile();

	//Constructor.
	BinaryInputSequentialFile(std::string filePath, unsigned int bufferMaxSize = 1);

	//Metodo para abrir el archivo.
	void open(std::string filePath, unsigned int bufferMaxSize = 1);

	//Destructor.
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
	this->setFileExists(!this->getFile().fail());
	this->load();
}

template<class T> BinaryInputSequentialFile<T>::~BinaryInputSequentialFile() {
	this->close();
}

#endif /* BINARYINPUTSEQUENTIALFILE_H_ */
