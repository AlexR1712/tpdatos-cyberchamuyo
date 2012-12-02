#ifndef FIXEDLENGTHRECORD_H_
#define FIXEDLENGTHRECORD_H_

#include <string>
#include <vector>

//Clase que representa un registro de longitud fija.
//TODO hacer heredar de record.
class FixedLengthRecord {
private:
	unsigned int recordSize;

protected:
	void setRecordSize(unsigned int recordSize);

public:
	//Constructor.
	FixedLengthRecord(unsigned int recordSize);

	unsigned int getRecordSize() const;

	//Metodo para hidratar el objeto desde un vector de char.
	virtual	void deserialize(std::vector<unsigned char>& recordAsCharArray) = 0;

	//Metodo para serializar el objeto a un vector de char.
	virtual void serialize(std::vector<unsigned char>& recordAsCharVector) = 0;

	//Destructor.
	virtual ~FixedLengthRecord() = 0;
};

#endif /* FIXEDLENGTHTEXTRECORD_H_ */
