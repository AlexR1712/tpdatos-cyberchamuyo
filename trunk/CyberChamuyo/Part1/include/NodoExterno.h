/*
 * NodoExterno.h
 *
 *  Created on: 06/05/2012
 *      Author: Shazgath
 */

#ifndef NODOEXTERNO_H_
#define NODOEXTERNO_H_

#include "Nodo.h"

#define E_CONTROL_SIZE (3 * sizeof(int) + 1 * sizeof(char))

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
	Registro* popMayor();
	//virtual std::string serializar();
	virtual std::vector<char>* serializar();
	virtual void hidratar(const std::vector<char>* data, int& pos);
	virtual void hidratar(string& s);
	int cantRegistros();
	Registro* popMenor();
	bool tieneOverflow();
	void setSiguiente(const int sig);
	int getSiguiente();
	virtual int insertarRecursivo(Registro* r);
	void aumentarNivel();		// ++nivel
	list<Registro*> getRegistrosDerecha();	// devuelve registros mayores que el central
	NodoExterno& operator+(NodoExterno& n); //  agrega los registros de n, alocando nuevos recursos
	NodoExterno& operator-(NodoExterno& n); //  quita de este nodo los registros que coincidan con registros de n
	NodoExterno& operator=(NodoExterno& n);
	friend std::ostream& operator<<(std::ostream& os, NodoExterno& ne);
	virtual int getNivel();
	virtual int buscar(Clave* c, Registro* reg);
	Registro* getRegistro(int pos, Registro* reg);
	virtual int getCantElem();
private:
	list<Registro*> registros;
	long nivel;
	long libre;
	long tipo;
	long siguiente;
	ArbolBp* arbol;
};

#endif /* NODOEXTERNO_H_ */
