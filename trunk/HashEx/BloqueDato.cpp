/*
 * BloqueDato.cpp
 *
 *  Created on: Sep 23, 2012
 *      Author: lucasj
 */

#include "BloqueDato.h"

// FUNCIONAMIENTO CONSTRUCTOR DE BLOQUE DATO:
// LLama al constructor del bloque para setear los valores
// del padre y setea el td.

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

// FUNCIONAMIENTO PRINT:
// Escribe del archivo binario el valor de su td.

void BloqueDato::print(std::ostream& oss) const {
	oss.write((char*)&(this->td), sizeof(unsigned int));
}

// FUNCIONAMIENTO INPUT:
// Lee del archivo binario el valor de su td.

void BloqueDato::input(std::istream& oss) const {
	oss.read((char*) (&(this->td)), sizeof(unsigned int));
}

// FUNCIONAMIENTO LLenarRegistros:
// Lee del archivo binario los registros y los carga al bloque.

void BloqueDato::LlenarRegistros(std::istream& oss, int cantReg) {
	int it = 0;
	while (it < cantReg) {
		RegistroVariable* nuevoRegistro = new Hash::RegistroDato;
		oss >> *nuevoRegistro;
		addRegistro(nuevoRegistro);
		++it;
	}
}

// FUNCIONAMIENTO IMPRIMIR A TEXTO:
// Imprime en un archivo de texto el contenido de los datos
// y los registros.

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

