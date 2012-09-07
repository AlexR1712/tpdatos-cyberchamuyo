/*
 * CEntero.cpp
 *
 *  Created on: 06/05/2012
 *      Author: Shazgath
 */

#include "CEntero.h"
#include "common.h"

C_Entero::C_Entero() {
}

C_Entero::C_Entero(long i) {
	clave = i;
}

C_Entero C_Entero::operator+(const Clave& c) {
	C_Entero cAux;
	cAux = dynamic_cast<const C_Entero&>(c).clave + clave;
	return cAux;
}

C_Entero C_Entero::operator+(unsigned long i) {
	C_Entero cAux;
	cAux = i + clave;
	return cAux;
}

C_Entero& C_Entero::operator=(unsigned long i) {
	clave = i;
	return *this;
}

C_Entero::~C_Entero() {
}

long C_Entero::size() {
	return sizeof(long);
}

bool C_Entero::operator<(const Clave& c) const {
	return (clave < dynamic_cast<const C_Entero&>(c).clave);
}

bool C_Entero::operator<(const long& i) const {
	return clave < i;
}

bool C_Entero::operator>(const long& i) const {
	return clave > i;
}

bool C_Entero::operator!=(const C_Entero& c) const {
	return clave != c.clave;
}

bool C_Entero::operator==(const Clave& c) const {
	return (clave == dynamic_cast<const C_Entero&>(c).clave);
}

bool C_Entero::operator!=(const Clave& c) const {
	return !(clave == dynamic_cast<const C_Entero&>(c).clave);
}

bool C_Entero::operator>(const Clave& c) const {
	return (clave > dynamic_cast<const C_Entero&>(c).clave);
}

std::ostream& operator<<(std::ostream& os, const C_Entero& c) {
	return(os << c.clave);
}

C_Entero& operator>>(std::istream& is, C_Entero& c) {
	is >> c.clave;
	return c;
}

void C_Entero::set(const long num) {
	clave = num;
}

long C_Entero::get() const {
	return clave;
}

std::string C_Entero::print() {
	std::string s(Auxiliar::int_to_hex(clave));
	return s;
}

std::string C_Entero::serializar() const {
	std::string ret = Auxiliar::int_to_hex(clave);
	return ret;
}


void C_Entero::hidratar(const std::string& s) {
	clave = Auxiliar::stoi(s);
}

