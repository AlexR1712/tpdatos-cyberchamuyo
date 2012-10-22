/*
 * ArrayBytes.h
 *
 *  Created on: Oct 6, 2012
 *      Author: lucasj
 */

#ifndef ARRAYBYTES_H_
#define ARRAYBYTES_H_

#include <vector>
#include <fstream>
#include <iostream>

typedef std::vector<unsigned int> array;
typedef std::vector<unsigned int>::iterator itArray;

// ARRAY BYTES: Clase que contiene particiones de la tabla de dispersión.
//

// ATRIBUTOS ArrayBytes
//
// ARREGLO: vector de unsigned int. que contiene una partición de
// la tabla de dispersión.
//

namespace Data {

class ArrayBytes {
private:
	array arreglo;
public:
	ArrayBytes();
	void insertar(unsigned int num);
	void Imprimir(std::ostream& oss);
	void serializar(std::ostream& oss);
	void concatenar(array& vec);
	virtual ~ArrayBytes();
	int getTamano();
	friend std::ostream& operator<<(std::ostream& oss,
					  ArrayBytes &a);
	friend std::istream& operator>>(std::istream& oss,
					 ArrayBytes &a);
};

std::ostream& operator<<(std::ostream& oss,
					  ArrayBytes &a);
std::istream& operator>>(std::istream& oss,
					  ArrayBytes &a);

}
#endif
