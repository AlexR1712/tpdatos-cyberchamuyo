/*
 * BloqueTabla.h
 *
 *  Created on: Sep 23, 2012
 *      Author: lucasj
 */

#ifndef BLOQUETABLA_H_
#define BLOQUETABLA_H_

#include "Bloque.h"
#include "RegistroTabla.h"

typedef std::list <Hash::RegistroTabla*> regTabla;
typedef std::list <Hash::RegistroTabla*>::iterator itRegTabla;

// BLOQUE TABLA: Tipo de Bloque que contiene particiones de la tabla
// de dispersión. Como esta tabla se guarda como una lista enlazada
// en el archivo binario, los bloques poseen una referencia al
// siguiente bloque con la continuación de la tabla.

// ATRIBUTOS BLOQUE TABLA
//
// SIGUIENTE: Número de bloque que contiene el próximo bloque
// tabla con la próxima partición de la tabla de dispersión.
//

class BloqueTabla: public Bloque {
private:
	regTabla registros;
	long tamanoBloque;
    long espacioLibre;
	unsigned int siguiente;
	virtual void LlenarRegistros(std::istream& oss, int cantReg);
	virtual void print(std::ostream& oss);
	virtual void input(std::istream& oss);
	virtual void setEspacioLibre(long espacioOcupado);
public:
	BloqueTabla(long tamanoBloque);
	int addRegistro(Hash::RegistroTabla* registro);
	virtual void anularRegistros(void);
    Hash::RegistroTabla* getRegistro(unsigned int posicion);
	unsigned int getSiguiente(void);
	void setSiguiente(unsigned int siguiente);
	void cargarTabla(array& vec);
	virtual void ImprimirATexto(std::ostream& oss);
	virtual void borrarRegistro(unsigned int posicion);
	virtual void borrarDatos(void);
	virtual bool estaVacio(void);
	virtual long getTamanoBloque(void);
    virtual long getEspacioLibre(void);
    virtual int getCantRegistros(void);
    virtual void vaciar(void);
     virtual bool buscarRegistro(unsigned int clave, unsigned int& pos);
	virtual ~BloqueTabla();
};


#endif /* BLOQUETABLA_H_ */
