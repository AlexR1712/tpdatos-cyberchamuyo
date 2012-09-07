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
        path.seekg(0);
        path.read((char*)&(this->tamanoBloque),sizeof(long));
        path.read((char*)&cantidadBloques,sizeof(int));
        path.read((char*)&cantidadBloquesLibres,sizeof(int));
        while(it<cantidadBloquesLibres){
            path.read((char*)&bloqueLibre,sizeof(int));
            bloquesLibres.push_back(bloqueLibre);
            it++;
        }
    }
}

long ArchivoBloquesFijos::getTamanoBloque(){

    return (this->tamanoBloque);
}

int ArchivoBloquesFijos::getCantidadBloques(){

    return (this->cantidadBloques);
}

void ArchivoBloquesFijos::setCantidadBloques(int cantidadBloques){

    this->cantidadBloques=cantidadBloques;
}

int ArchivoBloquesFijos::getCantidadBloquesLibres(){

    return (this->cantidadBloquesLibres);
}

void ArchivoBloquesFijos::setCantidadBloquesLibres(int cantidad){

    this->cantidadBloquesLibres=cantidad;
}

int ArchivoBloquesFijos::ObtenerBloqueLibre(){

    int bloqueLibre;
    if (cantidadBloquesLibres>0){
        bloqueLibre =bloquesLibres.at(0);
        return (bloqueLibre);
    }else{
        return -1;
    	//cantidadBloques++;
    	//return getCantidadBloques();
    }
}

int ArchivoBloquesFijos::VerificarBloqueLibre(int bloque){

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

void ArchivoBloquesFijos::SetearBloqueLibre(int bloque){

    int it = 0;
    std::vector<int>::iterator iterador = bloquesLibres.begin();
    while (it<cantidadBloquesLibres){
        if (bloquesLibres.at(it)==bloque){
            bloquesLibres.erase(iterador);
            break;
        }
        it++;
        iterador++;
    }
}

void ArchivoBloquesFijos::Escribir(Bloque* elemento, long posicion){

    int cantRegistros = (*elemento).getCantRegistros();
    int it = 0;
    RegistroVariable* regInsertar;
    long tamanoDato;
    string* datoInsertar;
    if (posicion > (cantidadBloques)){
        throw ExcepcionBloqueInexistente();
    }
    if (VerificarBloqueLibre(posicion)){
        SetearBloqueLibre(posicion);
    }
    if (posicion==cantidadBloques){
        cantidadBloques++;
    }
    int corrimiento = (posicion+1)*tamanoBloque*metadatasize;
    path.seekp(corrimiento);
    path.write((char*)&cantRegistros,sizeof(int));
    while (it<cantRegistros){
        regInsertar = (*elemento).getRegistro(it);
        tamanoDato = (*regInsertar).getTamanoDato();
        path.write((char*)&tamanoDato,sizeof(long));
        datoInsertar=(*regInsertar).getDato();
        path.write((*datoInsertar).data(),tamanoDato);
        it++;
    }
}

void ArchivoBloquesFijos::Leer(long posicion, Bloque* elemento){

    int cantRegistros;
    int it = 0;
    long tamanoDato;
    char* dato;
    string* nuevoDato;
    RegistroVariable* nuevoRegistro;
    if (posicion >= cantidadBloques){
        throw ExcepcionBloqueInexistente();
    }
    if (VerificarBloqueLibre(posicion)){
        throw ExcepcionBloqueLibre();
    }
    int corrimiento = (posicion+1)*tamanoBloque*metadatasize;
    path.seekg(corrimiento);
    path.read((char*)&cantRegistros,sizeof(int));
    while (it<cantRegistros){
        path.read((char*)&tamanoDato,sizeof(long));
        dato = new char[tamanoDato];
        path.read(dato,tamanoDato);
        nuevoDato = new string(dato);
        nuevoRegistro = new RegistroVariable(nuevoDato,tamanoDato);
        (*elemento).addRegistro(nuevoRegistro);
        it++;
        delete[] dato;
    }
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
        path.seekp(0);
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
