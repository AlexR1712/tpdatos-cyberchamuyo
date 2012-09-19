/*
 * ArbolBp.cpp
 *
 *  Created on: 19/05/2012
 *      Author: sebastian
 */

#include "NodoExterno.h"
#include "ArbolBp.h"
#include "common.h"

ArbolBp::ArbolBp(char* n_arch, int block_size) : arch_arbol(n_arch, N_SIZE), b_size(block_size) {
	if(arch_arbol.getCantidadBloques() > 0) {
		string raiz_s = leerNodo(0);
		if(raiz_s[0] == 'H') {
			raiz = new NodoExterno(0, this);
		} else {
			raiz = new NodoInterno(0, this);
		}
	} else {
		NodoExterno* n1 = new NodoExterno(0, this);
		raiz = n1;
		int n_id = crearNodoExterno(n1, 0);
		guardarNodo(n1, n_id);
	}
	max = 0;
	ultimoNodoLeido = NULL;
	ultimoRegistroLeido = 0;
}

ArbolBp::~ArbolBp() {
	delete raiz;
}

int ArbolBp::buscar(Clave* c, Registro*& reg) {
	return raiz->buscar(c, reg);
}

void ArbolBp::setUltimoLeido(NodoExterno* nE) {
	this->ultimoNodoLeido = nE;
}

int ArbolBp::insertarRegistro(Registro* r) {
	int res = raiz->insertarRecursivo(r);
	if(max == 0) {
		if(res == OVERFLOW) {
			NodoExterno* nh2 = new NodoExterno(0, this);
			int ne2_id = crearNodoExterno(nh2, 1);
			list<Registro*> listaReg = ((NodoExterno*)raiz)->getRegistrosDerecha();

			NodoInterno* nueva_raiz = new NodoInterno(1, this);
			int ni1_id = crearNodoInterno(nueva_raiz, 1);

			Clave* c = listaReg.back()->getClaveCopia();

			nueva_raiz->insertarHijoIzquierdo(ne2_id);
			nueva_raiz->insertarClave(c, ni1_id);
			//nueva_raiz->insertarClave(c, ni1_id);
			//(reinterpret_cast<NodoExterno*>(raiz))->aumentarNivel();

			list<Registro*>::iterator it;
			for(it = listaReg.begin(); it != listaReg.end(); ++it) {
				nh2->insertarRegistro(*it);
			}

			nh2->setSiguiente(0);
			dynamic_cast<NodoExterno*>(raiz)->setSiguiente(ni1_id);

			guardarNodo(nh2, ni1_id);
			guardarNodo(nueva_raiz, 0);
			guardarNodo(raiz, ne2_id);
			raiz = nueva_raiz;
			++max;
			return 0;
		} else {
			if(res == GUARDAR)
				guardarNodo(raiz, 0);
			return 0;
		}
	} else {
		if(res == OVERFLOW) {
			NodoInterno* nuevo_ni_derecho = new NodoInterno(dynamic_cast<NodoInterno*>(raiz)->getNivel(), this);
			NodoInterno* nueva_raiz = new NodoInterno(dynamic_cast<NodoInterno*>(raiz)->getNivel() + 1, this);

			int nuevo_ni_izquierdo_id = crearNodoInterno(nueva_raiz, 0);
			int nuevo_ni_derecho_id = crearNodoInterno(nuevo_ni_derecho, 1);

			nueva_raiz->insertarHijoIzquierdo(nuevo_ni_izquierdo_id);

			std::vector<int> vector_hijos_sobrantes = dynamic_cast<NodoInterno*>(raiz)->getHijosSobrantes();
			std::list<Clave*> lista_claves_sobrantes = dynamic_cast<NodoInterno*>(raiz)->getSobrantes();

			Clave* c = lista_claves_sobrantes.front();
			lista_claves_sobrantes.pop_front();
			nueva_raiz->insertarClave(c, nuevo_ni_derecho_id);

			std::list<Clave*>::iterator it;
			int i = 2;		//  cuidado con el orden
			nuevo_ni_derecho->insertarHijoIzquierdo(vector_hijos_sobrantes[vector_hijos_sobrantes.size() - 1]);
			for(it = lista_claves_sobrantes.begin(); it != lista_claves_sobrantes.end(); ++it) {
				nuevo_ni_derecho->insertarClave(*it, vector_hijos_sobrantes[vector_hijos_sobrantes.size() - i]);
				++i;
			}
			guardarNodo(nuevo_ni_derecho, nuevo_ni_derecho_id);
			guardarNodo(nueva_raiz, 0);
			guardarNodo(raiz, nuevo_ni_izquierdo_id);
			raiz = nueva_raiz;
		} else {
			if(res == GUARDAR)
				guardarNodo(raiz, 0);
		}
	}
	++max;
}

void ArbolBp::imprimirNodos() {
	int cant = arch_arbol.getCantidadBloques();
	for(int i = 0; i < cant; ++i) {
		std::string nodo = leerNodo(i);
		char t = nodo[0];
		if(t == 'I'){
			NodoInterno* nI;
			nI = new NodoInterno(0, this);
			nI->hidratar(nodo);
			long p = 1;
			long nivel = Auxiliar::leerEntero(p, nodo);
			for(int i = 0; i < nivel; ++i) {
				cout << "	";
			}
			std::cout << nI->serializarDecimal() << std::endl;
		} else {
			NodoExterno* nE;
			nE = new NodoExterno(0, this);
			nE->hidratar(nodo);
			long p = 1;
			int nivel = Auxiliar::leerEntero(p, nodo);
			for(int i = nivel; i > 0; --i) {
				cout << "	";
			}
			std::cout << *nE << std::endl;
		}
	}
}

void ArbolBp::guardarNodo(Nodo* n, unsigned int id) {
	std::string ns = n->serializar();
	RegistroVariable reg(&ns, ns.size());
	Bloque b(N_SIZE);
	b.addRegistro(&reg);
	arch_arbol.Escribir(&b, id);
}


int ArbolBp::crearNodoExterno(NodoExterno* nE, int nivel) {
	int libre = arch_arbol.ObtenerBloqueLibre();
		if(libre == -1) {
			Bloque b(N_SIZE);
			arch_arbol.Escribir(&b, arch_arbol.getCantidadBloques());
			return arch_arbol.getCantidadBloques() - 1;
		} else {
			return libre;
		}
}

int ArbolBp::crearNodoInterno(NodoInterno* nI, int nivel) {
	int libre = arch_arbol.ObtenerBloqueLibre();
	if(libre == -1) {
		Bloque b(N_SIZE);
		arch_arbol.Escribir(&b, arch_arbol.getCantidadBloques());
		return arch_arbol.getCantidadBloques() - 1;
	} else {
		return libre;
	}
}


std::string ArbolBp::leerNodo(int id) {
	Bloque b(N_SIZE);
	arch_arbol.Leer(id, &b);
	RegistroVariable* reg = b.getRegistro(0);
	std::string* data = reg->getDato();
	return *data;
}

bool ArbolBp::isEmpty() {
	return (this->raiz == NULL);
}

Registro* ArbolBp::siguiente() {
	Registro* res = NULL;
	res = ultimoNodoLeido->getRegistro(++ultimoRegistroLeido);
	return res;
}

void ArbolBp::aumentarUltimoRegistroLeido() {
	++ultimoRegistroLeido;
}

void ArbolBp::setUltimoRegistroLeido(int nReg) {
	ultimoRegistroLeido = nReg;
}

