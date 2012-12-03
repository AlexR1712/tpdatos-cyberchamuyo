#include "../include/dictionaryNormalizer.h"

#include "../include/propertiesLoader.h"
#include "../include/variableLengthRecordSequentialFile.h"
#include "../include/textFile.h"
#include "../include/textRecord.h"
#include "../include/wordNormalizer.h"

DictionaryNormalizer::DictionaryNormalizer() {
	PropertiesLoader propertiesLoader("config/dictionaryNormalizer.properties");
	this->outputFilePath = propertiesLoader.getPropertyValue(OUTPUT_FILE_PATH_PROPERTY_NAME);
}

std::string DictionaryNormalizer::getOutputFilePath() const {
	return this->outputFilePath;
}

void DictionaryNormalizer::normalize(std::string dictionaryPath) {
	WordNormalizer wordNormalizer;
	TextFile<TextRecord> dictionaryFile;
	//std::ifstream dictionaryFile;
	TextFile<TextRecord> normalizedDictionaryFile;
//	std::string word;
	TextRecord record;

	dictionaryFile.open(dictionaryPath);
	normalizedDictionaryFile.open(this->getOutputFilePath(),true);
	if (dictionaryFile.isFileExists()) {
		//std::getline(dictionaryFile,word);
		while (!dictionaryFile.endOfFile()) {
			record = dictionaryFile.getNextRecord();
			if (record.getData() != "") {
				record.setData(wordNormalizer.normalizeWord(record.getData()));
				normalizedDictionaryFile.putRecord(record);
			}
//			std::getline(dictionaryFile,word);
		}
	}
}

DictionaryNormalizer::~DictionaryNormalizer() {
}
