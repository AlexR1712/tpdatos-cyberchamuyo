/*
 * RegistroTabla.h
 *
 *  Created on: Sep 28, 2012
 *      Author: lucasj
 */

#ifndef REGISTROTABLA_H_
#define REGISTROTABLA_H_

#include "RegistroVariable.h"
#include "ArrayBytes.h"

namespace Hash {

class RegistroTabla: public RegistroVariable {
private:
	Data::ArrayBytes* dato;
	virtual void print(std::ostream& oss);
	virtual void read(std::istream& oss);
public:
	RegistroTabla(Data::ArrayBytes* dato);
	RegistroTabla(void);
	virtual ~RegistroTabla();
	virtual void serializar(std::ostream& oss);
	virtual void ImprimirATexto(std::ostream& oss);
	virtual void borrarDato();
    virtual unsigned long int getClaveDato(void);
    virtual int getTamanoDato(void);
    friend std::ostream& operator<<(std::ostream& oss,
					  RegistroTabla &reg);
	friend std::istream& operator>>(std::istream& oss,
					  RegistroTabla &reg);
};

std::ostream& operator<<(std::ostream& oss, RegistroTabla &reg);
std::istream& operator>>(std::istream& oss, RegistroTabla &reg);

}
#endif
