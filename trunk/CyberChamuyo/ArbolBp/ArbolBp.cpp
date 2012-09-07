/*
 * ArbolBp.cpp
 *
 *  Created on: 19/05/2012
 *      Author: sebastian
 */

#include "NodoExterno.h"
#include "ArbolBp.h"
#include "common.h"

ArbolBp::ArbolBp(int kd, char* n_arch, int block_size) : arch_arbol(n_arch, N_SIZE), b_size(block_size) {
	k = kd;
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
}

ArbolBp::~ArbolBp() {
	delete raiz;
}

int ArbolBp::insertarRegistro(Registro* r) {
	int res = raiz->insertarRecursivo(r);
	if(res == OVERFLOW) {
		NodoExterno* nh2 = new NodoExterno(1, this);
		int ne2_id = crearNodoExterno(nh2, 1);
		//int medio = reinterpret_cast<NodoExterno*>(raiz)->getValorCentral();
		//list<Registro*> listaReg = ((NodoExterno*)raiz)->getRegistrosDerecha();

		NodoInterno* nueva_raiz = new NodoInterno(0, this);
		int ni1_id = crearNodoInterno(nueva_raiz, 1);

		//Clave* c = new C_Entero(medio);

		//nueva_raiz->insertarHijoIzquierdo(ne2_id);
		//nueva_raiz->insertarClave(c, ni1_id);
		(reinterpret_cast<NodoExterno*>(raiz))->aumentarNivel();

		list<Registro*>::iterator it;
		//for(it = listaReg.begin(); it != listaReg.end(); ++it) {
		//	nh2->insertarRegistro(*it);
		//}
		guardarNodo(nh2, ni1_id);
		guardarNodo(nueva_raiz, 0);
		guardarNodo(raiz, ne2_id);
		raiz = nueva_raiz;
	} else {
		if(res == OK)
			guardarNodo(raiz, 0);
	}
}

void ArbolBp::imprimirNodos() {
	int cant = arch_arbol.getCantidadBloques();
	for(int i = 0; i < cant; ++i) {
		std::string nodo = leerNodo(i);
		Nodo* n;
		char t = nodo[0];
		if(t == 'I')
			n = new NodoInterno(0, this);
		else
			n = new NodoExterno(0, this);
		std::string s = nodo.substr(1);
		n->hidratar(s);
		long p = 1;
		long nivel = Auxiliar::leerEntero(p, nodo);
		for(int i = 0; i < nivel; ++i) {
			cout << "	";
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
