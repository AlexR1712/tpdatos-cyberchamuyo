/*
 * BloqueDato.h
 *
 *  Created on: Sep 23, 2012
 *      Author: lucasj
 */

#ifndef BLOQUEDATO_H_
#define BLOQUEDATO_H_

#include "Bloque.h"
#include "RegistroDato.h"


// BLOQUE DATO: Tipo de Bloque que contiene la frase y sus datos.
// También poseé el número de td asociado al bloque.

// ATRIBUTOS BLOQUE DATO
//
// TD: El número de td asociado al bloque.
//

typedef std::list <Hash::RegistroDato*> regDato;
typedef std::list <Hash::RegistroDato*>::iterator itRegDato;

class BloqueDato: public Bloque {
private:
	regDato registros;
	long tamanoBloque;
    long espacioLibre;
	unsigned int td;
	virtual void LlenarRegistros(std::istream& oss, int cantReg);
	virtual void print(std::ostream& oss);
	virtual void input(std::istream& oss);
	virtual void setEspacioLibre(long espacioOcupado);
public:
	BloqueDato(long tamanoBloque);
	int addRegistro(Hash::RegistroDato* registro);
    Hash::RegistroDato* getRegistro(unsigned int posicion);
	unsigned int getTd(void);
	void setTd(unsigned int td);
	void getFrase(unsigned int clave, std::string& frase);
	void getAutor(unsigned int clave, std::string& autor);
	virtual ~BloqueDato();
	virtual void anularRegistros(void);
	virtual void ImprimirATexto(std::ostream& oss);
	virtual void borrarDatos(void);
	virtual void borrarRegistro(unsigned int posicion);
	virtual bool estaVacio(void);
	virtual long getTamanoBloque(void);
    virtual long getEspacioLibre(void);
    virtual int getCantRegistros(void);
    virtual void vaciar(void);
    virtual bool buscarRegistro(unsigned int clave, unsigned int& pos);
};

#endif
