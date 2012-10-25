/*
 * IndiceArbol.h
 *
 *  Created on: 11/10/2012
 *      Author: sebastian
 */

#ifndef INDICEARBOL_H_
#define INDICEARBOL_H_

#include "ArbolBp.h"
#include <string>
#include "binaryInputSequentialFile.h"
#include "binaryDictionaryRecord.h"


#define LINUX

class IndiceArbol {
public:
	IndiceArbol();
	//IndiceArbol(BinaryInputSequentialFile<BinaryDictionaryRecord<false> >& f, const char* nombre_arch_arbol, int b_size);
	void createIndex(std::string path);
	bool find(const std::string& word);
	BinaryDictionaryRecord<true> next();
	bool hasNext();
	void insert(std::string& s);
	void exportar(const char* path);
	virtual ~IndiceArbol();
	void clear();
private:
	void crearIndice(std::ifstream& arch);
	ArbolBp arbol;
};

#endif /* INDICEARBOL_H_ */
