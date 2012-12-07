/*
 * RegistroArbol.cpp
 *
 *  Created on: 18/10/2012
 *      Author: sebastian
 */

#include "../include/RegistroArbol.h"
#include "../include/ArbolBp.h"

RegistroArbol::RegistroArbol() : Registro() {
	n = 0;
	s = 0;
	termId = 0;
}

RegistroArbol::RegistroArbol(Clave* c) : Registro(c) {
	n = 0;
	s = 0;
	termId = 0;
}

RegistroArbol::RegistroArbol(Clave* c, long tId, unsigned int se) : Registro(c) {
	n = 0;
	s = se;
	termId = tId;
}


RegistroArbol::RegistroArbol(Clave* c, std::string dat) : Registro(c, dat) {
	n = 0;
	s = 0;
	termId = 0;
}

RegistroArbol::RegistroArbol(Clave* c, std::string dat, long tId, unsigned int se) : Registro(c, dat) {
	n = 0;
	s = se;
	termId = tId;
}

RegistroArbol::RegistroArbol(RegistroArbol& reg) : Registro(reg) {
	n = reg.n;
	s = reg.s;
	termId = reg.termId;
}


RegistroArbol::~RegistroArbol() {
}

std::vector<char>* RegistroArbol::serializar(FrontCoding& encoder) {
	std::vector<char>* ret = Registro::serializar(encoder);
	ret = Auxiliar::insertarEntero(ret, n);
	ret = Auxiliar::insertarEntero(ret, s);
	ret = Auxiliar::insertarEntero(ret, termId);
	return ret;
}


void RegistroArbol::hidratar(const std::vector<char>* vec, FrontCoding& decoder,int& pos) {
	Registro::hidratar(vec, decoder, pos);
	n = Auxiliar::leerEntero(vec, pos);
	s = Auxiliar::leerEntero(vec, pos);
	termId = Auxiliar::leerEntero(vec, pos);
}

Registro* RegistroArbol::find() {
	++n;
	return (Registro*)this;
}

unsigned long RegistroArbol::getTermId() {
	return termId;
}

unsigned int RegistroArbol::getListId() {
	return s;
}

void RegistroArbol::setListId(unsigned int lId) {
	this->s = lId;
}

long RegistroArbol::timesSearched() {
	return n;
}

Registro& RegistroArbol::operator=(Registro& r) {
	Registro::setSize(r.size());
	Registro::setTipo(r.getTipo());
	int tipo = r.getClave()->getTipo();
	Clave* clave;
	if(Registro::getClave() == NULL) {
		switch(tipo) {
		case 0:
			clave = new C_Entero();
			break;
		case 1:
			clave = new CAlfa();
			break;
		}
	}
	*clave = *(r.getClave());
	Registro::setClave(clave);
	Registro::setDato(r.getDato());
	n = reinterpret_cast<RegistroArbol&>(r).n;
	s = reinterpret_cast<RegistroArbol&>(r).s;
	termId = reinterpret_cast<RegistroArbol&>(r).termId;
	return *this;
}

Registro& RegistroArbol::operator=(RegistroArbol& r) {
	Registro::setSize(r.size());
	Registro::setTipo(r.getTipo());
	int tipo = r.getClave()->getTipo();
	Clave* clave;
	if(Registro::getClave() == NULL) {
		switch(tipo) {
		case 0:
			clave = new C_Entero();
			break;
		case 1:
			clave = new CAlfa();
			break;
		}
	}
	*clave = *(r.getClave());
	Registro::setClave(clave);
	Registro::setDato(r.getDato());
	n = r.n;
	s = r.s;
	termId = r.termId;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const RegistroArbol& r) {
	if(&r != NULL)
		os << "Registro = "<< (r.getClave())->print() << "  |  Datos = " << r.getDato() << "| n = " << r.n << std::endl;
	return os;
}

void RegistroArbol::setReg(Registro& reg) {
	n = dynamic_cast<RegistroArbol&>(reg).n;
	s = dynamic_cast<RegistroArbol&>(reg).s;
	termId = dynamic_cast<RegistroArbol&>(reg).termId;
}

void RegistroArbol::setTermId(int id) {
	this->termId = id;
}

int RegistroArbol::totalSize() {
	int regSize = Registro::totalSize();
	return regSize + 3 * sizeof(int);
}
