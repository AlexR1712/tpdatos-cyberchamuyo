/* 
 * File:   Bloque.h
 *
 *
 */

#ifndef BLOQUE_H
#define	BLOQUE_H

#include "RegistroVariable.h"
#include "BloqueCtes.h"

#include <stdexcept>
using std::runtime_error;
#include <list>


// BLOQUE: Clase que representa la entidad bloque. Contiene
// registros variables que podrán ser agregados dependiendo
// del total de memoria disponible que posea.

// ATRIBUTOS BLOQUE
//
// TAMANOBLOQUE: Contiene el tamaño del bloque.
//
// REGISTRO: La lista de registros variables que contiene
// el bloque.
//
// ESPACIOLIBRE: La cantidad de espacio libre qu poseé el bloque.
//
// CANTIDAD REGISTROS: La cantidad total de registros que poseé
// el bloque.
//

class Bloque {
private:
    virtual void setEspacioLibre(long espacioOcupado) = 0;
    virtual void print(std::ostream& oss) = 0;
	virtual void input(std::istream& oss) = 0;
	virtual void LlenarRegistros(std::istream& oss, int cantReg) = 0;
public:
	Bloque(void);
	virtual void anularRegistros(void) = 0;
	virtual void borrarDatos(void) = 0;
	virtual long getTamanoBloque() = 0;
    virtual long getEspacioLibre() = 0;
    virtual void ImprimirATexto(std::ostream& oss) = 0;
    virtual int getCantRegistros() = 0;
    virtual void vaciar(void) = 0;
    virtual bool estaVacio(void) = 0;
    virtual void borrarRegistro(unsigned int posicion) = 0;
    virtual bool buscarRegistro(unsigned int clave, unsigned int& pos) = 0;
    virtual ~Bloque();
    friend std::ostream& operator<<(std::ostream& oss,
					  Bloque &bl);
	friend std::istream& operator>>(std::istream& oss,
					  Bloque &bl);
};


class ExcepcionPosicionInvalidaEnBloque : std::exception
{

	virtual const char* what() const throw() {
		return "Error PosicionInvalida";
	}
};


#endif	/* BLOQUE_H */

