/*
 * RegistroArbol.cpp
 *
 *  Created on: 18/10/2012
 *      Author: sebastian
 */

#include "RegistroArbol.h"
#include "ArbolBp.h"

RegistroArbol::RegistroArbol() {
	tipo = TIPO_ARBOL;
	n = 0;
	s = 0;
	clave = NULL;
}


RegistroArbol::RegistroArbol(Clave* c) {
	tipo = c->getTipo();
	clave = c;
	tam = 0;
	n = 0;
	s = 0;
}

RegistroArbol::RegistroArbol(Clave* c, long ne, short se) {
	tipo = c->getTipo();
	clave = c;
	tam = 0;
	n = ne;
	s = se;
}


RegistroArbol::RegistroArbol(Clave* c, std::string dat) {
	tipo = c->getTipo();
	clave = c;
	tam = dat.size() * sizeof(char);
	dato = dat;
	n = 0;
	s = 0;
}

RegistroArbol::RegistroArbol(Clave* c, std::string dat, long ne, short se) {
	tipo = c->getTipo();
	clave = c;
	tam = dat.size() * sizeof(char);
	dato = dat;
	n = ne;
	s = se;
}

RegistroArbol::RegistroArbol(RegistroArbol& reg) {
	tipo = reg.tipo;
	clave = reg.clave;
	tam = reg.tam;
	dato = reg.dato;
	n = reg.n;
	s = reg.s;
}


RegistroArbol::~RegistroArbol() {
	delete clave;
}

std::vector<char>* RegistroArbol::serializar(FrontCoding& encoder) {
	std::vector<char>* s = new std::vector<char>;
	s = Auxiliar::insertarEntero(s, tipo);
	std::vector<char>* s_clave = new std::vector<char>;
	s_clave = clave->serializar(s_clave);
	std::vector<char>* s_clave_coded = new std::vector<char>;
	encoder.encode(s_clave, s_clave_coded);
	s->push_back(s_clave_coded->size());
	s->insert(s->end(), s_clave_coded->begin(), s_clave_coded->end());
	s = Auxiliar::insertarEntero(s, tam);
	s = Auxiliar::insertarString(s, dato);
	delete s_clave;
	return s;
}


void RegistroArbol::hidratar(const std::vector<char>* vec, FrontCoding& decoder,int& pos) {
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

Registro* RegistroArbol::find() {
	++n;
	return (Registro*)this;
}

long RegistroArbol::timesSearched() {
	return n;
}
