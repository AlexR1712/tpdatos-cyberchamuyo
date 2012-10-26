/*
 * RegistroNodo.h
 *
 *  Created on: Oct 17, 2012
 *      Author: lucasj
 */

#ifndef REGISTRONODO_H_
#define REGISTRONODO_H_

#include "RegistroVariable.h"
#include "DatoNodo.h"

class RegistroNodo: public RegistroVariable {
private:
	DatoNodo* dato;
	virtual void print(std::ostream& oss);
	virtual void read(std::istream& oss);
public:
	RegistroNodo(DatoNodo* dato);
	RegistroNodo(void);
	virtual void serializar(std::ostream& oss);
	virtual void ImprimirATexto(std::ostream& oss);
	virtual void borrarDato();
    virtual unsigned long int getClaveDato(void);
    virtual int getTamanoDato(void);
	virtual ~RegistroNodo();
	friend std::ostream& operator<<(std::ostream& oss,
					  RegistroNodo &reg);
	friend std::istream& operator>>(std::istream& oss,
					  RegistroNodo &reg);
};

std::ostream& operator<<(std::ostream& oss, RegistroNodo &reg);
std::istream& operator>>(std::istream& oss, RegistroNodo &reg);

#endif
