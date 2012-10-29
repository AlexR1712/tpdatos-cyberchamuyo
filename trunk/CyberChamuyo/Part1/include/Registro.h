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
#include "CAlfa.h"
#include <vector>
#include "FrontCoding.h"

struct filtro {
	unsigned int first;
	unsigned int second;
	bool mostrar;
};

#define REG_CONTROL_SIZE (3 * sizeof(int))

using namespace std;

class Clave;

class Registro {
public:
	Registro();
	Registro(Clave* c);
	Registro(Clave* c, std::string dat);
	Registro(const Registro& r);
	virtual ~Registro();
	Clave* getClave() const;
	Clave* getClaveCopia();
	int size() const;
	void setSize(int size);
	int byte_size();
	void setClave(Clave* c);
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
	virtual Registro& operator=(Registro& r);
	void hidratar(const string& s);
	virtual int totalSize();		// tamaño total del regisytro serializado
	void insertarClave(Clave* c, int pos);
	void setTipo(int t);
	int getTipo() const;
	void setDato(char* dato);
	void setDato(std::string dato);
	std::string getDato() const;
	virtual std::vector<char>* serializar(FrontCoding& encoder);
	virtual void hidratar(const std::vector<char>* vec, FrontCoding& decoder, int& pos);
	friend std::ostream& operator<<(std::ostream& os, const Registro& r);
	virtual Registro* find();
	virtual void setReg(Registro& r){};
private:
	Clave* clave;
	string dato;
	long tam;		// tamanio solo de dato
	long tipo;
};

#endif /* REGISTRO_H_ */
