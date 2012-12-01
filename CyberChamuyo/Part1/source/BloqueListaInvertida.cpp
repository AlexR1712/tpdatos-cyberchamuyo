/*
 * BloqueListaInvertida.cpp
 *
 *  Created on: Nov 28, 2012
 *      Author: lucasj
 */

#include "../include/BloqueListaInvertida.h"

BloqueListaInvertida::BloqueListaInvertida(long tamanoBloque) {
	this->siguiente = 0;
	this->primero = 0;
	this->tamanoBloque = tamanoBloque;
    this->espacioLibre = tamanoBloque - 8;
}

unsigned int BloqueListaInvertida::getSiguiente(void) {
	return this->siguiente;
}

void BloqueListaInvertida::setSiguiente(unsigned int siguiente) {
	this->siguiente = siguiente;
}

unsigned int BloqueListaInvertida::getPrimero(void) {
	return this->primero;
}

void BloqueListaInvertida::setPrimero(unsigned int primero) {
	this->primero = primero;
}

// FUNCIONAMIENTO PRINT:
// Escribe del archivo binario el valor de su siguiente.

void BloqueListaInvertida::print(std::ostream& oss) {
	unsigned int cantReg = this->registros.size();
	oss.write((char*)&(cantReg), sizeof(unsigned int));
	oss.write((char*)&(this->primero), sizeof(unsigned int));
	oss.write((char*)&(this->siguiente), sizeof(unsigned int));
	for (itRegListaInvertida it = this->registros.begin(); it != this->registros.end();
			++it) {
		oss << *(*it);
	}
}

// FUNCIONAMIENTO INPUT:
// Lee del archivo binario el valor de su siguiente.

void BloqueListaInvertida::input(std::istream& oss) {
	int cantReg = 0;
	oss.read((char*) (&cantReg), sizeof(unsigned int));
	oss.read((char*) &(this->primero), sizeof(unsigned int));
	oss.read((char*) &(this->siguiente), sizeof(unsigned int));
	LlenarRegistros(oss, cantReg);
}

// FUNCIONAMIENTO LLenarRegistros:
// Lee del archivo binario los registros y los carga al bloque.

void BloqueListaInvertida::LlenarRegistros(std::istream& oss, int cantReg) {
	int it = 0;
	while (it < cantReg) {
		RegistroListaInvertida* nuevoRegistro = new RegistroListaInvertida;
		oss >> *nuevoRegistro;
		addRegistro(nuevoRegistro);
		++it;
	}
}

// FUNCIONAMIENTO IMPRIMIR A TEXTO:
// Imprime en un archivo de texto el contenido de los datos
// y los registros.

void BloqueListaInvertida::ImprimirATexto(std::ostream& oss) {
	//oss << "***********************" << std::endl;
	oss << "BLOQUE LISTA INVERTIDA: " << std::endl;
	oss << "PRIMERO: " << "\t" << this->primero << std::endl;
	oss << "SIGUIENTE: " << "\t" << this->siguiente << std::endl;
	int cantReg = this->getCantRegistros();
	for (int i = 0; i < cantReg; ++i) {
		RegistroVariable* Registro = this->getRegistro(i);
		Registro->ImprimirATexto(oss);
	}
}

// FUNCIONAMIENTO ADDREGISTRO:
// Agrega un registro a la estructura. En caso
// de no haber lugar devolverá error. En caso
// afirmativo lo agrega a la lista y modifica el
// espacio libre.

int BloqueListaInvertida::addRegistro(RegistroListaInvertida *registro){
    long espacioOcupado;
    espacioOcupado=(*registro).getTamanoDato();
    if(espacioOcupado <= this->espacioLibre){
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

RegistroListaInvertida* BloqueListaInvertida::getRegistro(unsigned int posicion){
    if ((posicion < this->registros.size()) && (posicion >= 0)){
        itRegListaInvertida iterador = this->registros.begin();
        for (unsigned int i = 0; i < posicion; i++){
            iterador ++;
        }
        return(*iterador);
    }else{
        throw ExcepcionPosicionInvalidaEnBloque();
    }
}

void BloqueListaInvertida::anularRegistros(void) {
	this->registros.clear();
}

// FUNCIONAMIENTO BORRAR DATOS:
// Libera la memoria dinámica de los registros variables.

void BloqueListaInvertida::borrarDatos(void) {
	itRegListaInvertida it;
	 for (it = this->registros.begin(); it != this->registros.end(); ++it) {
		 if (*it != NULL)
			 delete *it;
	 }
}

// FUNCIONAMIENTO BORRAR REGISTROS:
// Elimina un registro de un bloque dada la posición
// pasada como argumento. En caso afirmativo lo elimina
// en caso contrario devuelve error.

void BloqueListaInvertida::borrarRegistro(unsigned int posicion) {
	if ((posicion < this->registros.size()) && (posicion >= 0)){
        itRegListaInvertida iterador = registros.begin();
        for (unsigned int i = 0; i < posicion; i++){
            iterador ++;
        }
        delete *iterador;
        this->registros.erase(iterador);
	}else{
        throw ExcepcionPosicionInvalidaEnBloque();
    }
}

bool BloqueListaInvertida::estaVacio(void) {
	return this->registros.empty();
}

// FUNCIONAMIENTO VACIAR:
// Vacia un bloque.

void BloqueListaInvertida::vaciar(void) {
	this->espacioLibre = tamanoBloque;
	borrarDatos();
	anularRegistros();
}

long BloqueListaInvertida::getEspacioLibre(){
    return (this->espacioLibre);
}

long BloqueListaInvertida::getTamanoBloque(void){
    return (this->tamanoBloque);
}

void BloqueListaInvertida::setEspacioLibre(long espacioOcupado){
    this->espacioLibre=(this->espacioLibre)-espacioOcupado;
}

int BloqueListaInvertida::getCantRegistros(){
    return(this->registros.size());
}

bool BloqueListaInvertida::buscarRegistro(unsigned int clave, unsigned int& pos) {
	bool encontrado = false;
	itRegListaInvertida it = this->registros.begin();
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

void BloqueListaInvertida::cargarListaInvertida(invertedList::ListaInvertida& list, unsigned int offset) {
	RegistroListaInvertida* reg = this->getRegistro(0);
	reg->cargarListaInvertida(list, offset);
}


BloqueListaInvertida::~BloqueListaInvertida() {
	this->borrarDatos();
}

