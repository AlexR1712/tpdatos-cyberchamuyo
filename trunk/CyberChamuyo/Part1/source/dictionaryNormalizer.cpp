#include "../include/dictionaryNormalizer.h"

#include "../include/textInputSequentialFile.h"
#include "../include/textOutputSequentialFile.h"
#include "../include/textRecord.h"

DictionaryNormalizer::DictionaryNormalizer() {
	loadCharmap();
}

std::map<char,char>& DictionaryNormalizer::getCharMap() {
	return this->charMap;
}

void DictionaryNormalizer::loadCharmap() {
	TextInputSequentialFile<TextRecord> charMapFile(CHAR_MAP_FILE_PATH,FILE_BUFFER_SIZE);
	std::string charMapLine;

	while (!charMapFile.endOfFile()) {
		charMapLine = charMapFile.getRecord().getData();
		this->getCharMap().insert(std::pair<char,char>(charMapLine[0],charMapLine[2]));
	}
}

std::string DictionaryNormalizer::normalizeWord(const std::string string) {
	std::string normalizedWord;
	char c;
	std::map<char,char>::iterator it;

	for (unsigned int i = 0; i < string.length(); ++i) {
		c = string[i];

		it = this->getCharMap().find(c);
		if (it != this->getCharMap().end())
			c = it->second;

		if (c >= 'A' && c <= 'Z')
			c = c + 32;

		normalizedWord += c;
	};

	return normalizedWord;
}

void DictionaryNormalizer::normalize(std::string dictionaryPath) {
	TextInputSequentialFile<TextRecord> dictionaryFile(dictionaryPath,FILE_BUFFER_SIZE);
	TextOutputSequentialFile<TextRecord> normalizedDictionaryFile(OUTPUT_FILE_PATH,FILE_BUFFER_SIZE);
	TextRecord record;

	while (!dictionaryFile.endOfFile()) {
		record = dictionaryFile.getRecord();
		record.setData(this->normalizeWord(record.getData()));
		normalizedDictionaryFile.putRecord(record);
	}
}

DictionaryNormalizer::~DictionaryNormalizer() {
}
