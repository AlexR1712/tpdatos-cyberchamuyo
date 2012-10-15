#include "dictionaryNormalizer.h"

#include <string>

#include "textInputSequentialFile.h"
#include "textOutputSequentialFile.h"
#include "textDictionaryRecord.h"

DictionaryNormalizer::DictionaryNormalizer() {
}

void DictionaryNormalizer::normalize(std::string dictionaryPath) {
	TextInputSequentialFile<TextDictionaryRecord<false> > dictionaryFile(dictionaryPath,FILE_BUFFER_SIZE);
	TextOutputSequentialFile<TextDictionaryRecord<false> > normalizedDictionaryFile(OUTPUT_FILE_PATH,FILE_BUFFER_SIZE);
	TextDictionaryRecord<false> record;

	while (!dictionaryFile.endOfFile()) {
		record = dictionaryFile.getRecord();
		record.setWord(this->normalizeWord(record.getWord()));
		normalizedDictionaryFile.putRecord(record);
	}
}

std::string DictionaryNormalizer::normalizeWord(const std::string& string) const {
	std::string normalizedWord;
	char c;

	for (unsigned int i = 0; i < string.length(); ++i) {
		c = string[i];
		if ( (c == '�') || (c == '�') )
			c = 'a';
		if ( (c == '�') || (c == '�') )
			c = 'e';
		if ( (c == '�') || (c == '�') )
			c = 'i';
		if ( (c == '�') || (c == '�') )
			c = 'o';
		if ( (c == '�') || (c == '�') || (c == '�') || (c == '�') )
			c = 'u';
		if (c >= 'A' && c <= 'Z')
			c = c + 32;
		normalizedWord += c;
	};

	return normalizedWord;
}

DictionaryNormalizer::~DictionaryNormalizer() {
}
