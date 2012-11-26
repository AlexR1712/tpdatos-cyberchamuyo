/*
 * Bitmap.cpp
 *
 *  Created on: Nov 15, 2012
 *      Author: lucasj
 */

#include "../include/Bitmap.h"

Bitmap::Bitmap(unsigned int bloqueInicial) {
	this->bloqueTope = bloqueInicial;
}

Bitmap::Bitmap(void) {
	this->bloqueTope = 0;
}

unsigned int Bitmap::getCantidadBloquesLibres(void) {
	return this->listaBl.size();
}

bool Bitmap::agregarBloque(unsigned int posicion) {
	 if (posicion > this->bloqueTope)
		 return false;
	 else if (posicion == this->bloqueTope) {
		 ++this->bloqueTope;
		 if (this->verificarBloqueLibre(posicion))
			 this->setBloqueOcupado(posicion);
	 }
	  return true;
}

int Bitmap::verificarBloqueOcupado(unsigned int posicion) {
	if (posicion >= bloqueTope)
        return ERR_BLOQUE_INEXISTENTE;
	else if (this->verificarBloqueLibre(posicion))
		return ERR_BLOQUE_LIBRE;
	return RES_OK;
}

void Bitmap::completarMapa(unsigned int numByte, Mapa& map) {
	map.insert(map.end(), numByte + 1, 0);
}

void Bitmap::serializar(Mapa& map) {
	itLista it;
	for (it = this->listaBl.begin(); it != this->listaBl.end(); ++it) {
		setBit(*it, map);
	}
}

void Bitmap::setBit(unsigned int bloque, Mapa& map) {
	unsigned int numByte = bloque / 8;
	if (numByte >= map.size())
		completarMapa(numByte, map);
	unsigned int numBit = bloque % 8;
	unsigned char mask = 1;
	mask = mask << numBit;
	unsigned char nuevoValor = map[numByte] | mask;
	map[numByte] = nuevoValor;
}

void Bitmap::setBloqueLibre(unsigned int bloque) {
	this->listaBl.push_back(bloque);
}

void Bitmap::eliminarBloqueLista(unsigned int bloque) {
	itLista it = this->listaBl.begin();
	while ((it != this->listaBl.end()) && (*it != bloque))
		++it;
	if (it != this->listaBl.end())
		this->listaBl.erase(it);
}

void Bitmap::setBloqueOcupado(unsigned int bloque) {
	eliminarBloqueLista(bloque);
}

unsigned int Bitmap::getBloqueLibre(void) {
	if (this->listaBl.empty())
		return this->bloqueTope;
	else return this->listaBl.front();
}

unsigned int Bitmap::getCantidadBloques(void) {
	return this->bloqueTope;
}

void Bitmap::ImprimirATexto(std::ostream& oss) {
	oss << "CANTIDAD DE BLOQUES:" << "\t" << this->bloqueTope << std::endl;
	oss << "CANTIDAD DE BLOQUES LIBRES:" << "\t" << this->listaBl.size() << std::endl;
	itLista it;
	/*for (it = this->listaBl.begin(); it != this->listaBl.end(); ++it) {
		oss << "Bloques: " << *it << std::endl;
	}*/
}

bool Bitmap::verificarBloqueLibre(unsigned int bloque) {
	itLista it = this->listaBl.begin();
	while ((it != this->listaBl.end()) && (*it != bloque))
		++it;
	if (it != this->listaBl.end())
		return true;
	else return false;
}

std::ostream& operator<<(std::ostream& oss,	Bitmap &bm) {
	Mapa map;
	bm.serializar(map);
	oss.write((char*)&(bm.bloqueTope), sizeof(unsigned int));
	unsigned int N = map.size();
	oss.write((char*)&(N), sizeof(unsigned int));
	itMapa it;
	int i = 0;
	for (it = map.begin(); it != map.end(); ++it) {
		oss.write((char*)&(*it), sizeof(unsigned char));
		++i;
	}
	return oss;
}

void Bitmap::llenarListaBloques(unsigned char valor, unsigned int i) {
	unsigned char mask = 1;
	unsigned int j = 0;
	while (mask != 0) {
		if (valor & mask) {
			this->listaBl.push_back(i*8 + j);
		}
		++j;
		mask = mask << 1;
	}
}

std::istream& operator>>(std::istream& oss, Bitmap &bm) {
	unsigned int N = 0;
	oss.read((char*)&(bm.bloqueTope), sizeof(unsigned int));
	oss.read((char*) (&N), sizeof(unsigned int));
	for (unsigned int i = 0; i < N; ++i) {
		unsigned char valor;
		oss.read((char*) (&valor), sizeof(unsigned char));
		bm.llenarListaBloques(valor, i);
	}
	return oss;
}

Bitmap::~Bitmap() {

}

