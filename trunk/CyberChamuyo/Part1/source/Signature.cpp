/*
 * Signature.cpp
 *
 *  Created on: Dec 4, 2012
 *      Author: lucasj
 */

#include "../include/Signature.h"

namespace Signature {

Signature::Signature(unsigned int nTermino) {
	this->nTermino = nTermino;
}

Signature::Signature(void) {
	this->nTermino = 0;
}

void Signature::completarMapa(unsigned int numByte) {
	this->map.insert(this->map.end(), numByte + 1, 0);
}

void Signature::setBit(unsigned int nFrase) {
	--nFrase;
	unsigned int numByte = nFrase / 8;
	if (numByte >= this->map.size())
		completarMapa(numByte);
	unsigned int numBit = nFrase % 8;
	unsigned char mask = 1;
	mask = mask << numBit;
	unsigned char nuevoValor = this->map[numByte] | mask;
	this->map[numByte] = nuevoValor;
}

void Signature::eliminarBit(unsigned int nFrase) {
	--nFrase;
	unsigned int numByte = nFrase / 8;
	if (numByte <= this->map.size()) {
		unsigned int numBit = nFrase % 8;
		unsigned char mask = 1;
		mask = mask << numBit;
		unsigned char nuevoValor = this->map[numByte] ^ mask;
		this->map[numByte] = nuevoValor;
	}
}

void Signature::convertirABit(std::ostream& oss, unsigned char valor, unsigned int* i) {
	unsigned char mask = 1;
	unsigned int j = 0;
	while (mask != 0) {
		if (valor & mask) {
			unsigned int k = (*i) *8 + j + 1;
			oss << k << " ";
		}
		++j;
		mask = mask << 1;
	}
}

void Signature::convertirABit(listaFrases& list, unsigned char valor, unsigned int* i) {
	unsigned char mask = 1;
	unsigned int j = 0;
	while (mask != 0) {
		if (valor & mask) {
			unsigned int k = (*i) *8 + j + 1;
			list.push_back(k);
		}
		++j;
		mask = mask << 1;
	}
}


void Signature::Imprimir(std::ostream& oss) {
	itMapa it;
	oss << "FIRMA Nº TERMINO: " << this->nTermino << std::endl;
	oss << "FRASES: " << std::endl;
	unsigned int i = 0;
	for (it = this->map.begin(); it != this->map.end(); ++it) {
		convertirABit(oss, *it, &i);
		++i;
	}
	oss << std::endl;
}

std::istream& operator>>(std::istream& oss, Signature &s) {
	oss.read((char*) (&s.nTermino), sizeof(unsigned int));
	unsigned int N = 0;
	oss.read((char*) (&N), sizeof(unsigned int));
	for (unsigned int i = 0; i < N; ++i) {
		unsigned char valor;
		oss.read((char*) (&valor), sizeof(unsigned char));
		s.map.push_back(valor);
	}
	return oss;
}

std::ostream& operator<<(std::ostream& oss,	Signature &s) {
	oss.write((char*)&(s.nTermino), sizeof(unsigned int));
	unsigned int N = s.map.size();
	oss.write((char*)&(N), sizeof(unsigned int));
	itMapa it;
	int i = 0;
	for (it = s.map.begin(); it != s.map.end(); ++it) {
		oss.write((char*)&(*it), sizeof(unsigned char));
		++i;
	}
	return oss;
}

unsigned int Signature::getTamano(void) {
	return this->map.size()*sizeof(unsigned int);
}

void Signature::serializar(std::ostream& oss) {

}

unsigned int Signature::getClaveDato(void) {
	return this->nTermino;
}

void Signature::setClaveDato(unsigned int clave) {
	this->nTermino = clave;
}

void Signature::obtenerListaFrases(listaFrases& lista) {
	itMapa it;
	unsigned int i = 0;
	for (it = this->map.begin(); it != this->map.end(); ++it) {
		convertirABit(lista, *it, &i);
		++i;
	}
}


Signature::~Signature() {


}

} /* namespace Signature */
