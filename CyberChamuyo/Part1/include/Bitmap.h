/*
 * Bitmap.h
 *
 *  Created on: Nov 15, 2012
 *      Author: lucasj
 */

#ifndef BITMAP_H_
#define BITMAP_H_

#include <vector>
#include <list>
#include <iostream>
#include "ArchivoDispErr.h"

typedef std::vector<unsigned char> Mapa;
typedef std::vector<unsigned char>::iterator itMapa;
typedef std::list<unsigned int>::iterator itLista;

class Bitmap {
private:
	std::list<unsigned int> listaBl;
	unsigned int bloqueTope;
	void completarMapa(unsigned int numByte, Mapa& map);
	void serializar(Mapa& map);
	void setBit(unsigned int bloque, Mapa& map);
	void eliminarBloqueLista(unsigned int bloque);
	void llenarListaBloques(unsigned char valor, unsigned int i);
public:
	Bitmap(void);
	Bitmap(unsigned int bloqueInicial);
	void setBloqueLibre(unsigned int bloque);
	void setBloqueOcupado(unsigned int bloque);
	unsigned int getCantidadBloquesLibres(void);
	unsigned int getBloqueLibre(void);
	unsigned int getCantidadBloques(void);
	bool agregarBloque(unsigned int posicion);
	int verificarBloqueOcupado(unsigned int posicion);
	virtual ~Bitmap();
	bool verificarBloqueLibre(unsigned int bloque);
	void ImprimirATexto(std::ostream& oss);
	friend std::ostream& operator<<(std::ostream& oss,
					  Bitmap &bm);
	friend std::istream& operator>>(std::istream& oss,
					  Bitmap &bm);
};

#endif
