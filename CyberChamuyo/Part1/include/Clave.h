/*
 * Clave.h
 *
 *  Created on: 06/05/2012
 *      Author: Shazgath
 */

#ifndef CLAVE_H_
#define CLAVE_H_

#include <string>
#include <iostream>
#include <vector>

class Clave {
public:
	Clave();
	virtual ~Clave();
	virtual bool operator<(const Clave& c) const = 0;
	virtual bool operator>(const Clave& c) const = 0;
	virtual bool operator>=(const Clave& c) const = 0;
	virtual bool operator==(const Clave& c) const = 0;
	virtual bool operator!=(const Clave& c) const = 0;
	virtual Clave& operator=(const Clave& c) = 0;
	virtual std::string serializarDecimal() const = 0;
	virtual long size() = 0;
	virtual int byte_size() = 0;
	virtual void setSize(int size) = 0;
	virtual std::string print() = 0;
	virtual std::vector<char>*& serializar(std::vector<char>*& ret) const = 0;
	virtual void hidratar(const std::vector<char>* s, int& pos) = 0;
	virtual int getTipo() const = 0;
};

#endif /* CLAVE_H_ */
