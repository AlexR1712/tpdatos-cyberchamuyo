
/*
 * ArbolBp.h
 *
 *  Created on: 19/05/2012
 *      Author: sebastian
 */

#ifndef ARBOLBP_H_
#define ARBOLBP_H_

#include "NodoInterno.h"
#include "ArchivoBloquesFijos.h"
#include "Bloque.h"

#define N_SIZE 256
#define OK 0
#define OVERFLOW 1
#define GUARDAR 2
#define N_MIN (256 * 0.2)
#define REGISTRO_YA_EXISTENTE 3

#define TIPO_ARBOL 1

class ArbolBp {
	friend class NodoInterno;
public:
	ArbolBp(const char* filename, int block_size);
	virtual ~ArbolBp();
	//  permite visualizar el arbol en un formato entendible a simple vista.
	void imprimirNodos();
	//  Inserta un registro en el arbol. Recibe un registro creado
	int insertarRegistro(Registro* r);
	int buscar(Clave* c, Registro*& reg);
	bool isEmpty();
	std::string leerNodo(int id);	// metodo para obtener un bloque del arch de bloques
	std::vector<char>* leerNodo2(int id);
	void setUltimoLeido(NodoExterno* nE);
	Registro* siguiente();

	void setUltimoRegistroLeido(int nReg);
	void aumentarUltimoRegistroLeido();

private:
	Nodo* raiz;											//  nodo raiz del arbol
	ArchivoBloquesFijos arch_arbol;						//  archivo de bloques donde se guardan los nodos
	int b_size;											//  tamaño nodos
	int max;											//  altura del arbol
	NodoExterno* ultimoNodoLeido;						//  para lectura secuencial
	int ultimoRegistroLeido;							//  para lectura secuencial

	void guardarNodo(Nodo* n);							// no se usa
	void guardarNodo(Nodo* n, unsigned int id);			// metodo para guardar un nodo
	int crearNodoExterno(NodoExterno* nE, int nivel);	// metodo en el que hay que obtener un bloque vacio
	int crearNodoInterno(NodoInterno* nI, int nivel);	// metodo en el q hay q obtener un bloque vacio


};

#endif /* ARBOLBP_H_ */
