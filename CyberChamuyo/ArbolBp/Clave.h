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

class Clave {
public:
	Clave();
	virtual ~Clave();
	virtual bool operator<(const Clave& c) const = 0;
	virtual bool operator>(const Clave& c) const = 0;
	virtual bool operator==(const Clave& c) const = 0;
	virtual bool operator!=(const Clave& c) const = 0;
	virtual long size() = 0;
	virtual std::string print() = 0;
	virtual std::string serializar() const = 0;
	virtual void hidratar(const std::string& s) = 0;
};

#endif /* CLAVE_H_ */
