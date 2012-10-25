/* 
 * File:   ArchivoBloquesFijos.h
 * Author: emperor
 *
 * Created on 6 de abril de 2012, 19:23
 */

#ifndef ARCHIVOBLOQUESFIJOS_H
#define	ARCHIVOBLOQUESFIJOS_H
#include "Bloque.h"
#include "fstream"
#include <vector>
#define metadatasize 1.5;

class ArchivoBloquesFijos
{
private:
    std::fstream path;
    int cantidadBloques;
    long tamanoBloque;
    std::vector <int> bloquesLibres;
    int cantidadBloquesLibres;
    std::string pathString;

    void setCantidadBloques(int cantidadBloques);
    void setCantidadBloquesLibres (int cantidad);
    int VerificarBloqueLibre(int bloque);
    void SetearBloqueLibre (int bloque);
public:
    ArchivoBloquesFijos (const char* filename, long tamanoBloque);
    int getCantidadBloques();
    long getTamanoBloque();
    int getCantidadBloquesLibres();
    int ObtenerBloqueLibre ();
    void Escribir (Bloque* elemento, long posicion);
    void Leer (long posicion, Bloque* elemento);
    void Borrar (long posicion);
    void Clear();
    virtual ~ArchivoBloquesFijos();
};


class ExcepcionBloqueInexistente : public runtime_error
{
public:
    ExcepcionBloqueInexistente()
            : runtime_error("El bloque indicado no existe") {}
};


class ExcepcionBloqueLibre : public runtime_error
{
public:
    ExcepcionBloqueLibre()
            : runtime_error("El bloque indicado esta libre") {}
};



#endif	/* ARCHIVOBLOQUESFIJOS_H */

