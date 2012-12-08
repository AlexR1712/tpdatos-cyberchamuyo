/*
 * RegistroFirma.cpp
 *
 *  Created on: Dec 4, 2012
 *      Author: lucasj
 */

#include "../include/RegistroFirma.h"

void RegistroFirma::insertarFrase(unsigned int nFrase) {
	this->dato->setBit(nFrase);
}

void RegistroFirma::borrarFrase(unsigned int nFrase) {
	this->dato->eliminarBit(nFrase);
}

RegistroFirma::RegistroFirma(Signature::Signature* dato) {
	this->dato = dato;
}

RegistroFirma::~RegistroFirma() {
	delete this->dato;
}

RegistroFirma::RegistroFirma(void) {
	this->dato = NULL;
}

std::ostream& operator<<(std::ostream& oss, RegistroFirma &reg) {
	reg.print(oss);
	return oss;
}

std::istream& operator>>(std::istream& oss, RegistroFirma &reg) {
	reg.read(oss);
	return oss;
}

unsigned long int RegistroFirma::getClaveDato(void) {
	return this->dato->getClaveDato();
}

// FUNCIONAMIENTO READ:
// Lee el dato del archivo binario.

void RegistroFirma::read(std::istream& oss) {
	this->dato = new Signature::Signature;
	oss >> *(this->dato);
}

// FUNCIONAMIENTO PRINT:
// Escribe el dato al archivo binario.

void RegistroFirma::print(std::ostream& oss) {
	oss << *(this->dato);
}

void RegistroFirma::borrarDato() {
	delete this->dato;
	this->dato = NULL;
}

int RegistroFirma::getTamanoDato() {
	return this->dato->getTamano();
}

// FUNCIONAMIENTO SERIALIZAR:
// Serializa la tabla en un ostream.

void RegistroFirma::serializar(std::ostream& oss) {
	this->dato->serializar(oss);
}

void RegistroFirma::ImprimirATexto(std::ostream& oss) {
	oss << "REGISTRO FIRMA: " << std::endl;
	this->dato->Imprimir(oss);
}

void RegistroFirma::obtenerListaFrases(listaFrases& lista) {
	this->dato->obtenerListaFrases(lista);
}




