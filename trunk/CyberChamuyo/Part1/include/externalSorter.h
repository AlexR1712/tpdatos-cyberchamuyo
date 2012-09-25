#ifndef EXTERNALSORTER_H_
#define EXTERNALSORTER_H_

#include <string>
#include "heap.h"
#include "readBuffer.h"
#include "writeBuffer.h"
#include "binaryRecord.h"

class ExternalSorter {
private:
	Heap<BinaryRecord> heap;

	bool showId;

	unsigned int fileBuffersSize;

	Heap<BinaryRecord>& getHeap();

	unsigned int getFileBuffersSize() const;

	bool isShowId() const;

	void createHeap(ReadBuffer<BinaryRecord>& readBuffer);

	void flushHeap(WriteBuffer<BinaryRecord>& writeBuffer);

	void unfreeze(ReadBuffer<BinaryRecord>& freezeReadBuffer, WriteBuffer<BinaryRecord>& freezeWriteBuffer);

	void getFiles(std::vector<ReadBuffer<BinaryRecord>*>& readBuffers, std::string& directoryName, unsigned int inputFileLevelCounter, unsigned int& inputFileFileCounter);

	void clearTemp();

	void clearOutput(unsigned int level = 1);

	void merge();
public:
	ExternalSorter(unsigned int fileBuffersSize, bool showId);

	void sort(std::string filepath);

	~ExternalSorter();
};

#endif /* EXTERNALSORTER_H_ */
