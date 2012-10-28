#include "../include/externalSorter.h"

#include <time.h>

#include "../include/textInputSequentialFile.h"
#include "../include/binaryInputSequentialFile.h"
#include "../include/binaryOutputSequentialFile.h"
#include "../include/logRecord.h"
#include "../include/stringUtilities.h"
#include "../include/fileUtilities.h"

ExternalSorter::ExternalSorter(unsigned int filesBufferSize, bool showId) {
	this->showId = showId;
	this->filesBufferSize = filesBufferSize;
	this->tempFolderName = this->generateTempFolderName();
}

Heap<BinaryDictionaryRecord<true> >& ExternalSorter::getSortBuffer() {
	return this->sortBuffer;
}

bool ExternalSorter::isShowId() const {
    return this->showId;
}

unsigned int ExternalSorter::getFilesBufferSize() const {
    return this->filesBufferSize;
}

std::string ExternalSorter::getTempFolderName() const {
	return this->tempFolderName;
}

TextOutputSequentialFile<LogRecord>& ExternalSorter::getLog() {
	return this->log;
}

void ExternalSorter::createSortBuffer(BinaryInputSequentialFile<BinaryDictionaryRecord<true> >& inputFile) {
	BinaryDictionaryRecord<true> record;

	while ( (this->getSortBuffer().size() < 10 * this->getFilesBufferSize()) && !(inputFile.endOfFile()) ) {
		record = inputFile.getRecord();
		this->getSortBuffer().insert(record);
	}
}

void ExternalSorter::flushSortBuffer(BinaryOutputSequentialFile<BinaryDictionaryRecord<true> >& outputFile) {
	BinaryDictionaryRecord<true> record;

	if (!this->getSortBuffer().empty()) {
		while (this->getSortBuffer().size() > 1) {
			outputFile.putRecord(this->getSortBuffer().get(0));
			record = this->getSortBuffer().get(this->getSortBuffer().size() - 1);
			this->getSortBuffer().popBack();
			this->getSortBuffer().replaceRoot(record);
		}
		outputFile.putRecord(this->getSortBuffer().get(0));
		this->getSortBuffer().popBack();
	}
}

void ExternalSorter::unfreeze(BinaryOutputSequentialFile<BinaryDictionaryRecord<true> >& freezeFile) {
	freezeFile.close();

	BinaryInputSequentialFile<BinaryDictionaryRecord<true> > inputFile(this->getTempFolderName() + "/" + FREEZE_FILE_NAME,this->getFilesBufferSize());
	this->createSortBuffer(inputFile);
	inputFile.close();

	freezeFile.open(this->getTempFolderName() + "/" + FREEZE_FILE_NAME,this->getFilesBufferSize());
}

void ExternalSorter::createOrderedParts(std::string inputFilepath) {
	unsigned int outputFileNameCounter = 0;
	unsigned int freezedRegisters = 0;
	unsigned int outputFileRegisterCounter = 0;
	std::string partOutputFilePath = this->getTempFolderName() + "/" + PHASE_FOLDER_NAME_PREFIX + "0/" + ORDERED_FILE_PART_PREFIX + "_0_" + StringUtilities::intToString(outputFileNameCounter);

	FileUtilities::createFolder(this->getTempFolderName() + "/" + PHASE_FOLDER_NAME_PREFIX + "0");

	BinaryInputSequentialFile<BinaryDictionaryRecord<true> > inputFile(inputFilepath,this->getFilesBufferSize());
	BinaryOutputSequentialFile<BinaryDictionaryRecord<true> > outputlFile(partOutputFilePath,this->getFilesBufferSize());
	BinaryOutputSequentialFile<BinaryDictionaryRecord<true> > freezeFile(this->getTempFolderName() + "/" + FREEZE_FILE_NAME,this->getFilesBufferSize());
	BinaryDictionaryRecord<true> record;
	LogRecord logRecord("Particiones","particion");

	this->createSortBuffer(inputFile);
	while ( !(inputFile.endOfFile()) ) {
		record = inputFile.getRecord();
		if (record < this->getSortBuffer().get(0)) {
			freezeFile.putRecord(record);
			freezedRegisters++;

			if (freezedRegisters == 10 * this->getFilesBufferSize()) {
				outputFileRegisterCounter += this->getSortBuffer().size();
				logRecord.getLogItems().push_back(outputFileRegisterCounter);
				outputFileRegisterCounter = 0;
				this->flushSortBuffer(outputlFile);
				outputFileNameCounter++;
				partOutputFilePath = this->getTempFolderName() + "/" + PHASE_FOLDER_NAME_PREFIX + "0/" + ORDERED_FILE_PART_PREFIX + "_0_" + StringUtilities::intToString(outputFileNameCounter);
				outputlFile.open(partOutputFilePath,this->getFilesBufferSize());
				this->unfreeze(freezeFile);
				freezedRegisters = 0;
			}
		} else {
			outputlFile.putRecord(this->getSortBuffer().get(0));
			outputFileRegisterCounter++;
			this->getSortBuffer().replaceRoot(record);
		}
	}

	outputFileRegisterCounter += this->getSortBuffer().size();
	logRecord.getLogItems().push_back(outputFileRegisterCounter);
	outputFileRegisterCounter = 0;
	this->flushSortBuffer(outputlFile);

	if (freezedRegisters != 0) {
		outputFileNameCounter++;
		partOutputFilePath = this->getTempFolderName() + "/" + PHASE_FOLDER_NAME_PREFIX + "0/" + ORDERED_FILE_PART_PREFIX + "_0_" + StringUtilities::intToString(outputFileNameCounter);
		outputlFile.open(partOutputFilePath,this->getFilesBufferSize());
		this->unfreeze(freezeFile);
		outputFileRegisterCounter += this->getSortBuffer().size();
		logRecord.getLogItems().push_back(outputFileRegisterCounter);
		this->flushSortBuffer(outputlFile);
	}

	this->getLog().putRecord(logRecord);
}

void ExternalSorter::merge(std::string outputFilepath) {
	bool levelFinished = true;
	bool directoryCreated = true;
	std::vector<BinaryInputSequentialFile<BinaryDictionaryRecord<true> >*> readBuffers;
	BinaryInputSequentialFile<BinaryDictionaryRecord<true> > binaryInputSequentialFile;
	BinaryOutputSequentialFile<BinaryDictionaryRecord<true> > binaryOutputSequentialFile;
	BinaryDictionaryRecord<true> binaryRecord;
	unsigned int smallerRegisterIndex;
	unsigned int inputFileLevelCounter = 0;
	unsigned int inputFileFileCounter;
	std::string inputDirectoryName = this->getTempFolderName() + "/" + PHASE_FOLDER_NAME_PREFIX + "0/";
	unsigned int outputFileFileCounter;
	unsigned int outputFileRegisterCounter;
	std::string outputFileName;
	std::string outputDirectoryName = this->getTempFolderName() + "/" + PHASE_FOLDER_NAME_PREFIX + "0/";
	LogRecord logRecord("Etapas","Etapa");

	while(levelFinished && directoryCreated) {
		inputFileFileCounter = 0;
		outputFileFileCounter = 0;
		outputFileRegisterCounter = 0;
		levelFinished = false;
		directoryCreated = false;
		while (!levelFinished) {
			this->loadMergeBuffer(readBuffers,inputDirectoryName,inputFileLevelCounter,inputFileFileCounter);
			if ( !(readBuffers.empty()) ) {
				if ( !((readBuffers.size() == 1) && (inputFileFileCounter == 1)) ) {
					if (!directoryCreated) {
						outputDirectoryName += PHASE_FOLDER_NAME_PREFIX + StringUtilities::intToString(inputFileLevelCounter + 1) + "/";
						FileUtilities::createFolder(outputDirectoryName);
						directoryCreated = true;
					}

					outputFileName = outputDirectoryName + ORDERED_FILE_PART_PREFIX + "_" + StringUtilities::intToString(inputFileLevelCounter + 1) + "_" + StringUtilities::intToString(outputFileFileCounter);
					binaryOutputSequentialFile.open(outputFileName,this->getFilesBufferSize());
					outputFileFileCounter++;

					while ( (!readBuffers.empty()) ) {
						smallerRegisterIndex = 0;
						for (unsigned int i = 1; i < readBuffers.size(); i++) {
							if (readBuffers[i]->peek() < readBuffers[smallerRegisterIndex]->peek())
								smallerRegisterIndex = i;
						}

						binaryOutputSequentialFile.putRecord(readBuffers[smallerRegisterIndex]->getRecord());
						outputFileRegisterCounter++;
						if (readBuffers[smallerRegisterIndex]->endOfFile()) {
							delete readBuffers[smallerRegisterIndex];
							readBuffers.erase(readBuffers.begin() + smallerRegisterIndex);
						}
					}
					binaryOutputSequentialFile.close();
				} else {
					outputFileName = outputDirectoryName + ORDERED_FILE_PART_PREFIX + "_" + StringUtilities::intToString(inputFileLevelCounter) + "_" + StringUtilities::intToString(outputFileFileCounter);
					levelFinished = true;
				}
			} else {
				levelFinished = true;
				if (inputFileLevelCounter == 0)
					inputDirectoryName = "";
				inputDirectoryName += outputDirectoryName;
				inputFileLevelCounter++;
			}
		}
		if (directoryCreated) {
			logRecord.getLogItems().push_back(outputFileRegisterCounter);
		}
	}

	binaryInputSequentialFile.open(outputFileName,this->getFilesBufferSize());
	binaryOutputSequentialFile.open(outputFilepath,this->getFilesBufferSize());

	while ( !(binaryInputSequentialFile.endOfFile()) ) {
		binaryRecord = binaryInputSequentialFile.getRecord();
		binaryOutputSequentialFile.putRecord(binaryRecord);
	}

	this->getLog().putRecord(logRecord);
}

void ExternalSorter::sort(std::string inputFilepath, std::string outputFilepath, bool leaveTraces) {
	FileUtilities::createFolder(this->getTempFolderName());
	this->getLog().open(this->getTempFolderName() + "/" + LOG_FILE_NAME);

	this->createOrderedParts(inputFilepath);

	this->merge(outputFilepath);

	if (!leaveTraces)
		this->clearTemp();
}

void ExternalSorter::loadMergeBuffer(std::vector<BinaryInputSequentialFile<BinaryDictionaryRecord<true> >*>& inputFiles, std::string folderName, unsigned int inputFileLevelCounter, unsigned int& inputFileFileCounter) {
	BinaryInputSequentialFile<BinaryDictionaryRecord<true> >* readBufferPointer;
	std::string inputFileName;
	bool finished = false;

	while ( !finished && (inputFiles.size() < this->getFilesBufferSize() + 1) ) {
		inputFileName = folderName + ORDERED_FILE_PART_PREFIX + "_" + StringUtilities::intToString(inputFileLevelCounter) + "_" + StringUtilities::intToString(inputFileFileCounter);
		readBufferPointer = new BinaryInputSequentialFile<BinaryDictionaryRecord<true> >(inputFileName,this->getFilesBufferSize());

		if (readBufferPointer->endOfFile()) {
			delete readBufferPointer;
			finished = true;
		} else {
			inputFiles.push_back(readBufferPointer);
			inputFileFileCounter++;
		}
	}
}

std::string ExternalSorter::generateTempFolderName() {
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime (&rawtime);
	std::string tempFolderName = OUTPUTFILES_FOLDER_NAME;

	tempFolderName = tempFolderName + "/" +
					 TEMP_FOLDER_NAME_PREFIX +
					 StringUtilities::intToString(timeinfo->tm_year + 1900) +
					 StringUtilities::intToString(timeinfo->tm_mon + 1) +
					 StringUtilities::intToString(timeinfo->tm_mday) +
					 StringUtilities::intToString(timeinfo->tm_hour) +
					 StringUtilities::intToString(timeinfo->tm_min) +
					 StringUtilities::intToString(timeinfo->tm_sec);

	return  tempFolderName;
}

void ExternalSorter::clearPhase(std::string parentFolderName, unsigned int level) {
	bool allFilesDeleted = false;
	bool folderExists = false;
	std::ifstream inputFile;
	std::string fileName;
	std::string folderName = parentFolderName + "/" + PHASE_FOLDER_NAME_PREFIX + StringUtilities::intToString(level);

	for (unsigned int i = 0; !allFilesDeleted; i++) {
		fileName = folderName + "/" + ORDERED_FILE_PART_PREFIX + "_" + StringUtilities::intToString(level) + "_" + StringUtilities::intToString(i);
		inputFile.open(fileName.c_str(),std::iostream::in);
		if (!inputFile.fail()) {
			folderExists = true;
			inputFile.close();
			FileUtilities::deleteFile(fileName);
		} else {
			allFilesDeleted = true;
			level++;
			if (folderExists)
				this->clearPhase(folderName,level);
		}
	}
	FileUtilities::deleteFolder(folderName);
}

void ExternalSorter::clearTemp() {
	this->clearPhase(this->getTempFolderName(),0);
	FileUtilities::deleteFile(this->getTempFolderName() + "/" + FREEZE_FILE_NAME);
	this->getLog().close();
	FileUtilities::deleteFile(this->getTempFolderName() + "/" + LOG_FILE_NAME);
	FileUtilities::deleteFolder(this->getTempFolderName());
}

ExternalSorter::~ExternalSorter() {
}
