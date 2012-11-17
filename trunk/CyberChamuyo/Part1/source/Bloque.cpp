/*
 * File: Bloque.cpp
 *
 */

#include <list>
#include <iostream>

#include "../include/Bloque.h"

// FUNCIONAMIENTO CONSTRUCTOR DE BLOQUE:
// Setea los valores iniciales del bloque.
// La cantidad de espacio libre es el tamaño del
// bloque.

Bloque::Bloque(void){

 }



Bloque::~Bloque(){

}

// FUNCIONAMIENTO OPERATOR<<:
// Serializa al archivo binario la metadata del bloque
// como la información de sus registros.

std::ostream& operator<<(std::ostream& oss,	Bloque &bl) {
	bl.print(oss);
	return oss;
}

// FUNCIONAMIENTO OPERATOR>>:
// Lee y carga del archivo binario la metadata del bloque
// como la información de sus registros.

std::istream& operator>>(std::istream& oss, Bloque &bl) {
	bl.input(oss);
	return oss;
}

