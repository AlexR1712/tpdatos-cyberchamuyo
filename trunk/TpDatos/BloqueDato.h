/*
 * BloqueDato.h
 *
 *  Created on: Sep 23, 2012
 *      Author: lucasj
 */

#ifndef BLOQUEDATO_H_
#define BLOQUEDATO_H_

#include "Bloque.h"
#include "RegistroDato.h"

class BloqueDato: public Bloque {
private:
	unsigned int td;
	virtual void LlenarRegistros(std::istream& oss, int cantReg);
	virtual void print(std::ostream& oss) const;
	virtual void input(std::istream& oss) const;
public:
	BloqueDato(long tamanoBloque);
	unsigned int getTd(void);
	void setTd(unsigned int td);
	virtual ~BloqueDato();
	virtual void ImprimirATexto(std::ostream& oss);
};

#endif
