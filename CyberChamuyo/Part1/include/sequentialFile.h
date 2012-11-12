#ifndef SEQUENTIALFILE_H_
#define SEQUENTIALFILE_H_

#include <fstream>
#include <queue>

//Clase que representa un archivo secuencial.
template<class T> class SequentialFile {
private:
	//File handler
	std::fstream file;

	/* flag que indica si el archivo existe (See debió agregar dado que el flag fail de fstream
	 * por alguna razón se setea con el EOF aunque según la documentación no debería.
	 */
	bool fileExists;

	//Buffer
	std::queue<T> buffer;

	//Tamaño máximo para el buffer
	unsigned int bufferMaxSize;

protected:
	std::fstream& getFile();

	std::queue<T>& getBuffer();

	const unsigned int getBufferMaxSize() const;

	void setBufferMaxSize(unsigned int bufferMaxSize);

	//Indica si el buffer está vacío.
	const bool isBufferEmpty();

	void setFileExists(bool fileExists);

public:
	//Constructor.
	SequentialFile();

	//Metodo para abir el archivo.
	virtual void open(std::string filePath, unsigned int bufferMaxSize = 1) = 0;

	//Metodo para cerrar el archivo.
	virtual void close() = 0;

	//Indica si se llegó al final del archivo.
	const bool endOfFile();

	//Indica si el archivo existe.
	const bool exists();

	//Destructor.
	virtual ~SequentialFile() = 0;
};

template<class T> SequentialFile<T>::SequentialFile(){
}

template<class T> std::queue<T>& SequentialFile<T>::getBuffer() {
	return this->buffer;
}

template<class T> std::fstream& SequentialFile<T>::getFile() {
	return this->file;
}

template<class T> const unsigned int SequentialFile<T>::getBufferMaxSize() const {
	return this->bufferMaxSize;
}

template<class T> void SequentialFile<T>::setBufferMaxSize(unsigned int bufferMaxSize) {
	this->bufferMaxSize = bufferMaxSize;
}

template<class T> const bool SequentialFile<T>::endOfFile() {
	return this->getBuffer().empty();
}

template<class T> void SequentialFile<T>::setFileExists(bool fileExists) {
	this->fileExists = fileExists;
}

template<class T> const bool SequentialFile<T>::exists() {
	return this->fileExists;
}

template<class T> SequentialFile<T>::~SequentialFile(){
}

#endif /* SEQUENTIALFILE_H_ */
