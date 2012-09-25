#include "externalSorter.h"

#include <fstream>
#include <iostream>

#include "record.h"
#include "heap.h"
#include "readBuffer.h"
#include "writeBuffer.h"
#include "statisticsRecord.h"
#include "stringUtilities.h"

ExternalSorter::ExternalSorter(unsigned int fileBuffersSize, bool showId) {
	this->showId = showId;
	this->fileBuffersSize = fileBuffersSize;
}

Heap<BinaryRecord>& ExternalSorter::getHeap() {
	return this->heap;
}

unsigned int ExternalSorter::getFileBuffersSize() const {
    return this->fileBuffersSize;
}

bool ExternalSorter::isShowId() const {
    return this->showId;
}

void ExternalSorter::createHeap(ReadBuffer<BinaryRecord>& readBuffer) {
	BinaryRecord record;

	while ( (this->getHeap().size() < 10 * this->getFileBuffersSize()) && !(readBuffer.empty()) ) {
		record = readBuffer.getRecord();
		this->getHeap().insert(record);
	}
}

void ExternalSorter::flushHeap(WriteBuffer<BinaryRecord>& writeBuffer) {
	BinaryRecord record;

	if (!this->getHeap().empty()) {
		while (this->getHeap().size() > 1) {
			writeBuffer.putRecord(this->getHeap().get(0));
			record = this->getHeap().get(this->getHeap().size() - 1);
			this->getHeap().popBack();
			this->getHeap().replaceRoot(record);
		}
		writeBuffer.putRecord(this->getHeap().get(0));
		this->getHeap().popBack();
	}
}

void ExternalSorter::unfreeze(ReadBuffer<BinaryRecord>& freezeReadBuffer, WriteBuffer<BinaryRecord>& freezeWriteBuffer) {
	freezeWriteBuffer.finalize();
	freezeReadBuffer.initialize("temp\\freezeFile_temp",this->getFileBuffersSize());
	this->createHeap(freezeReadBuffer);
	freezeReadBuffer.finalize();
	freezeWriteBuffer.initialize("temp\\freezeFile_temp",this->getFileBuffersSize());
}

void ExternalSorter::merge() {
	bool levelFinished;
	bool directoryCreated;
	std::vector<ReadBuffer<BinaryRecord>*> readBuffers;

	ReadBuffer<BinaryRecord> readBuffer;
	WriteBuffer<BinaryRecord> writeBuffer;
	BinaryRecord binaryRecord;
	unsigned int smallerRegisterIndex;

	unsigned int inputFileLevelCounter;
	unsigned int inputFileFileCounter;
	std::string inputDirectoryName = "temp\\";

	unsigned int outputFileFileCounter;
	unsigned int outputFileRegisterCounter;
	std::string outputFileName;
	std::string outputDirectoryName;

	StatisticsRecord statisticsRecord;
	std::ofstream statisticsFile;
	statisticsFile.open("estadisticas.txt",std::iostream::out);

	inputFileLevelCounter = 0;

	directoryCreated = true;
	levelFinished = true;
	while(levelFinished && directoryCreated) {
		inputFileFileCounter = 0;
		outputFileFileCounter = 0;
		levelFinished = false;
		directoryCreated = false;
		while (!levelFinished) {
			this->getFiles(readBuffers,inputDirectoryName,inputFileLevelCounter,inputFileFileCounter);
			if ( !(readBuffers.empty()) || ( (readBuffers.size() == 1) && (inputFileFileCounter != 1) ) ) {
				if (!directoryCreated) {
					statisticsRecord.setLevel(inputFileLevelCounter + 1);
					outputDirectoryName += "Etapa" + intToString(inputFileLevelCounter + 1) + "\\";

					mkdir(outputDirectoryName.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

					directoryCreated = true;
				}

				outputFileName = outputDirectoryName + "orderedFile_" + intToString(inputFileLevelCounter + 1) + "_" + intToString(outputFileFileCounter);
				writeBuffer.initialize(outputFileName,this->getFileBuffersSize());
				outputFileFileCounter++;
				outputFileRegisterCounter = 0;

				while ( (!readBuffers.empty()) ) {
					smallerRegisterIndex = 0;
					for (unsigned int i = 1; i < readBuffers.size(); i++) {
						if (readBuffers[i]->front() < readBuffers[smallerRegisterIndex]->front())
							smallerRegisterIndex = i;
					}

					writeBuffer.putRecord(readBuffers[smallerRegisterIndex]->getRecord());
					outputFileRegisterCounter++;
					if (readBuffers[smallerRegisterIndex]->empty()) {
						delete readBuffers[smallerRegisterIndex];
						readBuffers.erase(readBuffers.begin() + smallerRegisterIndex);
					}
				}
				writeBuffer.finalize();

				statisticsRecord.getFilesStatistics().push_back(outputFileRegisterCounter);
			} else {
				levelFinished = true;
				if (inputFileLevelCounter == 0)
					inputDirectoryName = "";
				inputDirectoryName += outputDirectoryName;
				inputFileLevelCounter++;
			}
		}
		if (directoryCreated) {
			statisticsFile << statisticsRecord.serialize();
			statisticsRecord.getFilesStatistics().clear();
		}
	}

	readBuffer.initialize(outputFileName,this->getFileBuffersSize());
	writeBuffer.initialize("dictionary_RANDOMIZED_ORDERED",this->getFileBuffersSize());

	while ( !(readBuffer.empty()) ) {
		binaryRecord = readBuffer.getRecord();
		binaryRecord.setIdVisible(this->isShowId());
		writeBuffer.putRecord(binaryRecord);
	}

}

void ExternalSorter::sort(std::string filepath){
	this->clearOutput();
	this->clearTemp();
	mkdir("temp", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	unsigned int outputFileNameCounter = 0;
	unsigned int freezedRegisters = 0;
	std::string outputFileName = "temp\\orderedFile_0_" + intToString(outputFileNameCounter);

	ReadBuffer<BinaryRecord> readBuffer(filepath,this->getFileBuffersSize());
	WriteBuffer<BinaryRecord> writeBuffer(outputFileName,this->getFileBuffersSize());
	ReadBuffer<BinaryRecord> freezeReadBuffer;
	WriteBuffer<BinaryRecord> freezeWriteBuffer("temp\\freezeFile_temp",this->getFileBuffersSize());
	BinaryRecord record;

	this->createHeap(readBuffer);

	while ( !(readBuffer.empty()) ) {
		record = readBuffer.getRecord();
		if (record < this->getHeap().get(0)) {
			freezeWriteBuffer.putRecord(record);
			freezedRegisters++;

			if (freezedRegisters == 10 * this->getFileBuffersSize()) {
				//vaciar heap
				this->flushHeap(writeBuffer);

				outputFileNameCounter++;
				outputFileName = "temp\\orderedFile_0_" + intToString(outputFileNameCounter);
				writeBuffer.initialize(outputFileName,this->getFileBuffersSize());

				this->unfreeze(freezeReadBuffer,freezeWriteBuffer);

				freezedRegisters = 0;
			}
		} else {
			writeBuffer.putRecord(this->getHeap().get(0));
			this->getHeap().replaceRoot(record);
		}
	}

	this->flushHeap(writeBuffer);

	if (freezedRegisters != 0) {
		outputFileNameCounter++;
		outputFileName = "temp\\orderedFile_0_" + intToString(outputFileNameCounter);
		writeBuffer.initialize(outputFileName,this->getFileBuffersSize());

		this->unfreeze(freezeReadBuffer,freezeWriteBuffer);

		this->flushHeap(writeBuffer);
	}

	this->merge();
}

void ExternalSorter::getFiles(std::vector<ReadBuffer<BinaryRecord>*>& readBuffers, std::string& directoryName, unsigned int inputFileLevelCounter, unsigned int& inputFileFileCounter) {
	ReadBuffer<BinaryRecord>* readBufferPointer;
	std::string inputFileName;
	bool finished = false;

	while ( !finished && (readBuffers.size() < this->getFileBuffersSize() + 1) ) {
		inputFileName = directoryName + "orderedFile_" + intToString(inputFileLevelCounter) + "_" + intToString(inputFileFileCounter);
		readBufferPointer = new ReadBuffer<BinaryRecord>(inputFileName,this->getFileBuffersSize());

		if (readBufferPointer->empty()) {
			delete readBufferPointer;
			finished = true;
		} else {
			readBuffers.push_back(readBufferPointer);
			inputFileFileCounter++;
		}
	}
}

void ExternalSorter::clearTemp() {
	bool finished = false;
	std::ifstream inputFile;
	std::string fileName;

	for (unsigned int i = 0; !finished; i++) {
		fileName = "temp\\orderedFile_0_" + intToString(i);
		inputFile.open(fileName.c_str(),std::iostream::in);
		if (!inputFile.fail()) {
			inputFile.close();
			unlink(fileName.c_str());
		} else {
			finished = true;
		}
	}
	unlink("temp\\freezeFile_temp");
}

void ExternalSorter::clearOutput(unsigned int level) {
	bool finished = false;
	bool folderExists = false;
	std::ifstream inputFile;
	std::string folderName = "Etapa1";
	std::string fileName;

	for (unsigned int i = 1; i < level; i++) {
		folderName += "\\Etapa" + intToString(i + 1);
	}

	for (unsigned int i = 0; !finished; i++) {
		fileName = folderName + "\\orderedFile_" + intToString(level) + "_" + intToString(i);
		inputFile.open(fileName.c_str(),std::iostream::in);
		if (!inputFile.fail()) {
			folderExists = true;
			inputFile.close();
			unlink(fileName.c_str());
		} else {
			finished = true;
			level++;
			if (folderExists)
				this->clearOutput(level);
		}
	}
	rmdir(folderName.c_str());
}

ExternalSorter::~ExternalSorter() {
}
