/*
 * RegistroArbol.h
 *
 *  Created on: 18/10/2012
 *      Author: sebastian
 */

#ifndef REGISTROARBOL_H_
#define REGISTROARBOL_H_

#include "Registro.h"
#include "FrontCoding.h"

class RegistroArbol : public Registro {
public:
	RegistroArbol();
	RegistroArbol(Clave* c);
	RegistroArbol(Clave* c, std::string s);
	RegistroArbol(Clave* c, long ne, short se);
	RegistroArbol(Clave* c, std::string s,long ne, short se);
	RegistroArbol(RegistroArbol& reg);
	virtual std::vector<char>* serializar(FrontCoding& encoder);
	virtual void hidratar(const std::vector<char>* vec, FrontCoding& decoder,int& pos);
	virtual ~RegistroArbol();
	virtual Registro* find();
	long timesSearched();
private:
	Clave* clave;
	string dato;
	long n;
	short s;
	long tam;		// tamanio solo de dato
	long tipo;
};

#endif /* REGISTROARBOL_H_ */
