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

/*	IndiceArbol: Clase que se utiliza como una capa externa al arbol para ofrecer
 * 	cierta funcionalidad
 */

#define LINUX

class IndiceArbol {
public:
	//  crea un arbol vacio en el archivo con nombre file_name
	IndiceArbol(std::string file_name);

	//  inicializa el arbol. Carga cada linea del archivo con nombre "path" y
	//  las inserta en el arbol
	void createIndex(std::string path);

	//  devuelve 1 si la palabra "word" esta en el arbol, 0 sino
	bool find(std::string word);

	//  devuelve siguiente registro del arbol
	BinaryDictionaryRecord<true> next();

	// 1 si tiene siguiente, 0 sino (leer siguiente() en Arbol)
	bool hasNext();

	//  inserta la palabra "s" en el arbol
	void insert(std::string& s);

	//  devuelve un archivo con todos registros del arbol
	//  leer exportar(std::string) en arbol
	void exportar(const char* path);
	virtual ~IndiceArbol();

	//  borra el arbol
	void clear();

	// wrapper de rewind() de arbol
	void rewind();

	//  1 si esta vacio, 0 sino
	bool isEmpty();

	void mostrar();
private:
	void crearIndice(std::ifstream& arch);
	ArbolBp arbol;
};

#endif /* INDICEARBOL_H_ */
