/*
 * NodoExterno.h
 *
 *  Created on: 06/05/2012
 *      Author: Shazgath
 */

#ifndef NODOEXTERNO_H_
#define NODOEXTERNO_H_

#include "Nodo.h"

class ArbolBp;

class NodoExterno : public Nodo {
public:
	NodoExterno();
	NodoExterno(int lvl);
	NodoExterno(int lvl, ArbolBp* arbol);
	virtual ~NodoExterno();
	int insertarRegistro(Registro* r);		// insertar un registro
	bool eliminarRegistro(Clave* c);
	Registro* sacarRegistro(Clave* c);
	Registro* sacarRegistro();
	virtual string serializar();
	virtual void hidratar(string& s);
	int cantRegistros();
	Registro* popMenor();
	bool tieneOverflow();
	virtual int insertarRecursivo(Registro* r);
	void aumentarNivel();		// ++nivel
	list<Registro*> getRegistrosDerecha();			// devuelve registros mayores que el central
	NodoExterno& operator+(NodoExterno& n);  //  agrega los registros de n, alocando nuevos recursos
	NodoExterno& operator-(NodoExterno& n);  //  quita de este nodo los registros que coincidan con registros de n
	friend std::ostream& operator<<(std::ostream& os, NodoExterno& ne);
private:
	list<Registro*> registros;
	long nivel;
	long libre;
	long tipo;
	long siguiente;
	ArbolBp* arbol;
};

#endif /* NODOEXTERNO_H_ */
