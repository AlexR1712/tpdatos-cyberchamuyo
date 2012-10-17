/*
 * BloqueTabla.h
 *
 *  Created on: Sep 23, 2012
 *      Author: lucasj
 */

#ifndef BLOQUETABLA_H_
#define BLOQUETABLA_H_

#include "Bloque.h"
#include "RegistroTabla.h"

class BloqueTabla: public Bloque {
private:
	unsigned int siguiente;
	virtual void LlenarRegistros(std::istream& oss, int cantReg);
	virtual void print(std::ostream& oss) const;
	virtual void input(std::istream& oss) const;
public:
	BloqueTabla(long tamanoBloque);
	unsigned int getSiguiente(void);
	void setSiguiente(unsigned int siguiente);
	void cargarTabla(array& vec);
	virtual void ImprimirATexto(std::ostream& oss);
	virtual ~BloqueTabla();
};


#endif /* BLOQUETABLA_H_ */
