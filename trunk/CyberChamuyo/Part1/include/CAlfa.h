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
	CAlfa();
	CAlfa(const std::string& s);
	virtual ~CAlfa();
	std::string getWord();
	void set(const std::string& s);
	virtual Clave& operator=(const Clave& c);
	virtual CAlfa& operator=(const CAlfa& c);
	CAlfa operator+(const CAlfa& c);
	virtual std::string print();
	virtual void hidratar(const std::vector<char>* s, int& pos);
	virtual long size();
	virtual int byte_size();
	virtual void setSize(int size);
	virtual std::string serializarDecimal() const;
	virtual bool operator<(const Clave& c) const;
	virtual bool operator>=(const Clave& c) const;
	virtual bool operator>(const Clave& c) const;
	virtual bool operator==(const Clave& c) const;
	virtual bool operator!=(const Clave& c) const;
	virtual std::vector<char>*& serializar(std::vector<char>*& ret) const;
	std::string getString();

	friend std::ostream& operator<<(std::ostream& os, const CAlfa& c);
	friend CAlfa& operator>>(std::istream& is, CAlfa& c);

	virtual int getTipo() const;
private:
	std::string clave;
	int tam;
};

#endif /* CALFA_H_ */
