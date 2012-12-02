#ifndef VARIABLELENGTHRECORDSEQUENTIALFILE_H_
#define VARIABLELENGTHRECORDSEQUENTIALFILE_H_

//#include <fstream>
#include "sequentialFile.h"

#include <vector>
//#include <iostream>

//#include "Bitmap.h"

//Clase que representa un archivo secuencial de registros de longitud fija.
template<class Record> class VariableLengthRecordSequentialFile : public SequentialFile<Record> {
private:

public:
	//Constructor.
	VariableLengthRecordSequentialFile();

	//Metodo para abir el archivo.
	void open(std::string filePath, bool overwrite = false);

	//Indica si se llegó al final del archivo.
	const bool endOfFile();

	//Método para ubicar el puntero de lectura del archivo al primer registro.
	void rewind();

	//Metodo para leer el registro ubicado en la posición indicada.
	Record getNextRecord();

	//Metodo para insertar un registro en el archivo.
	void putRecord(Record& record);

	//Metodo para cerrar el archivo.
	void close();

	//Destructor.
	~VariableLengthRecordSequentialFile();
};

template<class Record> VariableLengthRecordSequentialFile<Record>::VariableLengthRecordSequentialFile() {
}

template<class Record> void VariableLengthRecordSequentialFile<Record>::open(std::string filePath, bool overwrite) {
	if (this->getFile().is_open())
		this->close();

	if (overwrite) {
		this->getFile().open(filePath.c_str(),std::ios_base::in | std::ios_base::out | std::iostream::binary | std::ios_base::trunc);
		this->setFileExists(true);
	} else {
		this->getFile().open(filePath.c_str(),std::ios_base::in | std::ios_base::out | std::iostream::binary);
		if(this->getFile().is_open())
			this->setFileExists(true);
		else
			this->setFileExists(false);
	}
}

template<class Record> const bool VariableLengthRecordSequentialFile<Record>::endOfFile() {
	return this->getFile().eof();
}

template<class Record> void VariableLengthRecordSequentialFile<Record>::rewind() {
	this->getFile().seekg(0,std::ios_base::beg);
}

template<class Record> Record VariableLengthRecordSequentialFile<Record>::getNextRecord() {
	char* recordAsCharArray;
	std::vector<unsigned char> recordAsCharVector;
	unsigned int recordSize;
	Record record;

	if (this->getFile().good()) {
		this->getFile().read(reinterpret_cast<char*>(&recordSize),sizeof(unsigned int));
		record.setRecordSize(recordSize);
		recordAsCharArray = new char[recordSize];
		this->getFile().read(recordAsCharArray,recordSize);
		for (unsigned int i = 0; i < recordSize; i++) {
			recordAsCharVector.push_back(recordAsCharArray[i]);
		}
		record.deserialize(recordAsCharVector);
		delete[] recordAsCharArray;
	}

	return record;
}

template<class Record> void VariableLengthRecordSequentialFile<Record>::putRecord(Record& record) {
	char* recordAsCharArray;
	std::vector<unsigned char> recordAsCharVector;
	unsigned int recordSize;

	record.serialize(recordAsCharVector);
	recordSize = recordAsCharVector.size();
	recordAsCharArray = new char[recordSize];
	for (unsigned int i = 0; i < recordSize; i++) {
		recordAsCharArray[i] = recordAsCharVector[i];
	}
	this->getFile().write(reinterpret_cast<const char*>(&recordSize),sizeof(unsigned int));
	this->getFile().write(recordAsCharArray,recordSize);
	delete[] recordAsCharArray;
}


template<class Record> void VariableLengthRecordSequentialFile<Record>::close() {
	this->getFile().close();
}

template<class Record> VariableLengthRecordSequentialFile<Record>::~VariableLengthRecordSequentialFile() {
	this->close();
}

#endif /* VARIABLELENGTHRECORDSEQUENTIALFILE_H_ */
