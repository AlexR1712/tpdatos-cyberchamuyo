/*
 * CAlfa.h
 *
 *  Created on: 06/09/2012
 *      Author: sebastian
 */

#ifndef CALFA_H_
#define CALFA_H_

#include "Clave.h"

/* CAlfa: Clase para utilizar claves de cadenas de caracteres */

class CAlfa : public Clave {
public:
	// No realiza acciones
	CAlfa();

	// costructor que setea la clave con una copia de s
	CAlfa(const std::string& s);

	virtual ~CAlfa();

	//  devuelve la clave
	std::string getWord();

	//  setea la clave
	void set(const std::string& s);

	//  operadores
	virtual Clave& operator=(const Clave& c);
	virtual CAlfa& operator=(const CAlfa& c);
	CAlfa operator+(const CAlfa& c);
	virtual bool operator<(const Clave& c) const;
	virtual bool operator>=(const Clave& c) const;
	virtual bool operator>(const Clave& c) const;
	virtual bool operator==(const Clave& c) const;
	virtual bool operator!=(const Clave& c) const;
	friend std::ostream& operator<<(std::ostream& os, const CAlfa& c);
	friend CAlfa& operator>>(std::istream& is, CAlfa& c);

	virtual std::string print();
	virtual void hidratar(const std::vector<char>* s, int& pos);
	virtual long size();
	virtual int byte_size();
	virtual void setSize(int size);
	virtual std::string serializarDecimal() const;
	virtual std::vector<char>*& serializar(std::vector<char>*& ret) const;
	std::string getString();
	virtual int getTipo() const;
private:
	std::string clave;
	int tam;			//  tamaño clave, se utiliza al hidratar una clave
};

#endif /* CALFA_H_ */
