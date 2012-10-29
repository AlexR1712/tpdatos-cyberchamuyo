#include <string>
#include <ostream>
#include "record.h"

#ifndef DICTIONARYRECORD_H_
#define DICTIONARYRECORD_H_

//Clase que representa un registro de diccionario.
class DictionaryRecord : public Record {
private:
	//Id del registro
	unsigned long int id;

	//Palabra
	std::string word;

	//Indica si el ID se encuentra presente en el archivo o si se debe guardar.
	bool idInFile;

protected:
	bool getIdInFile() const;

	void setIdInFile(bool idInFile);

public:
	//Constructor
	DictionaryRecord(bool idInFile = true);

	void setId(unsigned long int id);

	unsigned long int getId() const;

	const std::string getWord() const;

	void setWord(const std::string word);

	DictionaryRecord& operator=(const DictionaryRecord& other);

	bool operator>(const DictionaryRecord& other);

	bool operator<(const DictionaryRecord& other);

	//Destructor
	virtual ~DictionaryRecord() = 0;
};

#endif /* DICTIONARYRECORD_H_ */
