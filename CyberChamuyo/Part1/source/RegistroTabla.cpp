/*
 * RegistroTabla.cpp
 *
 *  Created on: Sep 28, 2012
 *      Author: lucasj
 */

#include "../include/RegistroTabla.h"

namespace Hash {

RegistroTabla::RegistroTabla(Data::ArrayBytes* dato) {
	this->dato = dato;
}

RegistroTabla::~RegistroTabla() {
	delete this->dato;
}

RegistroTabla::RegistroTabla(void) {
	this->dato = NULL;
}

std::ostream& operator<<(std::ostream& oss, RegistroTabla &reg) {
	reg.print(oss);
	return oss;
}

std::istream& operator>>(std::istream& oss, RegistroTabla &reg) {
	reg.read(oss);
	return oss;
}

unsigned long int RegistroTabla::getClaveDato(void) {
	return 0;
}

// FUNCIONAMIENTO READ:
// Lee el dato del archivo binario.

void RegistroTabla::read(std::istream& oss) {
	this->dato = new Data::ArrayBytes;
	oss >> *(this->dato);
}

// FUNCIONAMIENTO PRINT:
// Escribe el dato al archivo binario.

void RegistroTabla::print(std::ostream& oss) {
	oss << *(this->dato);
}

void RegistroTabla::borrarDato() {
	delete this->dato;
	this->dato = NULL;
}

int RegistroTabla::getTamanoDato() {
	return this->dato->getTamano();
}

// FUNCIONAMIENTO SERIALIZAR:
// Serializa la tabla en un ostream.

void RegistroTabla::serializar(std::ostream& oss) {
	this->dato->serializar(oss);
}

void RegistroTabla::ImprimirATexto(std::ostream& oss) {
	oss << "REGISTRO TABLA: " << std::endl;
	this->dato->Imprimir(oss);
}

void RegistroTabla::cargarTabla(array& vec) {
	this->dato->concatenar(vec);
}

}


