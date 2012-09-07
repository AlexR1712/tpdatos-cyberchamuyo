/*
 * Registro.cpp
 *
 *  Created on: 06/05/2012
 *      Author: Shazgath
 */

#include "Registro.h"
#include "common.h"

Registro::Registro() {
	tipo = 0;
}

Registro::Registro(Clave* c) {
	tipo = 0;
	clave = c;
}

Registro::Registro(Clave* c, std::string dat) {
	tipo = 0;
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
	// TODO Auto-generated destructor stub
}

string Registro::serializar() {
	string s;
	s.append(Auxiliar::int_to_hex(tipo));
	s.append(Auxiliar::int_to_hex(clave->size()));
	string s2(clave->serializar());
	s.append(s2);
	s.append(Auxiliar::int_to_hex(tam));
	s.append(dato);
	return s;
}

void Registro::hidratar(const string &s) {
	long p = 0;
	tipo = Auxiliar::leerEntero(p, s);
	switch(tipo){
	case 0:
		clave = new C_Entero();
	}
	long size = Auxiliar::leerEntero(p, s);
	std::string clave_string = s.substr(p, size);
	p+= size;
	clave->hidratar(clave_string);
	tam = Auxiliar::leerEntero(p, s);
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

Clave* Registro::getClave(){
	return clave;
}

std::ostream& operator<<(std::ostream& os, const Registro& r) {
	os << "Registro = "<< (r.clave)->print() << "  |  Datos = " << r.dato << endl;
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
