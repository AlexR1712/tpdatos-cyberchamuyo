/*
 * Frase.h
 *
 *  Created on: Sep 20, 2012
 *      Author: lucasj
 */

#ifndef FRASE_H_
#define FRASE_H_

#include <iostream>
#include "../include/_Aux.h"

// FRASE: Clase que contiene los datos de una frase.

// ATRIBUTOS FRASE:
//
// N: Número aleatorio de la frase.
//
// AUTOR: Autor de la frase.
//
// FRASE: Frase.

namespace Data {

class Frase {
private:
	unsigned long int n;
	std::string autor;
	std::string frase;
public:
	Frase(std::string& author, std::string& phrase, unsigned long int m);
	void Imprimir(std::ostream& oss);
	Frase(void);
	unsigned long int getClave(void);
	std::string* Deshidratar(void);
	void serializar(std::ostream& oss);
	std::string& getFrase(void);
	std::string& getAutor(void);
	int getTamano();
	virtual ~Frase();
	friend std::ostream& operator<<(std::ostream& oss,
					  Frase &phrase);
	friend std::istream& operator>>(std::istream& oss,
					  Frase &phrase);
};

std::ostream& operator<<(std::ostream& oss, Frase &phrase);
std::istream& operator>>(std::istream& oss, Frase &phrase);

}
#endif
