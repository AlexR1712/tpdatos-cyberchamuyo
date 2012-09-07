/*
 * CAlfa.h
 *
 *  Created on: 06/09/2012
 *      Author: sebastian
 */

#ifndef CALFA_H_
#define CALFA_H_

#include "Clave.h"

class CAlfa : public Clave {
public:
	CAlfa(std::string s);
	virtual ~CAlfa();
	CAlfa operator+(const CAlfa& c);
	virtual std::string print();
	virtual std::string serializar() const;
	virtual void hidratar(const std::string& s);
	virtual long size();

	virtual bool operator<(const Clave& c) const {return true;};
	virtual bool operator>(const Clave& c) const {return true;};
	virtual bool operator==(const Clave& c) const {return true;};
	virtual bool operator!=(const Clave& c) const {return true;};

private:
	std::string clave;
};

#endif /* CALFA_H_ */
