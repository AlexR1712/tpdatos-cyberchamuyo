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
	long p = 0;
	nivel = Auxiliar::leerEntero(p, s);
	libre = Auxiliar::leerEntero(p, s);
	int cant_claves = Auxiliar::leerEntero(p, s);
	int cont = 0;
	while(cont < cant_claves) {
		int totalSize = Auxiliar::leerEntero(p, s);
		Clave* c;
		if(tipo == 1)
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
		//ret.append(c->serializarDecimal());
		ret.append("]");
		ret.append(" - ");
	}
	ret.append("Nodos:  ");
	vector<int>::iterator it2;
	for(it2 = nodos.begin(); it2 != nodos.end(); ++it2) {
		ret.append(Auxiliar::int_to_dec(*it2));
		ret.append(" - ");
	}
	cout << ret << std::endl;
}
int NodoInterno::getHijoCorrespondiente(Clave* c) {
	list<Clave*>::iterator it;
	int i = 0;
	for(it = claves.begin(); it != claves.end(); ++it) {
		Clave* cAux = *it;
		//int res = c->compare(cAux);
		//if(res < 0)
		//	return nodos[i];
		//else
		//	++i;
	}
	return nodos[nodos.size()-1];
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
			/*if(c->compare(cAux) < 0) {
				it = claves.insert(it, c);
				itv = nodos.insert(itv, nodo);
				libre -= c->size();
				libre -= INT_SIZE;
				return;
			}*/
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
	for(--it; it != claves.begin() && libre < (N_SIZE)/2 ; --it) {
		Clave* c = *it;
		it = claves.erase(it);
		listaNueva.push_front(c);
		libre += c->size();
	}
	return listaNueva;
}

vector<int> NodoInterno::getHijosSobrantes() {
	list<Clave*> listaNueva;
	list<Clave*>::iterator it = claves.end();
	int elibre = libre;
	vector<int> hijos;
	for(--it; it != claves.begin() && elibre < (N_SIZE)/2 ; --it) {
		Clave* c = *it;
		int nodo = nodos.back();
		nodos.pop_back();
		hijos.push_back(nodo);
		elibre += c->size();
	}
	return hijos;
}
/*
int NodoInterno::insertarRecursivo(Registro* r) {
	Clave* c = r->getClave(getPosicionClave());
	int hc = getHijoCorrespondiente(c);  // cambiar 0 por algo relacionado a k
	string nes = arbol->leerNodo(hc);
	if(nes[0] == 'H') {
		NodoExterno* nE = new NodoExterno(0, arbol);
		string nodo_externo_string = nes.substr(1);
		nE->hidratar(nodo_externo_string);
		int resultado = nE->insertarRegistro(r);
		if(nE->tieneOverflow()) {
			NodoExterno* nE2;
			int hc2;
			if(libre < N_TEST) {
				NodoInterno* nodo_interno_nuevo = new NodoInterno(nivel + 1, arbol);
				int ni_id = arbol->crearNodoInterno(nodo_interno_nuevo, nivel + 1);
				//int i = nE->getPromedio();
				int valor_central = nE->getValorCentral();
				nE2 = new NodoExterno(nivel + 2, arbol);
				hc2 = arbol->crearNodoExterno(nE2, nivel + 2);

				list<Registro*> lr = nE->getRegistrosDerecha();
				C_Entero* clave = new C_Entero(valor_central);

				list<Registro*>::iterator it2 = lr.begin();

				list<Registro*>::iterator it;
				nodo_interno_nuevo->insertarHijoIzquierdo(ni_id);		// guardo el que va a ser el externo

				nodo_interno_nuevo->insertarClave(clave, hc2);
				nE->aumentarNivel();

				for(it = lr.begin(); it != lr.end(); ++it) {
					nE2->insertarRegistro(*it);
				}
				arbol->guardarNodo(nodo_interno_nuevo, hc);		// guardo el nodo interno en donde estaba el ext
				arbol->guardarNodo(nE, ni_id);	//  guardo el nodo externo en el lugar que se le dio al interno
				arbol->guardarNodo(nE2, hc2);
			} else {
				int i = nE->getPromedio();
				nE2 = new NodoExterno(nivel + 1, arbol);
				hc2 = arbol->crearNodoExterno(nE2, nivel + 1);

				list<Registro*> lr = nE->getRegistrosDerecha();

				list<Registro*>::iterator it;

				C_Entero* clave = new C_Entero();
				clave->setNum((reinterpret_cast<C_Entero*>((lr.front())->getClave(getPosicionClave())))->getNum());
				insertarClave(clave, hc2);
				for(it = lr.begin(); it != lr.end(); ++it) {
					nE2->insertarRegistro(*it);
				}
				arbol->guardarNodo(nE, hc);
				arbol->guardarNodo(nE2, hc2);
			}
			return OK;
		} else {
			arbol->guardarNodo(nE, hc);
			return OK;
		}
	} else {
		NodoInterno* nodo_interno = new NodoInterno(nivel + 1, arbol);
		std::string nodo_interno_string = nes.substr(1);
		nodo_interno->hidratar(nodo_interno_string);
		nodo_interno->insertarRecursivo(r);
	}
}

void NodoInterno::insertarHijoIzquierdo(int hI) {
	//nodos[0] = hI;
	nodos.push_back(hI);
}


int NodoInterno::getPosicionClave() {
	int k = arbol->getK();
	return nivel % k;
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

void NodoInterno::buscarEnHijo(Clave* clave, std::vector<std::pair<unsigned int, unsigned int> >& rangos, std::ostream& file_output) {
	int hijo = getHijoCorrespondiente(clave);
	std::string nodo_s = arbol->leerNodo(hijo);
	Nodo* nodo;
	if(nodo_s[0] == 'H')
		nodo = new NodoExterno(nivel + 1, arbol);
	else
		nodo = new NodoInterno(nivel + 1, arbol);
	std::string nodo_string = nodo_s.substr(1);
	nodo->hidratar(nodo_string);
	nodo->buscarPorRango(rangos, file_output);
}
*/
