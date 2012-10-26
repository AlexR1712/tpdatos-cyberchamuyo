/*
 * RegistroNodo.cpp
 *
 *  Created on: Oct 17, 2012
 *      Author: lucasj
 */

#include "../include/RegistroNodo.h"

RegistroNodo::RegistroNodo(DatoNodo* dato) {
	this->dato = dato;
}

RegistroNodo::RegistroNodo(void) {
	this->dato = NULL;
}

RegistroNodo::~RegistroNodo() {
	delete this->dato;
}

std::ostream& operator<<(std::ostream& oss, RegistroNodo &reg) {
	reg.print(oss);
	return oss;
}

std::istream& operator>>(std::istream& oss, RegistroNodo &reg) {
	reg.read(oss);
	return oss;
}

unsigned long int RegistroNodo::getClaveDato(void) {
	return 0;
}

void RegistroNodo::read(std::istream& oss) {
	this->dato = new DatoNodo;
	oss >> *(this->dato);
}

void RegistroNodo::print(std::ostream& oss) {
	oss << *(this->dato);
}

void RegistroNodo::borrarDato() {
	delete this->dato;
	this->dato = NULL;
}

int RegistroNodo::getTamanoDato() {
	return this->dato->getTamano();
}

void RegistroNodo::ImprimirATexto(std::ostream& oss) {
	oss << "REGISTRO NODO: " << std::endl;
	this->dato->Imprimir(oss);
}

void RegistroNodo::serializar(std::ostream& oss) {
	this->dato->serializar(oss);
}

