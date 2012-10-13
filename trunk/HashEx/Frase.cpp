/*
 * Frase.cpp
 *
 *  Created on: Sep 20, 2012
 *      Author: lucasj
 */

#include "Frase.h"

namespace Data {

Frase::Frase(std::string& author, std::string& phrase, unsigned long int m):autor(author), frase(phrase) {
	this->n = m;
}


std::string* Frase::Deshidratar(void) {
	std::ostringstream buffer;
	buffer << *this;
	std::string* dato = new std::string(buffer.str().c_str());
	return dato;
}


Frase::Frase(void):autor(""), frase("") {
	this->n = 0;

}

int Frase::getTamano() {
	return (this->autor.length() + this->frase.length() + sizeof(this->n));
}

unsigned long int Frase::getClave(void) {
	return this->n;
}

Frase::~Frase() {
}

void Frase::Imprimir(std::ostream& oss) {
	//oss << "***********************" << std::endl;
	oss << "Nº ALEATORIO: " << std::endl;
	oss << "\t" << this->n << std::endl;
	oss << "AUTOR: " << std::endl;
	oss << "\t" << this->autor << std::endl;
	oss << "FRASE: " << std::endl;
	oss << "\t" << this->frase << std::endl;
	oss << std::endl;
	//oss << "***********************" << std::endl;
}

std::ostream& operator<<(std::ostream& oss, Frase &phrase) {
	oss.write((char*)&phrase.n, sizeof(phrase.n));
	int N = phrase.autor.length();
	int M = phrase.frase.length();
	oss.write((char*)&(N), sizeof(char));
	oss.write(phrase.autor.c_str(), phrase.autor.length());
	oss.write((char*)&(M), sizeof(int));
	oss.write(phrase.frase.c_str(), phrase.frase.length());
	return oss;
}

std::istream& operator>>(std::istream& oss, Frase &phrase) {
	int tamanoAutor = 0;
	int tamanoFrase = 0;
	oss.read((char*) ((&phrase.n)), sizeof(unsigned long int));
	oss.read((char*) ((&tamanoAutor)), sizeof(char));
	char* author = new char [tamanoAutor + 1];
	oss.read(author, tamanoAutor);
	author[tamanoAutor] = 0;
	oss.read((char*) ((&tamanoFrase)), sizeof(int));
	char* phhrase = new char [tamanoFrase + 1];
	oss.read(phhrase, tamanoFrase);
	phhrase[tamanoFrase] = 0;
	phrase.autor = author;
	phrase.frase = phhrase;
	delete [] author;
	delete [] phhrase;
	return oss;
}

}
