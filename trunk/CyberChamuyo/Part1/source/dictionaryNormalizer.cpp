#include "../include/dictionaryNormalizer.h"

#include "../include/textInputSequentialFile.h"
#include "../include/textOutputSequentialFile.h"
#include "../include/textRecord.h"
#include "../include/stringUtilities.h"

DictionaryNormalizer::DictionaryNormalizer() {
	loadCharmap();
}

std::map<std::wstring,char>& DictionaryNormalizer::getCharMap() {
	return this->charMap;
}

void DictionaryNormalizer::loadCharmap() {
	TextInputSequentialFile<TextRecord> charMapFile(CHAR_MAP_FILE_PATH,FILE_BUFFER_SIZE);
	std::vector<std::string> charMapParams;
	std::wstring ws;
	while (!charMapFile.endOfFile()) {
		StringUtilities::splitString(charMapFile.getRecord().getData(),charMapParams,'=');
		ws.assign(charMapParams[0].begin(), charMapParams[0].end());
		this->getCharMap().insert(std::pair<std::wstring,char>(ws,(charMapParams[1])[0]));
	}
}

std::string DictionaryNormalizer::normalizeWord(const std::string string) {
	std::string normalizedWord;
	std::wstring ws;
	wchar_t c;
	ws.assign(string.begin(), string.end());
	std::map<std::wstring,char>::iterator it;
	for(unsigned int i = 0; i < ws.size(); ++i) {
		c = ws[i];
		it = this->getCharMap().find(&c);
		if (it != this->getCharMap().end()) {
			c = it->second;
		}
		if (c >= 'A' && c <= 'Z')
			c = c + 32;
		normalizedWord += c;
	};
	StringUtilities::sacarR(normalizedWord);
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
