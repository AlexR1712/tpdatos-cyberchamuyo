#ifndef SEQUENTIALFILE_H_
#define SEQUENTIALFILE_H_

#include <fstream>
//#include <queue>

//Clase que representa un archivo secuencial.
template<class Record> class SequentialFile {
private:
	//File handler
	std::fstream file;

	bool getSuccessfull;

	bool fileExists;

protected:
	std::fstream& getFile();

	void setGetSuccessfull(bool getSuccessfull);

	void setFileExists(bool fileExists);

public:
	//Constructor.
	SequentialFile();

	//Metodo para abir el archivo.
	virtual void open(std::string filePath, bool createOrOverwrite) = 0;

	//Indica si el archivo existe.
	const bool isFileExists();

	//Indica si el archivo se inicializó correctamente.
	const bool good();

	bool isGetSuccessfull() const;

	//Indica si se llegó al final del archivo.
	virtual const bool endOfFile() = 0;

	virtual void rewind() = 0;

	virtual Record getNextRecord() = 0;

	//Metodo para cerrar el archivo.
	virtual void close() = 0;

	//Destructor.
	virtual ~SequentialFile() = 0;
};

template<class Record> SequentialFile<Record>::SequentialFile(){
}

template<class Record> std::fstream& SequentialFile<Record>::getFile() {
	return this->file;
}

template<class Record> bool SequentialFile<Record>::isGetSuccessfull() const {
	return this->getSuccessfull;
}

template<class Record> void SequentialFile<Record>::setGetSuccessfull(bool getSuccessfull) {
	this->getSuccessfull = getSuccessfull;
}

template<class Record> void SequentialFile<Record>::setFileExists(bool fileExists) {
	this->fileExists = fileExists;
}

template<class Record> const bool SequentialFile<Record>::isFileExists() {
	return this->fileExists;
}

template<class Record> const bool SequentialFile<Record>::good() {
	return this->getFile().good();
}

template<class Record> SequentialFile<Record>::~SequentialFile(){
}

#endif /* SEQUENTIALFILE_H_ */
