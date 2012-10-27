#include "../include/dictionaryNormalizer.h"

#include "../include/textInputSequentialFile.h"
#include "../include/textOutputSequentialFile.h"
#include "../include/textRecord.h"
#include "../include/stringUtilities.h"

DictionaryNormalizer::DictionaryNormalizer() {
	loadCharmap();
}

std::map<std::wstring,std::string>& DictionaryNormalizer::getCharMap() {
	return this->charMap;
}

void DictionaryNormalizer::loadCharmap() {
	TextInputSequentialFile<TextRecord> charMapFile(CHAR_MAP_FILE_PATH,FILE_BUFFER_SIZE);
	std::vector<std::string> charMapParams;

	while (!charMapFile.endOfFile()) {
		StringUtilities::splitString(charMapFile.getRecord().getData(),charMapParams,'=');
		this->getCharMap().insert(std::pair<std::wstring,std::string>(charMapParams[0],charMapParams[1]));
	}
}

std::string DictionaryNormalizer::normalizeWord(const std::string string) {
	std::string normalizedWord;
	wchar_t c;
	std::wstring s;
	std::map<std::wstring,std::string>::iterator it;
	for(unsigned int i = 0; i < s.size(); ++i) {
		c = s[i];
		it = this->getCharMap().find(c);
		if (it != this->getCharMap().end())
			c = it->second;
		/*if (c >= "A" && c <= "Z")
			c = c + 32;*/
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
