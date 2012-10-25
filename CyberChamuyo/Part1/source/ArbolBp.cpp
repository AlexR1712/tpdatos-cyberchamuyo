/*
 * ArbolBp.cpp
 *
 *  Created on: 19/05/2012
 *      Author: sebastian
 */

#include "NodoExterno.h"
#include "ArbolBp.h"
#include "common.h"
#include "RegistroArbol.h"

ArbolBp::ArbolBp(const char* n_arch, int block_size) : arch_arbol(n_arch, N_SIZE), b_size(block_size) {
	if(arch_arbol.getCantidadBloques() > 0) {
		std::vector<char>* raiz_data = leerNodo2(0);
		if((*raiz_data)[0] == 'H') {
			raiz = new NodoExterno(0, this);
		} else {
			raiz = new NodoInterno(0, this);
		}
		int pos = 0;
		raiz->hidratar(raiz_data, pos);
		max = raiz->getNivel();
	} else {
		max = 0;
		NodoExterno* n1 = new NodoExterno(0, this);
		raiz = n1;
		int n_id = crearNodo();
		guardarNodo(n1, n_id);
	}
	ultimoNodoLeido = NULL;
	ultimoRegistroLeido = 0;
}

ArbolBp::~ArbolBp() {
	delete raiz;
	delete ultimoNodoLeido;
}

int ArbolBp::buscar(Clave* c, Registro*& reg) {
	NodoExterno* anteriorUltimoLeido = ultimoNodoLeido;
	int res = raiz->buscar(c, reg);
	if((ultimoNodoLeido != anteriorUltimoLeido) && (anteriorUltimoLeido != NULL))
		delete anteriorUltimoLeido;
	return res;
}

void ArbolBp::setUltimoLeido(NodoExterno* nE) {
	this->ultimoNodoLeido = nE;
}

int ArbolBp::insertarRegistro(Registro* r) {
	int res = 0;
	try {
		res = raiz->insertarRecursivo(r);
	} catch(const int excepcion) {
		std::cout << "Error registro ya existente" << std::endl;
		return -1;
	}
	if(res == -1) {
		std::cout << "Error registro ya existente" << std::endl;
		return -1;
	}
	if(max == 0) {
		if(res == OVERFLOW) {
			NodoExterno* nh2 = new NodoExterno(0, this);
			int ne2_id = crearNodo();
			list<Registro*> listaReg = ((NodoExterno*)raiz)->getRegistrosDerecha();

			NodoInterno* nueva_raiz = new NodoInterno(1, this);
			int ni1_id = crearNodo();

			Clave* c = listaReg.back()->getClaveCopia();

			nueva_raiz->insertarHijoIzquierdo(ne2_id);
			nueva_raiz->insertarClave(c, ni1_id);

			list<Registro*>::iterator it;
			for(it = listaReg.begin(); it != listaReg.end(); ++it) {
				nh2->insertarRegistro(*it);
				delete *it;
			}


			nh2->setSiguiente(0);
			dynamic_cast<NodoExterno*>(raiz)->setSiguiente(ni1_id);

			++max;
			guardarNodo(nh2, ni1_id);
			guardarNodo(nueva_raiz, 0);
			guardarNodo(raiz, ne2_id);
			delete raiz;
			raiz = nueva_raiz;
			delete nh2;
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

			int nuevo_ni_izquierdo_id = crearNodo();
			int nuevo_ni_derecho_id = crearNodo();

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
			++max;
			guardarNodo(nuevo_ni_derecho, nuevo_ni_derecho_id);
			guardarNodo(nueva_raiz, 0);
			guardarNodo(raiz, nuevo_ni_izquierdo_id);
			delete raiz;
			raiz = nueva_raiz;
			delete nuevo_ni_derecho;
		} else {
			if(res == GUARDAR)
				guardarNodo(raiz, 0);
		}
	}
	return OK;
}

void ArbolBp::imprimirNodos() {
	int cant = arch_arbol.getCantidadBloques();
	int pos;
	std::fstream file;
	file.open("Arboltest.bin", std::fstream::in|std::fstream::out|std::fstream::binary);
	for(int i = 0; i < cant; ++i) {
		std::vector<char>* nodo = leerNodo2(i);
		char t = (*nodo)[0];
		if(t == 'I'){
			pos = 0;
			NodoInterno* nI;
			nI = new NodoInterno(0, this);
			nI->hidratar(nodo, pos);
			long nivel = nI->getNivel();
			for(int i = 0; i < nivel; ++i) {
				cout << "	";
			}
			std::cout << nI->serializarDecimal() << std::endl;
			delete nI;
		} else {
			pos = 0;
			NodoExterno* nE;
			nE = new NodoExterno(0, this);
			nE->hidratar(nodo, pos);
			int nivel = nE->getNivel();
			for(int i = nivel; i > 0; --i) {
				cout << "	";
			}
			std::cout << *nE << std::endl;
			delete nE;
		}
		delete nodo;
	}
}

void ArbolBp::guardarNodo(Nodo* n, unsigned int id) {
	std::vector<char>* ns = n->serializar();
	Bloque b(N_SIZE, ns, ns->size());
	try {
		arch_arbol.Escribir(&b, id);
	} catch(const ExcepcionBloqueInexistente& exc) {
		throw(Exc_GuardarArchivo());
	}
	delete ns;
}
/*
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
*/
int ArbolBp::crearNodo() {
	int libre = arch_arbol.ObtenerBloqueLibre();
	if(libre == -1) {
		Bloque b(N_SIZE);
		arch_arbol.Escribir(&b, arch_arbol.getCantidadBloques());
		return arch_arbol.getCantidadBloques() - 1;
	} else {
		return libre;
	}
}

void ArbolBp::clear() {
	delete raiz;
	delete ultimoNodoLeido;
	ultimoRegistroLeido = 0;
	arch_arbol.Clear();
}


std::string ArbolBp::leerNodo(int id) {
	Bloque b(N_SIZE);
	arch_arbol.Leer(id, &b);
	RegistroVariable* reg = b.getRegistro(0);
	std::string* data = reg->getDato();
	return *data;
}

std::vector<char>* ArbolBp::leerNodo2(int id) {
	Bloque b(N_SIZE);
	arch_arbol.Leer(id, &b);
	RegistroVariable* reg = b.getRegistro(0);
	std::string* data_s = reg->getDato();
	std::string::iterator it;
	std::vector<char>* data = new std::vector<char>;
	for(it = data_s->begin(); it != data_s->end(); ++it) {
		data->push_back(*it);
	}
	return data;
}

bool ArbolBp::isEmpty() {
	return (this->raiz == NULL);
}

Registro* ArbolBp::siguiente() {
	if(ultimoNodoLeido == NULL) {
		int pos = 0;
		int primero = encontrarPrimero();
		NodoExterno* nE = new NodoExterno();
		std::vector<char>* nodo_data = leerNodo2(primero);
		nE->hidratar(nodo_data, pos);
		ultimoNodoLeido = nE;
	}
	NodoExterno* ultimoNodoAnterior = ultimoNodoLeido;
	Registro* ret = new RegistroArbol();
	ret = ultimoNodoLeido->getRegistro(++ultimoRegistroLeido, ret);
	if(ultimoNodoLeido != ultimoNodoAnterior)
		delete ultimoNodoAnterior;
	return ret;
}

void ArbolBp::aumentarUltimoRegistroLeido() {
	++ultimoRegistroLeido;
}

void ArbolBp::setUltimoRegistroLeido(int nReg) {
	ultimoRegistroLeido = nReg;
}

int ArbolBp::encontrarPrimero() {
	if(max == 0) {
		return 0;
	} else {
		return reinterpret_cast<NodoInterno*>(raiz)->encontrarPrimero();
	}
}

void ArbolBp::exportar(BinaryOutputSequentialFile<BinaryDictionaryRecord<true> >& os) {
	BinaryDictionaryRecord<true> record;
	int primero = encontrarPrimero();
	NodoExterno* nE = new NodoExterno(0, this);
	int pos = 0;
	std::vector<char>* nodo_data = leerNodo2(primero);
	nE->hidratar(nodo_data, pos);
	ultimoNodoLeido = nE;
	Registro* reg = new RegistroArbol();
	reg = nE->getRegistro(0, reg);
	while(reg != NULL) {
		record.setId(dynamic_cast<RegistroArbol*>(reg)->timesSearched());
		record.setWord(reinterpret_cast<CAlfa*>(reg->getClave())->getWord());
		os.putRecord(record);
		reg = siguiente();
	}
	delete reg;
	if(ultimoNodoLeido == nE)
		ultimoNodoLeido = NULL;
	delete nodo_data;
	//if(ultimoNodoLeido != nE)
	//	delete nE;
}

bool ArbolBp::hasNext() {
	if((ultimoNodoLeido->cantRegistros() == (ultimoRegistroLeido - 1)) && !(ultimoNodoLeido->getSiguiente()))
		return false;
	return true;
}
