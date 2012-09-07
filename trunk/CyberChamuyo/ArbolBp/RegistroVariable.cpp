/*
 * File:   Estruct.cpp
 * Author: emperor
 *
 * Created on 7 de abril de 2012, 20:30
 */

#include <iosfwd>

#include "RegistroVariable.h"
using std::string;

RegistroVariable::RegistroVariable(){

    this->dato=NULL;
    this->tamanoDato=0;
 }

RegistroVariable::RegistroVariable(string* dato, long tamanoDato){

    this->dato=dato;
    this->tamanoDato=tamanoDato;
}

string* RegistroVariable::getDato(){

    return (this->dato);
}

void RegistroVariable::setDato(string* dato, long tamanoDato){

    delete(this->dato);
    this->dato=dato;
    this->tamanoDato=tamanoDato;
}

long RegistroVariable::getTamanoDato(){

    return (this->tamanoDato);
}

RegistroVariable::~RegistroVariable(){

}


