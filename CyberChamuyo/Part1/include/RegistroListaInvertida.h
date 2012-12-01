/*
 * RegistroListaInvertida.h
 *
 *  Created on: Nov 28, 2012
 *      Author: lucasj
 */

#ifndef REGISTROLISTAINVERTIDA_H_
#define REGISTROLISTAINVERTIDA_H_

#include "RegistroVariable.h"
#include "ListaInvertida.h"

class RegistroListaInvertida: public RegistroVariable {
private:
	invertedList::ListaInvertida* dato;
	virtual void print(std::ostream& oss);
	virtual void read(std::istream& oss);
public:
	RegistroListaInvertida(invertedList::ListaInvertida* dato);
	virtual ~RegistroListaInvertida();
	RegistroListaInvertida(void);
	void cargarListaInvertida(invertedList::ListaInvertida& list, unsigned int offset);
	virtual void serializar(std::ostream& oss);
	virtual void ImprimirATexto(std::ostream& oss);
	virtual void borrarDato();
    virtual unsigned long int getClaveDato(void);
    virtual int getTamanoDato(void);
    friend std::ostream& operator<<(std::ostream& oss,
					  RegistroListaInvertida &reg);
	friend std::istream& operator>>(std::istream& oss,
					  RegistroListaInvertida &reg);

};

#endif
