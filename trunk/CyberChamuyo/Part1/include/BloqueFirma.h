/*
 * BloqueFirma.h
 *
 *  Created on: Dec 4, 2012
 *      Author: lucasj
 */

#ifndef BLOQUEFIRMA_H_
#define BLOQUEFIRMA_H_

#include "Bloque.h"
#include "RegistroFirma.h"

class BloqueFirma: public Bloque {
private:
	RegistroFirma* reg;
	long tamanoBloque;
    long espacioLibre;
    bool ocupado;
	virtual void LlenarRegistros(std::istream& oss, int cantReg);
	virtual void print(std::ostream& oss);
	virtual void input(std::istream& oss);
	virtual void setEspacioLibre(long espacioOcupado);
public:
	BloqueFirma(long tamanoBloque);
	virtual ~BloqueFirma();
	int addRegistro(RegistroFirma *registro);
	void obtenerListaFrases(listaFrases& lista);
	RegistroFirma* getRegistro(void);
	virtual void anularRegistros(void);
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

#endif /* BLOQUEFIRMA_H_ */
