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
		if ( (c == 'Á') || (c == 'á') )
			c = 'a';
		if ( (c == 'É') || (c == 'é') )
			c = 'e';
		if ( (c == 'Í') || (c == 'í') )
			c = 'i';
		if ( (c == 'Ó') || (c == 'ó') )
			c = 'o';
		if ( (c == 'Ú') || (c == 'ú') || (c == 'Ü') || (c == 'ü') )
			c = 'u';
		if (c >= 'A' && c <= 'Z')
			c = c + 32;
		normalizedWord += c;
	};

	return normalizedWord;
}

DictionayNormalizer::~DictionayNormalizer() {
}
