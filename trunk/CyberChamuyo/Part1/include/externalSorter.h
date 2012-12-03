#ifndef EXTERNALSORTER_H_
#define EXTERNALSORTER_H_

#include <string>
#include <list>
#include "heap.h"
//#include "binaryInputSequentialFile.h"
//#include "binaryOutputSequentialFile.h"
//#include "variableLengthRecordSequentialFile.h"
//#include "binaryDictionaryRecord.h"
//#include "textOutputSequentialFile.h"
#include "logRecord.h"
#include "fileUtilities.h"
#include "stringUtilities.h"

#include "readBuffer.h"
#include "writeBuffer.h"

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

//Clase para realizar ordenamiento externo de archivos con registros de diccionario.
template<class File,class Record> class ExternalSorter {
private:
	//Monticulo para realizar el ordenamiento
	Heap<Record> sortBuffer;

	//Indica si se debe guardar el ID en el archivo final ordenado.
	bool showId;

	//Tamaño del buffer de los archivos.
	unsigned int buffersSize;

	unsigned int recordSize;

	//Nombre de la carpeta temporal en la que se guardarán los archivos de trabajo.
	std::string tempFolderName;
//
	//Log donde se guardaran los datos del ordenamiento.
	VariableLengthRecordSequentialFile<LogRecord> log;

	Heap<Record >& getSortBuffer();

	bool isShowId() const;

	unsigned int getBuffersSize() const;

	unsigned int getRecordSize() const;

	std::string getTempFolderName() const;

	VariableLengthRecordSequentialFile<LogRecord>& getLog();

	//Metodo para llenar el monticulo desde un archivo
	void createSortBuffer(ReadBuffer<File,Record>& readBuffer);

	//Metodo para escribir en un archivo el monticulo
	void flushSortBuffer(WriteBuffer<File,Record>& writeBuffer);

	//Metodo para armar el monticulo con los registros congelados.
	void unfreezeRecords(File& freezeFile);

	//Metodo para cargar los archivos de trabajo a unir.
	void loadMergeBuffer(std::list<ReadBuffer<File,Record>*>& readBuffers, std::string folderName, unsigned int inputFileLevelCounter, unsigned int& inputFileFileCounter);

	//Metodo para generar el nombre de la carpeta temporal segun la fecha y hora actual
	std::string generateTempFolderName();

	//Metodo para borrar los archivos de trabajo creados en las sucesivas etapas de ordenamiento.
	void clearPhase(std::string parentFolderName, unsigned int level);

	//Metodo para borrar la carpeta temporal de archivos de trabajo.
	void clearTemp();

	//Metodo para crear las particiones ordenadas.
	void createOrderedPartitions(std::string inputFilepath);

	//Metodo para unir las particiones ordenadas.
	void merge(std::string outputFilepath);

public:
	//Constructor
	ExternalSorter(unsigned int filesBufferSize, bool showId);

	ExternalSorter(unsigned int filesBufferSize, bool showId, unsigned int recordSize);

	//Metodo para ordenar un archivo desordenado.
	void sort(std::string inputFilepath, std::string outputFilepath, bool leaveTraces);

	//Destructor
	~ExternalSorter();
};

template<class File,class Record> ExternalSorter<File,Record>::ExternalSorter(unsigned int filesBufferSize, bool showId) {
	this->showId = showId;
	this->buffersSize = filesBufferSize;
	this->recordSize = 0;
	this->tempFolderName = this->generateTempFolderName();
}

template<class File,class Record> ExternalSorter<File,Record>::ExternalSorter(unsigned int filesBufferSize, bool showId, unsigned int recordSize) {
	this->showId = showId;
	this->buffersSize = filesBufferSize;
	this->recordSize = recordSize;
	this->tempFolderName = this->generateTempFolderName();
}

template<class File,class Record> Heap<Record>& ExternalSorter<File,Record>::getSortBuffer() {
	return this->sortBuffer;
}

template<class File,class Record> bool ExternalSorter<File,Record>::isShowId() const {
    return this->showId;
}

template<class File,class Record> unsigned int ExternalSorter<File,Record>::getBuffersSize() const {
    return this->buffersSize;
}

template<class File,class Record> unsigned int ExternalSorter<File,Record>::getRecordSize() const {
	return this->recordSize;
}

template<class File,class Record> std::string ExternalSorter<File,Record>::getTempFolderName() const {
	return this->tempFolderName;
}

template<class File,class Record> VariableLengthRecordSequentialFile<LogRecord>& ExternalSorter<File,Record>::getLog() {
	return this->log;
}

template<class File,class Record> void ExternalSorter<File,Record>::createSortBuffer(ReadBuffer<File,Record>& readBuffer) {
	while ( !(readBuffer.empty()) && (this->getSortBuffer().size() < 10 * this->getBuffersSize()) ) {
		this->getSortBuffer().insert(readBuffer.getRecord());
	}
}

template<class File,class Record> void ExternalSorter<File,Record>::flushSortBuffer(WriteBuffer<File,Record>& writeBuffer) {
	Record record;

	if (!this->getSortBuffer().empty()) {
		while (this->getSortBuffer().size() > 1) {
			writeBuffer.putRecord(this->getSortBuffer().get(0));
			record = this->getSortBuffer().get(this->getSortBuffer().size() - 1);
			this->getSortBuffer().popBack();
			this->getSortBuffer().replaceRoot(record);
		}
		writeBuffer.putRecord(this->getSortBuffer().get(0));
		this->getSortBuffer().popBack();
	}
}

template<class File,class Record> void ExternalSorter<File,Record>::unfreezeRecords(File& freezeFile) {
	freezeFile.open(this->getTempFolderName() + "/" + FREEZE_FILE_NAME);

	while (!freezeFile.endOfFile()) {
		this->getSortBuffer().insert(freezeFile.getNextRecord());
	}

	freezeFile.open(this->getTempFolderName() + "/" + FREEZE_FILE_NAME,true);
}

template<class File,class Record> void ExternalSorter<File,Record>::createOrderedPartitions(std::string inputFilepath) {
	unsigned int outputFileNameCounter = 0;
	unsigned int freezedRegisters = 0;
	unsigned int outputFileRegisterCounter = 0;
	ReadBuffer<File,Record>* readBuffer;
	WriteBuffer<File,Record>* writeBuffer;
	File freezeFile;
	if (this->getRecordSize() != 0) {
//		readBuffer = new ReadBuffer<File,Record>(5,256);
//		writeBuffer = new WriteBuffer<File,Record>(5,256);
	} else {
		readBuffer = new ReadBuffer<File,Record>(5);
		writeBuffer = new WriteBuffer<File,Record>(5);
	}

	std::string partitionOutputFilePath = this->getTempFolderName() + "/" + PHASE_FOLDER_NAME_PREFIX + "0/" + ORDERED_FILE_PART_PREFIX + "_0_" + StringUtilities::intToString(outputFileNameCounter);
	FileUtilities::createFolder(this->getTempFolderName() + "/" + PHASE_FOLDER_NAME_PREFIX + "0");
	Record record;
	LogRecord logRecord("Particiones","particion");
	freezeFile.open(this->getTempFolderName() + "/" + FREEZE_FILE_NAME,true);
	writeBuffer->initialize(partitionOutputFilePath);
	readBuffer->Initialize(inputFilepath);

	this->createSortBuffer(*readBuffer);
	while ( !(readBuffer->empty()) ) {
		record = readBuffer->getRecord();
		if (record < this->getSortBuffer().get(0)) {
			freezeFile.putRecord(record);
			freezedRegisters++;

			if (freezedRegisters == 10 * this->getBuffersSize()) {
				outputFileRegisterCounter += this->getSortBuffer().size();
				logRecord.getLogItems().push_back(outputFileRegisterCounter);
				outputFileRegisterCounter = 0;
				this->flushSortBuffer(*writeBuffer);
				outputFileNameCounter++;
				partitionOutputFilePath = this->getTempFolderName() + "/" + PHASE_FOLDER_NAME_PREFIX + "0/" + ORDERED_FILE_PART_PREFIX + "_0_" + StringUtilities::intToString(outputFileNameCounter);
				writeBuffer->initialize(partitionOutputFilePath);
				this->unfreezeRecords(freezeFile);
				freezedRegisters = 0;
			}
		} else {
			writeBuffer->putRecord(this->getSortBuffer().get(0));
			outputFileRegisterCounter++;
			this->getSortBuffer().replaceRoot(record);
		}
	}

	outputFileRegisterCounter += this->getSortBuffer().size();
	logRecord.getLogItems().push_back(outputFileRegisterCounter);
	outputFileRegisterCounter = 0;
	this->flushSortBuffer(*writeBuffer);

	if (freezedRegisters != 0) {
		outputFileNameCounter++;
		partitionOutputFilePath = this->getTempFolderName() + "/" + PHASE_FOLDER_NAME_PREFIX + "0/" + ORDERED_FILE_PART_PREFIX + "_0_" + StringUtilities::intToString(outputFileNameCounter);
		writeBuffer->initialize(partitionOutputFilePath);
		this->unfreezeRecords(freezeFile);
		outputFileRegisterCounter += this->getSortBuffer().size();
		logRecord.getLogItems().push_back(outputFileRegisterCounter);
		this->flushSortBuffer(*writeBuffer);
	}

	this->getLog().putRecord(logRecord);

	delete readBuffer;
	delete writeBuffer;
}

template<class File,class Record> void ExternalSorter<File,Record>::merge(std::string outputFilepath) {
	bool levelFinished = true;
	bool directoryCreated = true;
	std::list<ReadBuffer<File,Record>*> readBuffers;
	typename std::list<ReadBuffer<File,Record>*>::iterator readBuffersIt;
	typename std::list<ReadBuffer<File,Record>*>::iterator smallerRecordIt;
	File binaryInputSequentialFile;
	WriteBuffer<File,Record>* writeBuffer;
	Record binaryRecord;
	unsigned int inputFileLevelCounter = 0;
	unsigned int inputFileFileCounter;
	std::string inputDirectoryName = this->getTempFolderName() + "/" + PHASE_FOLDER_NAME_PREFIX + "0/";
	unsigned int outputFileFileCounter;
	unsigned int outputFileRegisterCounter;
	std::string outputFileName;
	std::string outputDirectoryName = this->getTempFolderName() + "/" + PHASE_FOLDER_NAME_PREFIX + "0/";
	LogRecord logRecord("Etapas","Etapa");

	if (this->getRecordSize() != 0) {
		//writeBuffer = new WriteBuffer<File,Record>(5,256);
	} else {
		writeBuffer = new WriteBuffer<File,Record>(5);
	}

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
					writeBuffer->initialize(outputFileName);
					outputFileFileCounter++;

					while ( (!readBuffers.empty()) ) {
						smallerRecordIt = readBuffers.begin();
						for (readBuffersIt = readBuffers.begin(); readBuffersIt != readBuffers.end() ; ++readBuffersIt) {
							if ((*readBuffersIt)->peekRecord() < (*smallerRecordIt)->peekRecord())
								smallerRecordIt = readBuffersIt;
						}

						writeBuffer->putRecord((*smallerRecordIt)->getRecord());
						outputFileRegisterCounter++;
						if ((*smallerRecordIt)->empty()) {
							delete (*smallerRecordIt);
							readBuffers.erase(smallerRecordIt);
						}
					}
				} else {
					outputFileName = outputDirectoryName + ORDERED_FILE_PART_PREFIX + "_" + StringUtilities::intToString(inputFileLevelCounter) + "_" + StringUtilities::intToString(outputFileFileCounter);
					levelFinished = true;
				}
			} else {
				levelFinished = true;
				inputDirectoryName = "";
				inputDirectoryName += outputDirectoryName;
				inputFileLevelCounter++;
			}
		}
		if (directoryCreated) {
			logRecord.getLogItems().push_back(outputFileRegisterCounter);
		}
	}

	writeBuffer->initialize(outputFilepath);
	binaryInputSequentialFile.open(outputFileName,true);

	while ( !(binaryInputSequentialFile.endOfFile()) ) {
		binaryRecord = binaryInputSequentialFile.getNextRecord();
		writeBuffer->putRecord(binaryRecord);
	}

	this->getLog().putRecord(logRecord);

	delete writeBuffer;
}

template<class File,class Record> void ExternalSorter<File,Record>::sort(std::string inputFilepath, std::string outputFilepath, bool leaveTraces) {
	FileUtilities::createFolder(this->getTempFolderName());
	this->getLog().open(this->getTempFolderName() + "/" + LOG_FILE_NAME,true);

	this->createOrderedPartitions(inputFilepath);

	this->merge(outputFilepath);

	if (!leaveTraces)
		this->clearTemp();
}

template<class File,class Record> void ExternalSorter<File,Record>::loadMergeBuffer(std::list<ReadBuffer<File,Record>*>& readBuffers, std::string folderName, unsigned int inputFileLevelCounter, unsigned int& inputFileFileCounter) {
	ReadBuffer<File,Record>* readBufferPointer;
	std::string inputFileName;
	bool finished = false;

	while ( !finished && (readBuffers.size() < this->getBuffersSize() + 1) ) {
		inputFileName = folderName + ORDERED_FILE_PART_PREFIX + "_" + StringUtilities::intToString(inputFileLevelCounter) + "_" + StringUtilities::intToString(inputFileFileCounter);
		readBufferPointer = new ReadBuffer<File,Record>(this->getBuffersSize());
		readBufferPointer->Initialize(inputFileName);

		if (readBufferPointer->empty()) {
			delete readBufferPointer;
			finished = true;
		} else {
			readBuffers.push_back(readBufferPointer);
			inputFileFileCounter++;
		}
	}
}

template<class File,class Record> std::string ExternalSorter<File,Record>::generateTempFolderName() {
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

template<class File,class Record> void ExternalSorter<File,Record>::clearPhase(std::string parentFolderName, unsigned int level) {
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

template<class File,class Record> void ExternalSorter<File,Record>::clearTemp() {
	this->clearPhase(this->getTempFolderName(),0);
	FileUtilities::deleteFile(this->getTempFolderName() + "/" + FREEZE_FILE_NAME);
	this->getLog().close();
	FileUtilities::deleteFile(this->getTempFolderName() + "/" + LOG_FILE_NAME);
	FileUtilities::deleteFolder(this->getTempFolderName());
}

template<class File,class Record> ExternalSorter<File,Record>::~ExternalSorter() {
}


#endif /* EXTERNALSORTER_H_ */
