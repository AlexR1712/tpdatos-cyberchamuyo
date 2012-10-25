/* 
 * File:   Bloque.h
 * Author: emperor
 *
 * Created on 6 de abril de 2012, 19:30
 */

#ifndef BLOQUE_H
#define	BLOQUE_H

#include "RegistroVariable.h"
#include <list>
#include <stdexcept>
#include <vector>
using std::runtime_error;



class Bloque
{
private:
    long tamanoBloque;
    std::list <RegistroVariable*> registros;
    long espacioLibre;
    int cantRegistros;

    void setEspacioLibre(long espacioOcupado);
public:
    Bloque(long tamanoBloque);
    Bloque(long tamanoBloque, std::vector<char>* data, int data_size);
    long getTamanoBloque();
    long getEspacioLibre();
    void addRegistro(RegistroVariable* registro);
    RegistroVariable* getRegistro(int posicion);
    void setCantRegistros(int cantReg);
    int getCantRegistros();
    virtual ~Bloque();
};


class ExcepcionNoHayMemoriaEnBloque : public runtime_error
{
public:
    ExcepcionNoHayMemoriaEnBloque()
            : runtime_error("El elemento no entra en el bloque") {}
};


class ExcepcionPosicionInvalidaEnBloque : public runtime_error
{
public:
    ExcepcionPosicionInvalidaEnBloque()
            : runtime_error("No existe un elemento con esa posicion en el bloque") {}
};


#endif	/* BLOQUE_H */

