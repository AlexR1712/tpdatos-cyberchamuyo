/*
 * BloqueNodo.cpp
 *
 *  Created on: Oct 17, 2012
 *      Author: lucasj
 */

#include "BloqueNodo.h"

BloqueNodo::BloqueNodo(long tamanoBloque):Bloque(tamanoBloque) {
}

BloqueNodo::~BloqueNodo() {

}

void BloqueNodo::print(std::ostream& oss) const {

}

void BloqueNodo::input(std::istream& oss) const {

}

void BloqueNodo::LlenarRegistros(std::istream& oss, int cantReg) {
	int it = 0;
	while (it < cantReg) {
		RegistroVariable* nuevoRegistro = new RegistroNodo;
		oss >> *nuevoRegistro;
		addRegistro(nuevoRegistro);
		++it;
	}
}

void BloqueNodo::ImprimirATexto(std::ostream& oss) {
	oss << "BLOQUE NODO: " << std::endl;
	int cantReg = this->getCantRegistros();
	for (int i = 0; i < cantReg; ++i) {
		RegistroVariable* Registro = this->getRegistro(i);
		Registro->ImprimirATexto(oss);
	}
}
