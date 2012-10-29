#ifndef RECORD_H_
#define RECORD_H_

#include <string>

//Clase que representa un registro.
class Record {
public:
	//Constructor
	Record();

	//Metodo para hidratar el objeto desde un string
	virtual void deserialize(std::string string) = 0;

	//Metodo para serializar el objeto a un string
	virtual std::string serialize() = 0;

	//Destructor
	virtual ~Record() = 0;
};

#endif /* RECORD_H_ */
