#include "externalSorter.h"

#include <time.h>

#include "textInputSequentialFile.h"
#include "binaryInputSequentialFile.h"
#include "binaryOutputSequentialFile.h"
#include "statisticsRecord.h"
#include "stringUtilities.h"

//WINDOWS
#include "windows.h"
//LINUX
//#include <sys/stat.h>

ExternalSorter::ExternalSorter(unsigned int filesBufferSize, bool showId) {
	this->showId = showId;
	this->filesBufferSize = filesBufferSize;
}

Heap<BinaryDictionaryRecord<true> >& ExternalSorter::getSortBuffer() {
	return this->sortBuffer;
}

unsigned int ExternalSorter::getFilesBufferSize() const {
    return this->filesBufferSize;
}

bool ExternalSorter::isShowId() const {
    return this->showId;
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

void ExternalSorter::unfreeze(BinaryOutputSequentialFile<BinaryDictionaryRecord<true> >& outputFreezeFile) {
	outputFreezeFile.close();

	BinaryInputSequentialFile<BinaryDictionaryRecord<true> > inputFile("particiones\\freezeFile_temp",this->getFilesBufferSize());
	this->createSortBuffer(inputFile);
	inputFile.close();

	outputFreezeFile.open("particiones\\freezeFile_temp",this->getFilesBufferSize());
}

void ExternalSorter::merge() {
	bool levelFinished;
	bool directoryCreated;
	std::vector<BinaryInputSequentialFile<BinaryDictionaryRecord<true> >*> readBuffers;

	BinaryInputSequentialFile<BinaryDictionaryRecord<true> > binaryInputSequentialFile;
	BinaryOutputSequentialFile<BinaryDictionaryRecord<true> > binaryOutputSequentialFile;
	BinaryDictionaryRecord<true> binaryRecord;
	unsigned int smallerRegisterIndex;

	unsigned int inputFileLevelCounter;
	unsigned int inputFileFileCounter;
	std::string inputDirectoryName = "particiones\\";

	unsigned int outputFileFileCounter;
	unsigned int outputFileRegisterCounter;
	std::string outputFileName;
	std::string outputDirectoryName;

	StatisticsRecord statisticsRecord;
	std::ofstream statisticsFile;
	statisticsFile.open("estadisticas.txt",std::iostream::app);

	inputFileLevelCounter = 0;

	directoryCreated = true;
	levelFinished = true;
	while(levelFinished && directoryCreated) {
		inputFileFileCounter = 0;
		outputFileFileCounter = 0;
		outputFileRegisterCounter = 0;
		levelFinished = false;
		directoryCreated = false;
		while (!levelFinished) {
			this->loadSortBuffer(readBuffers,inputDirectoryName,inputFileLevelCounter,inputFileFileCounter);
			if ( !( (readBuffers.empty()) || ( (readBuffers.size() == 1) && (inputFileFileCounter == 1) ) ) ) {
				if (!directoryCreated) {
					outputDirectoryName += "Etapa" + intToString(inputFileLevelCounter + 1) + "\\";

					//WINDOWS
					CreateDirectory(outputDirectoryName.c_str(),NULL);
					//LINUX
					//mkdir(outputDirectoryName.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

					directoryCreated = true;
				}

				outputFileName = outputDirectoryName + "orderedFile_" + intToString(inputFileLevelCounter + 1) + "_" + intToString(outputFileFileCounter);
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
				levelFinished = true;
				if (inputFileLevelCounter == 0)
					inputDirectoryName = "";
				inputDirectoryName += outputDirectoryName;
				inputFileLevelCounter++;
			}
		}
		if (directoryCreated) {
			statisticsRecord.getFilesStatistics().push_back(outputFileRegisterCounter);
		}
	}
	statisticsFile << "Etapas: " << std::endl;
	statisticsFile << statisticsRecord.serialize("Etapa") << std::endl;

	binaryInputSequentialFile.open(outputFileName,this->getFilesBufferSize());
	binaryOutputSequentialFile.open("dictionary_RANDOMIZED_ORDERED",this->getFilesBufferSize());

	while ( !(binaryInputSequentialFile.endOfFile()) ) {
		binaryRecord = binaryInputSequentialFile.getRecord();
		//binaryRecord.setShowId(this->isShowId());
		binaryOutputSequentialFile.putRecord(binaryRecord);
	}
	binaryOutputSequentialFile.close();
}

void ExternalSorter::sort(std::string filepath, bool leaveTraces){
	std::string tempFolderName = "particiones" + (unsigned)time(NULL);
	//WINDOWS
	CreateDirectory(tempFolderName.c_str(),NULL);

	//LINUX
	//mkdir(tempFolderName.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	unsigned int outputFileNameCounter = 0;
	unsigned int freezedRegisters = 0;
	std::string outputFilePath = tempFolderName + "\\orderedFile_0_" + intToString(outputFileNameCounter);
	BinaryInputSequentialFile<BinaryDictionaryRecord<true> > inputFile(filepath,this->getFilesBufferSize());
	BinaryOutputSequentialFile<BinaryDictionaryRecord<true> > outputlFile(outputFilePath,this->getFilesBufferSize());
	BinaryOutputSequentialFile<BinaryDictionaryRecord<true> > freezeFile(tempFolderName + "\\freezeFile_temp",this->getFilesBufferSize());
	BinaryDictionaryRecord<true> record;

	StatisticsRecord statisticsRecord;
	std::ofstream statisticsFile;
	statisticsFile.open("estadisticas.txt",std::iostream::app);
	unsigned int outputFileRegisterCounter = 0;

	this->createSortBuffer(inputFile);
	while ( !(inputFile.endOfFile()) ) {
		record = inputFile.getRecord();
		if (record < this->getSortBuffer().get(0)) {
			freezeFile.putRecord(record);
			freezedRegisters++;

			if (freezedRegisters == 10 * this->getFilesBufferSize()) {
				//vaciar heap
				outputFileRegisterCounter += this->getSortBuffer().size();
				statisticsRecord.getFilesStatistics().push_back(outputFileRegisterCounter);
				outputFileRegisterCounter = 0;

				this->flushSortBuffer(outputlFile);

				outputFileNameCounter++;
				outputFilePath = tempFolderName + "\\orderedFile_0_" + intToString(outputFileNameCounter);
				outputlFile.open(outputFilePath,this->getFilesBufferSize());

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
	statisticsRecord.getFilesStatistics().push_back(outputFileRegisterCounter);
	outputFileRegisterCounter = 0;
	this->flushSortBuffer(outputlFile);

	if (freezedRegisters != 0) {
		outputFileNameCounter++;
		outputFilePath = tempFolderName + "\\orderedFile_0_" + intToString(outputFileNameCounter);
		outputlFile.open(outputFilePath,this->getFilesBufferSize());

		this->unfreeze(freezeFile);

		outputFileRegisterCounter += this->getSortBuffer().size();
		statisticsRecord.getFilesStatistics().push_back(outputFileRegisterCounter);
		this->flushSortBuffer(outputlFile);
	}
	outputlFile.close();
	statisticsFile << "Particiones:" <<std::endl;
	statisticsFile << statisticsRecord.serialize("Partici�n") << std::endl;

	this->merge();

	if (!leaveTraces) {
		this->clearOutput();
		this->clearTemp(tempFolderName);
	}
}

void ExternalSorter::loadSortBuffer(std::vector<BinaryInputSequentialFile<BinaryDictionaryRecord<true> >*>& readBuffers, std::string& directoryName, unsigned int inputFileLevelCounter, unsigned int& inputFileFileCounter) {
	BinaryInputSequentialFile<BinaryDictionaryRecord<true> >* readBufferPointer;
	std::string inputFileName;
	bool finished = false;

	while ( !finished && (readBuffers.size() < this->getFilesBufferSize() + 1) ) {
		inputFileName = directoryName + "orderedFile_" + intToString(inputFileLevelCounter) + "_" + intToString(inputFileFileCounter);
		readBufferPointer = new BinaryInputSequentialFile<BinaryDictionaryRecord<true> >(inputFileName,this->getFilesBufferSize());

		if (readBufferPointer->endOfFile()) {
			delete readBufferPointer;
			finished = true;
		} else {
			readBuffers.push_back(readBufferPointer);
			inputFileFileCounter++;
		}
	}
}

void ExternalSorter::clearTemp(std::string tempFolderName) {
	bool finished = false;
	std::ifstream inputFile;
	std::string fileName;


	for (unsigned int i = 0; !finished; i++) {
		fileName = tempFolderName + "\\orderedFile_0_" + intToString(i);
		inputFile.open(fileName.c_str(),std::iostream::in);
		if (!inputFile.fail()) {
			inputFile.close();
			//WINDOWS
			DeleteFile(fileName.c_str());
			//LINUX
			//unlink(fileName.c_str());
		} else {
			finished = true;
		}
	}
	//WINDOWS
	DeleteFile((tempFolderName + "\\freezeFile_temp").c_str());
	//LINUX
	//unlink((tempFolderName + "\\freezeFile_temp").c_str());
}

void ExternalSorter::clearOutput(unsigned int level) {
	bool allFilesDeleted = false;
	bool folderExists = false;
	std::ifstream inputFile;
	std::string folderName = "Etapa1";
	std::string fileName;

	for (unsigned int i = 1; i < level; i++) {
		folderName += "\\Etapa" + intToString(i + 1);
	}

	for (unsigned int i = 0; !allFilesDeleted; i++) {
		fileName = folderName + "\\orderedFile_" + intToString(level) + "_" + intToString(i);
		inputFile.open(fileName.c_str(),std::iostream::in);
		if (!inputFile.fail()) {
			folderExists = true;
			inputFile.close();
			//WINDOWS
			DeleteFile(fileName.c_str());
			//LINUX
			//unlink(fileName.c_str());
		} else {
			allFilesDeleted = true;
			level++;
			if (folderExists)
				this->clearOutput(level);
		}
	}
	//WINDOWS
	RemoveDirectory(folderName.c_str());
	DeleteFile("estadisticas.txt");
	//LINUX
	//rmdir(folderName.c_str());
	//unlink("estadisticas.txt");
}

ExternalSorter::~ExternalSorter() {
}