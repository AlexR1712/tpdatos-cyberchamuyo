/*
 * CAlfa.cpp
 *
 *  Created on: 06/09/2012
 *      Author: sebastian
 */

#include "CAlfa.h"

CAlfa::CAlfa(std::string s) {
	clave = s;
}

CAlfa::~CAlfa() {
}

CAlfa CAlfa::operator+(const CAlfa& c) {
	CAlfa cAux(clave + c.clave);
	return cAux;
}

void CAlfa::hidratar(const std::string& s) {
}

std::string CAlfa::print() {
}

long CAlfa::size() {
	return clave.size() * sizeof(char);
}

std::string CAlfa::serializar() const {

}
