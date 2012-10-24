#ifndef EXTERNALSORTER_H_
#define EXTERNALSORTER_H_

#include <string>
#include "heap.h"
#include "binaryInputSequentialFile.h"
#include "binaryOutputSequentialFile.h"
#include "binaryDictionaryRecord.h"

class ExternalSorter {
private:
	Heap<BinaryDictionaryRecord<true> > sortBuffer;

	bool showId;

	unsigned int filesBufferSize;

	std::string tempFolderName;

	Heap<BinaryDictionaryRecord<true> >& getSortBuffer();

	unsigned int getFilesBufferSize() const;

	bool isShowId() const;

	void createSortBuffer(BinaryInputSequentialFile<BinaryDictionaryRecord<true> >& inputFile);

	void flushSortBuffer(BinaryOutputSequentialFile<BinaryDictionaryRecord<true> >& outputFile);

	void unfreeze(BinaryOutputSequentialFile<BinaryDictionaryRecord<true> >& outputFreezeFile);

	void loadSortBuffer(std::vector<BinaryInputSequentialFile<BinaryDictionaryRecord<true> >*>& sortBuffer, std::string& directoryName, unsigned int inputFileLevelCounter, unsigned int& inputFileFileCounter);

	void clearTemp(std::string tempFolderName);

	void clearOutput(unsigned int level = 1);

	void merge(std::string outputFilepath);

public:
	ExternalSorter(unsigned int filesBufferSize, bool showId);

	void sort(std::string inputFilepath, std::string outputFilepath, bool leaveTraces);

	~ExternalSorter();
};

#endif /* EXTERNALSORTER_H_ */
