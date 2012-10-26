#include "../include/externalSorter.h"

#include <time.h>

#include "../include/textInputSequentialFile.h"
#include "../include/binaryInputSequentialFile.h"
#include "../include/binaryOutputSequentialFile.h"
#include "../include/statisticsRecord.h"
#include "../include/stringUtilities.h"

#define LINUX

//WINDOWS
#ifdef WINDOWS
#include "windows.h"
#endif
//LINUX
#ifdef LINUX
#include <sys/stat.h>
#endif

ExternalSorter::ExternalSorter(unsigned int filesBufferSize, bool showId) {
	this->showId = showId;
	this->filesBufferSize = filesBufferSize;

	//TODO pasar a chrono
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime (&rawtime);

	this->tempFolderName = "particiones_" +
							StringUtilities::intToString(timeinfo->tm_year + 1900) +
							StringUtilities::intToString(timeinfo->tm_mon + 1) +
							StringUtilities::intToString(timeinfo->tm_mday) +
							StringUtilities::intToString(timeinfo->tm_hour) +
							StringUtilities::intToString(timeinfo->tm_min) +
							StringUtilities::intToString(timeinfo->tm_sec);
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

	BinaryInputSequentialFile<BinaryDictionaryRecord<true> > inputFile(tempFolderName + "/freezeFile_temp",this->getFilesBufferSize());
	this->createSortBuffer(inputFile);
	inputFile.close();

	outputFreezeFile.open(tempFolderName + "/freezeFile_temp",this->getFilesBufferSize());
}

void ExternalSorter::merge(std::string outputFilepath) {
	bool levelFinished;
	bool directoryCreated;
	std::vector<BinaryInputSequentialFile<BinaryDictionaryRecord<true> >*> readBuffers;

	BinaryInputSequentialFile<BinaryDictionaryRecord<true> > binaryInputSequentialFile;
	BinaryOutputSequentialFile<BinaryDictionaryRecord<true> > binaryOutputSequentialFile;
	BinaryDictionaryRecord<true> binaryRecord;
	unsigned int smallerRegisterIndex;

	unsigned int inputFileLevelCounter;
	unsigned int inputFileFileCounter;
	std::string inputDirectoryName = tempFolderName + "/";

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
					outputDirectoryName += "Etapa" + StringUtilities::intToString(inputFileLevelCounter + 1) + "/";

					//WINDOWS
//#ifdef WINDOWS
//					CreateDirectory(outputDirectoryName.c_str(),NULL);
//#endif
					//LINUX
					mkdir(outputDirectoryName.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
					directoryCreated = true;
				}

				outputFileName = outputDirectoryName + "orderedFile_" + StringUtilities::intToString(inputFileLevelCounter + 1) + "_" + StringUtilities::intToString(outputFileFileCounter);
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
	if(( (readBuffers.size() == 1) && (inputFileFileCounter == 1) ) && !outputFileName.size()) {
		outputDirectoryName = tempFolderName + "/";
		outputFileName = outputDirectoryName + "orderedFile_" + StringUtilities::intToString(0) + "_" + StringUtilities::intToString(0);
	}
	statisticsFile << "Etapas: " << std::endl;
	statisticsFile << statisticsRecord.serialize("Etapa") << std::endl;

	binaryInputSequentialFile.open(outputFileName,this->getFilesBufferSize());
	binaryOutputSequentialFile.open(outputFilepath,this->getFilesBufferSize());

	while ( !(binaryInputSequentialFile.endOfFile()) ) {
		binaryRecord = binaryInputSequentialFile.getRecord();
		binaryOutputSequentialFile.putRecord(binaryRecord);
	}
	binaryOutputSequentialFile.close();
}

void ExternalSorter::sort(std::string inputFilepath, std::string outputFilepath, bool leaveTraces) {

	//WINDOWS
#ifdef WINDOWS
	CreateDirectory(tempFolderName.c_str(),NULL);
#endif
#ifdef LINUX
	//LINUX
	mkdir(tempFolderName.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif
	unsigned int outputFileNameCounter = 0;
	unsigned int freezedRegisters = 0;
	std::string partOutputFilePath = tempFolderName + "/orderedFile_0_" + StringUtilities::intToString(outputFileNameCounter);
	BinaryInputSequentialFile<BinaryDictionaryRecord<true> > inputFile(inputFilepath,this->getFilesBufferSize());
	BinaryOutputSequentialFile<BinaryDictionaryRecord<true> > outputlFile(partOutputFilePath,this->getFilesBufferSize());
	BinaryOutputSequentialFile<BinaryDictionaryRecord<true> > freezeFile(tempFolderName + "/freezeFile_temp",this->getFilesBufferSize());
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
				partOutputFilePath = tempFolderName + "/orderedFile_0_" + StringUtilities::intToString(outputFileNameCounter);
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
	statisticsRecord.getFilesStatistics().push_back(outputFileRegisterCounter);
	outputFileRegisterCounter = 0;
	this->flushSortBuffer(outputlFile);

	if (freezedRegisters != 0) {
		outputFileNameCounter++;
		partOutputFilePath = tempFolderName + "/orderedFile_0_" + StringUtilities::intToString(outputFileNameCounter);
		outputlFile.open(partOutputFilePath,this->getFilesBufferSize());

		this->unfreeze(freezeFile);

		outputFileRegisterCounter += this->getSortBuffer().size();
		statisticsRecord.getFilesStatistics().push_back(outputFileRegisterCounter);
		this->flushSortBuffer(outputlFile);
	}
	outputlFile.close();
	statisticsFile << "Particiones:" <<std::endl;
	statisticsFile << statisticsRecord.serialize("Particion") << std::endl;

	this->merge(outputFilepath);

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
		inputFileName = directoryName + "orderedFile_" + StringUtilities::intToString(inputFileLevelCounter) + "_" + StringUtilities::intToString(inputFileFileCounter);
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
		fileName = tempFolderName + "/orderedFile_0_" + StringUtilities::intToString(i);
		inputFile.open(fileName.c_str(),std::iostream::in);
		if (!inputFile.fail()) {
			inputFile.close();
			//WINDOWS
#ifdef WINDOWS
			DeleteFile(fileName.c_str());
#endif
#ifdef LINUX
			//LINUX
			unlink(fileName.c_str());
#endif
		} else {
			finished = true;
		}
	}
	//WINDOWS
#ifdef WINDOWS
	DeleteFile((tempFolderName + "\\freezeFile_temp").c_str());
#endif
#ifdef LINUX
	//LINUX
	unlink((tempFolderName + "\\freezeFile_temp").c_str());
#endif
}

void ExternalSorter::clearOutput(unsigned int level) {
	bool allFilesDeleted = false;
	bool folderExists = false;
	std::ifstream inputFile;
	std::string folderName = "Etapa1";
	std::string fileName;

	for (unsigned int i = 1; i < level; i++) {
		folderName += "/Etapa" + StringUtilities::intToString(i + 1);
	}

	for (unsigned int i = 0; !allFilesDeleted; i++) {
		fileName = folderName + "/orderedFile_" + StringUtilities::intToString(level) + "_" + StringUtilities::intToString(i);
		inputFile.open(fileName.c_str(),std::iostream::in);
		if (!inputFile.fail()) {
			folderExists = true;
			inputFile.close();
			//WINDOWS
#ifdef WINDOWS
			DeleteFile(fileName.c_str());
#endif
			//LINUX
#ifdef LINUX
			unlink(fileName.c_str());
#endif
		} else {
			allFilesDeleted = true;
			level++;
			if (folderExists)
				this->clearOutput(level);
		}
	}
	//WINDOWS
#ifdef WINDOWS
	RemoveDirectory(folderName.c_str());
	DeleteFile("estadisticas.txt");
#endif
	//LINUX
#ifdef LINUX
	rmdir(folderName.c_str());
	unlink("estadisticas.txt");
#endif
}

ExternalSorter::~ExternalSorter() {
}
