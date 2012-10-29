#ifndef TEXTRECORD_H_
#define TEXTRECORD_H_

#include <string>
#include "record.h"

//Clase que representa un registro de texto.
class TextRecord : public Record {
private:
	//Informacion contenida en el registro.
	std::string data;

public:
	//Constructor.
	TextRecord();

	//Metodo para hidratar el objeto desde un string.
	void deserialize(std::string string);

	TextRecord& operator=(const TextRecord& other);

	std::string getData() const;

	void setData(std::string data);

	//Metodo para serializar el objeto a un string.
	std::string serialize();

	//Destructor.
	virtual ~TextRecord();
};

#endif /* TEXTRECORD_H_ */
