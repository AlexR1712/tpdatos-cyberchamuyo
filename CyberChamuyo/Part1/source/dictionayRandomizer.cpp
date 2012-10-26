#include "../include/dictionaryRandomizer.h"


//quitar esto cuando ande c++ 11
//#include <time.h>
//#include <stdlib.h>

#include "../include/textInputSequentialFile.h"
#include "../include/textOutputSequentialFile.h"
#include "../include/binaryOutputSequentialFile.h"
#include "../include/textDictionaryRecord.h"
#include "../include/textRecord.h"
#include "../include/binaryDictionaryRecord.h"
#include "../include/externalSorter.h"

DictionayRandomizer::DictionayRandomizer() {
	this->getGenerator().seed(std::chrono::system_clock::now().time_since_epoch().count());

	//quitar esto cuando ande c++ 11
	//srand((unsigned)time(NULL));
}

std::default_random_engine& DictionayRandomizer::getGenerator() {
	return this->generator;
}

void DictionayRandomizer::createRandomIds(std::string dictionaryPath) {
	TextInputSequentialFile<TextRecord> dictionary(dictionaryPath,FILE_BUFFER_SIZE);
	TextOutputSequentialFile<TextDictionaryRecord<true> > textRandomizedDiccionary(OUTPUT_FILE_PATH_TEXT,FILE_BUFFER_SIZE);
	BinaryOutputSequentialFile<BinaryDictionaryRecord<true> > binaryRandomizedDiccionary(OUTPUT_FILE_PATH_BINARY,FILE_BUFFER_SIZE);
	TextRecord inputRecord;
	TextDictionaryRecord<true> outputTextRecord;
	BinaryDictionaryRecord<true> outputBinaryRecord;
	std::string line;
	std::string randomizedLine;
	long random;

	while (!dictionary.endOfFile()) {
		random = generateRandomId();
		inputRecord = dictionary.getRecord();
		outputTextRecord.setId(random);
		outputTextRecord.setWord(inputRecord.getData());
		outputBinaryRecord.setId(random);
		outputBinaryRecord.setWord(inputRecord.getData());
		textRandomizedDiccionary.putRecord(outputTextRecord);
		binaryRandomizedDiccionary.putRecord(outputBinaryRecord);
	}
}

long DictionayRandomizer::generateRandomId() {
	std::uniform_int_distribution<int> distribution(RANDOM_RANGE_MIN,RANDOM_RANGE_MAX);
	return distribution(this->getGenerator());

	//quitar esto cuando ande c++ 11
	//return rand();
}

void DictionayRandomizer::randomizeDictionary(std::string dictionaryPath, bool showId) {
	ExternalSorter externalSorter(FILE_BUFFER_SIZE,showId);

	this->createRandomIds(dictionaryPath);

	externalSorter.sort(OUTPUT_FILE_PATH_BINARY,OUTPUT_FILE_PATH_BINARY_ORDERED,true);
}

DictionayRandomizer::~DictionayRandomizer() {
}
