#ifndef FIXEDLENGTHRECORDSEQUENTIALFILE_H_
#define FIXEDLENGTHRECORDSEQUENTIALFILE_H_

#include <fstream>
#include <iostream>

#include "Bitmap.h"

//Clase que representa un archivo secuencial de registros de longitud fija.
template<class T> class FixedLengthRecordSequentialFile {
private:
	//File handler
	std::fstream file;

	unsigned int recordSize;

	unsigned int lastRecordPosition;

	//Bitmap
	Bitmap bitMap;

	bool getSuccessfull;

	std::fstream& getFile();

	unsigned int getRecordSize() const;

	unsigned int getLastRecordPosition() const;

	void setLastRecordPosition(unsigned int lastRecordPosition);

	Bitmap& getBitMap();

	void setGetSuccessfull(bool getSuccessfull);

	T getRecord();

	//Método para cargar el bitmap del archivo en memoria.
	void loadMetaData();

	//Método para guardar el bitmap al archivo.
	void saveMetaData();

public:
	//Constructor.
	FixedLengthRecordSequentialFile(unsigned int recordSize);

	//Metodo para abir el archivo.
	void open(std::string filePath);

	bool isGetSuccessfull() const;

	//Indica si se llegó al final del archivo.
	const bool endOfFile();

	//Método para ubicar el puntero de lectura del archivo al primer registro.
	void rewind();

	//Metodo para insertar un registro en el archivo.
	unsigned int putRecord(T& record);

	//Metodo para leer el registro ubicado en la posición indicada.
	T getRecord(unsigned int recordPosition);

	//Metodo para leer el registro próximo al puntero de lectura y avanzar el mismo para que apunte al próximo registro.
	T getNextRecord();

	void deleteRecord(unsigned int recordPosition);

	//Metodo para cerrar el archivo.
	void close();

	//Destructor.
	~FixedLengthRecordSequentialFile();
};

template<class T> FixedLengthRecordSequentialFile<T>::FixedLengthRecordSequentialFile(unsigned int recordSize) : bitMap(1) {
	this->recordSize = recordSize;
	this->lastRecordPosition = 0;
}

template<class T> std::fstream& FixedLengthRecordSequentialFile<T>::getFile() {
	return this->file;
}

template<class T> unsigned int FixedLengthRecordSequentialFile<T>::getRecordSize() const {
	return this->recordSize;
}

template<class T> unsigned int FixedLengthRecordSequentialFile<T>::getLastRecordPosition() const {
	return this->lastRecordPosition;
}

template<class T> void FixedLengthRecordSequentialFile<T>::setLastRecordPosition(unsigned int lastRecordPosition) {
	this->lastRecordPosition = lastRecordPosition;
}

template<class T> Bitmap& FixedLengthRecordSequentialFile<T>::getBitMap() {
	return this->bitMap;
}

template<class T> bool FixedLengthRecordSequentialFile<T>::isGetSuccessfull() const {
	return this->getSuccessfull;
}

template<class T> void FixedLengthRecordSequentialFile<T>::setGetSuccessfull(bool getSuccessfull) {
	this->getSuccessfull = getSuccessfull;
}

template<class T> T FixedLengthRecordSequentialFile<T>::getRecord() {
	char* recordAsCharArray;
	std::vector<unsigned char> recordAsCharVector;
	T fixedLengthRecord(this->getRecordSize());

	if ( (this->isGetSuccessfull()) && (this->getFile().good()) ) {
		recordAsCharArray = new char[this->getRecordSize()];
		this->getFile().read(recordAsCharArray,this->getRecordSize());
		for (unsigned int i = 0; i < this->getRecordSize(); i++) {
			recordAsCharVector.push_back(recordAsCharArray[i]);
		}
		fixedLengthRecord.deserialize(recordAsCharVector);
		delete[] recordAsCharArray;
	}

	return fixedLengthRecord;
}

template<class T> void FixedLengthRecordSequentialFile<T>::loadMetaData() {
	unsigned int lastRecordPosition;

	if (this->getFile().good()) {
		this->getFile().seekg(0,std::ios_base::beg);
		this->getFile().read(reinterpret_cast<char*>(&lastRecordPosition),sizeof(unsigned int));
		this->setLastRecordPosition(lastRecordPosition);
		this->getFile() >> this->getBitMap();
	}
}

template<class T> void FixedLengthRecordSequentialFile<T>::saveMetaData() {
	unsigned int lastRecordPosition = this->getLastRecordPosition();

	if (this->getFile().good()) {
		this->getFile().seekp(0,std::ios_base::beg);
		this->getFile().write(reinterpret_cast<const char*>(&lastRecordPosition),sizeof(unsigned int));
		this->getFile() << this->getBitMap();
	}
}

template<class T> void FixedLengthRecordSequentialFile<T>::open(std::string filePath) {
	if (this->getFile().is_open())
		this->close();

	this->getFile().open(filePath.c_str(),std::ios_base::in | std::ios_base::out | std::iostream::binary);
	if(this->getFile().is_open())
		this->loadMetaData();
	else
		this->getFile().open(filePath.c_str(),std::ios_base::in | std::ios_base::out | std::ios_base::trunc | std::iostream::binary);
}

template<class T> const bool FixedLengthRecordSequentialFile<T>::endOfFile() {
	unsigned int position = this->getFile().tellg() / this->getRecordSize();
	return (position > this->getLastRecordPosition());
}

template<class T> void FixedLengthRecordSequentialFile<T>::rewind() {
	this->getFile().seekg(this->getRecordSize(),std::ios_base::beg);
}

template<class T> T FixedLengthRecordSequentialFile<T>::getRecord(unsigned int recordPosition) {
	if ( (this->getBitMap().verificarBloqueOcupado(recordPosition) == -2) ||
		 (recordPosition > this->getLastRecordPosition()) ||
		 (recordPosition == 0) )
		this->setGetSuccessfull(false);
	else {
		this->setGetSuccessfull(true);
		this->getFile().seekg(recordPosition * this->getRecordSize(),std::ios_base::beg);
	}

	return this->getRecord();
}

template<class T> T FixedLengthRecordSequentialFile<T>::getNextRecord() {
	unsigned int recordPosition = this->getFile().tellg() / this->getRecordSize();

	while (this->getBitMap().verificarBloqueLibre(recordPosition)) {
		recordPosition++;
	}

	if (recordPosition > this->getLastRecordPosition())
		this->setGetSuccessfull(false);
	else {
		this->setGetSuccessfull(true);
		this->getFile().seekg(recordPosition * this->getRecordSize(),std::ios_base::beg);
	}

	return this->getRecord();
}

template<class T> unsigned int FixedLengthRecordSequentialFile<T>::putRecord(T& fixedLengthRecord) {
	char* recordAsCharArray;
	std::vector<unsigned char> recordAsCharVector;
	unsigned int recordPosition;

	fixedLengthRecord.serialize(recordAsCharVector);
	recordAsCharArray = new char[this->getRecordSize()];
	for (unsigned int i = 0; i < recordAsCharVector.size(); i++) {
		recordAsCharArray[i] = recordAsCharVector[i];
	}
	recordPosition = this->getBitMap().getBloqueLibre();
	this->getFile().seekp(recordPosition * this->getRecordSize(),std::ios_base::beg);
	this->getFile().write(recordAsCharArray,this->getRecordSize());
	this->getFile().flush();
	delete[] recordAsCharArray;

	this->getBitMap().agregarBloque(recordPosition);

	if (this->getLastRecordPosition() < recordPosition)
		this->setLastRecordPosition(recordPosition);

	return recordPosition;
}

template<class T> void FixedLengthRecordSequentialFile<T>::deleteRecord(unsigned int recordPosition) {
	this->getBitMap().setBloqueLibre(recordPosition);
	if (recordPosition == this->getLastRecordPosition()) {
		while ( (this->getBitMap().verificarBloqueLibre(recordPosition)) && (recordPosition != 0) ){
			recordPosition--;
		}
		this->setLastRecordPosition(recordPosition);
	}
}

template<class T> void FixedLengthRecordSequentialFile<T>::close() {
	saveMetaData();
	this->getFile().close();
}

template<class T> FixedLengthRecordSequentialFile<T>::~FixedLengthRecordSequentialFile() {
	this->close();
}

#endif /* FIXEDLENGTHRECORDSEQUENTIALFILE_H_ */
