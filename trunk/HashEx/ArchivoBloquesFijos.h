/* 
 * File:   ArchivoBloquesFijos.h
 * Author: emperor
 *
 * Created on 6 de abril de 2012, 19:23
 */

#ifndef ARCHIVOBLOQUESFIJOS_H
#define	ARCHIVOBLOQUESFIJOS_H
#include "Bloque.h"
#include "ArchivoDispErr.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

class ArchivoBloquesFijos {
private:
    std::fstream path;
    int cantidadBloques;
    long tamanoBloque;
    std::vector <unsigned int> bloquesLibres;
    int cantidadBloquesLibres;
    void setCantidadBloques(int cantidadBloques);
    void setCantidadBloquesLibres (int cantidad);
    void SetearBloqueLibre (unsigned int bloque);
public:
    ArchivoBloquesFijos (const char* filename, long tamanoBloque);
    int getCantidadBloques();
    long getTamanoBloque();
    int getCantidadBloquesLibres();
    unsigned int ObtenerBloqueLibre ();
    int Escribir (Bloque* elemento, long posicion);
    int Leer (long posicion, Bloque* elemento);
    void Borrar (long posicion);
    virtual ~ArchivoBloquesFijos();
    int VerificarBloqueLibre(unsigned int bloque);
    friend std::ostream& operator<<(std::ostream& oss,
					  ArchivoBloquesFijos &arch);
};

std::ostream& operator<<(std::ostream& oss, ArchivoBloquesFijos &Arch);

class ExcepcionBloqueInexistente : public std::exception
{
public:
    virtual const char* what() const throw() {
		return "Error Bloque Inexistente";
	}
};

class ExcepcionBloqueLibre : public std::exception
{
public:
	virtual const char* what() const throw() {
		return "Error Bloque Libre";
	}
};

#endif	/* ARCHIVOBLOQUESFIJOS_H */

