#ifndef LOGRECORD_H_
#define LOGRECORD_H_

#include <string>
#include <vector>

#include "record.h"

//Clase que representa un registro de log.
class LogRecord : public Record {
private:
	//Titulo del registro.
	std::string title;

	//Nombre de los items del registro.
	std::string itemName;

	//Items del registro.
	std::vector<unsigned int> logItems;

	std::string getTitle() const;

	void setTitle(std::string title);

	std::string getItemName() const;

	void setItemName(std::string logItemName);

public:
	//Constructor.
	LogRecord();

	//Constructor.
	LogRecord(std::string title, std::string itemName);

	//Metodo para hidratar el objeto desde un string.
	void deserialize(std::vector<unsigned char>& recordAsCharVector);

	std::vector<unsigned int>& getLogItems();

	LogRecord& operator=(LogRecord& other);

	//Metodo para serializar el objeto a un string.
	void serialize(std::vector<unsigned char>& recordAsCharVector);

	//Destructor.
	virtual ~LogRecord();
};

#endif /* LOGRECORD_H_ */
