/*
 * Registro.cpp
 *
 *  Created on: 06/05/2012
 *      Author: Shazgath
 */

#include "../include/Registro.h"
#include "../include/common.h"
#include <cstring>
#include "../include/CAlfa.h"
#include "../include/ArbolBp.h"

Registro::Registro() {
	tipo = TIPO_ARBOL;
	clave = NULL;
	/*switch(TIPO_ARBOL) {
	case 0:
		clave = new C_Entero();
	case 1:
		clave = new CAlfa();
	}*/
}

Registro::Registro(Clave* c) {
	tipo = c->getTipo();
	clave = c;
	tam = 0;
}


Registro::Registro(Clave* c, std::string dat) {
	tipo = c->getTipo();
	clave = c;
	tam = dat.size() * sizeof(char);
	dato = dat;
}

Registro::Registro(const Registro& reg) {
	tipo = reg.tipo;
	switch(tipo) {
	case 0:
		clave = new C_Entero();
	case 1:
		clave = new CAlfa();
	}
	*clave = *(reg.clave);
	tam = reg.tam;
	dato = reg.dato;
}

Registro::~Registro() {
	delete clave;
}

std::vector<char>* Registro::serializar(FrontCoding& encoder) {
	std::vector<char>* s = new std::vector<char>;
	s = Auxiliar::insertarEntero(s, tipo);
	//s = Auxiliar::insertarEntero(s, clave->size() + 1);
	std::vector<char>* s_clave = new std::vector<char>;
	s_clave = clave->serializar(s_clave);
	std::vector<char>* s_clave_coded = new std::vector<char>;
	encoder.encode(s_clave, s_clave_coded);
	s->push_back(s_clave_coded->size());
	s->insert(s->end(), s_clave_coded->begin(), s_clave_coded->end());
	s = Auxiliar::insertarEntero(s, tam);
	s = Auxiliar::insertarString(s, dato);
	delete s_clave;
	delete s_clave_coded;
	return s;
}

void Registro::hidratar(const std::vector<char>* vec, FrontCoding& decoder,int& pos) {
	int p = 0;
	tipo = Auxiliar::leerEntero(vec, pos);
	switch(tipo) {
	case 0:
		std::cout << "entre a 0 en registro hidratar" << std::endl;
		clave = new C_Entero();
	case 1:
		clave = new CAlfa();
	}
	char c_size = (*vec)[pos++];
	std::string clave_raw, clave_deco;
	for(int i = pos; i < pos + c_size; ++i)
		clave_raw.push_back((*vec)[i]);
	decoder.decode(clave_raw, clave_deco);
	std::vector<char> vecAux;
	vecAux.insert(vecAux.begin(), clave_deco.begin(), clave_deco.end());
	clave->setSize(vecAux.size());
	clave->hidratar(&vecAux,pos); // sacar possss
	pos += c_size;	//  por el byte de cant de front coding
	tam = Auxiliar::leerEntero(vec, pos);
	Auxiliar::leerString(vec, dato, pos, tam);
}

void Registro::hidratar(const string &s) {
	long p, size = 0;
	//tipo = Auxiliar::leerEntero(p, s);
	switch(tipo){
	case 0:
		std::cout << "entre a 0 en Registro hidratar" << std::endl;
		clave = new C_Entero();
	case 1:
		clave = new CAlfa();
	}
	//long size = Auxiliar::leerEntero(p, s);
	std::string clave_string = s.substr(p, size);
	p+= size;
	std::vector<char> vec;
	for(int i = 0; i < size; ++i)
		vec.push_back(clave_string[i]);
	//clave->hidratar(vec, 0);
	//tam = Auxiliar::leerEntero(p, s);
	string data = s.substr(p, tam);
	dato = data;
}

int Registro::totalSize() {
	return tam + clave->size() + 3*sizeof(long);
}


void Registro::setTipo(int t) {
	tipo = t;
}

void Registro::setDato(char* d) {
	dato = d;
}

int Registro::size() {
	return tam;
}

Clave* Registro::getClave() {
	return clave;
}

int Registro::byte_size() {
	return tam + REG_CONTROL_SIZE + clave->byte_size();
}

Clave* Registro::getClaveCopia() {
	Clave* c;
	switch(tipo) {
	case 0:
		std::cout << "entre a 0 en getclavecopia" << std::endl;
		c = new C_Entero();
	case 1:
		c = new CAlfa();
	}
	(*c) = *clave;
	return c;
}

Registro& Registro::operator=(const Registro& r) {
	tam = r.tam;
	tipo = r.tipo;
	int tipo = r.clave->getTipo();
	if(clave == NULL) {
		switch(tipo) {
		case 0:
			clave = new C_Entero();
		case 1:
			clave = new CAlfa();
		}
	}
	*clave = *(r.clave);
	dato = r.dato;
}

std::ostream& operator<<(std::ostream& os, const Registro& r) {
	if(&r != NULL)
		os << "Registro = "<< (r.clave)->print() << "  |  Datos = " << r.dato;
	return os;
}

Registro* Registro::find() {
	return this;
}
