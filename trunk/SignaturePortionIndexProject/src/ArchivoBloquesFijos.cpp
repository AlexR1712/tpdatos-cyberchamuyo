/*
 * File:   Estruct.cpp
 * Author: emperor
 *
 * Created on 7 de abril de 2012, 20:30
 */

#include <iostream>
#include <fstream>
#include "ArchivoBloquesFijos.h"

ArchivoBloquesFijos::ArchivoBloquesFijos(const char* filename, long tamanoBloque){
    int it = 0;
    int bloqueLibre;
    path.open(filename, std::fstream::in|std::fstream::out|std::fstream::binary);
    if (!path){
        std:: fstream archivo (filename, std::fstream::out|std::fstream::binary);
        archivo.close();
        path.open(filename, std::fstream::in|std::fstream::out|std::fstream::binary);
        this->tamanoBloque=tamanoBloque;
        this->cantidadBloques=0;
        this->cantidadBloquesLibres=0;
    }else{ //probar
        path.seekg(0, std::ios::beg);
        path.read((char*)&(this->tamanoBloque),sizeof(long));
        path.read((char*)&cantidadBloques,sizeof(int));
        path.read((char*)&cantidadBloquesLibres,sizeof(int));
        while(it<cantidadBloquesLibres){
           path.read((char*)&bloqueLibre,sizeof(int));
            bloquesLibres.push_back(bloqueLibre);
            it++;
        }
    }
    this->dir = filename;
}

void ArchivoBloquesFijos::clear(void) {
	if(remove(this->dir.c_str()) != 0)
		throw ExcepcionDelete();
}

long ArchivoBloquesFijos::getTamanoBloque(){
    return (this->tamanoBloque);
}

int ArchivoBloquesFijos::getCantidadBloques(){
    return (this->cantidadBloques);
}

void ArchivoBloquesFijos::setCantidadBloques(int cantidadBloques){
    this->cantidadBloques = cantidadBloques;
}

int ArchivoBloquesFijos::getCantidadBloquesLibres(){
    return (this->cantidadBloquesLibres);
}

void ArchivoBloquesFijos::setCantidadBloquesLibres(int cantidad){
    this->cantidadBloquesLibres = cantidad;
}

unsigned int ArchivoBloquesFijos::ObtenerBloqueLibre(){
    unsigned int bloqueLibre;
    if (cantidadBloquesLibres>0){
        bloqueLibre =bloquesLibres.at(0);
        return (bloqueLibre);
    }else return ERR_BLOQUE_INEXISTENTE;
}

int ArchivoBloquesFijos::VerificarBloqueLibre(unsigned int bloque){
    int it = 0;
    int resultado = 0;
    while (it<cantidadBloquesLibres){
        if (bloquesLibres.at(it)==bloque){
            resultado=1;
            break;
        }
        it++;
    }
    return resultado;
}

void ArchivoBloquesFijos::SetearBloqueLibre(unsigned int bloque){
    int it = 0;
    std::vector<unsigned int>::iterator iterador = bloquesLibres.begin();
    while (it<cantidadBloquesLibres){
    	if (bloquesLibres.at(it)==bloque){
    		bloquesLibres.erase(iterador);
    		cantidadBloquesLibres--;
    		break;
    	}
    	it++;
    	iterador++;
    }
}

int ArchivoBloquesFijos::Escribir(Bloque* elemento, long posicion){
    if (posicion > (cantidadBloques)){
        return ERR_BLOQUE_INEXISTENTE;
    } else {
    	if (VerificarBloqueLibre(posicion))
    		SetearBloqueLibre(posicion);
    	if (posicion==cantidadBloques)
    		cantidadBloques++;
    	int corrimiento = (posicion + 1) * tamanoBloque * metadatasize;
    	path.seekp(corrimiento, std::ios::beg);
    	path << *elemento;
    }
   return RES_OK;
}

int ArchivoBloquesFijos::Leer(long posicion, Bloque* elemento){
    if (posicion >= cantidadBloques){
        return ERR_BLOQUE_INEXISTENTE;
    } else if (VerificarBloqueLibre(posicion)){
        return ERR_BLOQUE_LIBRE;
    } else {
    	long int corrimiento = (posicion + 1) * tamanoBloque * metadatasize;
    	path.seekg(corrimiento, std::ios::beg);
    	path >> *elemento;
    }
    return RES_OK;
}

void ArchivoBloquesFijos::Borrar(long posicion){
    if (posicion<cantidadBloques){
    	if (VerificarBloqueLibre(posicion)){
    		throw ExcepcionBloqueLibre();
    }else{
    	bloquesLibres.push_back(posicion);
    	cantidadBloquesLibres ++;
    }          
    }else{
        throw ExcepcionBloqueInexistente();
    }
}

ArchivoBloquesFijos::~ArchivoBloquesFijos(){
	int it = 0;
	int bloqueLibre;
	path.seekp(0, std::ios::beg);
	path.write((char*)&(this->tamanoBloque),sizeof(long));
	path.write((char*)&cantidadBloques,sizeof(int));
	path.write((char*)&cantidadBloquesLibres,sizeof(int));
	while(it<cantidadBloquesLibres){
		bloqueLibre = bloquesLibres.at(it);
		path.write((char*)&bloqueLibre,sizeof(int));
		it++;
	}
	path.close();
}

std::ostream& operator<<(std::ostream& oss, ArchivoBloquesFijos &arch) {
    oss << "***********************" << std::endl;
	oss << "ARCHIVO BLOQUES FIJOS: " << std::endl;
	oss << "***********************" << std::endl;
	oss << "TAMAÑO BLOQUE:" << "\t" << arch.tamanoBloque << std::endl;
	oss << "CANTIDAD DE BLOQUES:" << "\t" << arch.cantidadBloques << std::endl;
	oss << "CANTIDAD DE BLOQUES LIBRES:" << "\t" << arch.cantidadBloquesLibres << std::endl;
	return oss;
}



