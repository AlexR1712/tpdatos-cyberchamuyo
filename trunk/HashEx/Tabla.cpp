/*
 * Tabla.cpp
 *
 *  Created on: Sep 29, 2012
 *      Author: lucasj
 */

#include "Tabla.h"

namespace Hash {

Tabla::Tabla(ArchivoBloquesFijos& arch_disp):arch(arch_disp) {
	CargarTabla();
}

void Tabla::Hidratar(const std::string& dato) {
	int posActual = dato.find("\t");
	int posAnterior = 0;
	std::string valor = dato.substr(posAnterior, posActual);
	while (posActual > posAnterior) {
		unsigned int num = stoi(valor);
		this->tabla.push_back(num);
		obtenerSiguientePosicion(posAnterior, posActual, dato);
		valor = dato.substr(posAnterior + 1, posActual - posAnterior - 1);
	}
}

void Tabla::CargarTablaRecursivo(unsigned long int pos) {
	BloqueTabla bl(this->arch.getTamanoBloque());
	this->arch.Leer(pos, &bl);
	RegistroVariable* reg = bl.getRegistro(0);
	std::ostringstream oss;
	reg->serializar(oss);
	Hidratar(oss.str());
	unsigned int sig = bl.getSiguiente();
	if (sig != SIN_SIGUIENTE) {
		CargarTablaRecursivo(sig);
	}
}

void Tabla::CargarTabla(void) {
	if (arch.getCantidadBloques() != 0) {
		CargarTablaRecursivo(POSTABLA);
	} else {
		itArray it = this->tabla.begin();
		this->tabla.insert(it, 1);
	}
}

void Tabla::VincularAnterior(int pos, int siguiente) {
	BloqueTabla bl(this->arch.getTamanoBloque());
	if (this->arch.Leer(pos, &bl) != ERR_BLOQUE_INEXISTENTE) {
		if (bl.getSiguiente() == SIN_SIGUIENTE) {
			bl.setSiguiente(siguiente);
			this->arch.Escribir(&bl, pos);
		} else VincularAnterior(bl.getSiguiente(), siguiente);
	}
}

void Tabla::cargarListaBloquesTablaRecursiva(unsigned int pos, listaTabla& list) {
	long tamanoBloque = this->arch.getTamanoBloque();
	list.push_back(pos);
	BloqueTabla bl(tamanoBloque);
	this->arch.Leer(pos, &bl);
	int sig = bl.getSiguiente();
	if (sig != SIN_SIGUIENTE)
		cargarListaBloquesTablaRecursiva(sig, list);
}

void Tabla::ActualizarBloque(unsigned int pos, Data::ArrayBytes* dato) {
	BloqueTabla bl(this->arch.getTamanoBloque());
	this->arch.Leer(pos, &bl);
	bl.vaciar();
	RegistroVariable* reg = new RegistroTabla(dato);
	bl.addRegistro(reg);
	this->arch.Escribir(&bl, pos);
}

void Tabla::CrearBloqueTabla(Data::ArrayBytes* dato) {
	int nuevoBloque = this->arch.ObtenerBloqueLibre();
	if (nuevoBloque == ERR_BLOQUE_INEXISTENTE)
		nuevoBloque = this->arch.getCantidadBloques();
	BloqueTabla bl(this->arch.getTamanoBloque());
	bl.setSiguiente(0);
	VincularAnterior(POSTABLA, nuevoBloque);
	RegistroVariable* reg = new RegistroTabla(dato);
	bl.addRegistro(reg);
	this->arch.Escribir(&bl, nuevoBloque);
}

void Tabla::ActualizarOCrear(itListaTabla& jt, listaTabla& list,
		Data::ArrayBytes* dato) {
	if (jt != list.end()) {
		ActualizarBloque(*jt, dato);
		++jt;
	} else
		CrearBloqueTabla(dato);
}

void Tabla::ActualizarSiguiente(unsigned int pos) {
	BloqueTabla bl(this->arch.getTamanoBloque());
	this->arch.Leer(pos, &bl);
	int siguiente = bl.getSiguiente();
	if (siguiente != 0)
		bl.setSiguiente(0);
	this->arch.Escribir(&bl, pos);
}

void Tabla::ParticionarTabla(listaTabla& list) {
	itListaTabla jt = list.begin();
	int cant = (this->arch.getTamanoBloque()/sizeof(unsigned int));
	int j = 0;
	Data::ArrayBytes* dato = new Data::ArrayBytes;
	itArray it = this->tabla.begin();
	while (it != this->tabla.end()) {
		if (j != cant) {
			dato->insertar(*it);
			++j;
			++it;
		} else {
			ActualizarOCrear(jt, list, dato);
			dato = new Data::ArrayBytes;
			j = 0;
		}
	}
	if (jt != list.end())
		ActualizarSiguiente(*jt);
	ActualizarOCrear(jt, list, dato);
	while (jt != list.end()) {
		this->arch.Borrar(*jt);
		++jt;
	}
}

void Tabla::GuardarUnicaParticion(listaTabla& list) {
	Data::ArrayBytes* dato = new Data::ArrayBytes;
	for (itArray it = this->tabla.begin(); it != this->tabla.end(); ++it) {
		dato->insertar(*it);
	}
	ActualizarSiguiente(POSTABLA);
	ActualizarBloque(POSTABLA, dato);
	itListaTabla jt = list.begin();
	++jt;
	while (jt != list.end()) {
		this->arch.Borrar(*jt);
		++jt;
	}
}

void Tabla::cargarListaBloquesTabla(listaTabla& list) {
	cargarListaBloquesTablaRecursiva(POSTABLA, list);
}

void Tabla::GuardarTablaInicial(void) {
	BloqueTabla bl(this->arch.getTamanoBloque());
	bl.setSiguiente(SIN_SIGUIENTE);
	Data::ArrayBytes* dato = new Data::ArrayBytes;
	dato->insertar(this->tabla[0]);
	RegistroVariable* reg = new RegistroTabla(dato);
	bl.addRegistro(reg);
	this->arch.Escribir(&bl, POSTABLA);
}

void Tabla::GuardarTabla(void) {
	listaTabla list;
	cargarListaBloquesTabla(list);
	if ((this->tabla.size() * 4) <= this->arch.getTamanoBloque()) {
		GuardarUnicaParticion(list);
	} else {
		ParticionarTabla(list);
	}
}

void Tabla::RecorrerYReemplazar(int posTabla, long nuevoValor, unsigned int td) {
	unsigned int i = posTabla;
	while (i < this->tabla.size()) {
		this->tabla[i] = nuevoValor;
		i = i + td;
	}
	int j = posTabla - td;
	while (j >= 0) {
		this->tabla[j] = nuevoValor;
		j = j - td;
	}
}

bool Tabla::BuscarYReemplazar(int posTabla, unsigned int td) {
	if (this->tabla.size() != 1) {
		unsigned int posDerecha = posTabla + td;
		if (posDerecha >= this->tabla.size())
			posDerecha = posDerecha - this->tabla.size();
		int posIzquierda = posTabla - td;
		if (posIzquierda < 0)
			posIzquierda = 0 - posIzquierda;
		if (this->tabla[posIzquierda] == this->tabla[posDerecha]) {
			this->tabla[posTabla] = this->tabla[posIzquierda];
			return true;
		} else return false;
	} else return true;
}

void Tabla::AumentarTabla() {
	this->tabla.insert(this->tabla.end(), this->tabla.begin(),
			this->tabla.end());
}

void Tabla::Imprimir() {
	itArray it;
	std::ofstream tabla("tabla.txt");
	for (it = this->tabla.begin(); it < this->tabla.end(); ++it) {
		tabla << *it << " ";
	}
	tabla.close();
}

void Tabla::actualizarTablaAlta(int nuevoBloque, int posTabla, unsigned int td) {
	RecorrerYReemplazar(posTabla, nuevoBloque, td);
	//Imprimir();
}

unsigned int Tabla::getSize(void) {
	return this->tabla.size();
}

unsigned int Tabla::getNumeroBloque(int posTabla) {
	return this->tabla[posTabla];
}

bool Tabla::verificarEspejamiento() {
	int mitad = this->tabla.size() / 2;
	bool noIgual = true;
	itArray it = this->tabla.begin();
	while ((it != this->tabla.begin() + mitad) && (noIgual == true)) {
		if (*it != *(it + mitad)) {
			noIgual = false;
		} else
			++it;
	}
	return noIgual;
}

bool Tabla::disminuirTabla(void) {
	if (verificarEspejamiento()) {
		int mitad = this->tabla.size() / 2;
		itArray it = this->tabla.begin();
		this->tabla.erase(it + mitad, this->tabla.end());
		return true;
	} else return false;
}

Tabla::~Tabla() {

}

}
