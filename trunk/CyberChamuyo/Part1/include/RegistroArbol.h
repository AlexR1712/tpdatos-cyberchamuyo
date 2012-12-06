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
	RegistroArbol(Clave* c, long ne, unsigned int se);
	RegistroArbol(Clave* c, std::string s,long ne, unsigned int se);
	RegistroArbol(RegistroArbol& reg);
	unsigned int getListId();
	void setListId(unsigned int id);
	unsigned long getTermId();
	virtual std::vector<char>* serializar(FrontCoding& encoder);
	virtual void hidratar(const std::vector<char>* vec, FrontCoding& decoder,int& pos);
	virtual ~RegistroArbol();
	virtual Registro* find();
	long timesSearched();
	virtual Registro& operator=(Registro& r);
	virtual Registro& operator=(RegistroArbol& r);
	friend std::ostream& operator<<(std::ostream& os, const RegistroArbol& r);
	virtual void setReg(Registro& r);
	virtual int totalSize();
private:
	long n;
	unsigned int s;
	unsigned int termId;
};



#endif /* REGISTROARBOL_H_ */
