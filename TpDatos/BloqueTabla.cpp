/*
 * BloqueTabla.cpp
 *
 *  Created on: Sep 23, 2012
 *      Author: lucasj
 */

#include "BloqueTabla.h"



BloqueTabla::BloqueTabla(long tamanoBloque):Bloque(tamanoBloque) {
	this->siguiente = 0;
}

BloqueTabla::~BloqueTabla() {
}

unsigned int BloqueTabla::getSiguiente(void) {
	return this->siguiente;

}

void BloqueTabla::setSiguiente(unsigned int siguiente) {
	this->siguiente = siguiente;
}

void BloqueTabla::print(std::ostream& oss) const {
	oss.write((char*)&(this->siguiente), sizeof(unsigned int));
}

void BloqueTabla::input(std::istream& oss) const {
	oss.read((char*) &(this->siguiente), sizeof(unsigned int));
}

void BloqueTabla::LlenarRegistros(std::istream& oss, int cantReg) {
	int it = 0;
	while (it < cantReg) {
		RegistroVariable* nuevoRegistro = new Hash::RegistroTabla;
		oss >> *nuevoRegistro;
		addRegistro(nuevoRegistro);
		++it;
	}
}

/*void BloqueTabla::cargarTabla(array& vec) {
	int cantReg = this->getCantRegistros();
	for (int i = 0; i < cantReg; ++i) {
		RegistroVariable* Registro = this->getRegistro(i);
		this->
	}
}*/

void BloqueTabla::ImprimirATexto(std::ostream& oss) {
	//oss << "***********************" << std::endl;
	oss << "BLOQUE TABLA: " << std::endl;
	oss << "SIGUIENTE: " << "\t" << this->siguiente << std::endl;
	int cantReg = this->getCantRegistros();
	for (int i = 0; i < cantReg; ++i) {
		RegistroVariable* Registro = this->getRegistro(i);
		Registro->ImprimirATexto(oss);
	}
}


