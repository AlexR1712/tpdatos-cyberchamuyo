/*
 * File:   Estruct.cpp
 * Author: emperor
 *
 * Created on 7 de abril de 2012, 20:30
 */

#include <list>
#include <iostream>

#include "Bloque.h"


Bloque::Bloque(long tamanoBloque){
    this->tamanoBloque=tamanoBloque;
    this->espacioLibre=tamanoBloque;
    this->cantRegistros=0;
 }

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

void Bloque::vaciar(void) {
	this->espacioLibre = tamanoBloque;
	this->cantRegistros = 0;
	borrarDatos();
	registros.clear();
}

long Bloque::getEspacioLibre(){

    return (this->espacioLibre);
}

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

void Bloque::borrarDatos(void) {
	std::list<RegistroVariable*>::iterator it;
	 for (it = registros.begin(); it != registros.end(); ++it) {
		 if (*it != NULL)
			 delete *it;
	 }
}

Bloque::~Bloque(){
	borrarDatos();
}

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

std::istream& operator>>(std::istream& oss, Bloque &bl) {
	int cantReg;
	bl.cantRegistros = 0;
	oss.read((char*) (&cantReg), sizeof(int));
	bl.input(oss);
	bl.LlenarRegistros(oss, cantReg);
	return oss;
}

