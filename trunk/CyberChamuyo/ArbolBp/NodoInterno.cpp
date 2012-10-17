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
	libre = N_SIZE - I_CONTROL_SIZE;
	tipo = TIPO_ARBOL;
	arbol = arb;
}

NodoInterno::~NodoInterno() {
	std::list<Clave*>::iterator it;
	for(it = claves.begin(); it != claves.end(); ++it) {
		delete(*it);
	}
}


void NodoInterno::hidratar(const std::vector<char>* data, int& pos) {
	tipo = TIPO_ARBOL;
	++pos;
	nivel = Auxiliar::leerEntero(data, pos);
	libre = Auxiliar::leerEntero(data, pos);
	int cant_claves = Auxiliar::leerEntero(data, pos);
	int cont = 0;
	FrontCoding decoder;
	while(cont < cant_claves) {
		//int totalSize = Auxiliar::leerEntero(data, pos);
		Clave* c;
		switch(tipo) {
		case 0:
			std::cout << "entre a 0 en nodo interno hidratar" << std::endl;
			c = new C_Entero();
		case 1:
			c = new CAlfa();
		}
		char c_size = (*data)[pos++];
		std::string clave_raw, clave_deco;
		for(int i = pos; i < pos + c_size; ++i)
			clave_raw.push_back((*data)[i]);
		decoder.decode(clave_raw, clave_deco);
		std::vector<char> vecAux;
		vecAux.insert(vecAux.begin(), clave_deco.begin(), clave_deco.end());
		c->setSize(vecAux.size());
		c->hidratar(&vecAux, pos);
		pos += c_size;
		claves.push_back(c);
		++cont;
	}
	for(int i = 0; i <= cant_claves; ++i) {
		nodos.push_back(Auxiliar::leerEntero(data, pos));
	}
}

void NodoInterno::hidratar(std::string& s) {
	tipo = TIPO_ARBOL;
	long p = 1;
	//nivel = Auxiliar::leerEntero(p, s);
	//libre = Auxiliar::leerEntero(p, s);
	//int cant_claves = Auxiliar::leerEntero(p, s);
	int cont, cant_claves, totalSize = 0;
	while(cont < cant_claves) {
		//int totalSize = Auxiliar::leerEntero(p, s);
		Clave* c;
		if(tipo == 0)
			c = new C_Entero();
		else
			c = new CAlfa();
		string sAux = s.substr(p, totalSize);
		//c->hidratar(sAux);
		p += totalSize;
		claves.push_back(c);
		++cont;
	}
	for(int i = 0; i <= cant_claves; ++i) {
		//nodos.push_back(Auxiliar::leerEntero(p, s));
	}

}
/*
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
		//ret.append(c->serializar());
	}
	vector<int>::iterator it2;
	for(it2 = nodos.begin(); it2 != nodos.end(); ++it2) {
		ret.append(Auxiliar::int_to_hex(*it2));
	}
	return ret;
}
*/

std::vector<char>* NodoInterno::serializar() {
	std::vector<char>* ret = new std::vector<char>;
	ret->push_back('I');
	ret = Auxiliar::insertarEntero(ret, nivel);
	ret = Auxiliar::insertarEntero(ret, libre);
	ret = Auxiliar::insertarEntero(ret, claves.size());
	std::list<Clave*>::iterator it;
	FrontCoding encoder;
	for(it = claves.begin(); it != claves.end(); ++it) {
		Clave* c = *it;
		//int totalSize = c->size();
		//ret = Auxiliar::insertarEntero(ret, totalSize);
		std::vector<char>* data_clave = new std::vector<char>;
		data_clave = c->serializar(data_clave);
		std::vector<char>* data_clave_coded = new std::vector<char>;
		encoder.encode(data_clave, data_clave_coded);
		ret->push_back(data_clave_coded->size());
		ret->insert(ret->end(), data_clave_coded->begin(), data_clave_coded->end());
		delete data_clave;
	}
	vector<int>::iterator it_hijos;
	for(it_hijos = nodos.begin(); it_hijos != nodos.end(); ++it_hijos) {
		ret = Auxiliar::insertarEntero(ret, *it_hijos);
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
	libre -= sizeof(int);
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
				libre -= c->byte_size();
				libre -= sizeof(int);
				return;
			}
			++itv;
		}
		claves.push_back(c);
		nodos.push_back(nodo);
		libre -= c->byte_size();
		libre -= 2 * sizeof(int);  //  uno por tamaño clave y otro por el hijo
		return;
	}
}

list<Clave*> NodoInterno::getSobrantes() {
	list<Clave*> listaNueva;
	list<Clave*>::iterator it = claves.end();
	for(--it; it != claves.begin() && libre < (N_SIZE * 0.5) ; --it) {
		Clave* c = *it;
		it = claves.erase(it);
		/*Clave* cNueva;
		int tipo = c->getTipo();
		switch(tipo) {
		case 0:
			cNueva = new C_Entero();
		case 1:
			cNueva = new CAlfa();
		}
		*cNueva = *c;
		*/listaNueva.push_front(c);
		libre += c->byte_size();
		//delete c;
	}
	return listaNueva;
}

int NodoInterno::getHijoMedio() {
	list<Clave*> listaNueva;
	list<Clave*>::iterator it = claves.end();
	for(--it; it != claves.begin() && libre < (N_SIZE)*0.5 ; --it) {
	}
	Clave* c = *(++it);
	return getHijoCorrespondiente(c);
}

vector<int> NodoInterno::getHijosSobrantes() {
	list<Clave*> listaNueva;
	list<Clave*>::iterator it = claves.end();
	int elibre = libre;
	vector<int> hijos;
	for(--it; it != claves.begin() && elibre < (N_SIZE)*0.50 ; --it) {
		Clave* c = *it;
		int nodo = nodos.back();
		nodos.pop_back();
		hijos.push_back(nodo);
		elibre += c->byte_size();
	}
	return hijos;
}

bool NodoInterno::tieneOverflow() {
	return ((libre) < N_MIN);
}

int NodoInterno::getNivel() {
	return nivel;
}

int NodoInterno::buscar(Clave* c, Registro*& reg) {
	int hijo = getHijoCorrespondiente(c);
	//string nodo_string = arbol->leerNodo(hijo);
	std::vector<char>* nodo_data = arbol->leerNodo2(hijo);
	int pos = 0;
	if((*nodo_data)[0] == 'H') {
		NodoExterno* nodo_Externo = new NodoExterno(0, arbol);
		nodo_Externo->hidratar(nodo_data, pos);
		return nodo_Externo->buscar(c, reg);
	} else {
		NodoInterno* nodo_interno = new NodoInterno(nivel - 1, arbol);
		nodo_interno->hidratar(nodo_data, pos);
		return nodo_interno->buscar(c, reg);
	}
}

int NodoInterno::insertarRecursivo(Registro* r) {
	Clave* c = r->getClave();
	int hijo = getHijoCorrespondiente(c);
	int pos = 0;
	//string nodo_string = arbol->leerNodo(hijo);
	std::vector<char>* nodo_data = arbol->leerNodo2(hijo);
	if((*nodo_data)[0] == 'H') {
		NodoExterno* nodo_Externo = new NodoExterno(0, arbol);
		nodo_Externo->hidratar(nodo_data, pos);
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
			clave = (*(--(l_reg.end())))->getClaveCopia();		//  copio clave
			insertarClave(clave, hijo2);
			for(it = l_reg.begin(); it != l_reg.end(); ++it) {
				nodo_Externo2->insertarRegistro(*it);
			}
			*nodo_Externo = *nodo_Externo - *nodo_Externo2;
			nodo_Externo2->setSiguiente(nodo_Externo->getSiguiente());
			nodo_Externo->setSiguiente(hijo2);
			arbol->guardarNodo(nodo_Externo, hijo);
			arbol->guardarNodo(nodo_Externo2, hijo2);
			delete nodo_Externo;
			delete nodo_Externo2;
			delete nodo_data;
			if(this->tieneOverflow())
				return OVERFLOW;
			return GUARDAR;
		} else {
			arbol->guardarNodo(nodo_Externo, hijo);
			delete nodo_data;
			delete nodo_Externo;
			return OK;
		}
	} else {  //  falta guarDAR
		NodoInterno* nodo_interno = new NodoInterno(nivel - 1, arbol);
		nodo_interno->hidratar(nodo_data, pos);
		int res = nodo_interno->insertarRecursivo(r);
		if(nodo_interno->tieneOverflow()) {
			////////////////  inicio copia  /////////////////
			NodoInterno* nuevo_ni_derecho = new NodoInterno(nivel - 1, arbol);

			int nuevo_ni_derecho_id = arbol->crearNodoInterno(nuevo_ni_derecho, 1);

			std::vector<int> vector_hijos_sobrantes = nodo_interno->getHijosSobrantes();
			std::list<Clave*> lista_claves_sobrantes = nodo_interno->getSobrantes();

			Clave* c = lista_claves_sobrantes.front();
			////////////////////
			//Clave* cNueva = new CAlfa();
			//*cNueva = *c;
			////////////////////
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
			delete nodo_interno;
			delete(nuevo_ni_derecho);
			delete nodo_data;
			//delete c;
			if(tieneOverflow())
				return OVERFLOW;
			return GUARDAR;
		}
		if(res == GUARDAR)
			arbol->guardarNodo(nodo_interno, hijo);
		delete nodo_data;
		delete nodo_interno;
		return OK;
	}
}

void NodoInterno::aumentarNivel() {
	++nivel;
}
