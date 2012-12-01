/*
 * MapaDeTerminos.h
 *
 *  Created on: 21/11/2012
 *      Author: sebastian
 */

#ifndef MAPADETERMINOS_H_
#define MAPADETERMINOS_H_

#include <set>
#include <vector>
#include "../include/BinaryArray.h"
#include <string>
#include "../include/IndiceArbol.h"

class MapaDeTerminos {
public:
	MapaDeTerminos(long termCount);
	virtual ~MapaDeTerminos();
private:
	IndiceArbol* lex;
	long termCount;
	long docCount;
	std::string path;
	std::fstream map_file;
};

#endif /* MAPADETERMINOS_H_ */
