/*
 * Registro.cpp
 *
 *  Created on: 06/05/2012
 *      Author: Shazgath
 */

#include "Registro.h"
#include "common.h"
#include <cstring>
#include "CAlfa.h"
#include "ArbolBp.h"

Registro::Registro() {
	tipo = TIPO_ARBOL;
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

Registro::Registro(Registro& reg) {
	tipo = reg.tipo;
	clave = reg.clave;
	tam = reg.tam;
	dato = reg.dato;
}

Registro::~Registro() {
	delete clave;
}
/*
string Registro::serializar() {
	string s;
	s.append(Auxiliar::int_to_hex(tipo));
	s.append(Auxiliar::int_to_hex(clave->size()));
	std::vector<char> clave_s;
	clave_s = clave->serializar();
	for(int i = 0; i < clave_s.size(); ++i) {
		s.push_back(clave_s[i]);
	}
	s.append(Auxiliar::int_to_hex(tam));
	s.append(dato);
	return s;
}
*/

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
	switch(tipo) {
	case 0:
		clave = new C_Entero();
	case 1:
		clave = new CAlfa();
	}
	*clave = *(r.clave);
	dato = r.dato;
}

std::ostream& operator<<(std::ostream& os, const Registro& r) {
	os << "Registro = "<< (r.clave)->print() << "  |  Datos = " << r.dato;
	return os;
}

/*

std::string Registro::serializarDecimal() {
	string s;
	vector<Clave*>::iterator it;
	s.append("  claves  ");
	for(it = claves.begin(); it != claves.end(); ++it) {
		Clave* clave = *it;
		s.append("[");
		s.append(clave->serializarDecimal());
		s.append("] ");
	}
	return s;
}

*/
