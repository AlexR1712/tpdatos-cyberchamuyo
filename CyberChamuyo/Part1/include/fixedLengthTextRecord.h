#ifndef FIXEDLENGTHTEXTRECORD_H_
#define FIXEDLENGTHTEXTRECORD_H_

#include "../include/fixedLengthRecord.h"

//#include <string>
//#include <vector>

//Clase que representa un registro de texto.
class FixedLengthTextRecord : public FixedLengthRecord{
private:
	//Informacion contenida en el registro.
	std::string data;

public:
	//Constructor.
	FixedLengthTextRecord(unsigned int recordSize);

	//Metodo para hidratar el objeto desde un vector de char.
	void deserialize(std::vector<unsigned char>& recordAsCharVector);

	FixedLengthTextRecord& operator=(const FixedLengthTextRecord& other);

	std::string getData() const;

	void setData(std::string data);

	//Metodo para serializar el objeto a un vector de char.
	void serialize(std::vector<unsigned char>& recordAsCharVector);

	//Destructor.
	~FixedLengthTextRecord();
};

#endif /* FIXEDLENGTHTEXTRECORD_H_ */
