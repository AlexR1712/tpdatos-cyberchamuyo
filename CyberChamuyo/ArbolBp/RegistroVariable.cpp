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

    this->dato = dato;
    this->tamanoDato=tamanoDato;
}

RegistroVariable::RegistroVariable(std::vector<char>* data_v, long tamanoDato){
    this->tamanoDato=tamanoDato;
    std::vector<char>::iterator it;
    dato = new std::string;
    for(it = data_v->begin(); it != data_v->end(); ++it) {
    	dato->push_back(*it);
    }
}

RegistroVariable& RegistroVariable::operator=(const RegistroVariable& reg) {
	tamanoDato = reg.tamanoDato;
	dato = new std::string();
	for(int i = 0; i < reg.dato->size(); ++i) {
		dato->push_back(reg.dato->operator[](i));
	}
	return *this;
}

string* RegistroVariable::getDato(){
    return (this->dato);
}

void RegistroVariable::setDato(string* dato, long tamanoDato){
	if(this->dato != NULL)
		delete(this->dato);
    this->dato = new string;

	(*this->dato) = (*dato);
    this->tamanoDato=tamanoDato;
}

long RegistroVariable::getTamanoDato(){
    return (this->tamanoDato);
}

RegistroVariable::~RegistroVariable(){
	if(dato != NULL)
		delete dato;
}


