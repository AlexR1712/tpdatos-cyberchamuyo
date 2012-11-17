/*
 * BloqueNodo.h
 *
 *  Created on: Oct 17, 2012
 *      Author: lucasj
 */

#ifndef BLOQUENODO_H_
#define BLOQUENODO_H_

#include "Bloque.h"
#include "RegistroNodo.h"

typedef std::list <RegistroNodo*> regNodo;
typedef std::list <RegistroNodo*>::iterator itRegNodo;

class BloqueNodo: public Bloque {
private:
	regNodo registros;
	long tamanoBloque;
	long espacioLibre;
	virtual void print(std::ostream& oss);
	virtual void input(std::istream& oss);
	virtual void LlenarRegistros(std::istream& oss, int cantReg);
	virtual void setEspacioLibre(long espacioOcupado);
public:
	BloqueNodo(long tamanoBloque);
	int addRegistro(RegistroNodo* registro);
    RegistroNodo* getRegistro(unsigned int posicion);
	virtual void ImprimirATexto(std::ostream& oss);
	virtual void anularRegistros(void);
	virtual void borrarDatos(void);
	virtual void borrarRegistro(unsigned int posicion);
	virtual bool estaVacio(void);
	virtual long getTamanoBloque(void);
    virtual long getEspacioLibre(void);
    virtual int getCantRegistros(void);
    virtual void vaciar(void);
    virtual bool buscarRegistro(unsigned int clave, unsigned int& pos);
	virtual ~BloqueNodo();
};

#endif
