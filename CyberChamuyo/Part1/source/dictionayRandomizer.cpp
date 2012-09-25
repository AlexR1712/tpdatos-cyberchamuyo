#include "dictionaryRandomizer.h"

#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>

#include "readBuffer.h"
#include "writeBuffer.h"
#include "stringRecord.h"
#include "binaryRecord.h"
#include "externalSorter.h"
#include "stringUtilities.h"

DictionayRandomizer::DictionayRandomizer() {
}

void DictionayRandomizer::randomizeDictionary(std::string dictionaryPath, bool showId) {
	ReadBuffer<StringRecord> readBuffer(dictionaryPath,N);
	WriteBuffer<StringRecord> stringWriteBuffer("dictionary_RANDOMIZED.txt",N);
	WriteBuffer<BinaryRecord> binaryWriteBuffer("dictionary_RANDOMIZED",N);
	ExternalSorter externalSorter(N,showId);
	StringRecord stringRecord;
	BinaryRecord binaryRecord;
	std::string line;
	std::string randomizedLine;
	int random;

	srand((unsigned)time(NULL));

	while (!readBuffer.empty()) {
		random = rand();
		line = readBuffer.getRecord().getWord();
		randomizedLine = intToString(random) + '\t' + line;
		stringRecord.parseString(randomizedLine);
		binaryRecord.parseString(randomizedLine);
		stringWriteBuffer.putRecord(stringRecord);
		binaryWriteBuffer.putRecord(binaryRecord);
	}

	binaryWriteBuffer.finalize();
	externalSorter.sort("dictionary_RANDOMIZED");
}

DictionayRandomizer::~DictionayRandomizer() {
}
