/*
 * ArrayBytes.cpp
 *
 *  Created on: Oct 6, 2012
 *      Author: lucasj
 */

#include "../include/ArrayBytes.h"

namespace Data {

ArrayBytes::ArrayBytes() {

}

// FUNCIONAMIENTO SERIALIZAR:
// Serializa el arreglo de bytes como una cadena de caracteres.

void ArrayBytes::serializar(std::ostream& oss) {
	itArray it;
	for (it = this->arreglo.begin(); it != this->arreglo.end(); ++it) {
		oss << *it << "\t";
	}
}

int ArrayBytes::getTamano() {
	return this->arreglo.size()*sizeof(unsigned int);
}

void ArrayBytes::insertar(unsigned int num) {
	this->arreglo.push_back(num);
}

// FUNCIONAMIENTO CONCATENAR:
// Concatena vectores.

void ArrayBytes::concatenar(array& vec) {
	vec.insert(vec.begin(), this->arreglo.begin(), this->arreglo.end());
}

ArrayBytes::~ArrayBytes() {

}

// FUNCIONAMIENTO IMPRIMIR:
// Imprime el array en un archivo de texto.

void ArrayBytes::Imprimir(std::ostream& oss) {
	oss << "PARTICION: " << std::endl;
	itArray it;
	for (it = this->arreglo.begin(); it != this->arreglo.end(); ++it) {
		oss << *it << " ";
	}
	oss << std::endl;
}

// FUNCIONAMIENTO OPERATOR<<:
// Serializa en un archivo binario el contenido de la clase.

std::ostream& operator<<(std::ostream& oss, ArrayBytes &a) {
	int n = a.arreglo.size();
	oss.write((char*)&n, sizeof(char));
	itArray it;
	for (it = a.arreglo.begin(); it != a.arreglo.end(); ++it) {
		oss.write((char*)&(*it), sizeof(unsigned int));
	}
	return oss;
}

// FUNCIONAMIENTO OPERATOR>>:
// Lee y carga de un archivo binario el contenido de la clase.

std::istream& operator>>(std::istream& oss, ArrayBytes &a) {
	int n = 0;
	oss.read((char*)&n, sizeof(char));
	for (int i = 0; i < n; ++i) {
		unsigned int num = 0;
		oss.read((char*)&num, sizeof(unsigned int));
		a.arreglo.push_back(num);
	}
	return oss;
}


}
