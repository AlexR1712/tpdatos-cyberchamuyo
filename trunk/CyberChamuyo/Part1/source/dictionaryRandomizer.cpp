#include "../include/dictionaryRandomizer.h"

#include "../include/propertiesLoader.h"
#include "../include/textInputSequentialFile.h"
#include "../include/textOutputSequentialFile.h"
#include "../include/binaryOutputSequentialFile.h"
#include "../include/textDictionaryRecord.h"
#include "../include/textRecord.h"
#include "../include/binaryDictionaryRecord.h"
#include "../include/externalSorter.h"
#include "../include/stringUtilities.h"

DictionaryRandomizer::DictionaryRandomizer() {
	PropertiesLoader propertiesLoader("config/dictionaryRandomizer.properties");
	this->randomRangeMin = StringUtilities::stringToInt(propertiesLoader.getPropertyValue(RANDOM_RANGE_MIN));
	this->randomRangeMax = StringUtilities::stringToInt(propertiesLoader.getPropertyValue(RANDOM_RANGE_MAX));
	this->randomizedDictionaryAsTextFilePath = propertiesLoader.getPropertyValue(OUTPUT_FILE_PATH_TEXT);
	this->randomizedDictionaryAsBinaryFilePath = propertiesLoader.getPropertyValue(OUTPUT_FILE_PATH_BINARY);
	this->orderedRandomizedDictionaryFilePath = propertiesLoader.getPropertyValue(OUTPUT_FILE_PATH_BINARY_ORDERED);
	this->getGenerator().seed(std::chrono::system_clock::now().time_since_epoch().count());
}

std::default_random_engine& DictionaryRandomizer::getGenerator() {
	return this->generator;
}

unsigned int DictionaryRandomizer::getRandomRangeMin() const {
    return this->randomRangeMin;
}

unsigned int DictionaryRandomizer::getRandomRangeMax() const {
    return this->randomRangeMax;
}

std::string DictionaryRandomizer::getRandomizedDictionaryAsTextFilePath() const {
    return this->randomizedDictionaryAsTextFilePath;
}

std::string DictionaryRandomizer::getRandomizedDictionaryAsBinaryFilePath() const {
    return this->randomizedDictionaryAsBinaryFilePath;
}

std::string DictionaryRandomizer::getOrderedRandomizedDictionaryFilePath() const {
    return this->orderedRandomizedDictionaryFilePath;
}

void DictionaryRandomizer::createRandomIds(std::string dictionaryPath) {
	TextInputSequentialFile<TextRecord> dictionary(dictionaryPath,5);
	TextOutputSequentialFile<TextDictionaryRecord<true> > textRandomizedDiccionary(this->getRandomizedDictionaryAsTextFilePath(),5);
	BinaryOutputSequentialFile<BinaryDictionaryRecord<true> > binaryRandomizedDiccionary(this->getRandomizedDictionaryAsBinaryFilePath(),5);
	TextRecord inputRecord;
	TextDictionaryRecord<true> outputTextRecord;
	BinaryDictionaryRecord<true> outputBinaryRecord;
	std::string line;
	std::string randomizedLine;
	long random;

	while (!dictionary.endOfFile()) {
		inputRecord = dictionary.getRecord();
		if (inputRecord.getData() != "") {
			random = generateRandomId();
			outputTextRecord.setId(random);
			outputTextRecord.setWord(inputRecord.getData());
			outputBinaryRecord.setId(random);
			outputBinaryRecord.setWord(inputRecord.getData());
			textRandomizedDiccionary.putRecord(outputTextRecord);
			binaryRandomizedDiccionary.putRecord(outputBinaryRecord);
		}
	}
}

long DictionaryRandomizer::generateRandomId() {
	std::uniform_int_distribution<int> distribution(this->getRandomRangeMin(),this->getRandomRangeMax());
	return distribution(this->getGenerator());
}

void DictionaryRandomizer::randomizeDictionary(std::string dictionaryPath, bool showId) {
	ExternalSorter externalSorter(5,showId);

	this->createRandomIds(dictionaryPath);

	externalSorter.sort(this->getRandomizedDictionaryAsBinaryFilePath(),this->getOrderedRandomizedDictionaryFilePath(),true);
}

DictionaryRandomizer::~DictionaryRandomizer() {
}
