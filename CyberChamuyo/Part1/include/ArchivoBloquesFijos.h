/* 
 * File:   ArchivoBloquesFijos.h
 *
 */

#ifndef ARCHIVOBLOQUESFIJOS_H
#define	ARCHIVOBLOQUESFIJOS_H
#include "Bloque.h"
#include "ArchivoDispErr.h"
#include "Bitmap.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

// ARCHIVO BLOQUES FIJOS: Clase que administra el archivo binario
// que posee bloques con registros variables. Determina la inserción
// de un bloque como así los bloques libres que vayan quedando luego
// de operaciones de borrado.

// ATRIBUTOS ArchivoBloquesFijos:
//
// PATH: El file descriptor del archivo de bloques.
//
// CANTIDADBLOQUES: Cantidad de bloques del archivo.
//
// TAMANOBLOQUE: El tamaño del bloque.
//
// BLOQUESLIBRES: Vector que contiene el número de bloque libre.
//
// CANTIDADBLOQUESLIBRES: Cantidad de bloques Libres.
//
// DIR: Path del file descriptor.
//

class ArchivoBloquesFijos {
private:
    std::fstream path;
    long tamanoBloque;
    std::string dir;
    Bitmap map;
    unsigned int autoId;
    void SetearBloqueLibre (unsigned int bloque);
public:
    ArchivoBloquesFijos (const char* filename, long tamanoBloque);
    int getCantidadBloques(void);
    long getTamanoBloque(void);
    int getCantidadBloquesLibres(void);
    unsigned int ObtenerBloqueLibre(void);
    int Escribir (Bloque* elemento, unsigned int posicion);
    int Leer (unsigned int posicion, Bloque* elemento);
    void Borrar (long posicion);
    virtual ~ArchivoBloquesFijos();
    int VerificarBloqueLibre(unsigned int bloque);
    unsigned int getNuevoId(void);
    unsigned int getId();
    void clear(void);
    void insertarBit(unsigned int byte, unsigned int offset, unsigned int corr);
    void borrarBit(unsigned int byte, unsigned int offset, unsigned int corr);
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

class ExcepcionDelete : public std::exception
{
public:
	virtual const char* what() const throw() {
		return "Error al Borrar Archivo";
	}
};

#endif	/* ARCHIVOBLOQUESFIJOS_H */

