/*
 * File:   Estruct.cpp
 * Author: emperor
 *
 * Created on 7 de abril de 2012, 20:30
 */

#include <iostream>
#include <fstream>
#include "../include/ArchivoBloquesFijos.h"

// FUNCIONAMIENTO Constructor de ArchivoBloquesFijos:
// Construye el objeto seteando sus valores en default o
// lee y carga del archivo en caso de existir.

ArchivoBloquesFijos::ArchivoBloquesFijos(const char* filename, long tamanoBloque){
    path.open(filename, std::fstream::in|std::fstream::out|std::fstream::binary);
    if (!path){
        std:: fstream archivo (filename, std::fstream::out|std::fstream::binary);
        archivo.close();
        path.open(filename, std::fstream::in|std::fstream::out|std::fstream::binary);
        this->tamanoBloque = tamanoBloque;
        this->autoId = 1;
    }else{ //probar
        path.seekg(0, std::ios::beg);
        path.read((char*)&(this->tamanoBloque),sizeof(long));
        path.read((char*)&(this->autoId),sizeof(unsigned int));
        path >> this->map;
    }
    this->dir = filename;
}

// FUNCIONAMIENTO CLEAR:
// Destruye el archivo de bloques fijos.

void ArchivoBloquesFijos::clear(void) {
	if(remove(this->dir.c_str()) != 0)
		throw ExcepcionDelete();
}

long ArchivoBloquesFijos::getTamanoBloque(){
    return (this->tamanoBloque);
}

int ArchivoBloquesFijos::getCantidadBloques(){
    return (this->map.getCantidadBloques());
}

int ArchivoBloquesFijos::getCantidadBloquesLibres(){
    return (this->map.getCantidadBloquesLibres());
}


// FUNCIONAMIENTO OBTENER BLOQUE LIBRE:
// Devuelve el primer bloque libre del vector de bloques libres.
// En caso de no existir devuelve ERR_BLOQUE_INEXISTENTE.

unsigned int ArchivoBloquesFijos::ObtenerBloqueLibre(){
	return this->map.getBloqueLibre();
}

// FUNCIONAMIENTO VERIFICAR BLOQUE LIBRE:
// Verifica su el número de bloque pasado por parámetro es un
// bloque libre..

int ArchivoBloquesFijos::VerificarBloqueLibre(unsigned int bloque){
    return (this->map.verificarBloqueLibre(bloque));
}

// FUNCIONAMIENTO SETEAR BLOQUE LIBRE:
// Borra un bloque libre pasado por parámetro.

void ArchivoBloquesFijos::SetearBloqueLibre(unsigned int bloque){
	this->map.setBloqueOcupado(bloque);
}

// FUNCIONAMIENTO ESCRIBIR:
// Escribe un bloque en el archivo. Cada clase sabe como persistirse.

int ArchivoBloquesFijos::Escribir(Bloque* elemento, unsigned int posicion){
	if (this->map.agregarBloque(posicion)) {
		int corrimiento = (posicion + 1) * tamanoBloque * metadatasize;
		path.seekp(corrimiento, std::ios::beg);
		path << *elemento;
	} else return ERR_BLOQUE_INEXISTENTE;
   return RES_OK;
}

// FUNCIONAMIENTO LEER:
// Lee un bloque en el archivo. Cada clase sabe como leerse.

int ArchivoBloquesFijos::Leer(unsigned int posicion, Bloque* elemento){
	int res = this->map.verificarBloqueOcupado(posicion);
	if (res == RES_OK) {
    	long int corrimiento = (posicion + 1) * tamanoBloque * metadatasize;
    	path.seekg(corrimiento, std::ios::beg);
    	path >> *elemento;
    } else return res;
    return RES_OK;
}

// FUNCIONAMIENTO BORRAR:
// Borra un bloque convirtiéndolo en bloque libre.

void ArchivoBloquesFijos::Borrar(long posicion){
	if (this->map.verificarBloqueOcupado(posicion) == RES_OK) {
		this->map.setBloqueLibre(posicion);
	} else {
		if (this->map.verificarBloqueLibre(posicion))
			throw ExcepcionBloqueLibre();
		else throw ExcepcionBloqueInexistente();
	}
}

// FUNCIONAMIENTO DESTRUCTOR DE ARCHIVO BLOQUES FIJOS:
// Escribe en el archivo la metadata para ser utilizada
// en otra sesión.

ArchivoBloquesFijos::~ArchivoBloquesFijos(){
	path.seekp(0, std::ios::beg);
	path.write((char*)&(this->tamanoBloque),sizeof(long));
	path.write((char*)&(this->autoId),sizeof(unsigned int));
	path << this->map;
	path.close();
}

// FUNCIONAMIENTO OPERATOR<<:
// Escribe en un archivo de texto la metadata de
// el archivo de bloques fijos.

std::ostream& operator<<(std::ostream& oss, ArchivoBloquesFijos &arch) {
    oss << "***********************" << std::endl;
	oss << "ARCHIVO BLOQUES FIJOS: " << std::endl;
	oss << "***********************" << std::endl;
	oss << "TAMAÑO BLOQUE:" << "\t" << arch.tamanoBloque << std::endl;
	oss << "PRÓXIMO NRO. ALEATORIO:" << "\t" << arch.autoId << std::endl;
	arch.map.ImprimirATexto(oss);
	return oss;
}

unsigned int ArchivoBloquesFijos::getNuevoId(void) {
	return this->autoId++;
}

unsigned int ArchivoBloquesFijos::getId() {
	return this->autoId;
}


void ArchivoBloquesFijos::insertarBit(unsigned int byte, unsigned int offset, unsigned int corr) {
	long int corrimiento = (offset + 1) * tamanoBloque * metadatasize;
	corrimiento = corrimiento + corr;
	unsigned int numByte = byte / 8;
	corrimiento = corrimiento + numByte;
	unsigned int numBit = byte % 8;
	unsigned char mask = 1;
	mask = mask << numBit;
	path.seekg(corrimiento, std::ios::beg);
	unsigned char nuevoValor = 0;
	path.read((char*) (&nuevoValor), sizeof(unsigned char));
	nuevoValor = nuevoValor | mask;
	path.seekg(corrimiento, std::ios::beg);
	path.write((char*) (&nuevoValor), sizeof(unsigned char));
}

void ArchivoBloquesFijos::borrarBit(unsigned int byte, unsigned int offset, unsigned int corr) {
	long int corrimiento = (offset + 1) * tamanoBloque * metadatasize;
	corrimiento = corrimiento + corr;
	unsigned int numByte = byte / 8;
	corrimiento = corrimiento + numByte;
	unsigned int numBit = byte % 8;
	unsigned char mask = 1;
	mask = mask << numBit;
	path.seekg(corrimiento, std::ios::beg);
	unsigned char nuevoValor = 0;
	path.read((char*) (&nuevoValor), sizeof(unsigned char));
	nuevoValor = nuevoValor ^ mask;
	path.seekg(corrimiento, std::ios::beg);
	path.write((char*) (&nuevoValor), sizeof(unsigned char));
}



