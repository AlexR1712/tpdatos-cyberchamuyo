#ifndef LOGRECORD_H_
#define LOGRECORD_H_

#include <string>
#include <vector>

#include "record.h"

//Clase que representa un registro de log.
class LogRecord : Record{
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
	LogRecord(std::string title, std::string itemName);

	//Metodo para hidratar el objeto desde un string.
	void deserialize(std::string string);

	std::vector<unsigned int>& getLogItems();

	LogRecord& operator=(LogRecord& other);

	//Metodo para serializar el objeto a un string.
	std::string serialize();

	//Destructor.
	virtual ~LogRecord();
};

#endif /* LOGRECORD_H_ */
