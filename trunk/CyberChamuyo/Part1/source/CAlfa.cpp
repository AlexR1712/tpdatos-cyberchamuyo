/*
 * CAlfa.cpp
 *
 *  Created on: 06/09/2012
 *      Author: sebastian
 */

#include "../include/CAlfa.h"

CAlfa::CAlfa() {

}

CAlfa::CAlfa(const std::string& s) {
	clave = s;
	tam = s.size();
}

CAlfa::~CAlfa() {
}

std::string CAlfa::getWord() {
	return clave;
}

void CAlfa::set(const std::string& s) {
	clave = s;
}

CAlfa CAlfa::operator+(const CAlfa& c) {
	CAlfa cAux(clave + c.clave);
	return cAux;
}

void CAlfa::hidratar(const std::vector<char>* data, int& pos){
	for(int i = 0; i < tam; ++i)
		clave.push_back((*data)[i]);
}

std::string CAlfa::print() {
	return clave;
}

Clave& CAlfa::operator=(const Clave& c) {
	clave = dynamic_cast<const CAlfa&>(c).clave;
	tam = dynamic_cast<const CAlfa&>(c).tam;
}

CAlfa& CAlfa::operator=(const CAlfa& c) {
	clave = dynamic_cast<const CAlfa&>(c).clave;
	tam = c.tam;
}

std::string CAlfa::serializarDecimal() const {
	return clave;
}
long CAlfa::size() {
	return (clave.size() * sizeof(char));
}

int CAlfa::byte_size() {
	bool notAligned = (clave.size() % 4) > 0?1:0;
	return (notAligned * (sizeof(int) - 1)) + (clave.size() * sizeof(char));
}

bool CAlfa::operator<(const Clave& c) const {
	return clave < (dynamic_cast<const CAlfa&>(c)).clave;
}

bool CAlfa::operator>(const Clave& c) const {
	return clave > (dynamic_cast<const CAlfa&>(c)).clave;
}

bool CAlfa::operator>=(const Clave& c) const {
	return clave >= (dynamic_cast<const CAlfa&>(c)).clave;
}

bool CAlfa::operator!=(const Clave& c) const {
	return (clave != (dynamic_cast<const CAlfa&>(c)).clave);
}

bool CAlfa::operator==(const Clave& c) const {
	return (clave == (dynamic_cast<const CAlfa&>(c)).clave);
}

std::vector<char>*& CAlfa::serializar(std::vector<char>*& ret) const {
	for(int i = 0; i < clave.size(); ++i)
		ret->push_back(clave[i]);
	return ret;
}

void CAlfa::setSize(int size) {
	tam = size;
}

std::ostream& operator<<(std::ostream& os, const CAlfa& c) {
	return (os << c.clave);
}

CAlfa& operator>>(std::istream& is, CAlfa& c) {
	std::string s;
	is >> s;
	c.set(s);
	return c;
}

int CAlfa::getTipo() const {
	return 1;
}

std::string CAlfa::getString() {
	return clave;
}
