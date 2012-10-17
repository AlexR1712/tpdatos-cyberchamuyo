/*
 * DatoNodo.cpp
 *
 *  Created on: Oct 17, 2012
 *      Author: lucasj
 */

#include "DatoNodo.h"

DatoNodo::DatoNodo(std::string& cadena) {
	this->cadena = cadena;
}

DatoNodo::~DatoNodo() {

}

DatoNodo::DatoNodo(void) {
	this->cadena = "";
}

void DatoNodo::Imprimir(std::ostream& oss) {
	oss << this->cadena << std::endl;
}

void DatoNodo::serializar(std::ostream& oss) {
	oss << this->cadena;
}

int DatoNodo::getTamano() {
	return this->cadena.length();
}

std::ostream& operator<<(std::ostream& oss, DatoNodo &n) {
	int N = n.cadena.length();
	oss.write((char*)&N, sizeof(N));
	oss.write(n.cadena.c_str(), N);
	return oss;
}

std::istream& operator>>(std::istream& oss, DatoNodo &n) {
	int N = 0;
	oss.read((char*) (&N), sizeof(int));
	char* tabla = new char [N + 1];
	oss.read(tabla, N);
	tabla[N] = 0;
	n.cadena = tabla;
	delete [] tabla;
	return oss;
}

