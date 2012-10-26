/*
 * DatoNodo.cpp
 *
 *  Created on: Oct 17, 2012
 *      Author: lucasj
 */

#include "../include/DatoNodo.h"

DatoNodo::DatoNodo(vectorChar* cadena) {
	this->cadena = cadena;
}

DatoNodo::~DatoNodo() {
	delete this->cadena;
}

DatoNodo::DatoNodo(void) {
	this->cadena = NULL;
}

void DatoNodo::Imprimir(std::ostream& oss) {
	itVChar it;
	for (it = this->cadena->begin(); it != this->cadena->end(); ++it)
		oss << *it;
	 oss << std::endl;
}

void DatoNodo::serializar(std::ostream& oss) {
	itVChar it;
	for (it = this->cadena->begin(); it != this->cadena->end(); ++it)
		oss << *it;
}

int DatoNodo::getTamano() {
	return this->cadena->size();
}

std::ostream& operator<<(std::ostream& oss, DatoNodo &n) {
	int N = n.cadena->size();
	oss.write((char*)&N, sizeof(N));
	itVChar it;
	for (it = n.cadena->begin(); it != n.cadena->end(); ++it)
		oss.write(&(*it), sizeof(char));
	return oss;
}

std::istream& operator>>(std::istream& oss, DatoNodo &n) {
	int N = 0;
	oss.read((char*) (&N), sizeof(int));
	char* tabla = new char [N + 1];
	oss.read(tabla, N);
	tabla[N] = 0;
	n.cadena = new vectorChar();
	for (int i = 0; i < N; ++i)
		n.cadena->push_back(tabla[i]);
	delete [] tabla;
	return oss;
}

