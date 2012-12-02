#include "../include/wordNormalizer.h"

#include "../include/propertiesLoader.h"
#include "../include/variableLengthRecordSequentialFile.h"
#include "../include/textRecord.h"
#include "../include/stringUtilities.h"

WordNormalizer::WordNormalizer() {
	PropertiesLoader propertiesLoader("config/wordNormalizer.properties");
	this->charMapFilePath = propertiesLoader.getPropertyValue(CHAR_MAP_FILE_PATH_PROPERTY_NAME);
	loadCharmap();
}

std::string WordNormalizer::getCharMapFilePath() const {
	return this->charMapFilePath;
}

std::unordered_map<char,char>& WordNormalizer::getCharMap() {
	return this->charMap;
}

void WordNormalizer::loadCharmap() {
	VariableLengthRecordSequentialFile<TextRecord> charMapFile;
	std::vector<std::string> charMapContents;

	charMapFile.open(this->getCharMapFilePath());
	while (!charMapFile.endOfFile()) {
		StringUtilities::splitString(charMapFile.getNextRecord().getData(),charMapContents,'=');
		this->getCharMap().insert(std::pair<char,char>(charMapContents[0][0],charMapContents[1][0]));
	}
}

std::string WordNormalizer::normalizeWord(const std::string string) {
	std::string normalizedWord;
	char c;
	std::unordered_map<char,char>::iterator it;

	StringUtilities::trim(string);
	for(unsigned int i = 0; i < string.size(); ++i) {
		c = string[i];
		it = this->getCharMap().find(c);
		if (it != this->getCharMap().end()) {
			c = it->second;
		}
		if (c != '\0') {
			normalizedWord += tolower(c);
		}
	};
	return normalizedWord;
}

WordNormalizer::~WordNormalizer() {
}
