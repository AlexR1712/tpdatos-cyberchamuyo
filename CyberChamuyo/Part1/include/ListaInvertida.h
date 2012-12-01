/*
 * ListaInvertida.h
 *
 *  Created on: Nov 28, 2012
 *      Author: lucasj
 */

#ifndef LISTAINVERTIDA_H_
#define LISTAINVERTIDA_H_

#include <list>
#include <fstream>

typedef std::list<unsigned int> listInt;
typedef std::list<unsigned int>::iterator itListInt;

namespace invertedList {

class ListaInvertida {
private:
	unsigned int id;
	listInt lista;
public:
	ListaInvertida();
	virtual ~ListaInvertida();
	void insertar(unsigned int num);
	void Imprimir(std::ostream& oss);
	void serializar(std::ostream& oss);
	int getTamano();
	void setId(unsigned int docId);
	unsigned int getId(void);
	const listInt& getParticion(void) const;
	friend std::ostream& operator<<(std::ostream& oss,
					  ListaInvertida &l);
	friend std::istream& operator>>(std::istream& oss,
					 ListaInvertida &l);
	ListaInvertida& operator+=(const ListaInvertida &l);

};

std::ostream& operator<<(std::ostream& oss,
			ListaInvertida &l);
std::istream& operator>>(std::istream& oss,
			ListaInvertida &l);

}
#endif
