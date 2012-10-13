/*
 * BloqueDato.cpp
 *
 *  Created on: Sep 23, 2012
 *      Author: lucasj
 */

#include "BloqueDato.h"

BloqueDato::BloqueDato(long tamanoBloque):Bloque(tamanoBloque) {
	this->td = 0;
}


BloqueDato::~BloqueDato() {

}

unsigned int BloqueDato::getTd(void) {
	return this->td;

}

void BloqueDato::setTd(unsigned int td) {
	this->td = td;
}

void BloqueDato::print(std::ostream& oss) const {
	oss.write((char*)&(this->td), sizeof(unsigned int));
}

void BloqueDato::input(std::istream& oss) const {
	oss.read((char*) (&(this->td)), sizeof(unsigned int));
}

void BloqueDato::LlenarRegistros(std::istream& oss, int cantReg) {
	int it = 0;
	while (it < cantReg) {
		RegistroVariable* nuevoRegistro = new Hash::RegistroDato;
		oss >> *nuevoRegistro;
		addRegistro(nuevoRegistro);
		++it;
	}
}

void BloqueDato::ImprimirATexto(std::ostream& oss) {
	//oss << "***********************" << std::endl;
	oss << "BLOQUE DATO: " << std::endl;
	oss << "TD:" << "\t" << this->td << std::endl;
	int cantReg = this->getCantRegistros();
	for (int i = 0; i < cantReg; ++i) {
		RegistroVariable* Registro = this->getRegistro(i);
		Registro->ImprimirATexto(oss);
	}
}

