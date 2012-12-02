#ifndef RECORD_H_
#define RECORD_H_

#include <vector>

//Clase que representa un registro.
class Record {
private:
	unsigned int recordSize;

public:
	//Constructor
	Record();

	unsigned int getRecordSize() const;

	void setRecordSize(unsigned int recordSize);

	//Metodo para hidratar el objeto desde un string
	virtual void deserialize(std::vector<unsigned char>& recordAsCharVector) = 0;

	//Metodo para serializar el objeto a un string
	virtual void serialize(std::vector<unsigned char>& recordAsCharVector) = 0;

	//Destructor
	virtual ~Record() = 0;
};

#endif /* RECORD_H_ */
