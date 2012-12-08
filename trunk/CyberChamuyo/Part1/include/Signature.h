/*
 * Signature.h
 *
 *  Created on: Dec 4, 2012
 *      Author: lucasj
 */

#ifndef SIGNATURE_H_
#define SIGNATURE_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <list>

typedef std::list<unsigned int> listaFrases;

namespace Signature {

typedef std::vector<unsigned char> MapaBytes;
typedef std::vector<unsigned char>::iterator itMapa;

class Signature {
private:
	unsigned int nTermino;
	MapaBytes map;
	void completarMapa(unsigned int numByte);
	void convertirABit(std::ostream& oss, unsigned char valor, unsigned int* i);
	void convertirABit(listaFrases& list, unsigned char valor, unsigned int* i);
public:
	Signature(unsigned int nTermino);
	Signature(void);
	void obtenerListaFrases(listaFrases& lista);
	void setBit(unsigned int nFrase);
	void eliminarBit(unsigned int nFrase);
	void Imprimir(std::ostream& oss);
	unsigned int getTamano(void);
	void serializar(std::ostream& oss);
	unsigned int getClaveDato(void);
	void setClaveDato(unsigned int clave);
	virtual ~Signature();
	friend std::ostream& operator<<(std::ostream& oss,
					  Signature &s);
	friend std::istream& operator>>(std::istream& oss,
					  Signature &s);
};

	std::ostream& operator<<(std::ostream& oss, Signature &s);
	std::istream& operator>>(std::istream& oss, Signature &s);

}
#endif
