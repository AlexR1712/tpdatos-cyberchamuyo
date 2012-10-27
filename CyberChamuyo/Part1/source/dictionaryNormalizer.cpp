#include "../include/dictionaryNormalizer.h"

#include "../include/textInputSequentialFile.h"
#include "../include/textOutputSequentialFile.h"
#include "../include/textRecord.h"
#include "../include/stringUtilities.h"

DictionaryNormalizer::DictionaryNormalizer() {
	loadCharmap();
}

std::map<wchar_t,char>& DictionaryNormalizer::getCharMap() {
	return this->charMap;
}

void DictionaryNormalizer::loadCharmap() {
	TextInputSequentialFile<TextRecord> charMapFile(CHAR_MAP_FILE_PATH,FILE_BUFFER_SIZE);
	std::wstring wCharMapLine;

	while (!charMapFile.endOfFile()) {
		wCharMapLine = StringUtilities::stringToWstring(charMapFile.getRecord().getData());
		this->getCharMap().insert(std::pair<wchar_t,char>(wCharMapLine[0],wCharMapLine[2]));
	}
}

std::string DictionaryNormalizer::normalizeWord(const std::wstring string) {
	std::string normalizedWord;
	wchar_t c;
	std::map<wchar_t,char>::iterator it;

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
	std::wstring wWord;

	while (!dictionaryFile.endOfFile()) {
		record = dictionaryFile.getRecord();
		wWord = StringUtilities::stringToWstring(record.getData());
		record.setData(this->normalizeWord(wWord));
		normalizedDictionaryFile.putRecord(record);
	}
}

DictionaryNormalizer::~DictionaryNormalizer() {
}
