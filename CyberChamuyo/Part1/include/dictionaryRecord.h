#include <string>
#include <ostream>
#include "record.h"

#ifndef DICTIONARYRECORD_H_
#define DICTIONARYRECORD_H_

class DictionaryRecord : public Record {
private:
	unsigned long int id;

	std::string word;

	bool idInFile;

protected:
	bool getIdInFile() const;

	void setIdInFile(bool idInFile);

public:
	DictionaryRecord(bool idInFile = true);

	void setId(unsigned long int id);

	unsigned long int getId() const;

	const std::string getWord() const;

	void setWord(const std::string word);

	DictionaryRecord& operator=(const DictionaryRecord& other);

	bool operator>(const DictionaryRecord& other);

	bool operator<(const DictionaryRecord& other);

	virtual ~DictionaryRecord() = 0;
};

#endif /* DICTIONARYRECORD_H_ */
