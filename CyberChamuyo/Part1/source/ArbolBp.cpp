/*
 * ArbolBp.cpp
 *
 *  Created on: 19/05/2012
 *      Author: sebastian
 */

#include "../include/NodoExterno.h"
#include "../include/ArbolBp.h"
#include "../include/common.h"
#include "../include/RegistroArbol.h"

ArbolBp::ArbolBp(const char* n_arch, int block_size) : arch_arbol(n_arch, block_size), b_size(block_size) {
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
		delete raiz_data;
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
	//delete ultimoNodoLeido;
}

void ArbolBp::modify(Registro* reg) {
	int res = raiz->modify(reg);
	if((this->max == 0) && res)
		guardarNodo(raiz, 0);
}

int ArbolBp::buscar(Clave* c, Registro*& reg) {
	//NodoExterno* anteriorUltimoLeido = ultimoNodoLeido;
	int res = raiz->buscar(c, reg);
	if((this->max == 0) && res)
		guardarNodo(raiz, 0);
	//if((ultimoNodoLeido != anteriorUltimoLeido) && (anteriorUltimoLeido != NULL) && anteriorUltimoLeido != raiz);
	//		delete anteriorUltimoLeido;
	return res;
}

int ArbolBp::buscar(Clave* c, RegistroArbol*& reg) {
	//NodoExterno* anteriorUltimoLeido = ultimoNodoLeido;
	int res = raiz->buscar(c, reg);
	if((this->max == 0) && res)
		guardarNodo(raiz, 0);
	//if((ultimoNodoLeido != anteriorUltimoLeido) && (anteriorUltimoLeido != NULL) && anteriorUltimoLeido != raiz);
	//		delete anteriorUltimoLeido;
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
	//delete r;
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
			if(raiz != ultimoNodoLeido)
				delete raiz;
			raiz = nueva_raiz;
			if(nh2 != ultimoNodoLeido)
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
	std::ofstream file("Arboltest.bin");
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
				file << "	";
			}
			file << nI->serializarDecimal() << std::endl;
			//delete nI;
		} else {
			pos = 0;
			NodoExterno* nE;
			nE = new NodoExterno(0, this);
			nE->hidratar(nodo, pos);
			int nivel = nE->getNivel();
			for(int i = nivel; i > 0; --i) {
				file << "	";
			}
			file << *nE << std::endl;
			//delete nE;
		}
		//delete nodo;
	}
}

void ArbolBp::guardarNodo(Nodo* n, unsigned int id) {
	std::vector<char>* ns = n->serializar();
	DatoNodo* dato = new DatoNodo(ns);
	RegistroNodo* reg = new RegistroNodo(dato);
	BloqueNodo b(N_SIZE);
	b.addRegistro(reg);
	arch_arbol.Escribir(&b, id);
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

NodoExterno* ArbolBp::getUltimoNodoLeido() {
	return ultimoNodoLeido;
}

int ArbolBp::crearNodo() {
	int libre = arch_arbol.ObtenerBloqueLibre();
	if(libre == -1) {
		BloqueNodo b(N_SIZE);
		arch_arbol.Escribir(&b, arch_arbol.getCantidadBloques());
		return arch_arbol.getCantidadBloques() - 1;
	} else {
		return libre;
	}
}

void ArbolBp::clear() {
	//delete raiz;
	//delete ultimoNodoLeido;
	ultimoRegistroLeido = 0;
	ultimoNodoLeido = NULL;
	arch_arbol.clear();
}

/*
std::string ArbolBp::leerNodo(int id) {
	BloqueNodo b(N_SIZE);
	arch_arbol.Leer(id, &b);
	RegistroVariable* reg = b.getRegistro(0);
	std::ostringstream oss;
	reg->serializar(oss);
	return oss.str();
}
*/
std::vector<char>* ArbolBp::leerNodo2(int id) {
	BloqueNodo b(N_SIZE);
	arch_arbol.Leer(id, &b);
	RegistroVariable* reg = b.getRegistro(0);
	std::ostringstream oss;
	reg->serializar(oss);
	std::string data_s = oss.str();
	std::string::iterator it;
	std::vector<char>* data = new std::vector<char>;
	for(it = data_s.begin(); it != data_s.end(); ++it) {
		data->push_back(*it);
	}
	return data;
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

void ArbolBp::exportar(VariableLengthRecordSequentialFile<WordRankingRecord>& os) {
	imprimirNodos();
	WordRankingRecord record;
	int primero = encontrarPrimero();
	NodoExterno* nE = new NodoExterno(0, this);
	int pos = 0;
	std::vector<char>* nodo_data = leerNodo2(primero);
	nE->hidratar(nodo_data, pos);
	ultimoNodoLeido = nE;
	Registro* reg = new RegistroArbol();
	reg = nE->getRegistro(0, reg);
	while(reg != NULL) {
		record.setNumberOfSearches(reinterpret_cast<RegistroArbol*>(reg)->timesSearched());
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

void ArbolBp::clearListReferences() {
	int primero = encontrarPrimero();
	NodoExterno* nE = new NodoExterno(0, this);
	int pos = 0;
	std::vector<char>* nodo_data = leerNodo2(primero);
	nE->hidratar(nodo_data, pos);
	ultimoNodoLeido = nE;
	Registro* reg = new RegistroArbol();
	reg = nE->getRegistro(0, reg);
	while(reg != NULL) {
		dynamic_cast<RegistroArbol*>(reg)->setListId(0);
		this->modify(reg);
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
	if(ultimoNodoLeido == NULL)
		return false;
	if((ultimoNodoLeido->cantRegistros() == (ultimoRegistroLeido + 1)) && !(ultimoNodoLeido->getSiguiente()))
		return false;
	return true;
}

void ArbolBp::rewind() {
	int primero = encontrarPrimero();
	NodoExterno* nE = new NodoExterno(0, this);
	std::vector<char>* data = leerNodo2(primero);
	int pos = 0;
	nE->hidratar(data, pos);
	if(ultimoNodoLeido != NULL)
		delete ultimoNodoLeido;
	ultimoNodoLeido = nE;
	ultimoRegistroLeido = 0;
	delete data;
}

bool ArbolBp::isEmpty() {
	if(this->raiz == NULL)
		return true;
	if(this->raiz->getCantElem() == 0)
		return true;
	return false;
}
