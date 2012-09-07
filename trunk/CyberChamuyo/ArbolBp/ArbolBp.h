
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

#define OVERFLOW 1
#define N_SIZE 512
#define OK 0
#define N_MIN 5

class ArbolBp {

	friend class NodoInterno;

public:
	ArbolBp(int kd, char* filename, int block_size);		// la raiz se crea con 3 registros de prueba, hay que sacarlos y que se cree vacia
	virtual ~ArbolBp();

	//  permite visualizar el arbol en un formato entendible a simple vista.
	void imprimirNodos();

	//  obtiene la cantidad de dimensiones del arbol
	int getK();

	//  Inserta un registro en el arbol. Recibe un registro creado
	int insertarRegistro(Registro* r);

	bool isEmpty();


private:
	Nodo* raiz;		//  nodo raiz del arbol
	int k;
	ArchivoBloquesFijos arch_arbol;
	int b_size;

	void guardarNodo(Nodo* n);		// no se usa
	void guardarNodo(Nodo* n, unsigned int id);		// metodo para guardar un nodo
	int crearNodoExterno(NodoExterno* nE, int nivel);	// metodo en el que hay que obtener un bloque vacio
	int crearNodoInterno(NodoInterno* nI, int nivel);	//  metodo  en el q hay q obtener un bloque vacio
	std::string leerNodo(int id);	// metodo para obtener un bloque del arch de bloques
	std::string leerNodo(unsigned int n_nodo);


};

#endif /* ARBOLBP_H_ */
