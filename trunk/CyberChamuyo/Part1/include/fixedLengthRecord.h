#ifndef FIXEDLENGTHRECORD_H_
#define FIXEDLENGTHRECORD_H_

#include "record.h"

#include <string>
#include <vector>

//Clase que representa un registro de longitud fija.
//TODO hacer heredar de record.
class FixedLengthRecord : public Record {
public:
	//Constructor.
	FixedLengthRecord(unsigned int recordSize);

//	//Metodo para hidratar el objeto desde un vector de char.
//	void deserialize(std::vector<unsigned char>& recordAsCharArray);
//
//	//Metodo para serializar el objeto a un vector de char.
//	void serialize(std::vector<unsigned char>& recordAsCharVector);

	//Destructor.
	~FixedLengthRecord();
};

#endif /* FIXEDLENGTHTEXTRECORD_H_ */
