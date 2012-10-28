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
#include "CAlfa.h"

using namespace std;

//  Nodo: Interfaz para nodos

class Nodo {
public:
	Nodo();
	virtual ~Nodo();
	virtual std::vector<char>* serializar() = 0;
	virtual void hidratar(string& s) = 0;
	virtual void hidratar(const std::vector<char>* data, int& pos) = 0;
	virtual int insertarRecursivo(Registro* r);
	virtual int getNivel() = 0;
	bool overflow();
	int getTipoClave();
	virtual int buscar(Clave* c, Registro* reg) = 0;
	virtual int getCantElem() = 0;
};

#endif /* NODO_H_ */
