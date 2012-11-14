#ifndef INPUTSEQUENTIALFILE_H_
#define INPUTSEQUENTIALFILE_H_

#include "sequentialFile.h"

#include <fstream>

#include "record.h"

//Clase que representa un archivo secuencial para lectura.
template<class T> class InputSequentialFile : public SequentialFile<T> {
private:
	/* flag que indica si el archivo existe (See debió agregar dado que el flag fail de fstream
	 * por alguna razón se setea con el EOF aunque según la documentación no debería.
	 */
	bool fileExists;

protected:
	//Metodo para cargar en el buffer del archivo los proximos registros del archivo.
	virtual void load() = 0;

	void setFileExists(bool fileExists);

public:
	//Constructor
	InputSequentialFile();

	//Metodo para cerrar el archivo.
	void close();

	//Metodo para obtener el contenido del primer elemento del buffer sin extraerlo.
	T& peek();

	T getRecord();

	//Indica si el archivo existe.
	const bool exists();

	//Destructor
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

template<class T> void InputSequentialFile<T>::setFileExists(bool fileExists) {
	this->fileExists = fileExists;
}

template<class T> const bool InputSequentialFile<T>::exists() {
	return this->fileExists;
}

template<class T> InputSequentialFile<T>::~InputSequentialFile() {
}

#endif /* INPUTSEQUENTIALFILE_H_ */
