#include "externalSorter.h"

#include <fstream>
#include <iostream>

#include <vector>

#include "record.h"
#include "heap.h"
#include "readBuffer.h"
#include "writeBuffer.h"
#include "stringUtilities.h"

ExternalSorter::ExternalSorter() {
}

void ExternalSorter::sort(std::string filepath){
	unsigned int outputFileNameCounter = 0;
	unsigned int freezedRegisters = 0;
	std::string outputFileName = "orderedFile_0_" + intToString(outputFileNameCounter);
	Heap sortBuffer;
	ReadBuffer readBuffer(filepath,N);
	WriteBuffer writeBuffer(outputFileName,N);
	WriteBuffer freezeBuffer("freezeFile_temp",N);
	ReadBuffer freezeReadBuffer(N);
	Record record;

	while ( (sortBuffer.getHeap().size() < 10 * N) && !(readBuffer.empty()) ) {
		record = readBuffer.getRecord();
		sortBuffer.insert(record);
	}

	while ( !(readBuffer.empty()) ) {
		record = readBuffer.getRecord();
		if (record < sortBuffer.getHeap()[0]) {
			freezeBuffer.putRecord(record);
			freezedRegisters++;
			if (freezedRegisters == 10 * N) {
				//vaciar heap
				while (sortBuffer.getHeap().size() > 1) {
					writeBuffer.putRecord(sortBuffer.getHeap()[0]);
					record = sortBuffer.getHeap()[sortBuffer.getHeap().size() - 1];
					sortBuffer.getHeap().pop_back();
					sortBuffer.replaceRoot(record);
				}
				writeBuffer.putRecord(sortBuffer.getHeap()[0]);
				sortBuffer.getHeap().pop_back();

				outputFileNameCounter++;
				outputFileName = "orderedFile_0_" + intToString(outputFileNameCounter);
				writeBuffer.initialize(outputFileName);

				//rearmarlo con el freezeBuffer
				freezeBuffer.finalize();
				freezeReadBuffer.initialize("freezeFile_temp");
				while ( !(freezeReadBuffer.empty()) ) {
					record = freezeReadBuffer.getRecord();
					sortBuffer.insert(record);
				}
				freezeReadBuffer.finalize();
				freezeBuffer.initialize("freezeFile_temp");
				freezedRegisters = 0;
			}
		} else {
			writeBuffer.putRecord(sortBuffer.getHeap()[0]);
			sortBuffer.replaceRoot(record);
		}
	}
	//vaciar heap
	while (sortBuffer.getHeap().size() > 1) {
		writeBuffer.putRecord(sortBuffer.getHeap()[0]);
		record = sortBuffer.getHeap()[sortBuffer.getHeap().size() - 1];
		sortBuffer.getHeap().pop_back();
		sortBuffer.replaceRoot(record);
	}
	if (sortBuffer.getHeap().size() == 1) {
		writeBuffer.putRecord(sortBuffer.getHeap()[0]);
		sortBuffer.getHeap().pop_back();
	}
	writeBuffer.finalize();

	//rearmarlo con el freezeBuffer
	freezeBuffer.finalize();
	freezeReadBuffer.initialize("freezeFile_temp");
	while ( !(freezeReadBuffer.empty()) ) {
		record = freezeReadBuffer.getRecord();
		sortBuffer.insert(record);
	}
	freezeReadBuffer.finalize();
	freezeBuffer.initialize("freezeFile_temp");
	freezedRegisters = 0;

	if (!sortBuffer.getHeap().empty()) {
		outputFileNameCounter++;
		outputFileName = "orderedFile_0_" + intToString(outputFileNameCounter);
		writeBuffer.initialize(outputFileName);
		//volver a vaciar heap
		while (sortBuffer.getHeap().size() > 1) {
			writeBuffer.putRecord(sortBuffer.getHeap()[0]);
			record = sortBuffer.getHeap()[sortBuffer.getHeap().size() - 1];
			sortBuffer.getHeap().pop_back();
			sortBuffer.replaceRoot(record);
		}
		if (sortBuffer.getHeap().size() == 1) {
			writeBuffer.putRecord(sortBuffer.getHeap()[0]);
			sortBuffer.getHeap().pop_back();
		}
	}

	//merge de archivos
	bool finished;
	bool levelFinished;
	std::vector<ReadBuffer*> readBuffers;
	ReadBuffer* readBufferPointer;
	WriteBuffer writeBuffer2(N);
	unsigned int smallerRegisterIndex;
	unsigned int inputFileLevelCounter;
	unsigned int inputFileFileCounter;
	unsigned int outputFileFileCounter;
	std::string inputFileName;

	inputFileLevelCounter = 0;
	finished = false;
	while (!finished) {
		inputFileFileCounter = 0;
		outputFileFileCounter = 0;
		levelFinished = false;
		while (!levelFinished) {
			while ( (!levelFinished) && (readBuffers.size() < N + 1) ) {
				inputFileName = "orderedFile_" + intToString(inputFileLevelCounter) + "_" + intToString(inputFileFileCounter);
				readBufferPointer = new ReadBuffer(inputFileName,N);

				if (readBufferPointer->empty()) {
					levelFinished = true;
					delete readBufferPointer;
				} else {
					readBuffers.push_back(readBufferPointer);
					inputFileFileCounter++;
				}
			}

			if ( (readBuffers.empty()) || ( (readBuffers.size() == 1) && (inputFileFileCounter == 1) ) ) {
				finished = true;
			} else {
				outputFileName = "orderedFile_" + intToString(inputFileLevelCounter + 1) + "_" + intToString(outputFileFileCounter);
				writeBuffer2.initialize(outputFileName);
				outputFileFileCounter++;
			}

			//ordenar
			while ( (!readBuffers.empty()) && (!finished) ) {
				smallerRegisterIndex = 0;
				for (unsigned int i = 1; i < readBuffers.size(); i++) {
					if (readBuffers[i]->front() < readBuffers[smallerRegisterIndex]->front())
						smallerRegisterIndex = i;
				}

				writeBuffer2.putRecord(readBuffers[smallerRegisterIndex]->getRecord());
				if (readBuffers[smallerRegisterIndex]->empty()) {
					delete readBuffers[smallerRegisterIndex];
					readBuffers.erase(readBuffers.begin() + smallerRegisterIndex);
				}
			}
		}
		inputFileLevelCounter++;
	}



}

ExternalSorter::~ExternalSorter() {
}
