#ifndef HEAP_H_
#define HEAP_H_

#include <vector>

#include "record.h"

class Heap {
private:
	std::vector<Record> heap;

	unsigned int getSmallestChildIndex(unsigned int parentIndex);

	void swapRecord(Record& x, Record& y);
public:
	Heap();

	std::vector<Record>& getHeap();

	void replaceRoot(const Record& record);

	void insert(const Record& record);

	~Heap();
};



#endif /* HEAP_H_ */
