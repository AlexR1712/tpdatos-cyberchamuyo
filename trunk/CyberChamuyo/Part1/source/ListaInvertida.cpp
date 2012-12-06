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
	std::vector<unsigned char> vec;
	vec = l.serialize();
	int n = vec.size();
	oss.write((char*)&n, sizeof(unsigned int));
	std::vector<unsigned char>::iterator it;
	for (it = vec.begin(); it != vec.end(); ++it) {
		oss.write((char*)&(*it), sizeof(char));
	}
	return oss;
}

// FUNCIONAMIENTO OPERATOR>>:
// Lee y carga de un archivo binario el contenido de la clase.

std::istream& operator>>(std::istream& oss, ListaInvertida &l) {
	oss.read((char*)&l.id, sizeof(unsigned int));
	int n = 0;
	oss.read((char*)&n, sizeof(unsigned int));
	std::vector<unsigned char> vec;
	std::vector<unsigned char>::iterator it;
	for (int i = 0; i < n; ++i) {
		unsigned char num = 0;
		oss.read((char*)&num, sizeof(char));
		vec.push_back(num);
	}
	l.deserialize(vec);
	return oss;
}

std::vector<unsigned char> ListaInvertida::serialize() {
	int last_pos = 0;
	std::vector<unsigned char> vec_aux;
	Auxiliar::insertarEnteroU(vec_aux, this->lista.size());
	BinaryArray2 res(0);
	for(itListInt it = this->lista.begin(); it != this->lista.end(); ++it) {
		BinaryArray2 ba = TextRecoveryUtilities::gammaEncode(*it);
		int gammaSize = TextRecoveryUtilities::gammaSize(*it);
		res.append(ba, last_pos, gammaSize);
		last_pos += gammaSize;
	}
	res.push_array_front(vec_aux);
	std::vector<unsigned char> ret;
	for(unsigned int i = 0; i < res.size(); ++i)
		ret.push_back(res[i]);
	return ret;
}

void ListaInvertida::deserialize(std::vector<unsigned char> data) {
	int pos = 0;
	unsigned int cant = Auxiliar::leerEnteroU(data, pos);
	std::vector<unsigned char> vec_aux;
	for(unsigned int i = 4; i < data.size(); ++i)
		vec_aux.push_back(data[i]);
	BinaryArray2 ba(vec_aux);
	unsigned int offset = 0;
	for(unsigned int i = 0; i < cant; ++i) {
		unsigned int n = TextRecoveryUtilities::gammaDecode(ba, offset);
		offset += TextRecoveryUtilities::gammaSize(n);
		this->lista.push_back(n);
	}
}

void ListaInvertida::borrar(unsigned int id) {
	listInt::iterator it;
	for(it = lista.begin(); it != lista.end() && *it <= id; ++it) {
		if(id == *it)
			it = lista.erase(it);
	}
}

unsigned int ListaInvertida::size() {
	return lista.size();
}

} /* namespace invertedList */



