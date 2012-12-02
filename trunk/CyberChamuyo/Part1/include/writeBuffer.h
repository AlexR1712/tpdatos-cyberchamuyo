#ifndef WRITEBUFFER_H_
#define WRITEBUFFER_H_

#include <queue>

template<class File,class Record> class WriteBuffer {
private:
	std::queue<Record> queue;

	File outputFile;

	unsigned int maxSize;

	//Requerido para poder usar registros de longitud fija.
	unsigned int recordSize;

	std::queue<Record>& getQueue();

	File& getFile();

	unsigned int getMaxSize() const;

	void setMaxSize(unsigned int maxSize);

	unsigned int getRecordSize() const;

	void setRecordSize(unsigned int recordSize);

	//Metodo para cargar en el buffer los proximos registros del archivo
	void flush();

public:
	//Constructor para usar con archivos de registros de longitud variable.
	WriteBuffer(unsigned int maxSize);

	WriteBuffer(unsigned int maxSize, unsigned int recordSize);

	void initialize(std::string outFilepath);

	void putRecord(const Record& record);

	bool empty();

	//Destructor.
	~WriteBuffer();
};

template<class File,class Record> WriteBuffer<File,Record>::WriteBuffer(unsigned int maxSize) {
	this->maxSize = maxSize;
}

template<class File,class Record> WriteBuffer<File,Record>::WriteBuffer(unsigned int maxSize, unsigned int recordSize) {
	this->maxSize = maxSize;
	this->recordSize = recordSize;
}

template<class File,class Record> void WriteBuffer<File,Record>::initialize(std::string outFilepath) {
	this->flush();
	this->getFile().close();
	this->getFile().open(outFilepath,true);
}

template<class File,class Record> std::queue<Record>& WriteBuffer<File,Record>::getQueue() {
	return this->queue;
}

template<class File,class Record> File& WriteBuffer<File,Record>::getFile() {
	return this->outputFile;
}

template<class File,class Record> unsigned int WriteBuffer<File,Record>::getMaxSize() const {
	return this->maxSize;
}

template<class File,class Record> void WriteBuffer<File,Record>::setMaxSize(unsigned int maxSize) {
	this->maxSize = maxSize;
}

template<class File,class Record> void WriteBuffer<File,Record>::flush() {
	Record record;

	while (!this->empty()) {
		this->getFile().putRecord(this->getQueue().front());
		this->getQueue().pop();
	}
}

template<class File,class Record> void WriteBuffer<File,Record>::putRecord(const Record& record) {
	this->getQueue().push(record);
	if (this->getQueue().size() == this->getMaxSize()) {
		this->flush();
	}
}

template<class File,class Record> bool WriteBuffer<File,Record>::empty() {
	return this->getQueue().empty();
}

template<class File,class Record> WriteBuffer<File,Record>::~WriteBuffer() {
	this->flush();
	this->getFile().close();
}

#endif /* WRITEBUFFER_H_ */
