#ifndef FIXEDLENGTHRECORDSEQUENTIALFILE_H_
#define FIXEDLENGTHRECORDSEQUENTIALFILE_H_

#include <fstream>
#include <iostream>

#include "Bitmap.h"

//Clase que representa un archivo secuencial de registros de longitud fija.
template<class Record> class FixedLengthRecordSequentialFile : public SequentialFile<Record> {
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

	void setRecordSize(unsigned int recordSize);

	unsigned int getLastRecordPosition() const;

	void setLastRecordPosition(unsigned int lastRecordPosition);

	Bitmap& getBitMap();

	void setGetSuccessfull(bool getSuccessfull);

	Record getRecord();

	//Método para cargar el bitmap del archivo en memoria.
	void loadMetaData();

	//Método para guardar el bitmap al archivo.
	void saveMetaData();

public:
	//Constructor.
	FixedLengthRecordSequentialFile();

	//Constructor.
	FixedLengthRecordSequentialFile(unsigned int recordSize);

	//Metodo para abir el archivo.
	void open(std::string filePath, bool overwrite = false);

	bool isGetSuccessfull() const;

	//Indica si se llegó al final del archivo.
	const bool endOfFile();

	//Método para ubicar el puntero de lectura del archivo al primer registro.
	void rewind();

	//Metodo para insertar un registro en el archivo.
	unsigned int putRecord(Record& record);

	//Metodo para leer el registro ubicado en la posición indicada.
	Record getRecord(unsigned int recordPosition);

	//Metodo para leer el registro próximo al puntero de lectura y avanzar el mismo para que apunte al próximo registro.
	Record getNextRecord();

	void deleteRecord(unsigned int recordPosition);

	//Metodo para cerrar el archivo.
	void close();

	//Destructor.
	~FixedLengthRecordSequentialFile();
};

template<class Record> FixedLengthRecordSequentialFile<Record>::FixedLengthRecordSequentialFile() : bitMap(1) {
	this->recordSize = 0;
	this->lastRecordPosition = 0;
}

template<class Record> FixedLengthRecordSequentialFile<Record>::FixedLengthRecordSequentialFile(unsigned int recordSize) : bitMap(1) {
	this->recordSize = recordSize;
	this->lastRecordPosition = 0;
}

template<class Record> std::fstream& FixedLengthRecordSequentialFile<Record>::getFile() {
	return this->file;
}

template<class Record> unsigned int FixedLengthRecordSequentialFile<Record>::getRecordSize() const {
	return this->recordSize;
}

template<class Record> void FixedLengthRecordSequentialFile<Record>::setRecordSize(unsigned int recordSize) {
	this->recordSize = recordSize;
}

template<class Record> unsigned int FixedLengthRecordSequentialFile<Record>::getLastRecordPosition() const {
	return this->lastRecordPosition;
}

template<class Record> void FixedLengthRecordSequentialFile<Record>::setLastRecordPosition(unsigned int lastRecordPosition) {
	this->lastRecordPosition = lastRecordPosition;
}

template<class Record> Bitmap& FixedLengthRecordSequentialFile<Record>::getBitMap() {
	return this->bitMap;
}

template<class Record> bool FixedLengthRecordSequentialFile<Record>::isGetSuccessfull() const {
	return this->getSuccessfull;
}

template<class Record> void FixedLengthRecordSequentialFile<Record>::setGetSuccessfull(bool getSuccessfull) {
	this->getSuccessfull = getSuccessfull;
}

template<class Record> Record FixedLengthRecordSequentialFile<Record>::getRecord() {
	char* recordAsCharArray;
	std::vector<unsigned char> recordAsCharVector;
	Record fixedLengthRecord(this->getRecordSize());

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

template<class Record> void FixedLengthRecordSequentialFile<Record>::loadMetaData() {
	unsigned int recordSize;
	unsigned int lastRecordPosition;

	if (this->getFile().good()) {
		this->getFile().seekg(0,std::ios_base::beg);
		this->getFile().read(reinterpret_cast<char*>(&recordSize),sizeof(unsigned int));
		this->recordSize = recordSize;
		this->getFile().read(reinterpret_cast<char*>(&lastRecordPosition),sizeof(unsigned int));
		this->setLastRecordPosition(lastRecordPosition);
		this->getFile() >> this->getBitMap();
	}
}

template<class Record> void FixedLengthRecordSequentialFile<Record>::saveMetaData() {
	unsigned int recordSize = this->getRecordSize();
	unsigned int lastRecordPosition = this->getLastRecordPosition();

	if (this->getFile().good()) {
		this->getFile().seekp(0,std::ios_base::beg);
		this->getFile().write(reinterpret_cast<const char*>(&recordSize),sizeof(unsigned int));
		this->getFile().write(reinterpret_cast<const char*>(&lastRecordPosition),sizeof(unsigned int));
		this->getFile() << this->getBitMap();
	}
}

template<class Record> void FixedLengthRecordSequentialFile<Record>::open(std::string filePath, bool createOrOverwrite) {
	if (this->getFile().is_open())
		this->close();

	if (createOrOverwrite) {
		this->getFile().open(filePath.c_str(),std::ios_base::in | std::ios_base::out | std::iostream::binary | std::ios_base::trunc);
		this->setFileExists(true);
	} else {
		this->getFile().open(filePath.c_str(),std::ios_base::in | std::ios_base::out | std::iostream::binary);
		if(this->getFile().is_open()) {
			this->setFileExists(true);
			this->loadMetaData();
		} else
			this->setFileExists(false);
	}
}

template<class Record> const bool FixedLengthRecordSequentialFile<Record>::endOfFile() {
	unsigned int position = this->getFile().tellg() / this->getRecordSize();
	return (position > this->getLastRecordPosition());
}

template<class Record> void FixedLengthRecordSequentialFile<Record>::rewind() {
	this->getFile().seekg(this->getRecordSize(),std::ios_base::beg);
}

template<class Record> Record FixedLengthRecordSequentialFile<Record>::getRecord(unsigned int recordPosition) {
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

template<class Record> Record FixedLengthRecordSequentialFile<Record>::getNextRecord() {
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

template<class Record> unsigned int FixedLengthRecordSequentialFile<Record>::putRecord(Record& fixedLengthRecord) {
	char* recordAsCharArray;
	std::vector<unsigned char> recordAsCharVector;
	unsigned int recordPosition;

	if ( (this->getRecordSize() == 0) && (this->getLastRecordPosition() == 0) )
		this->setRecordSize(fixedLengthRecord.getRecordSize());

	fixedLengthRecord.serialize(recordAsCharVector);
	recordAsCharArray = new char[this->getRecordSize()];
	for (unsigned int i = 0; i < this->getRecordSize(); ++i) {
		recordAsCharArray[i] = 0;
	}
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

template<class Record> void FixedLengthRecordSequentialFile<Record>::deleteRecord(unsigned int recordPosition) {
	this->getBitMap().setBloqueLibre(recordPosition);
	if (recordPosition == this->getLastRecordPosition()) {
		while ( (this->getBitMap().verificarBloqueLibre(recordPosition)) && (recordPosition != 0) ){
			recordPosition--;
		}
		this->setLastRecordPosition(recordPosition);
	}
}

template<class Record> void FixedLengthRecordSequentialFile<Record>::close() {
	saveMetaData();
	this->getFile().close();
}

template<class Record> FixedLengthRecordSequentialFile<Record>::~FixedLengthRecordSequentialFile() {
	this->close();
}

#endif /* FIXEDLENGTHRECORDSEQUENTIALFILE_H_ */
