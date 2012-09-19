/*
 * NodoInterno.cpp
 *
 *  Created on: 07/05/2012
 *      Author: Shazgath
 */

#include "NodoInterno.h"
#include "ArbolBp.h"

NodoInterno::NodoInterno(int lvl, ArbolBp* arb) {
	nivel = lvl;
	libre = N_SIZE - 3 * sizeof(int);
	tipo = 1;
	arbol = arb;
}

NodoInterno::~NodoInterno() {

}


void NodoInterno::hidratar(std::string& s) {
	tipo = s[0];
	long p = 1;
	nivel = Auxiliar::leerEntero(p, s);
	libre = Auxiliar::leerEntero(p, s);
	int cant_claves = Auxiliar::leerEntero(p, s);
	int cont = 0;
	while(cont < cant_claves) {
		int totalSize = Auxiliar::leerEntero(p, s);
		Clave* c;
		if(tipo == 73)
			c = new C_Entero();
		string sAux = s.substr(p, totalSize);
		c->hidratar(sAux);
		p += totalSize;
		claves.push_back(c);
		++cont;
	}
	for(int i = 0; i <= cant_claves; ++i) {
		nodos.push_back(Auxiliar::leerEntero(p, s));
	}

}

std::string NodoInterno::serializar() {
	string ret("I");
	ret.append(Auxiliar::int_to_hex(nivel));
	ret.append(Auxiliar::int_to_hex(libre));
	list<Clave*>::iterator it;
	ret.append(Auxiliar::int_to_hex(claves.size()));
	for(it = claves.begin(); it != claves.end(); ++it) {
		Clave* c = (*it);
		int totalSize = c->size();
		ret.append(Auxiliar::int_to_hex(totalSize));
		ret.append(c->serializar());
	}
	vector<int>::iterator it2;
	for(it2 = nodos.begin(); it2 != nodos.end(); ++it2) {
		ret.append(Auxiliar::int_to_hex(*it2));
	}
	return ret;
}

std::string NodoInterno::serializarDecimal() {
	string ret("I ");
	ret.append("Nivel: ");
	ret.append(Auxiliar::int_to_dec(nivel));
	ret.append("   Libre: ");
	ret.append(Auxiliar::int_to_dec(libre));
	list<Clave*>::iterator it;
	ret.append("  c.claves  ");
	ret.append(Auxiliar::int_to_dec(claves.size()));
	ret.append("  claves  ");
	for(it = claves.begin(); it != claves.end(); ++it) {
		Clave* c = (*it);
		ret.append(" - ");
		ret.append("[");
		ret.append(c->serializarDecimal());
		ret.append("]");
		ret.append(" - ");
	}
	ret.append("Nodos:  ");
	vector<int>::iterator it2;
	for(it2 = nodos.begin(); it2 != nodos.end(); ++it2) {
		ret.append(Auxiliar::int_to_dec(*it2));
		ret.append(" - ");
	}
	return ret;
}

int NodoInterno::getHijoCorrespondiente(Clave* c) {
	list<Clave*>::iterator it;
	int i = 0;
	for(it = claves.begin(); it != claves.end(); ++it) {
		Clave* cAux = *it;
		if(*c < *cAux)
			return nodos[i];
		else
			++i;
	}
	return nodos[nodos.size()-1];
}


void NodoInterno::insertarHijoIzquierdo(long hijoIzq) {
	if(!nodos.size())
		nodos.push_back(hijoIzq);
	this->nodos[0] = hijoIzq;
}

void NodoInterno::insertarClave(Clave* c, int nodo) {
	if(nodos.begin() == nodos.end()) {
		claves.push_back(c);
		nodos.push_back(nodo);
	} else {
		list<Clave*>::iterator it;
		vector<int>::iterator itv = nodos.begin(); ++itv;
		for(it = claves.begin(); it != claves.end(); ++it) {
			Clave* cAux = *it;
			++it;
			--it;
			if(*c < *cAux) {
				it = claves.insert(it, c);
				itv = nodos.insert(itv, nodo);
				libre -= c->size();
				libre -= sizeof(int);
				return;
			}
			++itv;
		}
		claves.push_back(c);
		nodos.push_back(nodo);
		libre -= c->size();
		libre -= sizeof(int);
		return;
	}
}

list<Clave*> NodoInterno::getSobrantes() {
	list<Clave*> listaNueva;
	list<Clave*>::iterator it = claves.end();
	for(--it; it != claves.begin() && libre < (N_SIZE*0.9)/*temporal*/ ; --it) {
		Clave* c = *it;
		it = claves.erase(it);
		listaNueva.push_front(c);
		libre += c->size();
	}
	return listaNueva;
}

int NodoInterno::getHijoMedio() {
	list<Clave*> listaNueva;
	list<Clave*>::iterator it = claves.end();
	for(--it; it != claves.begin() && libre < (N_SIZE)/2 ; --it) {
	}
	Clave* c = *(++it);
	return getHijoCorrespondiente(c);
}

vector<int> NodoInterno::getHijosSobrantes() {
	list<Clave*> listaNueva;
	list<Clave*>::iterator it = claves.end();
	int elibre = libre;
	vector<int> hijos;
	for(--it; it != claves.begin() && elibre < (N_SIZE)*0.90 ; --it) {
		Clave* c = *it;
		int nodo = nodos.back();
		nodos.pop_back();
		hijos.push_back(nodo);
		elibre += c->size();
	}
	return hijos;
}

bool NodoInterno::tieneOverflow() {
	return (this->libre < N_MIN);
}

int NodoInterno::getNivel() {
	return nivel;
}

int NodoInterno::buscar(Clave* c, Registro*& reg) {
	int hijo = getHijoCorrespondiente(c);
	string nodo_string = arbol->leerNodo(hijo);
	if(nodo_string[0] == 'H') {
		NodoExterno* nodo_Externo = new NodoExterno(0, arbol);
		nodo_Externo->hidratar(nodo_string);
		return nodo_Externo->buscar(c, reg);
	} else {
		NodoInterno* nodo_interno = new NodoInterno(nivel - 1, arbol);
		nodo_interno->hidratar(nodo_string);
		return nodo_interno->buscar(c, reg);
	}

}

int NodoInterno::insertarRecursivo(Registro* r) {
	Clave* c = r->getClave();
	int hijo = getHijoCorrespondiente(c);
	string nodo_string = arbol->leerNodo(hijo);
	if(nodo_string[0] == 'H') {
		NodoExterno* nodo_Externo = new NodoExterno(0, arbol);
		nodo_Externo->hidratar(nodo_string);
		nodo_Externo->insertarRegistro(r);
		if(nodo_Externo->tieneOverflow()) {
			NodoExterno* nodo_Externo2;
			int hijo2;
			nodo_Externo2 = new NodoExterno(0, arbol);
			hijo2 = arbol->crearNodoExterno(nodo_Externo2, 0);
			list<Registro*> l_reg = nodo_Externo->getRegistrosDerecha();
			list<Registro*>::iterator it;
			it = l_reg.begin();
			Clave* clave;
			clave = (*(--(l_reg.end())))->getClave();		//  copio clave
			insertarClave(clave, hijo2);
			for(it = l_reg.begin(); it != l_reg.end(); ++it) {
				nodo_Externo2->insertarRegistro(*it);
			}
			*nodo_Externo = *nodo_Externo - *nodo_Externo2;
			nodo_Externo2->setSiguiente(nodo_Externo->getSiguiente());
			nodo_Externo->setSiguiente(hijo2);
			arbol->guardarNodo(nodo_Externo, hijo);
			arbol->guardarNodo(nodo_Externo2, hijo2);
			if(this->tieneOverflow())
				return OVERFLOW;
			return GUARDAR;
		} else {
			arbol->guardarNodo(nodo_Externo, hijo);
			return OK;
		}
	} else {  //  falta guarDAR
		NodoInterno* nodo_interno = new NodoInterno(nivel - 1, arbol);
		nodo_interno->hidratar(nodo_string);
		int res = nodo_interno->insertarRecursivo(r);
		if(nodo_interno->tieneOverflow()) {
			////////////////  inicio copia  /////////////////
			NodoInterno* nuevo_ni_derecho = new NodoInterno(nivel - 1, arbol);

			int nuevo_ni_derecho_id = arbol->crearNodoInterno(nuevo_ni_derecho, 1);

			std::vector<int> vector_hijos_sobrantes = nodo_interno->getHijosSobrantes();
			std::list<Clave*> lista_claves_sobrantes = nodo_interno->getSobrantes();

			Clave* c = lista_claves_sobrantes.front();
			lista_claves_sobrantes.pop_front();
			insertarClave(c, nuevo_ni_derecho_id);

			std::list<Clave*>::iterator it;
			int i = 2;		//  cuidado con el orden
			nuevo_ni_derecho->insertarHijoIzquierdo(vector_hijos_sobrantes[vector_hijos_sobrantes.size() - 1]);
			for(it = lista_claves_sobrantes.begin(); it != lista_claves_sobrantes.end(); ++it) {
				nuevo_ni_derecho->insertarClave(*it, vector_hijos_sobrantes[vector_hijos_sobrantes.size() - i]);
				++i;
			}
			///////////////  fin copia  ////////////////////
			arbol->guardarNodo(nodo_interno, hijo);
			arbol->guardarNodo(nuevo_ni_derecho, nuevo_ni_derecho_id);
			if(tieneOverflow())
				return OVERFLOW;
			return GUARDAR;
		}
		if(res == GUARDAR)
			arbol->guardarNodo(nodo_interno, hijo);
		return OK;
	}
}

void NodoInterno::aumentarNivel() {
	++nivel;
}
/*
void NodoInterno::insertarHijoIzquierdo(int hI) {
	//nodos[0] = hI;
	nodos.push_back(hI);
}

void NodoInterno::buscarPorRango(std::vector<std::pair<unsigned int, unsigned int> >& rangos, std::ostream& file_output) {
	std::list<Clave*>::iterator it;
	it = claves.begin();
	if((*it)->compare(rangos[getPosicionClave()].first) >= 0) {
		std::string nodo_s = arbol->leerNodo(nodos[0]);
		Nodo* nodo;
		if(nodo_s[0] == 'H')
			nodo = new NodoExterno(nivel + 1, arbol);
		else
			nodo = new NodoInterno(nivel + 1, arbol);
		std::string nodo_string = nodo_s.substr(1);
		nodo->hidratar(nodo_string);
		nodo->buscarPorRango(rangos, file_output);
	}
	for(it = claves.begin() ; it != claves.end(); ++it) {
		if((*it)->compare(rangos[getPosicionClave()].first) <= 0) {
			std::list<Clave*>::iterator itAux = it;
			++itAux;
			if(itAux == claves.end() || (*itAux)->compare(rangos[getPosicionClave()].first > 0)) {
				buscarEnHijo(*it, rangos, file_output);
			}
		} else {
			if((*it)->compare(rangos[getPosicionClave()].second) <= 0) {
				buscarEnHijo(*it, rangos, file_output);
			}
		}
	}
}
*/
