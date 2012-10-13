/*
 * DispersionEx.cpp
 *
 *  Created on: Sep 15, 2012
 *      Author: lucasj
 */

#include "DispersionEx.h"

namespace Hash {

DispersionEx::DispersionEx(const char* archDir) :
		arch_disp(archDir, TAM_BLOQUE),tabla(arch_disp) {
	if (this->arch_disp.getCantidadBloques() == 0)
		this->tabla.GuardarTablaInicial();
	BloqueDato bl(this->arch_disp.getTamanoBloque());
	if (this->arch_disp.Leer(1, &bl) == ERR_BLOQUE_INEXISTENTE)
		crearNuevoBloque(1, this->tabla.getSize());
}

void DispersionEx::CargarFrases(const char* archFrases) {
	std::string linea;
	std::ifstream entradaTexto(archFrases);
	getline(entradaTexto, linea);
	unsigned int num = 1;
	while(!entradaTexto.eof()) {
		int posActual = linea.find("\t");
		int posAnterior = 0;
		std::string autor = linea.substr(posAnterior, posActual);
		obtenerSiguientePosicion(posAnterior, posActual, linea);
		std::string nombre = linea.substr(posAnterior + 1, posActual - posAnterior - 1);
		autor.append(" ");
		autor.append(nombre);
		obtenerSiguientePosicion(posAnterior, posActual, linea);
		std::string frase = linea.substr(posAnterior + 1, posActual - posAnterior - 1);
		Data::Frase* datoInsertar = new Data::Frase(autor, frase, num);
		RegistroVariable* reg = new Hash::RegistroDato(datoInsertar);
		this->insertarRegistro(reg, num);
		getline(entradaTexto, linea);
		++num;
	}
	entradaTexto.close();
}

void DispersionEx::crearNuevoBloque(int nuevoBloque, unsigned int td) {
	BloqueDato bl(this->arch_disp.getTamanoBloque());
	bl.setTd(td);
	this->arch_disp.Escribir(&bl, nuevoBloque);
}

void DispersionEx::ActualizarTablaAlta(unsigned int td, int posTabla) {
	long nuevoBloque = this->arch_disp.ObtenerBloqueLibre();
	if (nuevoBloque == -1)
		nuevoBloque = this->arch_disp.getCantidadBloques();
	if (td == this->tabla.getSize())
		this->tabla.AumentarTabla();
	this->tabla.RecorrerYReemplazar(posTabla, nuevoBloque, td*2);
	this->tabla.Imprimir();
	crearNuevoBloque(nuevoBloque, td*2);
}

void DispersionEx::redistribuir(listReg& list) {
	itListReg it;
	for (it = list.begin(); it != list.end(); ++it) {
		int clave = (*it)->getClaveDato();
		insertarRecursivo(*it, clave);
	}
}

void DispersionEx::ActualizarBloqueDispersado(BloqueDato& bl, unsigned int td,
		int numBloque) {
	bl.setTd(td * 2);
	bl.setCantRegistros(0);
	bl.anularRegistros();
	this->arch_disp.Escribir(&bl, numBloque);
}

void DispersionEx::LlenarListaRegistros(BloqueDato& bl, listReg& list) {
	int cantRegistros = bl.getCantRegistros();
	for (int j = 0; j < cantRegistros; ++j) {
		RegistroVariable* reg = bl.getRegistro(j);
		list.push_back(reg);
	}
}

void DispersionEx::ActualizarDispersion(BloqueDato& bl, int posTabla,
		int numBloque) {
	listReg list;
	unsigned int td = bl.getTd();
	ActualizarTablaAlta(td, posTabla);
	LlenarListaRegistros(bl, list);
	ActualizarBloqueDispersado(bl, td, numBloque);
	redistribuir(list);
}

int DispersionEx::insertarRecursivo(RegistroVariable* r, int clave) {
	int posTabla = clave % this->tabla.getSize();
	BloqueDato bl(this->arch_disp.getTamanoBloque());
	int numBloque = this->tabla.getNumeroBloque(posTabla);
	this->arch_disp.Leer(numBloque, &bl);
	if (bl.addRegistro(r) == ERR_NO_MEMORIA) {
		ActualizarDispersion(bl, posTabla, numBloque);
		insertarRecursivo(r, clave);
	} else this->arch_disp.Escribir(&bl, numBloque);
	return RES_OK;
}

void DispersionEx::insertarRegistro(RegistroVariable* r, int clave) {
		insertarRecursivo(r, clave);
		this->tabla.GuardarTabla();
}

std::ostream& operator<<(std::ostream& oss, DispersionEx &disp) {
	oss << disp.arch_disp;
	BloqueTabla* bl = new BloqueTabla(disp.arch_disp.getTamanoBloque());
	disp.arch_disp.Leer(POSTABLA, bl);
	oss << "***********************" << std::endl;
	oss << "BLOQUE 0" << std::endl;
	bl->ImprimirATexto(oss);
	int siguienteTab = bl->getSiguiente();
	int cantBloques = disp.arch_disp.getCantidadBloques();
	delete bl;
	for (int i = 1; i < cantBloques; ++i) {
		oss << "***********************" << std::endl;
		oss << "BLOQUE " << i << std::endl;
		if (siguienteTab == i) {
			BloqueTabla* bl = new BloqueTabla(disp.arch_disp.getTamanoBloque());
			disp.arch_disp.Leer(i, bl);
			siguienteTab = bl->getSiguiente();
			bl->ImprimirATexto(oss);
			delete bl;
		} else {
			BloqueDato* bl = new BloqueDato(disp.arch_disp.getTamanoBloque());
			if (disp.arch_disp.Leer(i, bl) == ERR_BLOQUE_LIBRE)
				oss << "BLOQUE LIBRE" << std::endl;
			else bl->ImprimirATexto(oss);
			delete bl;
		}
	}
	return oss;

}

DispersionEx::~DispersionEx() {

}

}
