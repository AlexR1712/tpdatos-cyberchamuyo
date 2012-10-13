/*
 * RegistroDato.cpp
 *
 *  Created on: Sep 27, 2012
 *      Author: lucasj
 */

#include "RegistroDato.h"

namespace Hash {

RegistroDato::RegistroDato(Data::Frase* dato) {
	this->dato = dato;
}

RegistroDato::RegistroDato(void) {
	this->dato = NULL;
}

RegistroDato::~RegistroDato() {
	delete this->dato;
}

std::ostream& operator<<(std::ostream& oss, RegistroDato &reg) {
	reg.print(oss);

	return oss;
}

std::istream& operator>>(std::istream& oss, RegistroDato &reg) {
	reg.read(oss);
	return oss;
}

unsigned long int RegistroDato::getClaveDato(void) {
	return this->dato->getClave();
}

void RegistroDato::read(std::istream& oss) {
	this->dato = new Data::Frase;
	oss >> *(this->dato);
}

void RegistroDato::print(std::ostream& oss) {
	oss << *(this->dato);
}

void RegistroDato::borrarDato() {
	delete this->dato;
	this->dato = NULL;
}

void RegistroDato::serializar(std::ostream& oss) {
}

int RegistroDato::getTamanoDato() {
	return this->dato->getTamano();
}

void RegistroDato::ImprimirATexto(std::ostream& oss) {
	//oss << "***********************" << std::endl;
	oss << "REGISTRO DATO: " << std::endl;
	this->dato->Imprimir(oss);
}

}
