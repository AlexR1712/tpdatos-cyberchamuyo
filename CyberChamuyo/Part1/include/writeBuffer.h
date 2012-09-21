#ifndef WRITEBUFFER_H_
#define WRITEBUFFER_H_

#include "buffer.h"
#include "record.h"

class WriteBuffer : public Buffer {
private:
	void flush();

public:
	WriteBuffer(unsigned int maxSize);

	WriteBuffer(std::string filePath, unsigned int maxSize);

	void initialize(std::string filePath);

	void finalize();

	void putRecord(const Record& record);

	~WriteBuffer();
};


#endif /* WRITEBUFFER_H_ */
