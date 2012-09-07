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

void Bloque::addRegistro(RegistroVariable *registro){

    long espacioOcupado;
    espacioOcupado=(*registro).getTamanoDato();
    if(espacioOcupado<=espacioLibre){
        registros.push_back(*registro);
        this->setEspacioLibre(espacioOcupado);
        cantRegistros=cantRegistros+1;
    }else{
        throw ExcepcionNoHayMemoriaEnBloque();
    }
}

long Bloque::getEspacioLibre(){

    return (this->espacioLibre);
}

RegistroVariable* Bloque::getRegistro(int posicion){

    if ((posicion<cantRegistros)&&(posicion>=0)){
        std::list<RegistroVariable>::iterator iterador = registros.begin();
        for (int i=0;i<posicion;i++){
            iterador ++;
        }
        return(&(*iterador));
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

Bloque::~Bloque(){

}