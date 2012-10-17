/*
 * BloqueNodo.h
 *
 *  Created on: Oct 17, 2012
 *      Author: lucasj
 */

#ifndef BLOQUENODO_H_
#define BLOQUENODO_H_

#include "Bloque.h"
#include "RegistroNodo.h"

class BloqueNodo: public Bloque {
private:
	  virtual void print(std::ostream& oss) const;
	  virtual void input(std::istream& oss) const;
	  virtual void LlenarRegistros(std::istream& oss, int cantReg);
public:
	BloqueNodo(long tamanoBloque);
	 virtual void ImprimirATexto(std::ostream& oss);
	virtual ~BloqueNodo();
};

#endif
