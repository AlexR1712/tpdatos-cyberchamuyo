/*
 * Nodo.h
 *
 *  Created on: 06/05/2012
 *      Author: Shazgath
 */

#ifndef NODO_H_
#define NODO_H_

#include "Registro.h"
#include <list>
#include <string>
#include "common.h"

using namespace std;

class Nodo {
public:
	Nodo();
	virtual ~Nodo();
	virtual std::string serializar() = 0;
	virtual void hidratar(string& s) = 0;
	virtual int insertarRecursivo(Registro* r);
	bool overflow();
	int getTipoClave();
};

#endif /* NODO_H_ */
