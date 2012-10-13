/* 
 * File:   Bloque.h
 * Author: emperor
 *
 * Created on 6 de abril de 2012, 19:30
 */

#ifndef BLOQUE_H
#define	BLOQUE_H

#include "RegistroVariable.h"
#include "BloqueCtes.h"
#include <list>
#include <stdexcept>
using std::runtime_error;

typedef std::list <RegistroVariable*> listaReg;
typedef std::list <RegistroVariable*>::iterator itListaReg;

class Bloque
{
private:
    long tamanoBloque;
    listaReg registros;
    long espacioLibre;
    int cantRegistros;
    void setEspacioLibre(long espacioOcupado);
    virtual void print(std::ostream& oss) const = 0;
	virtual void input(std::istream& oss) const = 0;
	virtual void LlenarRegistros(std::istream& oss, int cantReg) = 0;
	void borrarDatos(void);
public:
    Bloque(long tamanoBloque);
    long getTamanoBloque();
    long getEspacioLibre();
    virtual void ImprimirATexto(std::ostream& oss) = 0;
    int addRegistro(RegistroVariable* registro);
    RegistroVariable* getRegistro(int posicion);
    void setCantRegistros(int cantReg);
    int getCantRegistros();
    void anularRegistros(void);
    void vaciar(void);
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

