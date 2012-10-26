/*
 * DatoNodo.h
 *
 *  Created on: Oct 17, 2012
 *      Author: lucasj
 */

#ifndef DATONODO_H_
#define DATONODO_H_

#include <string>
#include <iostream>
#include <vector>

typedef std::vector<char> vectorChar;
typedef std::vector<char>::iterator itVChar;

class DatoNodo {
private:
	vectorChar* cadena;
public:
	DatoNodo(vectorChar* cadena);
	DatoNodo(void);
	void Imprimir(std::ostream& oss);
	void serializar(std::ostream& oss);
	virtual ~DatoNodo();
	int getTamano();
	friend std::ostream& operator<<(std::ostream& oss,
					  DatoNodo &n);
	friend std::istream& operator>>(std::istream& oss,
					 DatoNodo &n);
};

std::ostream& operator<<(std::ostream& oss, DatoNodo &n);
std::istream& operator>>(std::istream& oss, DatoNodo &n);

#endif
