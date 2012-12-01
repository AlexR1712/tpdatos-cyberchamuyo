/*
 * InvertedListFile.cpp
 *
 *  Created on: Nov 28, 2012
 *      Author: lucasj
 */

#include "../include/InvertedListFile.h"

namespace invertedList {

InvertedListFile::InvertedListFile(const char* filename):archList(filename, TAM_BLOQUE_LINV_FILE) {
}

unsigned int InvertedListFile::guardarParticion(invertedList::ListaInvertida* lista, unsigned int pos, unsigned int offset) {
	BloqueListaInvertida bloque(this->archList.getTamanoBloque());
	bloque.setPrimero(offset);
	bloque.setSiguiente(offset);
	RegistroListaInvertida* reg = new RegistroListaInvertida(lista);
	bloque.addRegistro(reg);
	if (this->archList.Escribir(&bloque, pos) == RES_OK)
		return offset;
	else return ERR_BLOQUE_INEXISTENTE;
}

void InvertedListFile::vincularAnterior(unsigned int pos, unsigned int nuevaPos) {
	BloqueListaInvertida bl(this->archList.getTamanoBloque());
	if (this->archList.Leer(pos, &bl) != ERR_BLOQUE_INEXISTENTE) {
		if (bl.getSiguiente() == bl.getPrimero()) {
			bl.setSiguiente(nuevaPos);
			this->archList.Escribir(&bl, pos);
		} else vincularAnterior(bl.getSiguiente(), nuevaPos);
	}
}

void InvertedListFile::crearBloque(invertedList::ListaInvertida* lista, unsigned int offset) {
	unsigned int nuevaPos = this->archList.ObtenerBloqueLibre();
	guardarParticion(lista, nuevaPos, offset);
	if (nuevaPos != offset)
		vincularAnterior(offset, nuevaPos);
}

void InvertedListFile::particionarLista(invertedList::ListaInvertida* lista, unsigned int offset) {
	listInt linverted = lista->getParticion();
	itListInt it = linverted.begin();
	int cant = ((this->archList.getTamanoBloque() - 12)/sizeof(unsigned int));
	int j = 0;
	invertedList::ListaInvertida* dato = new invertedList::ListaInvertida();
	while (it != linverted.end()) {
		if (j != cant) {
			dato->setId(lista->getId());
			dato->insertar(*it);
			++j;
			++it;
		} else {
			crearBloque(dato, offset);
			dato = new invertedList::ListaInvertida();
			j = 0;
		}
	}
	if (dato->getTamano() != 0)
		crearBloque(dato, offset);
	else delete dato;
	delete lista;
}

unsigned int InvertedListFile::insertarLista(invertedList::ListaInvertida* lista) {
	unsigned int offset = this->archList.ObtenerBloqueLibre();
	if (lista->getTamano() > this->archList.getTamanoBloque() - 12) {
		particionarLista(lista, offset);
		return offset;
	} else return guardarParticion(lista, offset, offset);
}

void InvertedListFile::liberarBloquesLista(unsigned int pos) {
	BloqueListaInvertida bl(this->archList.getTamanoBloque());
	this->archList.Leer(pos, &bl);
	this->archList.Borrar(pos);
	if (bl.getSiguiente() != bl.getPrimero())
		liberarBloquesLista(bl.getSiguiente());
}

void InvertedListFile::llenarLista(invertedList::ListaInvertida* lista, unsigned int pos) {
	BloqueListaInvertida bl(this->archList.getTamanoBloque());
	this->archList.Leer(pos, &bl);
	bl.cargarListaInvertida(*lista, pos);
	if (bl.getSiguiente() != bl.getPrimero())
		llenarLista(lista, bl.getSiguiente());
}

invertedList::ListaInvertida* InvertedListFile::getLista(unsigned int offset) {
	invertedList::ListaInvertida* lista = new invertedList::ListaInvertida;
	llenarLista(lista, offset);
	return lista;
}

void InvertedListFile::actualizarLista(invertedList::ListaInvertida* lista, unsigned int offset) {
	liberarBloquesLista(offset);
	if (lista->getTamano() > this->archList.getTamanoBloque() - 12) {
		particionarLista(lista, offset);
	} else guardarParticion(lista, offset, offset);
}

std::ostream& operator<<(std::ostream& oss,
					  InvertedListFile &listFile) {
	oss << listFile.archList;
	for (int i = 0; i < listFile.archList.getCantidadBloques(); ++i) {
		oss << "***********************" << std::endl;
		oss << "BLOQUE " << i << std::endl;
			BloqueListaInvertida* bl = new BloqueListaInvertida(listFile.archList.getTamanoBloque());
			if (listFile.archList.Leer(i, bl) == ERR_BLOQUE_LIBRE)
				oss << "BLOQUE LIBRE" << std::endl;
			else bl->ImprimirATexto(oss);
			delete bl;
		}
	return oss;
}

InvertedListFile::~InvertedListFile() {

}

void InvertedListFile::clear(void) {
	this->archList.clear();
}

}
