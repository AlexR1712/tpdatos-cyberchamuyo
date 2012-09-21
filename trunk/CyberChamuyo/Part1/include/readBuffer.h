#ifndef READBUFFER_H_
#define READBUFFER_H_

#include "buffer.h"
#include "record.h"

class ReadBuffer : public Buffer {
private:
	void load();

public:
	ReadBuffer(unsigned int maxSize);

	ReadBuffer(std::string filePath, unsigned int maxSize);

	void initialize(std::string filePath);

	void finalize();

	Record getRecord();

	~ReadBuffer();
};


#endif /* READBUFFER_H_ */
