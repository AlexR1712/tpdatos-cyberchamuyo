#include "dictionaryRandomizer.h"

#include <time.h>
#include <stdlib.h>

#include "textInputSequentialFile.h"
#include "textOutputSequentialFile.h"
#include "binaryOutputSequentialFile.h"
#include "textDictionaryRecord.h"
#include "binaryDictionaryRecord.h"
#include "externalSorter.h"

DictionayRandomizer::DictionayRandomizer() {
}

void DictionayRandomizer::createRandomIds(std::string dictionaryPath) {
	TextInputSequentialFile<TextDictionaryRecord<false> > dictionary(dictionaryPath,FILE_BUFFER_SIZE);
	TextOutputSequentialFile<TextDictionaryRecord<true> > textRandomizedDiccionary(OUTPUT_FILE_PATH_TEXT,FILE_BUFFER_SIZE);
	BinaryOutputSequentialFile<BinaryDictionaryRecord<true> > binaryRandomizedDiccionary(OUTPUT_FILE_PATH_BINARY,FILE_BUFFER_SIZE);
	TextDictionaryRecord<false> inputRecord;
	TextDictionaryRecord<true> outputTextRecord;
	BinaryDictionaryRecord<true> outputBinaryRecord;
	std::string line;
	std::string randomizedLine;
	int random;
	srand((unsigned)time(NULL));

	while (!dictionary.endOfFile()) {
		random = rand();
		inputRecord = dictionary.getRecord();
		outputTextRecord.setId(random);
		outputTextRecord.setWord(inputRecord.getWord());
		outputBinaryRecord.setId(random);
		outputBinaryRecord.setWord(inputRecord.getWord());
		textRandomizedDiccionary.putRecord(outputTextRecord);
		binaryRandomizedDiccionary.putRecord(outputBinaryRecord);
	}
}

void DictionayRandomizer::randomizeDictionary(std::string dictionaryPath, bool showId) {
	ExternalSorter externalSorter(FILE_BUFFER_SIZE,showId);

	this->createRandomIds(dictionaryPath);

	externalSorter.sort(OUTPUT_FILE_PATH_BINARY);
}

DictionayRandomizer::~DictionayRandomizer() {
}
