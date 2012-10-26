/*
 * BloqueTabla.cpp
 *
 *  Created on: Sep 23, 2012
 *      Author: lucasj
 */

#include "../include/BloqueTabla.h"


// FUNCIONAMIENTO CONSTRUCTOR DE BLOQUE TABLA:
// LLama al constructor del bloque para setear los valores
// del padre y setea el siguiente.

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

// FUNCIONAMIENTO PRINT:
// Escribe del archivo binario el valor de su siguiente.

void BloqueTabla::print(std::ostream& oss) const {
	oss.write((char*)&(this->siguiente), sizeof(unsigned int));
}

// FUNCIONAMIENTO INPUT:
// Lee del archivo binario el valor de su siguiente.

void BloqueTabla::input(std::istream& oss) const {
	oss.read((char*) &(this->siguiente), sizeof(unsigned int));
}

// FUNCIONAMIENTO LLenarRegistros:
// Lee del archivo binario los registros y los carga al bloque.

void BloqueTabla::LlenarRegistros(std::istream& oss, int cantReg) {
	int it = 0;
	while (it < cantReg) {
		RegistroVariable* nuevoRegistro = new Hash::RegistroTabla;
		oss >> *nuevoRegistro;
		addRegistro(nuevoRegistro);
		++it;
	}
}

// FUNCIONAMIENTO IMPRIMIR A TEXTO:
// Imprime en un archivo de texto el contenido de los datos
// y los registros.

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


