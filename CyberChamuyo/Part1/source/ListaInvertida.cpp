/*
 * ListaInvertida.cpp
 *
 *  Created on: Nov 28, 2012
 *      Author: lucasj
 */

#include "../include/ListaInvertida.h"

namespace invertedList {

const listInt& ListaInvertida::getParticion(void) const{
	return this->lista;
}

ListaInvertida& ListaInvertida::operator+=(const ListaInvertida &l) {
	this->lista.insert(this->lista.end(), l.getParticion().begin(), l.getParticion().end());
	this->id = l.id;
	return *this;
}

ListaInvertida::ListaInvertida() {
	this->id = 0;
}

void ListaInvertida::setId(unsigned int docId) {
	this->id = docId;
}

unsigned int ListaInvertida::getId(void) {
	return this->id;
}

ListaInvertida::~ListaInvertida() {

}

// FUNCIONAMIENTO SERIALIZAR:


void ListaInvertida::serializar(std::ostream& oss) {
	itListInt it;
	for (it = this->lista.begin(); it != this->lista.end(); ++it) {
		oss << *it << "\t";
	}
}

int ListaInvertida::getTamano() {
	return this->lista.size()*sizeof(unsigned int);
}

void ListaInvertida::insertar(unsigned int num) {
	this->lista.push_back(num);
}

// FUNCIONAMIENTO IMPRIMIR:
// Imprime el array en un archivo de texto.

void ListaInvertida::Imprimir(std::ostream& oss) {
	oss << "PARTICION: " << std::endl;
	oss << "ID: " << this->id << std::endl;
	itListInt it;
	for (it = this->lista.begin(); it != this->lista.end(); ++it) {
		oss << *it << " ";
	}
	oss << std::endl;
}

// FUNCIONAMIENTO OPERATOR<<:
// Serializa en un archivo binario el contenido de la clase.

std::ostream& operator<<(std::ostream& oss, ListaInvertida &l) {
	oss.write((char*)&l.id, sizeof(unsigned int));
	int n = l.lista.size();
	oss.write((char*)&n, sizeof(char));
	itListInt it;
	for (it = l.lista.begin(); it != l.lista.end(); ++it) {
		oss.write((char*)&(*it), sizeof(unsigned int));
	}
	return oss;
}

// FUNCIONAMIENTO OPERATOR>>:
// Lee y carga de un archivo binario el contenido de la clase.

std::istream& operator>>(std::istream& oss, ListaInvertida &l) {
	oss.read((char*)&l.id, sizeof(unsigned int));
	int n = 0;
	oss.read((char*)&n, sizeof(char));
	for (int i = 0; i < n; ++i) {
		unsigned int num = 0;
		oss.read((char*)&num, sizeof(unsigned int));
		l.lista.push_back(num);
	}
	return oss;
}


} /* namespace invertedList */



