#ifndef TEXTINPUTSEQUENTIALFILE_H_
#define TEXTINPUTSEQUENTIALFILE_H_

#include "inputSequentialFile.h"

#include <fstream>

#include "record.h"

//Clase que representa un archivo secuencial para lectura de registro de texto.
template<class T> class TextInputSequentialFile : public InputSequentialFile<T> {
private:
	//Metodo para cargar en el buffer del archivo los proximos registros del archivo
	void load();
public:
	//Constructor.
	TextInputSequentialFile();

	//Constructor.
	TextInputSequentialFile(std::string filePath, unsigned int bufferMaxSize = 1);

	//Metodo para abrir el archivo.
	void open(std::string filePath, unsigned int bufferMaxSize = 1);

	//Destructor.
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
