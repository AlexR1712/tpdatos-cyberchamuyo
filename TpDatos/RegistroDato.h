/*
 * RegistroDato.h
 *
 *  Created on: Sep 27, 2012
 *      Author: lucasj
 */

#ifndef REGISTRODATO_H_
#define REGISTRODATO_H_

#include "Frase.h"
#include <iostream>
#include "RegistroVariable.h"

namespace Hash {

class RegistroDato: public RegistroVariable {
private:
	Data::Frase* dato;
	virtual void print(std::ostream& oss);
	virtual void read(std::istream& oss);
	RegistroDato(const RegistroDato& d);
public:
	RegistroDato(Data::Frase* dato);
	RegistroDato(void);
	virtual void serializar(std::ostream& oss);
	virtual unsigned long int getClaveDato(void);
	virtual void borrarDato();
	virtual int getTamanoDato();
	virtual void ImprimirATexto(std::ostream& oss);
	virtual ~RegistroDato();
	friend std::ostream& operator<<(std::ostream& oss,
					  RegistroDato &reg);
	friend std::istream& operator>>(std::istream& oss,
					  RegistroDato &reg);

};
	std::ostream& operator<<(std::ostream& oss, RegistroDato &reg);
	std::istream& operator>>(std::istream& oss, RegistroDato &reg);
}
#endif
