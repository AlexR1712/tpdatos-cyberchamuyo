#include "dictionaryNormalizer.h"

#include <fstream>
#include <iostream>
#include <string>

#include "readBuffer.h"
#include "writeBuffer.h"
#include "stringRecord.h"

DictionayNormalizer::DictionayNormalizer() {
}

void DictionayNormalizer::normalizeDictionary(std::string dictionaryPath) {
	ReadBuffer<StringRecord> readBuffer(dictionaryPath,N);
	WriteBuffer<StringRecord> writeBuffer("dictionary_NORMALIZED.txt",N);
	std::string line;
	StringRecord record(false);

	while (!readBuffer.empty()) {
		line = this->normalizeWord(readBuffer.getRecord().getWord());
		record.parseString(line);
		writeBuffer.putRecord(record);
	}
}

std::string DictionayNormalizer::normalizeWord(const std::string& string) const {
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

DictionayNormalizer::~DictionayNormalizer() {
}
