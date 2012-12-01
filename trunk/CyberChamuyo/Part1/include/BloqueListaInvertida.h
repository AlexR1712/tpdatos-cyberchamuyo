/*
 * BloqueListaInvertida.h
 *
 *  Created on: Nov 28, 2012
 *      Author: lucasj
 */

#ifndef BLOQUELISTAINVERTIDA_H_
#define BLOQUELISTAINVERTIDA_H_

#include "Bloque.h"
#include "RegistroListaInvertida.h"

typedef std::list <RegistroListaInvertida*> regListaInvertida;
typedef std::list <RegistroListaInvertida*>::iterator itRegListaInvertida;

class BloqueListaInvertida: public Bloque {
private:
	regListaInvertida registros;
	long tamanoBloque;
    long espacioLibre;
	unsigned int siguiente;
	unsigned int primero;
	virtual void LlenarRegistros(std::istream& oss, int cantReg);
	virtual void print(std::ostream& oss);
	virtual void input(std::istream& oss);
	virtual void setEspacioLibre(long espacioOcupado);

public:
	BloqueListaInvertida(long tamanoBloque);
	virtual ~BloqueListaInvertida();
	int addRegistro(RegistroListaInvertida* registro);
	virtual void anularRegistros(void);
    RegistroListaInvertida* getRegistro(unsigned int posicion);
	unsigned int getSiguiente(void);
	unsigned int getPrimero(void);
	void setSiguiente(unsigned int siguiente);
	void setPrimero(unsigned int primero);
	void cargarListaInvertida(invertedList::ListaInvertida& list, unsigned int offset);
	virtual void ImprimirATexto(std::ostream& oss);
	virtual void borrarRegistro(unsigned int posicion);
	virtual void borrarDatos(void);
	virtual bool estaVacio(void);
	virtual long getTamanoBloque(void);
    virtual long getEspacioLibre(void);
    virtual int getCantRegistros(void);
    virtual void vaciar(void);
    virtual bool buscarRegistro(unsigned int clave, unsigned int& pos);
};

#endif
