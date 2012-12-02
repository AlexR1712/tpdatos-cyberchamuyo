#include "../include/dictionaryNormalizer.h"

#include "../include/propertiesLoader.h"
//#include "../include/textInputSequentialFile.h"
//#include "../include/textOutputSequentialFile.h"
#include "../include/variableLengthRecordSequentialFile.h"
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
	//VariableLengthRecordSequentialFile<TextRecord> dictionaryFile;
	std::ifstream dictionaryFile;
	VariableLengthRecordSequentialFile<TextRecord> normalizedDictionaryFile;
	std::string word;
	TextRecord record;

	dictionaryFile.open(dictionaryPath.c_str(),std::ios::in);
	normalizedDictionaryFile.open(this->getOutputFilePath(),true);
	if (dictionaryFile.good()) {
		std::getline(dictionaryFile,word);
		while (!dictionaryFile.eof()) {
			if (word != "") {
				record.setData(wordNormalizer.normalizeWord(word));
				normalizedDictionaryFile.putRecord(record);
			}
			std::getline(dictionaryFile,word);
		}
	}
}

DictionaryNormalizer::~DictionaryNormalizer() {
}
