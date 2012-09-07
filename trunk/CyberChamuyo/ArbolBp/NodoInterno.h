/*
 * NodoInterno.h
 *
 *  Created on: 07/05/2012
 *      Author: Shazgath
 */

#ifndef NODOINTERNO_H_
#define NODOINTERNO_H_

#include "NodoExterno.h"
#include <vector>

class ArbolBp;

class NodoInterno : public Nodo {
friend class ArbolBp;
public:
	NodoInterno(int lvl, ArbolBp* arbol);
	virtual ~NodoInterno();
	virtual void hidratar(std::string& s);
	std::string serializar();
	std::string serializarDecimal();
	int getHijoCorrespondiente(Clave* c);	// devuelve el numero de nodo que corresponde a la clave pasada por parametro
	void insertarClave(Clave* c, int nodo);		// inserta la clave con su correspondiente numero d enodo
	//virtual int insertarRecursivo(Registro* r);
	void insertarHijoIzquierdo(int hI);	// agrega el numero de nodo izquierdo
	list<Clave*> getSobrantes();	// no se usa, era para arbol b+
	vector<int> getHijosSobrantes();	// no se usa era para b+
	int getPosicionClave();	// devuelve la posicion del tipo de clave que corresponde a nivel
private:
	list<Clave*> claves;
	vector<int> nodos;
	int nivel;
	int libre;
	int tipo;	// no se usa creo
	ArbolBp* arbol;
	void buscarEnHijo(Clave* clave, std::vector<std::pair<unsigned int, unsigned int> >& rangos, std::ostream& file_output);
};

#endif /* NODOINTERNO_H_ */
