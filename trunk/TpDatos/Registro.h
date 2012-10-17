/*
 * Registro.h
 *
 *  Created on: 06/05/2012
 *      Author: Shazgath
 */

#ifndef REGISTRO_H_
#define REGISTRO_H_

#include <string>
#include "CEntero.h"
#include <vector>


struct filtro {
	unsigned int first;
	unsigned int second;
	bool mostrar;
};


using namespace std;

class Clave;

class Registro {
public:
	Registro();
	Registro(Clave* c);
	Registro(Clave* c, std::string dat);
	Registro(Registro& r);
	virtual ~Registro();
	Clave* getClave();
	Clave* getClaveCopia();
	int size();
	unsigned int sizeClave();	// suma del tamaño de todas las claves
	bool operator==(const Clave* c) const {
		return clave == c;
	}
	bool operator==(const Registro* r) const {
		return clave == r->clave;
	}
	bool operator<(const Registro* r) const {
		return (*clave) < (*r->clave);
	}
	bool operator<(const Registro& r) const {
		return (*clave) < (*r.clave);
	}
	bool operator>(const Registro& r) const {
		return (*clave) > (*r.clave);
	}
	bool operator==(const Registro& r) const {
		return ((*clave) == (*r.clave));
	}
	void hidratar(const string& s);
	int totalSize();		// tamaño total del regisytro serializado
	void insertarClave(Clave* c, int pos);
	void setTipo(int t);
	void setDato(char* dato);
	std::string serializar();
	friend std::ostream& operator<<(std::ostream& os, const Registro& r);
private:
	Clave* clave;
	string dato;
	long tam;		// tamanio solo de dato
	long tipo;
};

#endif /* REGISTRO_H_ */
