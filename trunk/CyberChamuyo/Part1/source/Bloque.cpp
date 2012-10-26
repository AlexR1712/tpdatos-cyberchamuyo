/*
 * File: Bloque.cpp
 *
 */

#include <list>
#include <iostream>

#include "../include/Bloque.h"

// FUNCIONAMIENTO CONSTRUCTOR DE BLOQUE:
// Setea los valores iniciales del bloque.
// La cantidad de espacio libre es el tamaño del
// bloque.

Bloque::Bloque(long tamanoBloque){
    this->tamanoBloque=tamanoBloque;
    this->espacioLibre=tamanoBloque;
    this->cantRegistros=0;
 }

// FUNCIONAMIENTO ADDREGISTRO:
// Agrega un registro a la estructura. En caso
// de no haber lugar devolverá error. En caso
// afirmativo lo agrega a la lista y modifica el
// espacio libre.

int Bloque::addRegistro(RegistroVariable *registro){
    long espacioOcupado;
    espacioOcupado=(*registro).getTamanoDato();
    if(espacioOcupado<=espacioLibre){
        registros.push_back(registro);
        this->setEspacioLibre(espacioOcupado);
        cantRegistros=cantRegistros+1;
    }else{
        return ERR_NO_MEMORIA;
    }
    return RES_OK;
}

// FUNCIONAMIENTO VACIAR:
// Vacia un bloque.

void Bloque::vaciar(void) {
	this->espacioLibre = tamanoBloque;
	this->cantRegistros = 0;
	borrarDatos();
	registros.clear();
}

long Bloque::getEspacioLibre(){

    return (this->espacioLibre);
}

// FUNCIONAMIENTO GET REGISTRO:
// Devuelve un registro variable dada la posición
// pasada por parámetro.

RegistroVariable* Bloque::getRegistro(int posicion){

    if ((posicion<cantRegistros)&&(posicion>=0)){
        std::list<RegistroVariable*>::iterator iterador = registros.begin();
        for (int i=0;i<posicion;i++){
            iterador ++;
        }
        return(*iterador);
    }else{
        throw ExcepcionPosicionInvalidaEnBloque();
    }
}

long Bloque::getTamanoBloque(){

    return (this->tamanoBloque);
}

void Bloque::setEspacioLibre(long espacioOcupado){

    this->espacioLibre=(this->espacioLibre)-espacioOcupado;
}

void Bloque::setCantRegistros(int cantReg){

    this->cantRegistros=cantReg;
}

int Bloque::getCantRegistros(){

    return(this->cantRegistros);
}

void Bloque::anularRegistros(void) {
	registros.clear();
}

// FUNCIONAMIENTO BORRAR DATOS:
// Libera la memoria dinámica de los registros variables.

void Bloque::borrarDatos(void) {
	std::list<RegistroVariable*>::iterator it;
	 for (it = registros.begin(); it != registros.end(); ++it) {
		 if (*it != NULL)
			 delete *it;
	 }
}

// FUNCIONAMIENTO BORRAR REGISTROS:
// Elimina un registro de un bloque dada la posición
// pasada como argumento. En caso afirmativo lo elimina
// en caso contrario devuelve error.

void Bloque::borrarRegistro(int posicion) {
	if ((posicion<cantRegistros)&&(posicion>=0)){
        std::list<RegistroVariable*>::iterator iterador = registros.begin();
        for (int i=0;i<posicion;i++){
            iterador ++;
        }
        delete *iterador;
        this->registros.erase(iterador);
        --this->cantRegistros;
    }else{
        throw ExcepcionPosicionInvalidaEnBloque();
    }
}

bool Bloque::estaVacio(void) {
	return this->registros.empty();
}

Bloque::~Bloque(){
	borrarDatos();
}

// FUNCIONAMIENTO OPERATOR<<:
// Serializa al archivo binario la metadata del bloque
// como la información de sus registros.

std::ostream& operator<<(std::ostream& oss,	Bloque &bl) {
	int cantReg = bl.cantRegistros;
	oss.write((char*)&(cantReg), sizeof(int));
	bl.print(oss);
	int it = 0;
	while (it < cantReg) {
		oss << *(bl.getRegistro(it));
		++it;
	}
	return oss;
}

// FUNCIONAMIENTO OPERATOR>>:
// Lee y carga del archivo binario la metadata del bloque
// como la información de sus registros.

std::istream& operator>>(std::istream& oss, Bloque &bl) {
	int cantReg;
	bl.cantRegistros = 0;
	oss.read((char*) (&cantReg), sizeof(int));
	bl.input(oss);
	bl.LlenarRegistros(oss, cantReg);
	return oss;
}

