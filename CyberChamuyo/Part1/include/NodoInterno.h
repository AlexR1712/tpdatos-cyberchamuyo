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

#define I_CONTROL_SIZE (3 * sizeof(int) + 1 * sizeof(char))

class NodoInterno : public Nodo {
friend class ArbolBp;
public:
	NodoInterno(int lvl, ArbolBp* arbol);
	virtual ~NodoInterno();
	virtual void hidratar(std::string& s);
	virtual void hidratar(const std::vector<char>* data, int& pos);
	virtual std::vector<char>* serializar();
	std::string serializarDecimal();
	int getHijoCorrespondiente(Clave* c);	// devuelve el numero de nodo que corresponde a la clave pasada por parametro
	void insertarClave(Clave* c, int nodo);		// inserta la clave con su correspondiente numero d enodo
	virtual int insertarRecursivo(Registro* r);
	void insertarHijoIzquierdo(long hI);	// agrega el numero de nodo izquierdo
	list<Clave*> getSobrantes();
	vector<int> getHijosSobrantes();
	bool tieneOverflow();
	virtual int getNivel();
	int getHijoMedio();
	void aumentarNivel();
	virtual int buscar(Clave* c, Registro* reg);
	int encontrarPrimero();
	virtual int getCantElem();
private:
	list<Clave*> claves;
	vector<int> nodos;  //  el lugar 0 corresponde a hijo izquierda, el resto corresponden 1 a 1 con las claves
	int nivel;
	int libre;
	int tipo;
	ArbolBp* arbol;
};

#endif /* NODOINTERNO_H_ */
