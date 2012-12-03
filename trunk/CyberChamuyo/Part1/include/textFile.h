#ifndef TEXTFILE_H_
#define TEXTFILE_H_

//#include <fstream>
#include "sequentialFile.h"

#include <vector>

//Clase que representa un archivo secuencial de registros de longitud fija.
template<class Record> class TextFile : public SequentialFile<Record> {
private:

public:
	//Constructor.
	TextFile();

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
	~TextFile();
};

template<class Record> TextFile<Record>::TextFile() {
}

template<class Record> void TextFile<Record>::open(std::string filePath, bool createOrOverwrite) {
	if (this->getFile().is_open())
		this->close();

	if (createOrOverwrite) {
		this->getFile().open(filePath.c_str(),std::ios_base::in | std::ios_base::out | std::ios_base::trunc);
		this->setFileExists(true);
	} else {
		this->getFile().open(filePath.c_str(),std::ios_base::in | std::ios_base::out);
		if(this->getFile().is_open())
			this->setFileExists(true);
		else
			this->setFileExists(false);
	}
}

template<class Record> const bool TextFile<Record>::endOfFile() {
	this->getFile().peek();
	return this->getFile().eof();
}

template<class Record> void TextFile<Record>::rewind() {
	this->getFile().seekg(0,std::ios_base::beg);
}

template<class Record> Record TextFile<Record>::getNextRecord() {
//	char* recordAsCharArray;
	std::vector<unsigned char> recordAsCharVector;
//	unsigned int recordSize;
	Record record;
	std::string line;

	if (this->getFile().good()) {
		std::getline(this->getFile(),line);
		record.setRecordSize(line.size());
		for (unsigned int i = 0; i < line.size(); i++) {
			recordAsCharVector.push_back(line[i]);
		}
		record.deserialize(recordAsCharVector);
	}

//	if (this->getFile().good()) {
//		this->getFile().read(reinterpret_cast<char*>(&recordSize),sizeof(unsigned int));
//		record.setRecordSize(recordSize);
//		recordAsCharArray = new char[recordSize];
//		this->getFile().read(recordAsCharArray,recordSize);
//		for (unsigned int i = 0; i < recordSize; i++) {
//			recordAsCharVector.push_back(recordAsCharArray[i]);
//		}
//		record.deserialize(recordAsCharVector);
//		delete[] recordAsCharArray;
//	}

	return record;
}

template<class Record> void TextFile<Record>::putRecord(Record& record) {
//	char* recordAsCharArray;
	std::vector<unsigned char> recordAsCharVector;
	std::string line;
//	unsigned int recordSize;

	record.serialize(recordAsCharVector);
	for (unsigned int i = 0; i < recordAsCharVector.size(); i++) {
		line += recordAsCharVector[i];
	}
	this->getFile() << line << std::endl;

//	recordSize = recordAsCharVector.size();
//	recordAsCharArray = new char[recordSize];
//	for (unsigned int i = 0; i < recordSize; i++) {
//		recordAsCharArray[i] = recordAsCharVector[i];
//	}
//	this->getFile().write(reinterpret_cast<const char*>(&recordSize),sizeof(unsigned int));
//	this->getFile().write(recordAsCharArray,recordSize);
//	delete[] recordAsCharArray;
}


template<class Record> void TextFile<Record>::close() {
	this->getFile().close();
}

template<class Record> TextFile<Record>::~TextFile() {
	this->close();
}

#endif /* TEXTFILE_H_ */
