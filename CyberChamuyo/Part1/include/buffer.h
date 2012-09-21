#ifndef BUFFER_H_
#define BUFFER_H_

#include <string>
#include <fstream>
#include <queue>

#include "record.h"

class Buffer {
private:
	std::fstream file;

	std::queue<Record> buffer;

	unsigned int maxSize;
protected:
	std::fstream& getFile();

	std::queue<Record>& getBuffer();

	const unsigned int getMaxSize() const;

	void push(const Record& record);

	void pop();
public:
	//pasar a protected luego de hacer el wrapper de queue.front()
	Buffer(unsigned int maxSize);

	virtual void initialize(std::string filePath) = 0;

	virtual void finalize() = 0;

	const unsigned int size();

	Record& front();

	bool empty();

	virtual ~Buffer() = 0;

};

#endif /* BUFFER_H_ */
