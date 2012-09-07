/*
 * NodoExterno.cpp
 *
 *  Created on: 06/05/2012
 *      Author: Shazgath
 */

#include "NodoExterno.h"
#include "ArbolBp.h"

NodoExterno::NodoExterno() {

}

NodoExterno::NodoExterno(int lvl) {
	nivel = lvl;
	siguiente = 0;
	tipo = 0;
	libre = N_SIZE - 4 * sizeof(int);
}

NodoExterno::NodoExterno(int lvl, ArbolBp* arb) : arbol(arb) {
	nivel = lvl;
	siguiente = 0;
	tipo = 0;
	libre = N_SIZE - 4 * sizeof(int);
}

void NodoExterno::aumentarNivel() {
	nivel++;
}

NodoExterno::~NodoExterno() {
}

int NodoExterno::insertarRegistro(Registro* r) {
	if(r->totalSize() > libre)
		return -1;
	list<Registro*>::iterator it;
	for(it = registros.begin();it != registros.end() && (*(*it) < *r)  ; ++it);
	registros.insert(it, r);
	libre -= r->totalSize();
	return 0;
}

int NodoExterno::insertarRecursivo(Registro* r) {
	int res = insertarRegistro(r);
	if(res < 0)
		throw(1);
	if(tieneOverflow())
		return OVERFLOW;
	return OK;
}

bool NodoExterno::eliminarRegistro(Clave* c) {
	list<Registro*>::iterator it;
	for(it = registros.begin(); (*(*it)->getClave() != (*c) && it != registros.end()); ++it) {
	}
	if(it == registros.end())
		return false;
	delete (*it);
	it = registros.erase(it);
	return true;
}

Registro* NodoExterno::popMenor() {
	Registro* r = registros.front();
	registros.pop_front();
	libre += r->totalSize();
	return r;
}

Registro* NodoExterno::sacarRegistro(Clave* c) {
	list<Registro*>::iterator it;
	for(it = registros.begin(); it != registros.end(); ++it) {
		Registro* r = *it;
		if((*r) == c) {
			it = registros.erase(it);
			libre += r->totalSize();
			return r;
		}
	}
	return NULL;
}

Registro* NodoExterno::sacarRegistro() {
	Registro* rAux = registros.back();
	registros.pop_back();
	return rAux;
}

int NodoExterno::cantRegistros() {
	return registros.size();
}

string NodoExterno::serializar() {
	string ret("H");
	ret.append(Auxiliar::int_to_hex(nivel));
	ret.append(Auxiliar::int_to_hex(libre));
	ret.append(Auxiliar::int_to_hex(siguiente));
	list<Registro*>::iterator it;
	ret.append(Auxiliar::int_to_hex(registros.size()));
	for(it = registros.begin(); it != registros.end(); ++it) {
		Registro* r = (*it);
		int totalSize = r->totalSize();
		ret.append(Auxiliar::int_to_hex(totalSize));
		ret.append(r->serializar());
	}
	return ret;
}


void NodoExterno::hidratar(string& s) {
	long p = 0;
	tipo = s[0];
	++p;
	nivel = Auxiliar::leerEntero(p, s);
	libre = Auxiliar::leerEntero(p, s);
	siguiente = Auxiliar::leerEntero(p, s);
	int cant = Auxiliar::leerEntero(p, s);
	int cont = 0;
	while(cont < cant) {
		long totalSize = Auxiliar::leerEntero(p, s);
		Registro* r = new Registro();
		string rs = s.substr(p, totalSize);
		r->hidratar(rs);
		p += totalSize;
		registros.push_back(r);
		cont++;
	}
}

bool NodoExterno::tieneOverflow() {
	if(libre < N_MIN)
		return true;
	return false;
}

NodoExterno& NodoExterno::operator+(NodoExterno& n) {
	std::list<Registro*>::iterator it;
	std::list<Registro*>* p_list = &(n.registros);
	for(it = p_list->begin(); it != p_list->end(); ++it) {
		Registro* reg = *it;
		Registro* newReg = new Registro();
		*newReg = *reg;
		registros.push_back(newReg);
	}
	return *this;
}

NodoExterno& NodoExterno::operator-(NodoExterno& n) {
	std::list<Registro*>::iterator it_member = registros.begin();
	std::list<Registro*>::iterator it_param;
	for(it_param = n.registros.begin(); it_param != n.registros.end(); ++it_param) {
		Registro* reg_param = *it_param;
		Registro* reg_member = *it_member;
		while((it_member != registros.end()) && (*reg_param) > (*reg_member)) {
			++it_member;
			if(it_member != registros.end())
			reg_member = *it_member;
		}
		if((*reg_param) == (*reg_member)) {
			it_member = registros.erase(it_member);
			delete reg_member;
		}
	}
	return *this;
}

std::ostream& operator<<(std::ostream& os, NodoExterno& ns) {
	os << "Nodo Externo " << std::endl;
	std::list<Registro*>::iterator it;
	std::list<Registro*>* p_list = &(ns.registros);
	for(it = p_list->begin(); it != p_list->end(); ++it) {
		Registro* reg = *it;
		os << (*reg);
	}
	return os;
}


std::list<Registro*> NodoExterno::getRegistrosDerecha() {
	std::list<Registro*> return_list;
	std::list<Registro*>::iterator it = registros.begin();
	int cant = registros.size();
	int pos_medio = (cant / 2) + (cant % 2);
	for(int i = 0; i < pos_medio - 1; ++i)
		++it;
	for(;it != registros.end();) {
		return_list.push_back(*it);
		it = registros.erase(it);
	}
	return return_list;
}

