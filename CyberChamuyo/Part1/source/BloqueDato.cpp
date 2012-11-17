/*
 * BloqueDato.cpp
 *
 *  Created on: Sep 23, 2012
 *      Author: lucasj
 */

#include "../include/BloqueDato.h"

// FUNCIONAMIENTO CONSTRUCTOR DE BLOQUE DATO:
// LLama al constructor del bloque para setear los valores
// del padre y setea el td.

BloqueDato::BloqueDato(long tamanoBloque) {
	this->td = 0;
	this->tamanoBloque=tamanoBloque;
    this->espacioLibre=tamanoBloque;
}

// FUNCIONAMIENTO ADDREGISTRO:
// Agrega un registro a la estructura. En caso
// de no haber lugar devolverá error. En caso
// afirmativo lo agrega a la lista y modifica el
// espacio libre.

int BloqueDato::addRegistro(Hash::RegistroDato *registro){
    long espacioOcupado;
    espacioOcupado=(*registro).getTamanoDato();
    if(espacioOcupado<=espacioLibre){
        this->registros.push_back(registro);
        this->setEspacioLibre(espacioOcupado);
    }else{
        return ERR_NO_MEMORIA;
    }
    return RES_OK;
}

// FUNCIONAMIENTO GET REGISTRO:
// Devuelve un registro variable dada la posición
// pasada por parámetro.

Hash::RegistroDato* BloqueDato::getRegistro(unsigned int posicion){
    if ((posicion < this->registros.size()) && (posicion >= 0)){
        itRegDato iterador = this->registros.begin();
        for (unsigned int i = 0; i < posicion; i++){
            iterador ++;
        }
        return(*iterador);
    }else{
        throw ExcepcionPosicionInvalidaEnBloque();
    }
}


BloqueDato::~BloqueDato() {
	borrarDatos();
}

unsigned int BloqueDato::getTd(void) {
	return this->td;

}

void BloqueDato::setTd(unsigned int td) {
	this->td = td;
}

// FUNCIONAMIENTO PRINT:
// Escribe del archivo binario el valor de su td.

void BloqueDato::print(std::ostream& oss) {
	int cantReg = this->registros.size();
	oss.write((char*)&(cantReg), sizeof(int));
	oss.write((char*) (&(this->td)), sizeof(unsigned int));
	for (itRegDato it = this->registros.begin(); it != this->registros.end(); ++it) {
		oss << *(*it);
	}
}

void BloqueDato::getFrase(unsigned int clave, std::string& frase) {
	unsigned int posReg = 0;
	if (this->buscarRegistro(clave, posReg)) {
		Hash::RegistroDato* reg = this->getRegistro(posReg);
		reg->getFrase(frase);
	}

}

void BloqueDato::getAutor(unsigned int clave, std::string& autor) {
	unsigned int posReg = 0;
	if (this->buscarRegistro(clave, posReg)) {
		Hash::RegistroDato* reg = this->getRegistro(posReg);
		reg->getAutor(autor);
	}
}


bool BloqueDato::buscarRegistro(unsigned int clave, unsigned int& pos) {
	bool encontrado = false;
	itRegDato it = this->registros.begin();
	unsigned int i = 0;
	while ((it != this->registros.end())  && (encontrado == false)) {
		if (clave == (*it)->getClaveDato())
			encontrado = true;
		else {
			++it;
			++i;
		}
	}
	if (encontrado == true) {
		pos = i;
		return true;
	} else return false;
}

// FUNCIONAMIENTO INPUT:
// Lee del archivo binario el valor de su td.

void BloqueDato::input(std::istream& oss) {
	int cantReg = 0;
	oss.read((char*) (&cantReg), sizeof(int));
	oss.read((char*) (&(this->td)), sizeof(unsigned int));
	LlenarRegistros(oss, cantReg);
}

// FUNCIONAMIENTO LLenarRegistros:
// Lee del archivo binario los registros y los carga al bloque.

void BloqueDato::LlenarRegistros(std::istream& oss, int cantReg) {
	int it = 0;
	while (it < cantReg) {
		Hash::RegistroDato* nuevoRegistro = new Hash::RegistroDato;
		oss >> *nuevoRegistro;
		addRegistro(nuevoRegistro);
		++it;
	}
}

// FUNCIONAMIENTO IMPRIMIR A TEXTO:
// Imprime en un archivo de texto el contenido de los datos
// y los registros.

void BloqueDato::ImprimirATexto(std::ostream& oss) {
	//oss << "***********************" << std::endl;
	oss << "BLOQUE DATO: " << std::endl;
	oss << "TD:" << "\t" << this->td << std::endl;
	int cantReg = this->getCantRegistros();
	for (int i = 0; i < cantReg; ++i) {
		RegistroVariable* Registro = this->getRegistro(i);
		Registro->ImprimirATexto(oss);
	}
}

void BloqueDato::anularRegistros(void) {
	this->registros.clear();
}

// FUNCIONAMIENTO BORRAR DATOS:
// Libera la memoria dinámica de los registros variables.

void BloqueDato::borrarDatos(void) {
	itRegDato it;
	 for (it = this->registros.begin(); it != this->registros.end(); ++it) {
		 if (*it != NULL)
			 delete *it;
	 }
}

// FUNCIONAMIENTO BORRAR REGISTROS:
// Elimina un registro de un bloque dada la posición
// pasada como argumento. En caso afirmativo lo elimina
// en caso contrario devuelve error.

void BloqueDato::borrarRegistro(unsigned int posicion) {
	if ((posicion < this->registros.size()) && (posicion >= 0)){
        itRegDato iterador = registros.begin();
        for (unsigned int i = 0; i < posicion; i++){
            iterador ++;
        }
        delete *iterador;
        this->registros.erase(iterador);
	}else{
        throw ExcepcionPosicionInvalidaEnBloque();
    }
}

bool BloqueDato::estaVacio(void) {
	return this->registros.empty();
}

// FUNCIONAMIENTO VACIAR:
// Vacia un bloque.

void BloqueDato::vaciar(void) {
	this->espacioLibre = tamanoBloque;
	borrarDatos();
	anularRegistros();
}

long BloqueDato::getEspacioLibre(){

    return (this->espacioLibre);
}

long BloqueDato::getTamanoBloque(void){
    return (this->tamanoBloque);
}

void BloqueDato::setEspacioLibre(long espacioOcupado){
    this->espacioLibre=(this->espacioLibre)-espacioOcupado;
}

int BloqueDato::getCantRegistros(){
    return(this->registros.size());
}






