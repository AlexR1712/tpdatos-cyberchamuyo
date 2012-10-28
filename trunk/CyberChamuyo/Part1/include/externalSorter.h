#ifndef EXTERNALSORTER_H_
#define EXTERNALSORTER_H_

#include <string>
#include "heap.h"
#include "binaryInputSequentialFile.h"
#include "binaryOutputSequentialFile.h"
#include "binaryDictionaryRecord.h"
#include "textOutputSequentialFile.h"
#include "logRecord.h"

#ifndef TEMP_FOLDER_NAME_PREFIX
#define TEMP_FOLDER_NAME_PREFIX "particiones"
#endif /*TEMP_FOLDER_NAME_PREFIX*/

#ifndef PHASE_FOLDER_NAME_PREFIX
#define PHASE_FOLDER_NAME_PREFIX "Etapa"
#endif /*PHASE_FOLDER_NAME_PREFIX*/

#ifndef OUTPUTFILES_FOLDER_NAME
#define OUTPUTFILES_FOLDER_NAME "outputFiles"
#endif /*OUTPUTFILES_FOLDER_NAME*/

#ifndef FREEZE_FILE_NAME
#define FREEZE_FILE_NAME "freezeFile.bin"
#endif /*FREEZE_FILE_NAME*/

#ifndef ORDERED_FILE_PART_PREFIX
#define ORDERED_FILE_PART_PREFIX "orderedFile"
#endif /*ORDERED_FILE_PART_PREFIX*/

#ifndef LOG_FILE_NAME
#define LOG_FILE_NAME "estadisticas.txt"
#endif /*LOG_FILE_NAME*/

class ExternalSorter {
private:
	Heap<BinaryDictionaryRecord<true> > sortBuffer;

	bool showId;

	unsigned int filesBufferSize;

	std::string tempFolderName;

	TextOutputSequentialFile<LogRecord> log;

	Heap<BinaryDictionaryRecord<true> >& getSortBuffer();

	bool isShowId() const;

	unsigned int getFilesBufferSize() const;

	std::string getTempFolderName() const;

	TextOutputSequentialFile<LogRecord>& getLog();

	void createSortBuffer(BinaryInputSequentialFile<BinaryDictionaryRecord<true> >& inputFile);

	void flushSortBuffer(BinaryOutputSequentialFile<BinaryDictionaryRecord<true> >& outputFile);

	void unfreeze(BinaryOutputSequentialFile<BinaryDictionaryRecord<true> >& freezeFile);

	void loadMergeBuffer(std::vector<BinaryInputSequentialFile<BinaryDictionaryRecord<true> >*>& inputFiles, std::string folderName, unsigned int inputFileLevelCounter, unsigned int& inputFileFileCounter);

	std::string generateTempFolderName();

	void clearPhase(std::string parentFolderName, unsigned int level);

	void clearTemp();

	void createOrderedParts(std::string inputFilepath);

	void merge(std::string outputFilepath);

public:
	ExternalSorter(unsigned int filesBufferSize, bool showId);

	void sort(std::string inputFilepath, std::string outputFilepath, bool leaveTraces);

	~ExternalSorter();
};

#endif /* EXTERNALSORTER_H_ */
