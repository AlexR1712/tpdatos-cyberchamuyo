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
	std::list<Registro*>::iterator it;
	for(it = registros.begin(); it != registros.end(); ++it) {
		delete (*it);
	}
}

NodoExterno& NodoExterno::operator=(NodoExterno& nE) {
	this->libre = nE.libre;
	this->nivel = nE.nivel;
	this->tipo = nE.tipo;
	this->arbol = nE.arbol;
	this->siguiente = nE.siguiente;
	this->registros = nE.registros;
	return *this;
}

int NodoExterno::insertarRegistro(Registro* r) {
	if(r->totalSize() > libre)
		return -1;
	list<Registro*>::iterator it;
	for(it = registros.begin();it != registros.end() && (*(*it) < *r)  ; ++it);
	if((it != registros.end()) && (*r == **it))
		throw REGISTRO_YA_EXISTENTE;
	else {
		registros.insert(it, r);
		libre -= r->totalSize();
		return 0;
	}
}

int NodoExterno::insertarRecursivo(Registro* r) {
	int res = insertarRegistro(r);
	if(res < 0)
		throw(1);
	if(tieneOverflow())
		return OVERFLOW;
	return GUARDAR;
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

void NodoExterno::setSiguiente(const int sig) {
	siguiente = sig;
}

int NodoExterno::getSiguiente() {
	return siguiente;
}

Registro* NodoExterno::popMayor() {
	Registro* rAux = registros.back();
	registros.pop_back();
	libre += rAux->totalSize();
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
	std::list<Registro*>::iterator it2;
	std::list<Registro*>* p_list = &(n.registros);
	for(it = p_list->begin(); it != p_list->end(); ++it) {
		Registro* reg_der = *it;
		it2 = registros.begin();
		for(; it2 != registros.end() && (*(*it2) < *reg_der); ++it2) {
		}
		if(it2 == registros.end() && !(*(registros.back()) == *reg_der)) {
			Registro* newReg = new Registro();
			*newReg = *reg_der;
			registros.push_back(newReg);
		} else {
			if(!(*(*it2) < *reg_der)) {
				Registro* newReg = new Registro();
				*newReg = *reg_der;
				registros.insert(it2,newReg);
			}
		}
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
		if(it_member == registros.end())
			--it_member;
		if((*reg_param) == (*reg_member)) {
			it_member = registros.erase(it_member);
			delete reg_member;
		}
	}
	return *this;
}

std::ostream& operator<<(std::ostream& os, NodoExterno& ns) {
	os << "H";
	os << " Nivel: ";
	std::list<Registro*>::iterator it;
	os << Auxiliar::int_to_dec(ns.nivel);
	std::list<Registro*>* p_list = &(ns.registros);
	os << "   Libre: ";
	os << Auxiliar::int_to_dec(ns.libre);
	os << "  siguiente  ";
	os << Auxiliar::int_to_dec(ns.siguiente);
	os << "  c.registros  ";
	os << Auxiliar::int_to_dec(ns.registros.size());
	os << " [";
	for(it = p_list->begin(); it != p_list->end(); ++it) {
		Registro* reg = *it;
		os << " - ";
		os << (*reg);
	}
	return os << "]";
}

int NodoExterno::getNivel() {
	return nivel;
}
/*
std::list<Registro*> NodoExterno::getRegistrosDerecha() {
	std::list<Registro*> return_list;
	std::list<Registro*>::iterator it = registros.begin();
	int cant = registros.size();
	int pos_medio = (cant / 2) + (cant % 2);
	for(int i = 0; i < pos_medio - 1; ++i)
		++it;
	for(;it != registros.end();) {
		return_list.push_back(*it);
		libre += (*it)->totalSize();
		it = registros.erase(it);
	}
	return return_list;
}
*/
std::list<Registro*> NodoExterno::getRegistrosDerecha() {
	list<Registro*> listaNueva;
	list<Registro*>::iterator it = registros.end();
	for(--it; it != registros.begin() && libre < (N_SIZE*0.9)/*temporal*/ ; --it) {
		Registro* reg = *it;
		it = registros.erase(it);
		listaNueva.push_back(reg);
		libre += reg->size();
	}
	return listaNueva;
}

int NodoExterno::buscar(Clave* c, Registro*& reg) {
	std::list<Registro*>::iterator it;
	int nReg = 0;
	for(it = registros.begin(); it != registros.end() && *c > *((*it)->getClave()); ++it);
		++nReg;
	if(it == registros.end()) {
		std::string nodo_string = arbol->leerNodo(siguiente);
		NodoExterno* nE = new NodoExterno(0, arbol);
		nE->hidratar(nodo_string);
		reg = nE->registros.front();
		arbol->setUltimoLeido(nE);
		arbol->setUltimoRegistroLeido(0);
		return 0;
	}
	reg = *it;
	arbol->setUltimoLeido(this); /// aca cambiar
	arbol->setUltimoRegistroLeido(nReg);
	if(*c == *((*it)->getClave()))
		return 1;
	return 0;
}

Registro* NodoExterno::getRegistro(int pos) {
	std::list<Registro*>::iterator it;
	int i = 0;
	for(it = registros.begin(); it != registros.end() && i < pos; ++it)
		++i;
	if(it == registros.end()) {
		NodoExterno* nE = new NodoExterno(0, arbol);
		std::string nodo_string = arbol->leerNodo(siguiente);
		nE->hidratar(nodo_string);
		arbol->setUltimoLeido(nE);
		return nE->registros.front();
	}
	return *it;
}
