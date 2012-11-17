/*
 * BloqueNodo.cpp
 *
 *  Created on: Oct 17, 2012
 *      Author: lucasj
 */

#include "../include/BloqueNodo.h"

BloqueNodo::BloqueNodo(long tamanoBloque) {
	this->tamanoBloque=tamanoBloque;
    this->espacioLibre=tamanoBloque;
}

BloqueNodo::~BloqueNodo() {
	borrarDatos();
}


void BloqueNodo::ImprimirATexto(std::ostream& oss) {
	oss << "BLOQUE NODO: " << std::endl;
	int cantReg = this->getCantRegistros();
	for (int i = 0; i < cantReg; ++i) {
		RegistroVariable* Registro = this->getRegistro(i);
		Registro->ImprimirATexto(oss);
	}
}

int BloqueNodo::addRegistro(RegistroNodo *registro){
    long espacioOcupado;
    espacioOcupado=(*registro).getTamanoDato();
    if(espacioOcupado<=espacioLibre){
        this->registros.push_back(registro);
        this->setEspacioLibre(espacioOcupado);
    }else{
        return ERR_NO_MEMORIA;
    }
    return RES_OK;
}

// FUNCIONAMIENTO GET REGISTRO:
// Devuelve un registro variable dada la posición
// pasada por parámetro.

RegistroNodo* BloqueNodo::getRegistro(unsigned int posicion){
    if ((posicion < this->registros.size()) && (posicion >= 0)){
        itRegNodo iterador = this->registros.begin();
        for (unsigned int i = 0; i < posicion; i++){
            iterador ++;
        }
        return(*iterador);
    }else{
        throw ExcepcionPosicionInvalidaEnBloque();
    }
}

bool BloqueNodo::buscarRegistro(unsigned int clave, unsigned int& pos) {
	bool encontrado = false;
	itRegNodo it = this->registros.begin();
	unsigned int i = 0;
	while ((it != this->registros.end())  && (encontrado == false)) {
		if (clave == (*it)->getClaveDato())
			encontrado = true;
		else {
			++it;
			++i;
		}
	}
	if (encontrado == true) {
		pos = i;
		return true;
	} else return false;
}

// FUNCIONAMIENTO INPUT:
// Lee del archivo binario el valor de su td.

void BloqueNodo::input(std::istream& oss) {
	int cantReg = 0;
	oss.read((char*) (&cantReg), sizeof(int));
	LlenarRegistros(oss, cantReg);
}

void BloqueNodo::print(std::ostream& oss) {
	int cantReg = this->registros.size();
	oss.write((char*)&(cantReg), sizeof(int));
	for (itRegNodo it = this->registros.begin(); it != this->registros.end(); ++it) {
		oss << *(*it);
	}
}

// FUNCIONAMIENTO LLenarRegistros:
// Lee del archivo binario los registros y los carga al bloque.

void BloqueNodo::LlenarRegistros(std::istream& oss, int cantReg) {
	int it = 0;
	while (it < cantReg) {
		RegistroNodo* nuevoRegistro = new RegistroNodo;
		oss >> *nuevoRegistro;
		this->addRegistro(nuevoRegistro);
		++it;
	}
}


void BloqueNodo::anularRegistros(void) {
	this->registros.clear();
}

// FUNCIONAMIENTO BORRAR DATOS:
// Libera la memoria dinámica de los registros variables.

void BloqueNodo::borrarDatos(void) {
	itRegNodo it;
	 for (it = this->registros.begin(); it != this->registros.end(); ++it) {
		 if (*it != NULL)
			 delete *it;
	 }
}

// FUNCIONAMIENTO BORRAR REGISTROS:
// Elimina un registro de un bloque dada la posición
// pasada como argumento. En caso afirmativo lo elimina
// en caso contrario devuelve error.

void BloqueNodo::borrarRegistro(unsigned int posicion) {
	if ((posicion < this->registros.size()) && (posicion >= 0)){
        itRegNodo iterador = registros.begin();
        for (unsigned int i = 0; i < posicion; i++){
            iterador ++;
        }
        delete *iterador;
        this->registros.erase(iterador);
	}else{
        throw ExcepcionPosicionInvalidaEnBloque();
    }
}

bool BloqueNodo::estaVacio(void) {
	return this->registros.empty();
}

// FUNCIONAMIENTO VACIAR:
// Vacia un bloque.

void BloqueNodo::vaciar(void) {
	this->espacioLibre = tamanoBloque;
	borrarDatos();
	anularRegistros();
}

long BloqueNodo::getEspacioLibre(){

    return (this->espacioLibre);
}

long BloqueNodo::getTamanoBloque(void){
    return (this->tamanoBloque);
}

void BloqueNodo::setEspacioLibre(long espacioOcupado){
    this->espacioLibre=(this->espacioLibre)-espacioOcupado;
}

int BloqueNodo::getCantRegistros(){
    return(this->registros.size());
}


