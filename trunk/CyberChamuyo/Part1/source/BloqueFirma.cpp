/*
 * BloqueFirma.cpp
 *
 *  Created on: Dec 4, 2012
 *      Author: lucasj
 */

#include "../include/BloqueFirma.h"

BloqueFirma::BloqueFirma(long tamanoBloque) {
	this->tamanoBloque = tamanoBloque;
    this->espacioLibre = tamanoBloque - 4;
    this->ocupado = false;
    this->reg = NULL;
}

BloqueFirma::~BloqueFirma() {
	this->borrarDatos();
}

void BloqueFirma::print(std::ostream& oss) {
	oss.write((char*) &(this->ocupado), sizeof(bool));
	oss << *this->reg;
}

// FUNCIONAMIENTO INPUT:
// Lee del archivo binario el valor de su siguiente.

void BloqueFirma::input(std::istream& oss) {
	oss.read((char*) &(this->ocupado), sizeof(bool));
	this->reg = new RegistroFirma;
	oss >> *this->reg;
}

// FUNCIONAMIENTO LLenarRegistros:
// Lee del archivo binario los registros y los carga al bloque.

void BloqueFirma::LlenarRegistros(std::istream& oss, int cantReg) {

}

// FUNCIONAMIENTO IMPRIMIR A TEXTO:
// Imprime en un archivo de texto el contenido de los datos
// y los registros.

void BloqueFirma::ImprimirATexto(std::ostream& oss) {
	//oss << "***********************" << std::endl;
	oss << "BLOQUE FIRMA: " << std::endl;
	if (this->ocupado) {
		oss << "OCUPADO:" << "\t"  << std::endl;
		this->reg->ImprimirATexto(oss);
	}
	else oss << "NO OCUPADO:" << "\t"  << std::endl;

}

// FUNCIONAMIENTO ADDREGISTRO:
// Agrega un registro a la estructura. En caso
// de no haber lugar devolverá error. En caso
// afirmativo lo agrega a la lista y modifica el
// espacio libre.

int BloqueFirma::addRegistro(RegistroFirma *registro){
	long espacioOcupado;
    espacioOcupado=(*registro).getTamanoDato();
    if(espacioOcupado <= this->espacioLibre) {
    	if(!this->ocupado) {
    		this->reg = registro;
    		this->setEspacioLibre(espacioOcupado);
    		this->ocupado = true;
    	} else {
    		return ERR_NO_MEMORIA;
    	}
    }
    return RES_OK;
}

// FUNCIONAMIENTO GET REGISTRO:
// Devuelve un registro variable dada la posición
// pasada por parámetro.

RegistroFirma* BloqueFirma::getRegistro(void){
    if (this->ocupado){
    	return(this->reg);
    }else{
        throw ExcepcionPosicionInvalidaEnBloque();
    }
}

void BloqueFirma::anularRegistros(void) {
	this->ocupado = false;
}

// FUNCIONAMIENTO BORRAR DATOS:
// Libera la memoria dinámica de los registros variables.

void BloqueFirma::borrarDatos(void) {
	if (this->reg != NULL)
		delete reg;
}

// FUNCIONAMIENTO BORRAR REGISTROS:
// Elimina un registro de un bloque dada la posición
// pasada como argumento. En caso afirmativo lo elimina
// en caso contrario devuelve error.

void BloqueFirma::borrarRegistro(unsigned int posicion) {
	if (this->ocupado){
        this->borrarDatos();
        this->ocupado = false;
	}else{
        throw ExcepcionPosicionInvalidaEnBloque();
    }
}

bool BloqueFirma::estaVacio(void) {
	return !this->ocupado;
}

// FUNCIONAMIENTO VACIAR:
// Vacia un bloque.

void BloqueFirma::vaciar(void) {
	this->espacioLibre = tamanoBloque;
	borrarDatos();
	anularRegistros();
}

long BloqueFirma::getEspacioLibre(){
    return (this->espacioLibre);
}

long BloqueFirma::getTamanoBloque(void){
    return (this->tamanoBloque);
}

void BloqueFirma::setEspacioLibre(long espacioOcupado){
    this->espacioLibre=(this->espacioLibre)-espacioOcupado;
}

int BloqueFirma::getCantRegistros() {
	if (this->ocupado)
		return 1;
	else return 0;
}

bool BloqueFirma::buscarRegistro(unsigned int clave, unsigned int& pos) {
	if (this->ocupado)
		return true;
	else return false;
}

void BloqueFirma::obtenerListaFrases(listaFrases& lista) {
	this->reg->obtenerListaFrases(lista);
}





