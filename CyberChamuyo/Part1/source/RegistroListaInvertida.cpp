/*
 * RegistroListaInvertida.cpp
 *
 *  Created on: Nov 28, 2012
 *      Author: lucasj
 */

#include "../include/RegistroListaInvertida.h"

RegistroListaInvertida::RegistroListaInvertida(invertedList::ListaInvertida* dato) {
	this->dato = dato;
}

RegistroListaInvertida::~RegistroListaInvertida() {
	delete this->dato;
}

RegistroListaInvertida::RegistroListaInvertida(void) {
	this->dato = NULL;
}

std::ostream& operator<<(std::ostream& oss, RegistroListaInvertida &reg) {
	reg.print(oss);
	return oss;
}

std::istream& operator>>(std::istream& oss, RegistroListaInvertida &reg) {
	reg.read(oss);
	return oss;
}

unsigned long int RegistroListaInvertida::getClaveDato(void) {
	return 0;
}

// FUNCIONAMIENTO READ:
// Lee el dato del archivo binario.

void RegistroListaInvertida::read(std::istream& oss) {
	this->dato = new invertedList::ListaInvertida;
	oss >> *(this->dato);
}

// FUNCIONAMIENTO PRINT:
// Escribe el dato al archivo binario.

void RegistroListaInvertida::print(std::ostream& oss) {
	oss << *(this->dato);
}

void RegistroListaInvertida::borrarDato() {
	delete this->dato;
	this->dato = NULL;
}

int RegistroListaInvertida::getTamanoDato() {
	return this->dato->getTamano();
}

// FUNCIONAMIENTO SERIALIZAR:
// Serializa la tabla en un ostream.

void RegistroListaInvertida::serializar(std::ostream& oss) {
	this->dato->serializar(oss);
}

void RegistroListaInvertida::ImprimirATexto(std::ostream& oss) {
	oss << "REGISTRO LISTA INVERTIDA: " << std::endl;
	this->dato->Imprimir(oss);
}

void RegistroListaInvertida::cargarListaInvertida(invertedList::ListaInvertida& list, unsigned int offset) {
	list += *this->dato;
}

