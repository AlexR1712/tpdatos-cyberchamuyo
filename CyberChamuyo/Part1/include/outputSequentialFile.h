#ifndef OUTPUTSEQUENTIALFILE_H_
#define OUTPUTSEQUENTIALFILE_H_

#include "sequentialFile.h"

#include <fstream>

#include "record.h"

//Clase que representa un archivo secuencial para escritura.
template<class T> class OutputSequentialFile : public SequentialFile<T> {
protected:
	//Metodo para escribir en el archivo el contenido del buffer del mismo.
	virtual void flush() = 0;
public:
	//Constructor
	OutputSequentialFile();

	//Metodo para cerrar el archivo.
	void close();

	//Metodo para insertar un registro en el buffer.
	void putRecord(const T& record);

	//Destructor
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
