#include "../include/dictionaryNormalizer.h"

#include "../include/propertiesLoader.h"
#include "../include/textInputSequentialFile.h"
#include "../include/textOutputSequentialFile.h"
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
	TextInputSequentialFile<TextRecord> dictionaryFile(dictionaryPath,10);
	TextOutputSequentialFile<TextRecord> normalizedDictionaryFile(this->getOutputFilePath(),10);
	TextRecord record;

	while (!dictionaryFile.endOfFile()) {
		record = dictionaryFile.getRecord();
		if (record.getData() != "") {
			record.setData(wordNormalizer.normalizeWord(record.getData()));
			normalizedDictionaryFile.putRecord(record);
		}
	}
}

DictionaryNormalizer::~DictionaryNormalizer() {
}
