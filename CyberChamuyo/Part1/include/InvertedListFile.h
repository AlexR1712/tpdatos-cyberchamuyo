/*
 * InvertedListFile.h
 *
 *  Created on: Nov 28, 2012
 *      Author: lucasj
 */

#ifndef INVERTEDLISTFILE_H_
#define INVERTEDLISTFILE_H_

#include "ArchivoBloquesFijos.h"
#include "ListaInvertida.h"
#include "BloqueListaInvertida.h"

#define TAM_BLOQUE_LINV_FILE 128

namespace invertedList {

class InvertedListFile {
private:
	ArchivoBloquesFijos archList;
	unsigned int guardarParticion(invertedList::ListaInvertida* lista, unsigned int pos, unsigned int offset);
	void particionarLista(invertedList::ListaInvertida* lista, unsigned int offset);
	void crearBloque(invertedList::ListaInvertida* lista, unsigned int offset);
	void vincularAnterior(unsigned int nuevaPos, unsigned int offset);
	void llenarLista(invertedList::ListaInvertida* lista,  unsigned int pos);
public:
	InvertedListFile(const char* filename);
	unsigned int getNuevoId(void);
	unsigned int getId();
	unsigned int insertarLista(invertedList::ListaInvertida* lista);
	void actualizarLista(invertedList::ListaInvertida* lista, unsigned int offset);
	invertedList::ListaInvertida* getLista(unsigned int offset);
	void clear(void);
	bool isLoaded();
	friend std::ostream& operator<<(std::ostream& oss,
					  InvertedListFile &listFile);
	friend std::istream& operator>>(std::istream& oss,
					  InvertedListFile &listFile);
	//////////////// lo hice publico
	void liberarBloquesLista(unsigned int offset);
	///////////////////////////////
	virtual ~InvertedListFile();
};

std::ostream& operator<<(std::ostream& oss,
					  InvertedListFile &listFile);

}
#endif
