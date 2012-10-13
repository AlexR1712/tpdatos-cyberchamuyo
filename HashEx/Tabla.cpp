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
	ActualizarOCrear(jt, list, dato);
	while (jt != list.end()) {
		this->arch.Borrar(*jt);
	}
}

void Tabla::GuardarUnicaParticion() {
	Data::ArrayBytes* dato = new Data::ArrayBytes;
	for (itArray it = this->tabla.begin(); it != this->tabla.end(); ++it) {
		dato->insertar(*it);
	}
	ActualizarBloque(POSTABLA, dato);
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
	if ((this->tabla.size() * 4) <= this->arch.getTamanoBloque()) {
		GuardarUnicaParticion();
	} else {
		listaTabla list;
		cargarListaBloquesTabla(list);
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

Tabla::~Tabla() {

}

}
