/*
 * BloqueTabla.cpp
 *
 *  Created on: Sep 23, 2012
 *      Author: lucasj
 */

#include "../include/BloqueTabla.h"


// FUNCIONAMIENTO CONSTRUCTOR DE BLOQUE TABLA:
// LLama al constructor del bloque para setear los valores
// del padre y setea el siguiente.

BloqueTabla::BloqueTabla(long tamanoBloque) {
	this->siguiente = 0;
	this->tamanoBloque=tamanoBloque;
    this->espacioLibre=tamanoBloque;
}


BloqueTabla::~BloqueTabla() {
	this->borrarDatos();
}

unsigned int BloqueTabla::getSiguiente(void) {
	return this->siguiente;

}

void BloqueTabla::setSiguiente(unsigned int siguiente) {
	this->siguiente = siguiente;
}

// FUNCIONAMIENTO PRINT:
// Escribe del archivo binario el valor de su siguiente.

void BloqueTabla::print(std::ostream& oss) {
	int cantReg = this->registros.size();
	oss.write((char*)&(cantReg), sizeof(int));
	oss.write((char*)&(this->siguiente), sizeof(unsigned int));
	for (itRegTabla it = this->registros.begin(); it != this->registros.end();
			++it) {
		oss << *(*it);
	}
}

// FUNCIONAMIENTO INPUT:
// Lee del archivo binario el valor de su siguiente.

void BloqueTabla::input(std::istream& oss) {
	int cantReg = 0;
	oss.read((char*) (&cantReg), sizeof(int));
	oss.read((char*) &(this->siguiente), sizeof(unsigned int));
	LlenarRegistros(oss, cantReg);
}

// FUNCIONAMIENTO LLenarRegistros:
// Lee del archivo binario los registros y los carga al bloque.

void BloqueTabla::LlenarRegistros(std::istream& oss, int cantReg) {
	int it = 0;
	while (it < cantReg) {
		Hash::RegistroTabla* nuevoRegistro = new Hash::RegistroTabla;
		oss >> *nuevoRegistro;
		addRegistro(nuevoRegistro);
		++it;
	}
}

// FUNCIONAMIENTO IMPRIMIR A TEXTO:
// Imprime en un archivo de texto el contenido de los datos
// y los registros.

void BloqueTabla::ImprimirATexto(std::ostream& oss) {
	//oss << "***********************" << std::endl;
	oss << "BLOQUE TABLA: " << std::endl;
	oss << "SIGUIENTE: " << "\t" << this->siguiente << std::endl;
	int cantReg = this->getCantRegistros();
	for (int i = 0; i < cantReg; ++i) {
		RegistroVariable* Registro = this->getRegistro(i);
		Registro->ImprimirATexto(oss);
	}
}

// FUNCIONAMIENTO ADDREGISTRO:
// Agrega un registro a la estructura. En caso
// de no haber lugar devolverá error. En caso
// afirmativo lo agrega a la lista y modifica el
// espacio libre.

int BloqueTabla::addRegistro(Hash::RegistroTabla *registro){
    long espacioOcupado;
    espacioOcupado=(*registro).getTamanoDato();
    if(espacioOcupado <= this->espacioLibre){
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

Hash::RegistroTabla* BloqueTabla::getRegistro(unsigned int posicion){
    if ((posicion < this->registros.size()) && (posicion >= 0)){
        itRegTabla iterador = this->registros.begin();
        for (unsigned int i = 0; i < posicion; i++){
            iterador ++;
        }
        return(*iterador);
    }else{
        throw ExcepcionPosicionInvalidaEnBloque();
    }
}

void BloqueTabla::anularRegistros(void) {
	this->registros.clear();
}

// FUNCIONAMIENTO BORRAR DATOS:
// Libera la memoria dinámica de los registros variables.

void BloqueTabla::borrarDatos(void) {
	itRegTabla it;
	 for (it = this->registros.begin(); it != this->registros.end(); ++it) {
		 if (*it != NULL)
			 delete *it;
	 }
}

// FUNCIONAMIENTO BORRAR REGISTROS:
// Elimina un registro de un bloque dada la posición
// pasada como argumento. En caso afirmativo lo elimina
// en caso contrario devuelve error.

void BloqueTabla::borrarRegistro(unsigned int posicion) {
	if ((posicion < this->registros.size()) && (posicion >= 0)){
        itRegTabla iterador = registros.begin();
        for (unsigned int i = 0; i < posicion; i++){
            iterador ++;
        }
        delete *iterador;
        this->registros.erase(iterador);
	}else{
        throw ExcepcionPosicionInvalidaEnBloque();
    }
}

bool BloqueTabla::estaVacio(void) {
	return this->registros.empty();
}

// FUNCIONAMIENTO VACIAR:
// Vacia un bloque.

void BloqueTabla::vaciar(void) {
	this->espacioLibre = tamanoBloque;
	borrarDatos();
	anularRegistros();
}

long BloqueTabla::getEspacioLibre(){
    return (this->espacioLibre);
}

long BloqueTabla::getTamanoBloque(void){
    return (this->tamanoBloque);
}

void BloqueTabla::setEspacioLibre(long espacioOcupado){
    this->espacioLibre=(this->espacioLibre)-espacioOcupado;
}

int BloqueTabla::getCantRegistros(){
    return(this->registros.size());
}

bool BloqueTabla::buscarRegistro(unsigned int clave, unsigned int& pos) {
	bool encontrado = false;
	itRegTabla it = this->registros.begin();
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

void BloqueTabla::cargarTabla(array& vec) {
	Hash::RegistroTabla* reg = this->getRegistro(0);
	reg->cargarTabla(vec);
}




