/*
 * CEntero.h
 *
 *  Created on: 06/05/2012
 *      Author: Shazgath
 */

#ifndef CENTERO_H_
#define CENTERO_H_

#include "Clave.h"

class C_Entero : public Clave {
public:
	C_Entero();
	C_Entero(long i);
	virtual ~C_Entero();
	virtual long size();
	long get() const;
	void set(const long i);
	virtual std::string print();
	C_Entero& operator=(unsigned long i);

	virtual bool operator<(const long& i) const;
	virtual bool operator>(const long& i) const;

	virtual bool operator<(const Clave& c) const;
	virtual bool operator>(const Clave& c) const;

	virtual bool operator!=(const C_Entero& c) const;

	virtual bool operator!=(const Clave& c) const;
	virtual bool operator==(const Clave& c) const;

	virtual C_Entero operator+(unsigned long i);
	virtual C_Entero operator+(const Clave& c);
	friend std::string operator<<(std::string& s, const C_Entero& c);
	friend std::ostream& operator<<(std::ostream& os, const C_Entero& c);
	friend C_Entero& operator>>(std::istream& is, C_Entero& c);
	std::string serializar() const;
	virtual void hidratar(const std::string& s);
private:
	long clave;
};



#endif /* CENTERO_H_ */
