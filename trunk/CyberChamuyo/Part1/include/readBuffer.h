#ifndef READBUFFER_H_
#define READBUFFER_H_

#include <queue>

template<class File,class Record> class ReadBuffer {
private:
	std::queue<Record> queue;

	File file;

	unsigned int maxSize;

	//Requerido para poder usar registros de longitud fija.
	unsigned int recordSize;

	std::queue<Record>& getQueue();

	File& getFile();

	unsigned int getMaxSize() const;

	unsigned int getRecordSize() const;

	void setRecordSize(unsigned int recordSize);

	//Metodo para cargar en el buffer los proximos registros del archivo
	void load();

public:
	//Constructor
	ReadBuffer(unsigned int maxSize);

	void Initialize(std::string inputFilepath);

	Record getRecord();

	Record peekRecord();

	bool empty();

	//Destructor.
	~ReadBuffer();
};

template<class File,class Record> ReadBuffer<File,Record>::ReadBuffer(unsigned int maxSize) {
	this->maxSize = maxSize;
}

template<class File,class Record> void ReadBuffer<File,Record>::Initialize(std::string inputFilepath) {
	this->getFile().close();
	this->getFile().open(inputFilepath);
	if (this->getFile().isFileExists())
		this->load();
}

template<class File,class Record> std::queue<Record>& ReadBuffer<File,Record>::getQueue() {
	return this->queue;
}

template<class File,class Record> File& ReadBuffer<File,Record>::getFile() {
	return this->file;
}

template<class File,class Record> unsigned int ReadBuffer<File,Record>::getMaxSize() const {
	return this->maxSize;
}

template<class File,class Record> unsigned int ReadBuffer<File,Record>::getRecordSize() const {
	return this->recordSize;
}

template<class File,class Record> void ReadBuffer<File,Record>::setRecordSize(unsigned int recordSize) {
	this->recordSize = recordSize;
}

template<class File,class Record> void ReadBuffer<File,Record>::load() {
	while ( !(this->getFile().endOfFile()) && (this->getQueue().size() < this->getMaxSize()) ) {
		this->getQueue().push(this->getFile().getNextRecord());
	}
}

template<class File,class Record> Record ReadBuffer<File,Record>::getRecord() {
	Record record;

	record = this->getQueue().front();
	this->getQueue().pop();
	if (this->empty()) {
		this->load();
	}

	return record;
}

template<class File,class Record> Record ReadBuffer<File,Record>::peekRecord() {
	return this->getQueue().front();
}

template<class File,class Record> bool ReadBuffer<File,Record>::empty() {
	return this->getQueue().empty();
}

template<class File,class Record> ReadBuffer<File,Record>::~ReadBuffer() {
}

#endif /* READBUFFER_H_ */
